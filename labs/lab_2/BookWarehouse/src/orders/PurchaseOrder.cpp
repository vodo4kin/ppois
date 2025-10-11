#include "orders/PurchaseOrder.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"

bool PurchaseOrder::isValidSupplierName(const std::string& supplierName) const {
    return StringValidation::isValidName(supplierName, OrderConfig::PurchaseOrder::MAX_SUPPLIER_NAME_LENGTH);
}

bool PurchaseOrder::isValidSupplierContact(const std::string& contact) const {
    return StringValidation::isValidName(contact, OrderConfig::PurchaseOrder::MAX_SUPPLIER_CONTACT_LENGTH);
}

bool PurchaseOrder::isValidShippingCost(double cost) const {
    return cost >= 0.0 && cost <= 10000.0;
}

PurchaseOrder::PurchaseOrder(const std::string& orderId, const std::string& orderDate,
                             const std::string& supplierName, const std::string& supplierContact,
                             const std::string& expectedDeliveryDate, double shippingCost,
                             const std::string& notes)
    : Order(orderId, orderDate, notes) {
    if (!isValidSupplierName(supplierName)) {
        throw DataValidationException("Invalid supplier name: " + supplierName);
    }
    if (!isValidSupplierContact(supplierContact)) {
        throw DataValidationException("Invalid supplier contact: " + supplierContact);
    }
    if (!expectedDeliveryDate.empty() && !StringValidation::isValidDate(expectedDeliveryDate)) {
        throw DataValidationException("Invalid expected delivery date: " + expectedDeliveryDate);
    }
    if (!isValidShippingCost(shippingCost)) {
        throw DataValidationException("Invalid shipping cost: " + std::to_string(shippingCost));
    }
    this->supplierName = supplierName;
    this->supplierContact = supplierContact;
    this->expectedDeliveryDate = expectedDeliveryDate;
    this->shippingCost = shippingCost;
    this->actualDeliveryDate = "";
    this->isReceived = false;
}

std::string PurchaseOrder::getSupplierName() const noexcept {
    return supplierName;
}

std::string PurchaseOrder::getSupplierContact() const noexcept {
    return supplierContact;
}

std::string PurchaseOrder::getExpectedDeliveryDate() const noexcept {
    return expectedDeliveryDate;
}

std::string PurchaseOrder::getActualDeliveryDate() const noexcept {
    return actualDeliveryDate;
}

double PurchaseOrder::getShippingCost() const noexcept {
    return shippingCost;
}

bool PurchaseOrder::isOrReceived() const noexcept {
    return isReceived;
}

void PurchaseOrder::setSupplierContact(const std::string& contact) {
    if (!isValidSupplierContact(contact)) {
        throw DataValidationException("Invalid supplier contact: " + contact);
    }
    this->supplierContact = contact;
}

void PurchaseOrder::setExpectedDeliveryDate(const std::string& deliveryDate) {
    if (!deliveryDate.empty() && !StringValidation::isValidDate(deliveryDate)) {
        throw DataValidationException("Invalid expected delivery date: " + deliveryDate);
    }
    this->expectedDeliveryDate = deliveryDate;
}

void PurchaseOrder::setShippingCost(double cost) {
    if (!isValidShippingCost(cost)) {
        throw DataValidationException("Invalid shipping cost: " + std::to_string(cost));
    }
    this->shippingCost = cost;
}

double PurchaseOrder::getTotalCost() const noexcept {
    return getTotalAmount() + shippingCost;
}

bool PurchaseOrder::isOverdue() const {
    if (isReceived || expectedDeliveryDate.empty()) {
        return false;
    }
    
    std::string currentDate = DateUtils::getCurrentDate();
    return currentDate > expectedDeliveryDate;
}

void PurchaseOrder::receiveOrder(const std::string& deliveryDate) {
    if (!canBeReceived()) {
        throw InvalidOrderStateException("Purchase order cannot be received in current state: " + getStatus().toString());
    }
    if (!StringValidation::isValidDate(deliveryDate)) {
        throw DataValidationException("Invalid delivery date: " + deliveryDate);
    }
    actualDeliveryDate = deliveryDate;
    isReceived = true;
    setStatus(OrderStatus::Status::DELIVERED, deliveryDate);
}

bool PurchaseOrder::canBeReceived() const noexcept {
    return !isReceived && 
           (getStatus().getStatus() == OrderStatus::Status::CONFIRMED || 
            getStatus().getStatus() == OrderStatus::Status::PROCESSING ||
            getStatus().getStatus() == OrderStatus::Status::SHIPPED);
}

std::string PurchaseOrder::getInfo() const noexcept {
    std::string info = Order::getInfo();
    info += ", Supplier: " + supplierName;
    info += ", Total Cost: " + std::to_string(getTotalCost());
    info += ", Received: " + std::string(isReceived ? "Yes" : "No");
    if (isOverdue()) {
        info += " (OVERDUE)";
    }
    return info;
}

bool PurchaseOrder::operator==(const PurchaseOrder& other) const noexcept {
    return Order::operator==(other) && supplierName == other.supplierName;
}

bool PurchaseOrder::operator!=(const PurchaseOrder& other) const noexcept {
    return !(*this == other);
}