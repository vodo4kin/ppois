#include "orders/CustomerOrder.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"

bool CustomerOrder::isValidCustomerDiscount(double discount) const {
    return discount >= 0.0 && discount <= OrderConfig::CustomerOrder::MAX_CUSTOMER_DISCOUNT;
}

bool CustomerOrder::isValidTaxAmount(double tax) const {
    return tax >= 0.0 && tax <= getTotalAmount() * OrderConfig::CustomerOrder::MAX_TAX_RATIO;
}

void CustomerOrder::recalculateFinalAmount() {
    double subtotal = getTotalAmount();
    double discountAmount = subtotal * (customerDiscount / 100.0);
    double amountAfterDiscount = subtotal - discountAmount;
    finalAmount = amountAfterDiscount + taxAmount;
}

CustomerOrder::CustomerOrder(const std::string& orderId, const std::string& orderDate,
                             std::shared_ptr<Customer> customer, std::shared_ptr<ShippingInfo> shipping,
                             const std::string& notes)
    : Order(orderId, orderDate, notes) {
    
    if (!customer) {
        throw DataValidationException("Customer cannot be null");
    }
    if (!shipping) {
        throw DataValidationException("Shipping info cannot be null");
    }
    this->customer = customer;
    this->shipping = shipping;
    this->customerDiscount = customer->calculateDiscount();
    this->taxAmount = 0.0;
    recalculateFinalAmount();
}

std::shared_ptr<Customer> CustomerOrder::getCustomer() const noexcept {
    return customer;
}

std::shared_ptr<ShippingInfo> CustomerOrder::getShippingInfo() const noexcept {
    return shipping;
}

double CustomerOrder::getCustomerDiscount() const noexcept {
    return customerDiscount;
}

double CustomerOrder::getTaxAmount() const noexcept {
    return taxAmount;
}

double CustomerOrder::getFinalAmount() const noexcept {
    return finalAmount;
}

void CustomerOrder::setShippingInfo(std::shared_ptr<ShippingInfo> shipping) {
    if (!shipping) {
        throw DataValidationException("Shipping info cannot be null");
    }
    this->shipping = shipping;
    recalculateFinalAmount();
}

void CustomerOrder::setCustomerDiscount(double discount) {
    if (!isValidCustomerDiscount(discount)) {
        throw DataValidationException("Invalid customer discount: " + std::to_string(discount));
    }
    this->customerDiscount = discount;
    recalculateFinalAmount();
}

void CustomerOrder::setTaxAmount(double tax) {
    if (!isValidTaxAmount(tax)) {
        throw DataValidationException("Invalid tax amount: " + std::to_string(tax));
    }
    this->taxAmount = tax;
    recalculateFinalAmount();
}

double CustomerOrder::getTotalWithShipping() const noexcept {
    return finalAmount + (qualifiesForFreeShipping() ? 0.0 : shipping->getTotalShippingCost());
}

void CustomerOrder::applyCustomerCategoryDiscount() {
    customerDiscount = customer->calculateDiscount();
    recalculateFinalAmount();
}

bool CustomerOrder::qualifiesForFreeShipping() const noexcept {
    return customer->getCategory().hasFreeShipping() || getTotalAmount() >= 
    OrderConfig::CustomerOrder::FREE_SHIPPING_THRESHOLD;
}

void CustomerOrder::processPayment(const std::string& paymentDate) {
    if (!StringValidation::isValidDate(paymentDate)) {
        throw DataValidationException("Invalid payment date: " + paymentDate);
    }
    if (getStatus().getStatus() != OrderStatus::Status::PENDING && 
        getStatus().getStatus() != OrderStatus::Status::CONFIRMED) {
        throw InvalidOrderStateException("Order cannot be paid in current state: " + getStatus().toString());
    }
    setStatus(OrderStatus::Status::CONFIRMED, paymentDate);
    customer->addPurchase(getFinalAmount());
}

void CustomerOrder::shipOrder(const std::string& shipDate) {
    if (!StringValidation::isValidDate(shipDate)) {
        throw DataValidationException("Invalid ship date: " + shipDate);
    }
    if (getStatus().getStatus() != OrderStatus::Status::PROCESSING && 
        getStatus().getStatus() != OrderStatus::Status::READY_FOR_SHIPPING) {
        throw InvalidOrderStateException("Order cannot be shipped in current state: " + getStatus().toString());
    }
    setStatus(OrderStatus::Status::SHIPPED, shipDate);
    shipping->setStatus(ShippingInfo::ShippingStatus::IN_TRANSIT);
}

void CustomerOrder::deliverOrder(const std::string& deliveryDate) {
    if (!StringValidation::isValidDate(deliveryDate)) {
        throw DataValidationException("Invalid delivery date: " + deliveryDate);
    }
    if (getStatus().getStatus() != OrderStatus::Status::SHIPPED) {
        throw InvalidOrderStateException("Order cannot be delivered in current state: " + getStatus().toString());
    }
    
    setStatus(OrderStatus::Status::DELIVERED, deliveryDate);
    shipping->setActualDelivery(deliveryDate);
}

std::string CustomerOrder::getInfo() const noexcept {
    std::string info = Order::getInfo();
    info += ", Customer: " + customer->getFullName();
    info += ", Final Amount: " + std::to_string(getFinalAmount());
    info += ", Shipping: " + shipping->getCarrier();
    if (qualifiesForFreeShipping()) {
        info += " (Free Shipping)";
    }
    return info;
}

bool CustomerOrder::operator==(const CustomerOrder& other) const noexcept {
    return Order::operator==(other) && customer == other.customer;
}

bool CustomerOrder::operator!=(const CustomerOrder& other) const noexcept {
    return !(*this == other);
}