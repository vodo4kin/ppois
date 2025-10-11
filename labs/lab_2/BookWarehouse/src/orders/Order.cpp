#include "orders/Order.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"
#include <algorithm>

bool Order::isValidOrderId(const std::string& orderId) const {
    return !orderId.empty() && orderId.length() <= OrderConfig::Order::MAX_ORDER_ID_LENGTH && StringValidation::isValidName(orderId);
}

bool Order::isValidNotes(const std::string& notes) const {
    return notes.length() <= OrderConfig::Order::MAX_NOTES_LENGTH;
}

bool Order::isValidOrderDate(const std::string& orderDate) const {
    return StringValidation::isValidDate(orderDate);
}

void Order::recalculateTotalAmount() {
    totalAmount = 0.0;
    for (const auto& item : items) {
        totalAmount += item->getTotalPrice();
    }
}

Order::Order(const std::string& orderId, const std::string& orderDate, const std::string& notes)
    : status(OrderStatus::Status::PENDING, orderDate) {
    if (!isValidOrderId(orderId)) {
        throw DataValidationException("Invalid order ID: " + orderId);
    }
    if (!isValidOrderDate(orderDate)) {
        throw DataValidationException("Invalid order date: " + orderDate);
    }
    if (!isValidNotes(notes)) {
        throw DataValidationException("Invalid notes length");
    }
    this->orderId = orderId;
    this->orderDate = orderDate;
    this->notes = notes;
    this->totalAmount = 0.0;
}

std::string Order::getOrderId() const noexcept {
    return orderId;
}

std::string Order::getOrderDate() const noexcept {
    return orderDate;
}

OrderStatus Order::getStatus() const noexcept {
    return status;
}

double Order::getTotalAmount() const noexcept {
    return totalAmount;
}

std::string Order::getNotes() const noexcept {
    return notes;
}

std::vector<std::shared_ptr<OrderItem>> Order::getItems() const noexcept {
    return items;
}

void Order::setStatus(OrderStatus::Status newStatus, const std::string& changeDate) {
    status.updateStatus(newStatus, changeDate);
}

void Order::setNotes(const std::string& notes) {
    if (!isValidNotes(notes)) {
        throw DataValidationException("Invalid notes length");
    }
    this->notes = notes;
}

void Order::addItem(std::shared_ptr<OrderItem> item) {
    if (!item) {
        throw DataValidationException("Order item cannot be null");
    }
    std::string bookIsbn = item->getBook()->getISBN().getCode();
    for (const auto& existingItem : items) {
        if (existingItem->getBook()->getISBN().getCode() == bookIsbn) {
            throw DuplicateBookException("Book already exists in order: " + bookIsbn);
        }
    }
    items.push_back(item);
    recalculateTotalAmount();
}

void Order::removeItem(std::shared_ptr<OrderItem> item) {
    if (!item) {
        throw DataValidationException("Order item cannot be null");
    }
    auto it = std::find(items.begin(), items.end(), item);
    if (it == items.end()) {
        throw BookNotFoundException("Order item not found in order");
    }
    items.erase(it);
    recalculateTotalAmount();
}

size_t Order::getItemCount() const noexcept {
    return items.size();
}

bool Order::containsBook(const std::string& bookIsbn) const noexcept {
    for (const auto& item : items) {
        if (item->getBook()->getISBN().getCode() == bookIsbn) {
            return true;
        }
    }
    return false;
}

int Order::getBookQuantity(const std::string& bookIsbn) const noexcept {
    for (const auto& item : items) {
        if (item->getBook()->getISBN().getCode() == bookIsbn) {
            return item->getQuantity();
        }
    }
    return 0;
}

bool Order::isEmpty() const noexcept {
    return items.empty();
}

bool Order::isCompleted() const noexcept {
    return status.isCompleted();
}

bool Order::isCancellable() const noexcept {
    return status.isCancellable();
}

void Order::cancelOrder(const std::string& cancelDate) {
    if (!isCancellable()) {
        throw InvalidOrderStateException("Order cannot be cancelled in current state: " + status.toString());
    }
    status.updateStatus(OrderStatus::Status::CANCELLED, cancelDate);
}

double Order::getTotalDiscount() const noexcept {
    double totalDiscount = 0.0;
    for (const auto& item : items) {
        totalDiscount += item->getTotalDiscount();
    }
    return totalDiscount;
}

std::string Order::getInfo() const noexcept {
    return "Order ID: " + orderId + 
           ", Date: " + orderDate + 
           ", Status: " + status.toString() + 
           ", Items: " + std::to_string(getItemCount()) + 
           ", Total: " + std::to_string(totalAmount);
}

bool Order::operator==(const Order& other) const noexcept {
    return orderId == other.orderId;
}

bool Order::operator!=(const Order& other) const noexcept {
    return !(*this == other);
}