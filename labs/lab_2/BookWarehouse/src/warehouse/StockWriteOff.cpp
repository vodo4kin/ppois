#include "warehouse/StockWriteOff.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "utils/Utils.hpp"
#include "warehouse/Warehouse.hpp"
#include "warehouse/InventoryItem.hpp"
#include <algorithm>

bool StockWriteOff::isValidDetailedReason(const std::string& detailedReason) const {
    return !detailedReason.empty() && 
           detailedReason.length() <= WarehouseConfig::StockMovement::MAX_DETAILED_REASON_LENGTH;
}

StockWriteOff::StockWriteOff(const std::string& movementId, const std::string& movementDate,
                           const std::string& employeeId, std::shared_ptr<Warehouse> warehouse,
                           WriteOffReason reason, const std::string& detailedReason, const std::string& notes)
    : StockMovement(movementId, MovementType::WRITE_OFF, movementDate, employeeId, warehouse, notes) {
    if (!isValidDetailedReason(detailedReason)) {
        throw DataValidationException("Invalid detailed reason: " + detailedReason);
    }
    this->reason = reason;
    this->detailedReason = detailedReason;
}

StockWriteOff::WriteOffReason StockWriteOff::getReason() const noexcept {
    return reason;
}

std::string StockWriteOff::getDetailedReason() const noexcept {
    return detailedReason;
}

void StockWriteOff::execute() {
    if (getStatus() != MovementStatus::PENDING) {
        throw WarehouseException("Cannot execute write-off that is not pending");
    }
    setStatus(MovementStatus::IN_PROGRESS);
    
    try {
        auto warehouse = getWarehouse();
        if (!warehouse) {
            throw WarehouseException("Warehouse not available for write-off operation");
        }
        for (const auto& item : getAffectedItems()) {
            if (!item) continue;
            auto location = item->getLocation();
            if (!location) {
                throw WarehouseException("Inventory item has no valid location");
            }
            int writeOffQuantity = item->getQuantity();
            if (writeOffQuantity > location->getCurrentLoad()) {
                throw InsufficientStockException("Cannot write off " + std::to_string(writeOffQuantity) + 
                                               " from location " + location->getLocationId() + 
                                               " (current: " + std::to_string(location->getCurrentLoad()) + ")");
            }
            item->decreaseQuantity(writeOffQuantity);
            location->removeBooks(writeOffQuantity);
            if (item->getQuantity() == 0) {
                warehouse->removeInventoryItem(
                    item->getBook()->getISBN().getCode(),
                    item->getLocation()->getLocationId()
                );
            }
        }
        
        setStatus(MovementStatus::COMPLETED);
    } catch (const std::exception& e) {
        setStatus(MovementStatus::CANCELLED);
        throw WarehouseException("Failed to execute write-off: " + std::string(e.what()));
    }
}

void StockWriteOff::cancel() {
    if (!isCancellable()) {
        throw WarehouseException("Cannot cancel write-off that is not pending or in progress");
    }
    auto warehouse = getWarehouse();
    if (getStatus() == MovementStatus::IN_PROGRESS && warehouse) {
        for (const auto& item : getAffectedItems()) {
            if (!item) continue;
            auto location = item->getLocation();
            if (location) {
                try {
                    int writeOffQuantity = item->getQuantity();
                    item->increaseQuantity(writeOffQuantity);
                    location->addBooks(writeOffQuantity);
                    
                } catch (const std::exception& e) {
                    // логи
                }
            }
        }
    }
    setStatus(MovementStatus::CANCELLED);
}

std::string StockWriteOff::getInfo() const noexcept {
    std::string baseInfo = StockMovement::getInfo();
    return baseInfo + 
           " | Reason: " + getReasonString() +
           " | Details: " + detailedReason +
           " | Total Written Off: " + std::to_string(getTotalWrittenOffQuantity());
}

std::string StockWriteOff::getReasonString() const noexcept {
    switch (reason) {
        case WriteOffReason::DAMAGED: return "Damaged";
        case WriteOffReason::EXPIRED: return "Expired";
        case WriteOffReason::OBSOLETE: return "Obsolete";
        case WriteOffReason::LOST: return "Lost";
        case WriteOffReason::QUALITY_ISSUE: return "Quality Issue";
        case WriteOffReason::OTHER: return "Other";
        default: return "Unknown";
    }
}

int StockWriteOff::getTotalWrittenOffQuantity() const noexcept {
    int total = 0;
    for (const auto& item : getAffectedItems()) {
        if (item) {
            total += item->getQuantity();
        }
    }
    return total;
}

bool StockWriteOff::isDueToDamage() const noexcept {
    return reason == WriteOffReason::DAMAGED;
}

bool StockWriteOff::isDueToExpiration() const noexcept {
    return reason == WriteOffReason::EXPIRED;
}

bool StockWriteOff::operator==(const StockWriteOff& other) const noexcept {
    return static_cast<const StockMovement&>(*this) == static_cast<const StockMovement&>(other) &&
           reason == other.reason &&
           detailedReason == other.detailedReason;
}

bool StockWriteOff::operator!=(const StockWriteOff& other) const noexcept {
    return !(*this == other);
}