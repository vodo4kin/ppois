#include "StockTransfer.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "Warehouse.hpp"
#include <regex>

bool StockTransfer::isValidTransferReason(const std::string& reason) const {
    return !reason.empty() && 
           reason.length() <= WarehouseConfig::StockMovement::MAX_TRANSFER_REASON_LENGTH;
}

bool StockTransfer::areLocationsValid(std::shared_ptr<StorageLocation> source, 
                                     std::shared_ptr<StorageLocation> destination) const {
    if (!source || !destination) {
        return false;
    }
    if (source == destination) {
        return false;
    }
    if (source->getLocationId() == destination->getLocationId()) {
        return false;
    }
    return true;
}

StockTransfer::StockTransfer(const std::string& movementId, const std::string& movementDate,
                           const std::string& employeeId, std::shared_ptr<Warehouse> warehouse,
                           std::shared_ptr<StorageLocation> sourceLocation,
                           std::shared_ptr<StorageLocation> destinationLocation, 
                           const std::string& transferReason, const std::string& notes)
    : StockMovement(movementId, MovementType::TRANSFER, movementDate, employeeId, warehouse, notes) {
    if (!areLocationsValid(sourceLocation, destinationLocation)) {
        throw DataValidationException("Invalid source or destination location for transfer");
    }
    if (!isValidTransferReason(transferReason)) {
        throw DataValidationException("Invalid transfer reason: " + transferReason);
    }
    this->sourceLocation = sourceLocation;
    this->destinationLocation = destinationLocation;
    this->transferReason = transferReason;
}

std::shared_ptr<StorageLocation> StockTransfer::getSourceLocation() const noexcept {
    return sourceLocation;
}

std::shared_ptr<StorageLocation> StockTransfer::getDestinationLocation() const noexcept {
    return destinationLocation;
}

std::string StockTransfer::getTransferReason() const noexcept {
    return transferReason;
}

void StockTransfer::execute() {
    if (getStatus() != MovementStatus::PENDING) {
        throw WarehouseException("Cannot execute transfer that is not pending");
    }
    setStatus(MovementStatus::IN_PROGRESS);
    try {
        if (!doesSourceHaveSufficientStock()) {
            throw InsufficientStockException("Source location " + sourceLocation->getLocationId() + 
                                           " has insufficient stock for transfer");
        }
        if (!canDestinationAccommodate()) {
            throw WarehouseException("Destination location " + destinationLocation->getLocationId() + 
                                   " cannot accommodate transfer");
        }
        for (const auto& item : getAffectedItems()) {
            if (!item) continue;
            int transferQuantity = item->getQuantity();
            sourceLocation->removeBooks(transferQuantity);
            destinationLocation->addBooks(transferQuantity);
            item->setLocation(destinationLocation);
        }
        setStatus(MovementStatus::COMPLETED);
    } catch (const std::exception& e) {
        try {
            for (const auto& item : getAffectedItems()) {
                if (!item) continue;
                int transferQuantity = item->getQuantity();
                if (sourceLocation) {
                    sourceLocation->addBooks(transferQuantity);
                }
                if (destinationLocation) {
                    destinationLocation->removeBooks(transferQuantity);
                }
                item->setLocation(sourceLocation);
            }
        } catch (const std::exception& rollbackError) {
            // don't interrupt
        }
        setStatus(MovementStatus::CANCELLED);
        throw WarehouseException("Failed to execute transfer: " + std::string(e.what()));
    }
}

void StockTransfer::cancel() {
    if (!isCancellable()) {
        throw WarehouseException("Cannot cancel transfer that is not pending or in progress");
    }
    if (getStatus() == MovementStatus::IN_PROGRESS) {
        for (const auto& item : getAffectedItems()) {
            if (!item) continue;
            int transferQuantity = item->getQuantity();
            try {
                if (sourceLocation) {
                    sourceLocation->addBooks(transferQuantity);
                }
                if (destinationLocation) {
                    destinationLocation->removeBooks(transferQuantity);
                }
                item->setLocation(sourceLocation);
            } catch (const std::exception& e) {
                // don't interrupt
            }
        }
    }
    setStatus(MovementStatus::CANCELLED);
}

std::string StockTransfer::getInfo() const noexcept {
    std::string baseInfo = StockMovement::getInfo();
    std::string sourceId = sourceLocation ? sourceLocation->getLocationId() : "N/A";
    std::string destId = destinationLocation ? destinationLocation->getLocationId() : "N/A";
    return baseInfo + 
           " | Source: " + sourceId +
           " | Destination: " + destId +
           " | Reason: " + transferReason +
           " | Quantity: " + std::to_string(getTotalTransferQuantity()) +
           " | Cross-Section: " + (isCrossSectionTransfer() ? "Yes" : "No");
}

int StockTransfer::getTotalTransferQuantity() const noexcept {
    int total = 0;
    for (const auto& item : getAffectedItems()) {
        if (item) {
            total += item->getQuantity();
        }
    }
    return total;
}

bool StockTransfer::isCrossSectionTransfer() const noexcept {
    if (!sourceLocation || !destinationLocation) {
        return false;
    }
    std::string sourceSection = sourceLocation->getLocationId().substr(0, 1);
    std::string destSection = destinationLocation->getLocationId().substr(0, 1);
    return sourceSection != destSection;
}

bool StockTransfer::canDestinationAccommodate() const noexcept {
    if (!destinationLocation) {
        return false;
    }
    int totalTransferQuantity = getTotalTransferQuantity();
    return destinationLocation->canAccommodate(totalTransferQuantity);
}

bool StockTransfer::doesSourceHaveSufficientStock() const noexcept {
    if (!sourceLocation) {
        return false;
    }
    int totalTransferQuantity = getTotalTransferQuantity();
    return sourceLocation->getCurrentLoad() >= totalTransferQuantity;
}

bool StockTransfer::operator==(const StockTransfer& other) const noexcept {
    bool locationsEqual = false;
    if (sourceLocation && other.sourceLocation && destinationLocation && other.destinationLocation) {
        locationsEqual = (sourceLocation->getLocationId() == other.sourceLocation->getLocationId()) &&
                        (destinationLocation->getLocationId() == other.destinationLocation->getLocationId());
    } else {
        locationsEqual = (sourceLocation == other.sourceLocation) && 
                        (destinationLocation == other.destinationLocation);
    }
    return static_cast<const StockMovement&>(*this) == static_cast<const StockMovement&>(other) &&
           locationsEqual &&
           transferReason == other.transferReason;
}

bool StockTransfer::operator!=(const StockTransfer& other) const noexcept {
    return !(*this == other);
}