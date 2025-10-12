#include "warehouse/StockReceipt.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "utils/Utils.hpp"
#include "warehouse/Warehouse.hpp"
#include <regex>

bool StockReceipt::isValidSupplierName(const std::string& supplierName) const {
    return StringValidation::isValidName(supplierName, 100);
}

bool StockReceipt::isValidPurchaseOrderNumber(const std::string& poNumber) const {
    std::regex pattern("^PO-\\d{4}-\\d{3}$");
    return std::regex_match(poNumber, pattern);
}

bool StockReceipt::isValidInvoiceNumber(const std::string& invoiceNumber) const {
    std::regex pattern("^INV-\\d{4}-\\d{3}$");
    return std::regex_match(invoiceNumber, pattern);
}

bool StockReceipt::isValidTotalCost(double cost) const {
    return cost >= WarehouseConfig::StockReceipt::MIN_TOTAL_COST && 
           cost <= WarehouseConfig::StockReceipt::MAX_TOTAL_COST;
}

StockReceipt::StockReceipt(const std::string& movementId, const std::string& movementDate,
                         const std::string& employeeId, std::shared_ptr<Warehouse> warehouse,
                         const std::string& supplierName, const std::string& purchaseOrderNumber, 
                         const std::string& invoiceNumber, double totalCost, const std::string& notes)
    : StockMovement(movementId, MovementType::RECEIPT, movementDate, employeeId, warehouse, notes) {
    
    if (!isValidSupplierName(supplierName)) {
        throw DataValidationException("Invalid supplier name: " + supplierName);
    }
    if (!isValidPurchaseOrderNumber(purchaseOrderNumber)) {
        throw DataValidationException("Invalid purchase order number: " + purchaseOrderNumber);
    }
    if (!isValidInvoiceNumber(invoiceNumber)) {
        throw DataValidationException("Invalid invoice number: " + invoiceNumber);
    }
    if (!isValidTotalCost(totalCost)) {
        throw DataValidationException("Invalid total cost: " + std::to_string(totalCost));
    }
    
    this->supplierName = supplierName;
    this->purchaseOrderNumber = purchaseOrderNumber;
    this->invoiceNumber = invoiceNumber;
    this->totalCost = totalCost;
}

std::string StockReceipt::getSupplierName() const noexcept {
    return supplierName;
}

std::string StockReceipt::getPurchaseOrderNumber() const noexcept {
    return purchaseOrderNumber;
}

std::string StockReceipt::getInvoiceNumber() const noexcept {
    return invoiceNumber;
}

double StockReceipt::getTotalCost() const noexcept {
    return totalCost;
}

void StockReceipt::execute() {
    if (getStatus() != MovementStatus::PENDING) {
        throw WarehouseException("Cannot execute receipt that is not pending");
    }
    
    setStatus(MovementStatus::IN_PROGRESS);
    
    try {
        auto warehouse = getWarehouse();
        if (!warehouse) {
            throw WarehouseException("Warehouse not available for receipt operation");
        }
        
        for (const auto& item : getAffectedItems()) {
            if (!item) continue;
            
            auto location = item->getLocation();
            if (!location) {
                throw WarehouseException("Inventory item has no valid location");
            }
            
            if (location->getStatus() == StorageLocation::LocationStatus::BLOCKED) {
                throw WarehouseException("Cannot add items to blocked location: " + location->getLocationId());
            }
            
            // Добавляем InventoryItem в warehouse (если его еще нет)
            warehouse->addInventoryItem(item);
            
            // Увеличиваем quantity в InventoryItem и добавляем в location
            int receiptQuantity = item->getQuantity();
            item->increaseQuantity(receiptQuantity);
            location->addBooks(receiptQuantity);
        }
        
        setStatus(MovementStatus::COMPLETED);
        
    } catch (const std::exception& e) {
        setStatus(MovementStatus::CANCELLED);
        throw WarehouseException("Failed to execute receipt: " + std::string(e.what()));
    }
}

void StockReceipt::cancel() {
    if (!isCancellable()) {
        throw WarehouseException("Cannot cancel receipt that is not pending or in progress");
    }
    
    auto warehouse = getWarehouse();
    if (getStatus() == MovementStatus::IN_PROGRESS && warehouse) {
        for (const auto& item : getAffectedItems()) {
            if (!item) continue;
            
            auto location = item->getLocation();
            if (location) {
                try {
                    // Уменьшаем quantity и удаляем из location
                    int receiptQuantity = item->getQuantity();
                    item->decreaseQuantity(receiptQuantity);
                    location->removeBooks(receiptQuantity);
                    
                    // Если quantity стало 0, удаляем InventoryItem из warehouse
                    if (item->getQuantity() == 0) {
                        warehouse->removeInventoryItem(
                            item->getBook()->getISBN().getCode(),
                            item->getLocation()->getLocationId()
                        );
                    }
                } catch (const std::exception& e) {
                    // Логируем ошибку, но продолжаем откат других items
                }
            }
        }
    }
    
    setStatus(MovementStatus::CANCELLED);
}

std::string StockReceipt::getInfo() const noexcept {
    std::string baseInfo = StockMovement::getInfo();
    return baseInfo + 
           " | Supplier: " + supplierName +
           " | PO: " + purchaseOrderNumber +
           " | Invoice: " + invoiceNumber +
           " | Total Cost: $" + std::to_string(totalCost);
}

double StockReceipt::calculateAverageCost() const noexcept {
    int totalQuantity = 0;
    for (const auto& item : getAffectedItems()) {
        if (item) {
            totalQuantity += item->getQuantity();
        }
    }
    if (totalQuantity == 0) return 0.0;
    return totalCost / totalQuantity;
}

bool StockReceipt::operator==(const StockReceipt& other) const noexcept {
    return static_cast<const StockMovement&>(*this) == static_cast<const StockMovement&>(other) &&
           supplierName == other.supplierName &&
           purchaseOrderNumber == other.purchaseOrderNumber &&
           invoiceNumber == other.invoiceNumber &&
           totalCost == other.totalCost;
}

bool StockReceipt::operator!=(const StockReceipt& other) const noexcept {
    return !(*this == other);
}