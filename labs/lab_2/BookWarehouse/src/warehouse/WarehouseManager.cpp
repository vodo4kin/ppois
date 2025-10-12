#include "warehouse/WarehouseManager.hpp"
#include "config/WarehouseConfig.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"

WarehouseManager::WarehouseManager(std::shared_ptr<Warehouse> warehouse) 
    : warehouse(warehouse) {
    if (!warehouse) {
        throw DataValidationException("Warehouse cannot be null in WarehouseManager");
    }
}

std::shared_ptr<Warehouse> WarehouseManager::getWarehouse() const noexcept {
    return warehouse;
}

void WarehouseManager::setWarehouse(std::shared_ptr<Warehouse> warehouse) {
    if (!warehouse) {
        throw DataValidationException("Warehouse cannot be null");
    }
    this->warehouse = warehouse;
}

std::shared_ptr<StockReceipt> WarehouseManager::processStockReceipt(
    const std::string& supplierName,
    const std::string& purchaseOrderNumber,
    const std::string& invoiceNumber,
    double totalCost,
    const std::vector<std::pair<std::shared_ptr<Book>, int>>& items,
    const std::string& employeeId,
    const std::string& notes) {
    validateWarehouse();
    if (items.empty()) {
        throw DataValidationException("Cannot process receipt with no items");
    }
    std::string movementId = generateMovementId("REC");
    std::string currentDate = DateUtils::getCurrentDate();
    auto receipt = std::make_shared<StockReceipt>(
        movementId, currentDate, employeeId, warehouse,
        supplierName, purchaseOrderNumber, invoiceNumber, totalCost, notes
    );
    for (const auto& item : items) {
        auto book = item.first;
        int quantity = item.second;
        if (!book) {
            throw DataValidationException("Cannot add null book to receipt");
        }
        if (quantity <= 0) {
            throw DataValidationException("Receipt quantity must be positive");
        }
        auto location = findOptimalBookLocation(book, quantity);
        if (!location) {
            throw WarehouseException("No available location found for book");
        }
        auto inventoryItem = std::make_shared<InventoryItem>(
            book, quantity, location, currentDate
        );
        receipt->addAffectedItem(inventoryItem);
    }
    warehouse->processStockMovement(receipt);
    return receipt;
}

std::shared_ptr<StockWriteOff> WarehouseManager::processStockWriteOff(
    StockWriteOff::WriteOffReason reason,
    const std::string& detailedReason,
    const std::vector<std::tuple<std::shared_ptr<Book>, std::shared_ptr<StorageLocation>, int>>& items,
    const std::string& employeeId,
    const std::string& notes) {
    validateWarehouse();
    if (items.empty()) {
        throw DataValidationException("Cannot process write-off with no items");
    }
    std::string movementId = generateMovementId("WO");
    std::string currentDate = DateUtils::getCurrentDate();
    auto writeOff = std::make_shared<StockWriteOff>(
        movementId, currentDate, employeeId, warehouse,
        reason, detailedReason, notes
    );
    for (const auto& item : items) {
        auto book = std::get<0>(item);
        auto location = std::get<1>(item);
        int quantity = std::get<2>(item);
        if (!book || !location) {
            throw DataValidationException("Cannot add null book or location to write-off");
        }
        if (quantity <= 0) {
            throw DataValidationException("Write-off quantity must be positive");
        }
        auto existingItem = warehouse->findInventoryItem(
            book->getISBN().getCode(), 
            location->getLocationId()
        );
        if (!existingItem) {
            throw BookNotFoundException("Inventory item not found for write-off");
        }
        if (existingItem->getQuantity() < quantity) {
            throw InsufficientStockException("Insufficient stock for write-off");
        }
        auto writeOffItem = std::make_shared<InventoryItem>(
            book, quantity, location, currentDate
        );
        writeOff->addAffectedItem(writeOffItem);
    }
    warehouse->processStockMovement(writeOff);
    return writeOff;
}

std::shared_ptr<StockTransfer> WarehouseManager::processStockTransfer(
    std::shared_ptr<StorageLocation> sourceLocation,
    std::shared_ptr<StorageLocation> destinationLocation,
    const std::string& transferReason,
    const std::vector<std::pair<std::shared_ptr<Book>, int>>& items,
    const std::string& employeeId,
    const std::string& notes) {
    validateWarehouse();
    if (!sourceLocation || !destinationLocation) {
        throw DataValidationException("Source and destination locations cannot be null");
    }
    if (items.empty()) {
        throw DataValidationException("Cannot process transfer with no items");
    }
    std::string movementId = generateMovementId("TRF");
    std::string currentDate = DateUtils::getCurrentDate();
    auto transfer = std::make_shared<StockTransfer>(
        movementId, currentDate, employeeId, warehouse,
        sourceLocation, destinationLocation, transferReason, notes
    );
    
    for (const auto& item : items) {
        auto book = item.first;
        int quantity = item.second;
        if (!book) {
            throw DataValidationException("Cannot add null book to transfer");
        }
        if (quantity <= 0) {
            throw DataValidationException("Transfer quantity must be positive");
        }
        auto existingItem = warehouse->findInventoryItem(
            book->getISBN().getCode(), 
            sourceLocation->getLocationId()
        );
        if (!existingItem) {
            throw BookNotFoundException("Inventory item not found at source location");
        }
        if (existingItem->getQuantity() < quantity) {
            throw InsufficientStockException("Insufficient stock for transfer");
        }
        auto transferItem = std::make_shared<InventoryItem>(
            book, quantity, sourceLocation, currentDate
        );
        transfer->addAffectedItem(transferItem);
    }
    warehouse->processStockMovement(transfer);
    return transfer;
}

std::shared_ptr<Delivery> WarehouseManager::createDelivery(
    const std::string& supplierName,
    const std::string& scheduledDate,
    const std::string& trackingNumber,
    const std::string& carrier,
    double shippingCost,
    const std::vector<std::shared_ptr<Book>>& books) {
    std::string deliveryId = generateMovementId("DEL");
    auto delivery = std::make_shared<Delivery>(
        deliveryId, supplierName, scheduledDate, trackingNumber, carrier, shippingCost
    );
    for (const auto& book : books) {
        if (!book) {
            throw DataValidationException("Cannot add null book to delivery");
        }
        delivery->addBook(book);
    }
    return delivery;
}

std::shared_ptr<StockReceipt> WarehouseManager::processDeliveryArrival(
    std::shared_ptr<Delivery> delivery,
    const std::string& employeeId) {
    validateWarehouse();
    if (!delivery) {
        throw DataValidationException("Delivery cannot be null");
    }
    if (!delivery->isInTransit() && !delivery->isDelayed()) {
        throw WarehouseException("Cannot process arrival for delivery that is not in transit or delayed");
    }
    delivery->processArrival();
    std::vector<std::pair<std::shared_ptr<Book>, int>> receiptItems;
    for (const auto& book : delivery->getBooks()) {
        receiptItems.emplace_back(book, 1);
    }
    auto receipt = processStockReceipt(
        delivery->getSupplierName(),
        "PO-" + delivery->getDeliveryId(),
        "INV-" + delivery->getDeliveryId(),
        delivery->getShippingCost(),
        receiptItems,
        employeeId,
        "Processed from delivery: " + delivery->getDeliveryId()
    );
    delivery->setStockReceipt(receipt);
    delivery->completeDelivery();
    return receipt;
}

std::shared_ptr<StorageLocation> WarehouseManager::findOptimalBookLocation(
    std::shared_ptr<Book> book,
    int quantity,
    WarehouseSection::SectionType preferredSectionType) const {
    validateWarehouse();
    if (!book) {
        throw DataValidationException("Book cannot be null");
    }
    if (quantity <= 0) {
        throw DataValidationException("Quantity must be positive");
    }
    return warehouse->findOptimalLocation(quantity, preferredSectionType);
}

std::string WarehouseManager::getBookStockInfo(const std::string& bookIsbn) const {
    validateWarehouse();
    int totalQuantity = warehouse->getBookTotalQuantity(bookIsbn);
    auto inventoryItems = warehouse->findInventoryByBook(bookIsbn);
    std::string info = "Book ISBN: " + bookIsbn + "\n";
    info += "Total Quantity: " + std::to_string(totalQuantity) + "\n";
    info += "Locations: " + std::to_string(inventoryItems.size()) + "\n";
    for (const auto& item : inventoryItems) {
        if (item && item->getLocation()) {
            info += "  - " + item->getLocation()->getLocationId() + 
                   ": " + std::to_string(item->getQuantity()) + " units\n";
        }
    }
    return info;
}

bool WarehouseManager::isBookAvailable(const std::string& bookIsbn, int requiredQuantity) const {
    validateWarehouse();
    if (requiredQuantity <= 0) {
        throw DataValidationException("Required quantity must be positive");
    }
    int availableQuantity = warehouse->getBookTotalQuantity(bookIsbn);
    return availableQuantity >= requiredQuantity;
}

std::string WarehouseManager::getWarehouseUtilizationReport() const {
    validateWarehouse();
    std::string report = "=== WAREHOUSE UTILIZATION REPORT ===\n";
    report += warehouse->getInfo() + "\n";
    return report;
}

std::string WarehouseManager::getInventorySummary() const {
    validateWarehouse();
    std::string summary = "=== INVENTORY SUMMARY ===\n";
    summary += "Total Capacity: " + std::to_string(warehouse->getTotalCapacity()) + "\n";
    summary += "Current Load: " + std::to_string(warehouse->getCurrentLoad()) + "\n";
    summary += "Available Space: " + std::to_string(warehouse->getAvailableSpace()) + "\n";
    return summary;
}

std::vector<std::string> WarehouseManager::getLowStockAlerts(int threshold) const {
    validateWarehouse();
    std::vector<std::string> alerts;
    if (warehouse->getAvailableSpace() < threshold) {
        alerts.push_back("Low warehouse space: " + 
                        std::to_string(warehouse->getAvailableSpace()) + " units left");
    }
    return alerts;
}

bool WarehouseManager::operator==(const WarehouseManager& other) const noexcept {
    return warehouse == other.warehouse;
}

bool WarehouseManager::operator!=(const WarehouseManager& other) const noexcept {
    return !(*this == other);
}

void WarehouseManager::validateWarehouse() const {
    if (!warehouse) {
        throw WarehouseException("Warehouse not set in WarehouseManager");
    }
}

std::string WarehouseManager::generateMovementId(const std::string& prefix) const {
    static int counter = 1;
    std::string currentDate = DateUtils::getCurrentDate();
    std::string year = currentDate.substr(0, 4);
    std::stringstream ss;
    ss << prefix << "-" << year << "-" << std::setw(3) << std::setfill('0') << counter++;
    return ss.str();
}