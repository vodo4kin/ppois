#include "Warehouse.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "utils/Utils.hpp"
#include <algorithm>

bool Warehouse::isValidName(const std::string& name) const {
    return StringValidation::isValidName(name, WarehouseConfig::Warehouse::MAX_NAME_LENGTH);
}

bool Warehouse::isValidAddress(const std::string& address) const {
    return !address.empty() && address.length() <= 200; // Reasonable address length
}

Warehouse::Warehouse(const std::string& name, const std::string& address) {
    if (!isValidName(name)) {
        throw DataValidationException("Invalid warehouse name: " + name);
    }
    if (!isValidAddress(address)) {
        throw DataValidationException("Invalid warehouse address: " + address);
    }
    this->name = name;
    this->address = address;
}

void Warehouse::cleanupZeroQuantityItems() {
    inventory.erase(
        std::remove_if(inventory.begin(), inventory.end(),
            [](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getQuantity() == 0;
            }),
        inventory.end()
    );
}

void Warehouse::processStockMovement(std::shared_ptr<StockMovement> movement) {
    if (!movement) {
        throw DataValidationException("Cannot process null stock movement");
    }
    try {
        movement->execute();
        cleanupZeroQuantityItems(); // Clean up after movement
    } catch (const std::exception& e) {
        throw WarehouseException("Failed to process stock movement: " + std::string(e.what()));
    }
}

std::string Warehouse::getName() const noexcept {
    return name;
}

std::string Warehouse::getAddress() const noexcept {
    return address;
}

std::vector<std::shared_ptr<WarehouseSection>> Warehouse::getSections() const noexcept {
    return sections;
}

int Warehouse::getSectionsCount() const noexcept {
    return sections.size();
}

void Warehouse::addSection(std::shared_ptr<WarehouseSection> section) {
    if (!section) {
        throw DataValidationException("Cannot add null section to warehouse");
    }
    if (containsSection(section->getSectionId())) {
        throw DataValidationException("Section " + section->getSectionId() + " already exists in warehouse");
    }
    if (sections.size() >= WarehouseConfig::Warehouse::MAX_SECTIONS) {
        throw WarehouseException("Warehouse cannot have more than " + 
                               std::to_string(WarehouseConfig::Warehouse::MAX_SECTIONS) + " sections");
    }
    sections.push_back(section);
}

void Warehouse::removeSection(const std::string& sectionId) {
    auto it = std::find_if(sections.begin(), sections.end(),
        [&sectionId](const std::shared_ptr<WarehouseSection>& section) {
            return section->getSectionId() == sectionId;
        });
    if (it != sections.end()) {
        sections.erase(it);
    }
}

std::shared_ptr<WarehouseSection> Warehouse::findSection(const std::string& sectionId) const noexcept {
    auto it = std::find_if(sections.begin(), sections.end(),
        [&sectionId](const std::shared_ptr<WarehouseSection>& section) {
            return section->getSectionId() == sectionId;
        });
    return (it != sections.end()) ? *it : nullptr;
}

bool Warehouse::containsSection(const std::string& sectionId) const noexcept {
    return findSection(sectionId) != nullptr;
}

void Warehouse::addInventoryItem(std::shared_ptr<InventoryItem> inventoryItem) {
    if (!inventoryItem) {
        throw DataValidationException("Cannot add null inventory item to warehouse");
    }
    
    auto location = inventoryItem->getLocation();
    if (!location) {
        throw DataValidationException("Inventory item has no valid location");
    }
    location->addBooks(inventoryItem->getQuantity());
    
    auto existing = findInventoryItem(
        inventoryItem->getBook()->getISBN().getCode(),
        location->getLocationId()
    );
    if (existing) {
        location->removeBooks(inventoryItem->getQuantity());
        throw DataValidationException("Inventory item already exists for book " + 
                                    inventoryItem->getBook()->getISBN().getCode() + 
                                    " at location " + location->getLocationId());
    }
    inventory.push_back(inventoryItem);
}

void Warehouse::removeInventoryItem(const std::string& bookIsbn, const std::string& locationId) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&bookIsbn, &locationId](const std::shared_ptr<InventoryItem>& item) {
            return item->getBook()->getISBN().getCode() == bookIsbn &&
                   item->getLocation()->getLocationId() == locationId;
        });
    if (it != inventory.end()) {
        auto location = (*it)->getLocation();
        if (location) {
            location->removeBooks((*it)->getQuantity());
        }
        inventory.erase(it);
    }
}

std::vector<std::shared_ptr<InventoryItem>> Warehouse::findInventoryByBook(const std::string& bookIsbn) const noexcept {
    std::vector<std::shared_ptr<InventoryItem>> result;
    for (const auto& item : inventory) {
        if (item->getBook()->getISBN().getCode() == bookIsbn) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<std::shared_ptr<InventoryItem>> Warehouse::findInventoryByBook(std::shared_ptr<Book> book) const noexcept {
    if (!book) return {};
    return findInventoryByBook(book->getISBN().getCode());
}

std::shared_ptr<InventoryItem> Warehouse::findInventoryItem(const std::string& bookIsbn, const std::string& locationId) const noexcept {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&bookIsbn, &locationId](const std::shared_ptr<InventoryItem>& item) {
            return item->getBook()->getISBN().getCode() == bookIsbn &&
                   item->getLocation()->getLocationId() == locationId;
        });
    return (it != inventory.end()) ? *it : nullptr;
}

int Warehouse::getBookTotalQuantity(const std::string& bookIsbn) const noexcept {
    int total = 0;
    for (const auto& item : inventory) {
        if (item->getBook()->getISBN().getCode() == bookIsbn) {
            total += item->getQuantity();
        }
    }
    return total;
}

bool Warehouse::isBookInStock(const std::string& bookIsbn) const noexcept {
    return getBookTotalQuantity(bookIsbn) > 0;
}

std::vector<std::shared_ptr<StorageLocation>> Warehouse::findAvailableLocations() const noexcept {
    std::vector<std::shared_ptr<StorageLocation>> availableLocations;
    for (const auto& section : sections) {
        auto sectionAvailable = section->findAvailableLocations();
        availableLocations.insert(availableLocations.end(), sectionAvailable.begin(), sectionAvailable.end());
    }
    return availableLocations;
}

std::shared_ptr<StorageLocation> Warehouse::findOptimalLocation(int quantity, WarehouseSection::SectionType preferredSectionType) const noexcept {
    for (const auto& section : sections) {
        if (section->getSectionType() != preferredSectionType) {
            continue;
        }
        auto availableLocations = section->findAvailableLocations();
        for (const auto& location : availableLocations) {
            if (location->canAccommodate(quantity)) {
                return location;
            }
        }
    }
    auto allAvailable = findAvailableLocations();
    for (const auto& location : allAvailable) {
        if (location->canAccommodate(quantity)) {
            return location;
        }
    }
    return nullptr;
}

int Warehouse::getTotalCapacity() const noexcept {
    int total = 0;
    for (const auto& section : sections) {
        total += section->getTotalCapacity();
    }
    return total;
}

int Warehouse::getCurrentLoad() const noexcept {
    int total = 0;
    for (const auto& section : sections) {
        total += section->getCurrentLoad();
    }
    return total;
}

int Warehouse::getAvailableSpace() const noexcept {
    return getTotalCapacity() - getCurrentLoad();
}

double Warehouse::getUtilizationPercentage() const noexcept {
    int totalCapacity = getTotalCapacity();
    if (totalCapacity == 0) return 0.0;
    return (static_cast<double>(getCurrentLoad()) / totalCapacity) * 100.0;
}

bool Warehouse::isEmpty() const noexcept {
    return getCurrentLoad() == 0;
}

bool Warehouse::isFull() const noexcept {
    return getAvailableSpace() == 0;
}

std::string Warehouse::getInfo() const noexcept {
    return "Warehouse: " + name + 
           " | Address: " + address +
           " | Sections: " + std::to_string(sections.size()) +
           " | Capacity: " + std::to_string(getTotalCapacity()) +
           " | Load: " + std::to_string(getCurrentLoad()) +
           " | Available: " + std::to_string(getAvailableSpace()) +
           " | Utilization: " + std::to_string(getUtilizationPercentage()) + "%";
}

std::string Warehouse::getDetailedReport() const noexcept {
    std::string report = "=== WAREHOUSE DETAILED REPORT ===\n";
    report += "Name: " + name + "\n";
    report += "Address: " + address + "\n";
    report += "Total Sections: " + std::to_string(sections.size()) + "\n";
    report += "Total Capacity: " + std::to_string(getTotalCapacity()) + "\n";
    report += "Current Load: " + std::to_string(getCurrentLoad()) + "\n";
    report += "Available Space: " + std::to_string(getAvailableSpace()) + "\n";
    report += "Utilization: " + std::to_string(getUtilizationPercentage()) + "%\n";
    report += "\n=== SECTIONS ===\n";
    for (const auto& section : sections) {
        report += section->getInfo() + "\n";
    }
    report += "\n=== INVENTORY SUMMARY ===\n";
    report += "Total Inventory Items: " + std::to_string(inventory.size()) + "\n";
    return report;
}

bool Warehouse::operator==(const Warehouse& other) const noexcept {
    return name == other.name &&
           address == other.address &&
           sections == other.sections &&
           inventory == other.inventory;
}

bool Warehouse::operator!=(const Warehouse& other) const noexcept {
    return !(*this == other);
}