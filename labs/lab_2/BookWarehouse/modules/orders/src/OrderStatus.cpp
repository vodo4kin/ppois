#include "OrderStatus.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"

OrderStatus::OrderStatus(Status status, const std::string& statusChangedDate) {
    if (!StringValidation::isValidDate(statusChangedDate)) {
        throw DataValidationException("Invalid status change date: " + statusChangedDate);
    }
    this->status = status;
    this->statusChangedDate = statusChangedDate;
}

OrderStatus::Status OrderStatus::getStatus() const noexcept {
    return status;
}

std::string OrderStatus::getStatusChangedDate() const noexcept {
    return statusChangedDate;
}

std::string OrderStatus::toString() const noexcept {
    switch(status) {
        case Status::PENDING: return "Pending";
        case Status::CONFIRMED: return "Confirmed";
        case Status::PROCESSING: return "Processing";
        case Status::READY_FOR_SHIPPING: return "Ready for Shipping";
        case Status::SHIPPED: return "Shipped";
        case Status::DELIVERED: return "Delivered";
        case Status::CANCELLED: return "Cancelled";
        case Status::REFUNDED: return "Refunded";
        case Status::ON_HOLD: return "On Hold";
        case Status::BACKORDERED: return "Backordered";
        default: return "Unknown";
    }
}

bool OrderStatus::isValidTransition(Status newStatus) const noexcept {
    if (status == newStatus) return true;
    
    switch(status) {
        case Status::PENDING:
            return newStatus == Status::CONFIRMED || newStatus == Status::CANCELLED 
            || newStatus == Status::ON_HOLD;
        case Status::CONFIRMED:
            return newStatus == Status::PROCESSING || newStatus == Status::CANCELLED 
            || newStatus == Status::BACKORDERED;
        case Status::PROCESSING:
            return newStatus == Status::READY_FOR_SHIPPING || newStatus == Status::CANCELLED 
            || newStatus == Status::BACKORDERED;
        case Status::READY_FOR_SHIPPING:
            return newStatus == Status::SHIPPED || newStatus == Status::CANCELLED;
        case Status::SHIPPED:
            return newStatus == Status::DELIVERED;
        case Status::DELIVERED:
            return newStatus == Status::REFUNDED;
        case Status::ON_HOLD:
            return newStatus == Status::CONFIRMED || newStatus == Status::CANCELLED;
        case Status::BACKORDERED:
            return newStatus == Status::PROCESSING || newStatus == Status::CANCELLED;
        case Status::CANCELLED:
        case Status::REFUNDED:
            return false;
        default:
            return false;
    }
}

void OrderStatus::updateStatus(Status newStatus, const std::string& changeDate) {
    if (!StringValidation::isValidDate(changeDate)) {
        throw DataValidationException("Invalid change date: " + changeDate);
    }
    if (!isValidTransition(newStatus)) {
        throw InvalidOrderStateException("Invalid status transition from " + toString() + " to " + 
                                       OrderStatus(newStatus, changeDate).toString());
    }
    status = newStatus;
    statusChangedDate = changeDate;
}

bool OrderStatus::isCompleted() const noexcept {
    return status == Status::DELIVERED || status == Status::CANCELLED || status == Status::REFUNDED;
}

bool OrderStatus::isActive() const noexcept {
    return !isCompleted() && status != Status::ON_HOLD;
}

bool OrderStatus::isCancellable() const noexcept {
    return status == Status::PENDING || status == Status::CONFIRMED || status == Status::PROCESSING || 
           status == Status::ON_HOLD || status == Status::BACKORDERED;
}

bool OrderStatus::requiresAction() const noexcept {
    return status == Status::PENDING || status == Status::ON_HOLD || status == Status::BACKORDERED;
}

std::vector<OrderStatus::Status> OrderStatus::getNextPossibleStatuses() const noexcept {
    std::vector<Status> possibleStatuses;
    for (Status s : {Status::PENDING, Status::CONFIRMED, Status::PROCESSING, Status::READY_FOR_SHIPPING,
                    Status::SHIPPED, Status::DELIVERED, Status::CANCELLED, Status::REFUNDED, 
                    Status::ON_HOLD, Status::BACKORDERED}) {
        if (isValidTransition(s)) {
            possibleStatuses.push_back(s);
        }
    }
    return possibleStatuses;
}

bool OrderStatus::operator==(const OrderStatus& other) const noexcept {
    return status == other.status && statusChangedDate == other.statusChangedDate;
}

bool OrderStatus::operator!=(const OrderStatus& other) const noexcept {
    return !(*this == other);
}