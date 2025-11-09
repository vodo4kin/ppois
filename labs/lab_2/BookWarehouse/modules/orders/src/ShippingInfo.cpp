#include "ShippingInfo.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"

bool ShippingInfo::isValidTrackingNumber(const std::string& trackingNumber) const {
    return !trackingNumber.empty() && trackingNumber.length() <= 50 && StringValidation::isValidName(trackingNumber);
}

bool ShippingInfo::isValidCarrier(const std::string& carrier) const {
    return StringValidation::isValidName(carrier, 50);
}

bool ShippingInfo::isValidShippingCost(double cost) const {
    return cost >= 0.0 && cost <= OrderConfig::ShippingInfo::MAX_SHIPPING_COST;
}

bool ShippingInfo::isValidInsuranceCost(double cost) const {
    return cost >= 0.0 && cost <= OrderConfig::ShippingInfo::MAX_INSURANCE_COST;
}

ShippingInfo::ShippingInfo(std::shared_ptr<Address> shippingAddress, std::shared_ptr<Address> returnAddress,
                           ShippingMethod method, const std::string& trackingNumber, const std::string& carrier,
                           double shippingCost, double insuranceCost, const std::string& estimatedDelivery) {
    if (!shippingAddress) {
        throw DataValidationException("Shipping address cannot be null");
    }
    if (!returnAddress) {
        throw DataValidationException("Return address cannot be null");
    }
    if (!isValidTrackingNumber(trackingNumber)) {
        throw DataValidationException("Invalid tracking number: " + trackingNumber);
    }
    if (!isValidCarrier(carrier)) {
        throw DataValidationException("Invalid carrier: " + carrier);
    }
    if (!isValidShippingCost(shippingCost)) {
        throw DataValidationException("Invalid shipping cost: " + std::to_string(shippingCost));
    }
    if (!isValidInsuranceCost(insuranceCost)) {
        throw DataValidationException("Invalid insurance cost: " + std::to_string(insuranceCost));
    }
    if (!estimatedDelivery.empty() && !StringValidation::isValidDate(estimatedDelivery)) {
        throw DataValidationException("Invalid estimated delivery date: " + estimatedDelivery);
    }
    this->shippingAddress = shippingAddress;
    this->returnAddress = returnAddress;
    this->method = method;
    this->trackingNumber = trackingNumber;
    this->carrier = carrier;
    this->shippingCost = shippingCost;
    this->insuranceCost = insuranceCost;
    this->estimatedDelivery = estimatedDelivery;
    this->status = ShippingStatus::PENDING;
    this->actualDelivery = "";
}

std::shared_ptr<Address> ShippingInfo::getShippingAddress() const noexcept {
    return shippingAddress;
}

std::shared_ptr<Address> ShippingInfo::getReturnAddress() const noexcept {
    return returnAddress;
}

ShippingInfo::ShippingMethod ShippingInfo::getMethod() const noexcept {
    return method;
}

ShippingInfo::ShippingStatus ShippingInfo::getStatus() const noexcept {
    return status;
}

std::string ShippingInfo::getTrackingNumber() const noexcept {
    return trackingNumber;
}

std::string ShippingInfo::getCarrier() const noexcept {
    return carrier;
}

double ShippingInfo::getShippingCost() const noexcept {
    return shippingCost;
}

double ShippingInfo::getInsuranceCost() const noexcept {
    return insuranceCost;
}

std::string ShippingInfo::getEstimatedDelivery() const noexcept {
    return estimatedDelivery;
}

std::string ShippingInfo::getActualDelivery() const noexcept {
    return actualDelivery;
}

void ShippingInfo::setStatus(ShippingStatus status) noexcept {
    this->status = status;
}

void ShippingInfo::setTrackingNumber(const std::string& trackingNumber) {
    if (!isValidTrackingNumber(trackingNumber)) {
        throw DataValidationException("Invalid tracking number: " + trackingNumber);
    }
    this->trackingNumber = trackingNumber;
}

void ShippingInfo::setActualDelivery(const std::string& deliveryDate) {
    if (!StringValidation::isValidDate(deliveryDate)) {
        throw DataValidationException("Invalid delivery date: " + deliveryDate);
    }
    this->actualDelivery = deliveryDate;
    this->status = ShippingStatus::DELIVERED;
}

double ShippingInfo::getTotalShippingCost() const noexcept {
    return shippingCost + insuranceCost;
}

bool ShippingInfo::isDelivered() const noexcept {
    return status == ShippingStatus::DELIVERED;
}

bool ShippingInfo::isInTransit() const noexcept {
    return status == ShippingStatus::IN_TRANSIT || status == ShippingStatus::OUT_FOR_DELIVERY;
}

bool ShippingInfo::requiresSignature() const noexcept {
    return method == ShippingMethod::EXPRESS || method == ShippingMethod::OVERNIGHT || 
           method == ShippingMethod::INTERNATIONAL || insuranceCost > 
           OrderConfig::ShippingInfo::SIGNATURE_THRESHOLD;
}

std::string ShippingInfo::getMethodString() const noexcept {
    switch(method) {
        case ShippingMethod::STANDARD: return "Standard";
        case ShippingMethod::EXPEDITED: return "Expedited";
        case ShippingMethod::EXPRESS: return "Express";
        case ShippingMethod::OVERNIGHT: return "Overnight";
        case ShippingMethod::INTERNATIONAL: return "International";
        default: return "Unknown";
    }
}

std::string ShippingInfo::getStatusString() const noexcept {
    switch(status) {
        case ShippingStatus::PENDING: return "Pending";
        case ShippingStatus::LABEL_CREATED: return "Label Created";
        case ShippingStatus::PICKED_UP: return "Picked Up";
        case ShippingStatus::IN_TRANSIT: return "In Transit";
        case ShippingStatus::OUT_FOR_DELIVERY: return "Out for Delivery";
        case ShippingStatus::DELIVERED: return "Delivered";
        case ShippingStatus::FAILED: return "Failed";
        case ShippingStatus::RETURNED: return "Returned";
        default: return "Unknown";
    }
}

std::string ShippingInfo::getInfo() const noexcept {
    return "Method: " + getMethodString() + 
           ", Carrier: " + carrier +
           ", Tracking: " + trackingNumber +
           ", Status: " + getStatusString() +
           ", Total Cost: " + std::to_string(getTotalShippingCost());
}

bool ShippingInfo::operator==(const ShippingInfo& other) const noexcept {
    return trackingNumber == other.trackingNumber && 
           carrier == other.carrier && 
           method == other.method && 
           status == other.status;
}

bool ShippingInfo::operator!=(const ShippingInfo& other) const noexcept {
    return !(*this == other);
}