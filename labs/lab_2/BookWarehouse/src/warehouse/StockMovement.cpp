#include "warehouse/StockMovement.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"
#include <regex>

bool StockMovement::isValidMovementId(const std::string& movementId) const {
    std::regex pattern("^(MOV|REC|WO|TRF|DEL)-\\d{4}-\\d{3}$");
    return std::regex_match(movementId, pattern);
}

bool StockMovement::isValidDate(const std::string& date) const {
    return StringValidation::isValidDate(date);
}

bool StockMovement::isValidEmployeeId(const std::string& employeeId) const {
    //"EMP-001"
    std::regex pattern("^EMP-\\d{3}$");
    return std::regex_match(employeeId, pattern);
}

StockMovement::StockMovement(const std::string& movementId, MovementType movementType,
                           const std::string& movementDate, const std::string& employeeId,
                           std::shared_ptr<Warehouse> warehouse, const std::string& notes) {
    if (!isValidMovementId(movementId)) {
        throw DataValidationException("Invalid movement ID format: " + movementId);
    }
    if (!isValidDate(movementDate)) {
        throw DataValidationException("Invalid movement date: " + movementDate);
    }
    if (!isValidEmployeeId(employeeId)) {
        throw DataValidationException("Invalid employee ID: " + employeeId);
    }
    if (!warehouse) {
        throw DataValidationException("Warehouse cannot be null");
    }
    this->movementId = movementId;
    this->movementType = movementType;
    this->movementDate = movementDate;
    this->employeeId = employeeId;
    this->warehouse = warehouse;
    this->notes = notes;
    this->status = MovementStatus::PENDING;
}

std::string StockMovement::getMovementId() const noexcept {
    return movementId;
}

StockMovement::MovementType StockMovement::getMovementType() const noexcept {
    return movementType;
}

StockMovement::MovementStatus StockMovement::getStatus() const noexcept {
    return status;
}

std::string StockMovement::getMovementDate() const noexcept {
    return movementDate;
}

std::string StockMovement::getEmployeeId() const noexcept {
    return employeeId;
}

std::vector<std::shared_ptr<InventoryItem>> StockMovement::getAffectedItems() const noexcept {
    return affectedItems;
}

std::string StockMovement::getNotes() const noexcept {
    return notes;
}

std::shared_ptr<Warehouse> StockMovement::getWarehouse() const noexcept {
    return warehouse.lock();
}

void StockMovement::setStatus(MovementStatus status) noexcept {
    this->status = status;
}

void StockMovement::setNotes(const std::string& notes) noexcept {
    this->notes = notes;
}

void StockMovement::addAffectedItem(std::shared_ptr<InventoryItem> item) {
    if (!item) {
        throw DataValidationException("Cannot add null inventory item to movement");
    }
    auto it = std::find(affectedItems.begin(), affectedItems.end(), item);
    if (it != affectedItems.end()) {
        throw DataValidationException("Inventory item already added to movement");
    }
    affectedItems.push_back(item);
}

void StockMovement::removeAffectedItem(std::shared_ptr<InventoryItem> item) {
    if (!item) return;
    auto it = std::find(affectedItems.begin(), affectedItems.end(), item);
    if (it != affectedItems.end()) {
        affectedItems.erase(it);
    }
}

bool StockMovement::isCompleted() const noexcept {
    return status == MovementStatus::COMPLETED;
}

bool StockMovement::isPending() const noexcept {
    return status == MovementStatus::PENDING;
}

bool StockMovement::isCancellable() const noexcept {
    return status == MovementStatus::PENDING || status == MovementStatus::IN_PROGRESS;
}

std::string StockMovement::getInfo() const noexcept {
    return "Movement: " + movementId + 
           " | Type: " + getMovementTypeString() +
           " | Status: " + getMovementStatusString() +
           " | Date: " + movementDate +
           " | Employee: " + employeeId +
           " | Items: " + std::to_string(affectedItems.size()) +
           (notes.empty() ? "" : " | Notes: " + notes);
}

std::string StockMovement::getMovementTypeString() const noexcept {
    switch (movementType) {
        case MovementType::RECEIPT: return "Receipt";
        case MovementType::WRITE_OFF: return "Write-Off";
        case MovementType::TRANSFER: return "Transfer";
        default: return "Unknown";
    }
}

std::string StockMovement::getMovementStatusString() const noexcept {
    switch (status) {
        case MovementStatus::PENDING: return "Pending";
        case MovementStatus::IN_PROGRESS: return "In Progress";
        case MovementStatus::COMPLETED: return "Completed";
        case MovementStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}

bool StockMovement::operator==(const StockMovement& other) const noexcept {
    return movementId == other.movementId &&
           movementType == other.movementType &&
           status == other.status &&
           movementDate == other.movementDate &&
           employeeId == other.employeeId &&
           affectedItems == other.affectedItems &&
           notes == other.notes;
}

bool StockMovement::operator!=(const StockMovement& other) const noexcept {
    return !(*this == other);
}