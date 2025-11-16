#include "InventoryReport.hpp"
#include "config/WarehouseConfig.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"

InventoryReport::InventoryReport(std::shared_ptr<Warehouse> warehouse) 
    : warehouse(warehouse) {
    if (!warehouse) {
        throw DataValidationException("Warehouse cannot be null in InventoryReport");
    }
}

std::shared_ptr<Warehouse> InventoryReport::getWarehouse() const noexcept {
    return warehouse;
}

void InventoryReport::setWarehouse(std::shared_ptr<Warehouse> warehouse) {
    if (!warehouse) {
        throw DataValidationException("Warehouse cannot be null");
    }
    this->warehouse = warehouse;
}

void InventoryReport::validateWarehouse() const {
    if (!warehouse) {
        throw WarehouseException("Warehouse not set in InventoryReport");
    }
}

std::string InventoryReport::generateFullReport() const {
    validateWarehouse();
    std::string report = "=== COMPREHENSIVE INVENTORY REPORT ===\n\n";
    report += generateStatisticsReport() + "\n\n";
    report += generateCapacityReport() + "\n\n";
    report += generateSectionUtilizationReport() + "\n\n";
    report += generateLowStockReport() + "\n\n";
    return report;
}

std::string InventoryReport::generateStockLevelReport() const {
    validateWarehouse();
    auto inventory = warehouse->findInventoryByBook("");
    auto counts = calculateBookCounts(inventory);
    std::string report = "=== STOCK LEVEL REPORT ===\n";
    report += "Total Unique Books: " + std::to_string(counts.uniqueBooks) + "\n";
    report += "Total Physical Books: " + std::to_string(counts.totalBooks) + "\n";
    report += "Total Inventory Items: " + std::to_string(inventory.size()) + "\n";
    return report;
}

std::string InventoryReport::generateBookStockReport(const std::string& bookIsbn) const {
    validateWarehouse();
    auto items = warehouse->findInventoryByBook(bookIsbn);
    if (items.empty()) {
        throw ReportGenerationException("No stock found for book ISBN: " + bookIsbn);
    }
    std::string report = "=== BOOK STOCK REPORT ===\n";
    report += buildBookHeader(items, bookIsbn);
    report += buildLocationDetails(items);
    return report;
}

std::string InventoryReport::generateCapacityReport() const {
    validateWarehouse();
    std::string report = "=== CAPACITY REPORT ===\n";
    report += buildCapacityMetrics();
    report += buildWarehouseStatus();
    return report;
}

std::string InventoryReport::generateSectionUtilizationReport() const {
    validateWarehouse();
    std::string report = "=== SECTION UTILIZATION REPORT ===\n";
    auto sections = warehouse->getSections();
    for (const auto& section : sections) {
        if (section) {
            report += section->getInfo() + "\n";
        }
    }
    return report;
}

std::string InventoryReport::generateLowStockReport(int threshold) const {
    validateWarehouse();
    std::string report = "=== LOW STOCK ALERTS ===\n";
    report += buildLowStockAlerts(threshold);
    return report;
}

std::string InventoryReport::generateEmptyLocationsReport() const {
    validateWarehouse();
    auto availableLocations = warehouse->findAvailableLocations();
    std::string report = "=== EMPTY LOCATIONS REPORT ===\n";
    report += buildEmptyLocationsList(availableLocations);
    return report;
}

std::string InventoryReport::generateFullLocationsReport() const {
    validateWarehouse();
    auto fullLocations = findFullLocations();
    std::string report = "=== FULL LOCATIONS REPORT ===\n";
    report += buildFullLocationsList(fullLocations);
    return report;
}

std::string InventoryReport::generateStatisticsReport() const {
    validateWarehouse();
    std::string report = "=== INVENTORY STATISTICS ===\n";
    report += buildBasicStatistics();
    return report;
}

InventoryReport::BookCounts InventoryReport::calculateBookCounts(
    const std::vector<std::shared_ptr<InventoryItem>>& inventory) const {
    BookCounts counts = {0, 0};
    std::string lastIsbn = "";
    for (const auto& item : inventory) {
        if (isValidInventoryItem(item)) {
            std::string currentIsbn = item->getBook()->getISBN().getCode();
            counts = updateBookCounts(counts, currentIsbn, lastIsbn, item->getQuantity());
            lastIsbn = currentIsbn;
        }
    }
    return counts;
}

bool InventoryReport::isValidInventoryItem(std::shared_ptr<InventoryItem> item) const {
    return item && item->getBook();
}

InventoryReport::BookCounts InventoryReport::updateBookCounts(
    BookCounts counts, const std::string& currentIsbn, 
    const std::string& lastIsbn, int quantity) const {
    if (currentIsbn != lastIsbn) {
        counts.uniqueBooks++;
    }
    counts.totalBooks += quantity;
    return counts;
}

std::string InventoryReport::buildBookHeader(
    const std::vector<std::shared_ptr<InventoryItem>>& items, 
    const std::string& bookIsbn) const {
    std::string header = "ISBN: " + bookIsbn + "\n";
    if (!items.empty() && items[0]->getBook()) {
        header += "Title: " + items[0]->getBook()->getTitle().getFullTitle() + "\n";
    }
    int totalQuantity = warehouse->getBookTotalQuantity(bookIsbn);
    header += "Total Quantity: " + std::to_string(totalQuantity) + "\n";
    header += "Storage Locations: " + std::to_string(items.size()) + "\n\n";
    return header;
}

std::string InventoryReport::buildLocationDetails(
    const std::vector<std::shared_ptr<InventoryItem>>& items) const {
    std::string details = "Location Details:\n";
    for (const auto& item : items) {
        if (isValidInventoryItem(item) && item->getLocation()) {
            details += buildLocationLine(item);
        }
    }
    return details;
}

std::string InventoryReport::buildLocationLine(std::shared_ptr<InventoryItem> item) const {
    return "  - " + item->getLocation()->getLocationId() + 
           ": " + std::to_string(item->getQuantity()) + " units\n";
}

std::string InventoryReport::buildCapacityMetrics() const {
    return "Total Capacity: " + std::to_string(warehouse->getTotalCapacity()) + "\n" +
           "Current Load: " + std::to_string(warehouse->getCurrentLoad()) + "\n" +
           "Available Space: " + std::to_string(warehouse->getAvailableSpace()) + "\n" +
           "Utilization: " + std::to_string(warehouse->getUtilizationPercentage()) + "%\n";
}

std::string InventoryReport::buildWarehouseStatus() const {
    if (warehouse->isEmpty()) {
        return "Status: EMPTY\n";
    } else if (warehouse->isFull()) {
        return "Status: FULL\n";
    } else {
        return "Status: OPERATIONAL\n";
    }
}

std::string InventoryReport::buildLowStockAlerts(int threshold) const {
    int availableSpace = warehouse->getAvailableSpace();
    if (availableSpace < threshold) {
        return "Low warehouse space: " + std::to_string(availableSpace) + " units remaining\n";
    } else {
        return "No low stock alerts\n";
    }
}

std::string InventoryReport::buildEmptyLocationsList(
    const std::vector<std::shared_ptr<StorageLocation>>& locations) const {
    std::string list = "Total Empty Locations: " + std::to_string(locations.size()) + "\n";
    for (const auto& location : locations) {
        if (location) {
            list += buildEmptyLocationLine(location);
        }
    }
    return list;
}

std::string InventoryReport::buildEmptyLocationLine(std::shared_ptr<StorageLocation> location) const {
    return "  - " + location->getLocationId() + 
           " (Capacity: " + std::to_string(location->getCapacity()) + ")\n";
}

std::vector<std::shared_ptr<StorageLocation>> InventoryReport::findFullLocations() const {
    std::vector<std::shared_ptr<StorageLocation>> fullLocations;
    auto sections = warehouse->getSections();
    for (const auto& section : sections) {
        if (section) {
            collectFullLocationsFromSection(section, fullLocations);
        }
    }
    return fullLocations;
}

void InventoryReport::collectFullLocationsFromSection(
    std::shared_ptr<WarehouseSection> section,
    std::vector<std::shared_ptr<StorageLocation>>& fullLocations) const { 
    auto shelves = section->getShelves();
    for (const auto& shelf : shelves) {
        if (shelf) {
            collectFullLocationsFromShelf(shelf, fullLocations);
        }
    }
}

void InventoryReport::collectFullLocationsFromShelf(
    std::shared_ptr<Shelf> shelf,
    std::vector<std::shared_ptr<StorageLocation>>& fullLocations) const {
    auto locations = shelf->getLocations();
    for (const auto& location : locations) {
        if (location && location->isFull()) {
            fullLocations.push_back(location);
        }
    }
}

std::string InventoryReport::buildFullLocationsList(
    const std::vector<std::shared_ptr<StorageLocation>>& fullLocations) const {
    std::string list = "Total Full Locations: " + std::to_string(fullLocations.size()) + "\n";
    for (const auto& location : fullLocations) {
        list += buildFullLocationLine(location);
    }
    return list;
}

std::string InventoryReport::buildFullLocationLine(std::shared_ptr<StorageLocation> location) const {
    return "  - " + location->getLocationId() + 
           " (Load: " + std::to_string(location->getCurrentLoad()) + 
           "/" + std::to_string(location->getCapacity()) + ")\n";
}

std::string InventoryReport::buildBasicStatistics() const {
    return "Warehouse: " + warehouse->getName() + "\n" +
           "Report Date: " + DateUtils::getCurrentDate() + "\n" +
           "Total Sections: " + std::to_string(warehouse->getSectionsCount()) + "\n" +
           "Total Capacity: " + std::to_string(warehouse->getTotalCapacity()) + "\n" +
           "Current Utilization: " + std::to_string(warehouse->getUtilizationPercentage()) + "%\n";
}

bool InventoryReport::operator==(const InventoryReport& other) const noexcept {
    return warehouse == other.warehouse;
}

bool InventoryReport::operator!=(const InventoryReport& other) const noexcept {
    return !(*this == other);
}