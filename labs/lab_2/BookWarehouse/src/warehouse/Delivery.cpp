#include "warehouse/Delivery.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "utils/Utils.hpp"
#include <regex>

bool Delivery::isValidDeliveryId(const std::string& deliveryId) const {
    // "DEL-2025-001"
    std::regex pattern("^DEL-\\d{4}-\\d{3}$");
    return std::regex_match(deliveryId, pattern);
}

bool Delivery::isValidTrackingNumber(const std::string& trackingNumber) const {
    return !trackingNumber.empty() && trackingNumber.length() <= WarehouseConfig::DeliveryConfig::MAX_TRACKING_LENGTH;
}

bool Delivery::isValidShippingCost(double cost) const {
    return cost >= 0.0 && cost <= WarehouseConfig::DeliveryConfig::MAX_SHIPPING_COST;
}

Delivery::Delivery(const std::string& deliveryId, const std::string& supplierName,
                 const std::string& scheduledDate, const std::string& trackingNumber,
                 const std::string& carrier, double shippingCost) {
    
    if (!isValidDeliveryId(deliveryId)) {
        throw DataValidationException("Invalid delivery ID format: " + deliveryId);
    }
    if (!StringValidation::isValidName(supplierName, WarehouseConfig::StockReceipt::MAX_SUPPLIER_NAME_LENGTH)) {
        throw DataValidationException("Invalid supplier name: " + supplierName);
    }
    if (!StringValidation::isValidDate(scheduledDate)) {
        throw DataValidationException("Invalid scheduled date: " + scheduledDate);
    }
    if (!isValidTrackingNumber(trackingNumber)) {
        throw DataValidationException("Invalid tracking number: " + trackingNumber);
    }
    if (!StringValidation::isValidName(carrier, WarehouseConfig::DeliveryConfig::MAX_CARRIER_LENGTH)) {
        throw DataValidationException("Invalid carrier: " + carrier);
    }
    if (!isValidShippingCost(shippingCost)) {
        throw DataValidationException("Invalid shipping cost: " + std::to_string(shippingCost));
    }
    this->deliveryId = deliveryId;
    this->supplierName = supplierName;
    this->scheduledDate = scheduledDate;
    this->trackingNumber = trackingNumber;
    this->carrier = carrier;
    this->shippingCost = shippingCost;
    this->status = DeliveryStatus::SCHEDULED;
    this->actualDate = "";
}

std::string Delivery::getDeliveryId() const noexcept {
    return deliveryId;
}

std::string Delivery::getSupplierName() const noexcept {
    return supplierName;
}

std::string Delivery::getScheduledDate() const noexcept {
    return scheduledDate;
}

std::string Delivery::getActualDate() const noexcept {
    return actualDate;
}

Delivery::DeliveryStatus Delivery::getStatus() const noexcept {
    return status;
}

std::string Delivery::getTrackingNumber() const noexcept {
    return trackingNumber;
}

std::string Delivery::getCarrier() const noexcept {
    return carrier;
}

double Delivery::getShippingCost() const noexcept {
    return shippingCost;
}

std::vector<std::shared_ptr<Book>> Delivery::getBooks() const noexcept {
    return books;
}

std::shared_ptr<StockReceipt> Delivery::getStockReceipt() const noexcept {
    return stockReceipt;
}

void Delivery::addBook(std::shared_ptr<Book> book) {
    if (!book) {
        throw DataValidationException("Cannot add null book to delivery");
    }
    if (containsBook(book)) {
        throw DataValidationException("Book already in delivery: " + book->getTitle().getFullTitle());
    }
    if (status != DeliveryStatus::SCHEDULED) {
        throw WarehouseException("Cannot add books to delivery that is not scheduled");
    }
    books.push_back(book);
}

void Delivery::removeBook(std::shared_ptr<Book> book) {
    if (!book) return;
    if (status != DeliveryStatus::SCHEDULED) {
        throw WarehouseException("Cannot remove books from delivery that is not scheduled");
    }
    auto it = std::find(books.begin(), books.end(), book);
    if (it != books.end()) {
        books.erase(it);
    }
}

void Delivery::setStatus(DeliveryStatus status) noexcept {
    this->status = status;
}

void Delivery::setActualDate(const std::string& date) {
    if (!StringValidation::isValidDate(date)) {
        throw DataValidationException("Invalid actual date: " + date);
    }
    this->actualDate = date;
}

void Delivery::setStockReceipt(std::shared_ptr<StockReceipt> receipt) {
    this->stockReceipt = receipt;
}

bool Delivery::containsBook(std::shared_ptr<Book> book) const noexcept {
    return std::find(books.begin(), books.end(), book) != books.end();
}

size_t Delivery::getBookCount() const noexcept {
    return books.size();
}

bool Delivery::isCompleted() const noexcept {
    return status == DeliveryStatus::COMPLETED;
}

bool Delivery::isInTransit() const noexcept {
    return status == DeliveryStatus::IN_TRANSIT;
}

bool Delivery::isDelayed() const noexcept {
    return status == DeliveryStatus::DELAYED;
}

void Delivery::processArrival() {
    if (status != DeliveryStatus::IN_TRANSIT && status != DeliveryStatus::DELAYED) {
        throw WarehouseException("Cannot process arrival for delivery that is not in transit or delayed");
    }
    status = DeliveryStatus::ARRIVED;
    actualDate = DateUtils::getCurrentDate();
}

void Delivery::completeDelivery() {
    if (status != DeliveryStatus::ARRIVED && status != DeliveryStatus::UNLOADING) {
        throw WarehouseException("Cannot complete delivery that has not arrived");
    }
    if (books.empty()) {
        throw WarehouseException("Cannot complete delivery with no books");
    }
    if (!stockReceipt) {
        throw WarehouseException("Stock receipt must be set before completing delivery. Use setStockReceipt() first.");
    }
    status = DeliveryStatus::COMPLETED;
}

std::string Delivery::getInfo() const noexcept {
    return "Delivery: " + deliveryId + 
           " | Supplier: " + supplierName +
           " | Status: " + getStatusString() +
           " | Scheduled: " + scheduledDate +
           " | Actual: " + (actualDate.empty() ? "N/A" : actualDate) +
           " | Books: " + std::to_string(books.size()) +
           " | Carrier: " + carrier +
           " | Tracking: " + trackingNumber +
           " | Cost: $" + std::to_string(shippingCost);
}

std::string Delivery::getStatusString() const noexcept {
    switch (status) {
        case DeliveryStatus::SCHEDULED: return "Scheduled";
        case DeliveryStatus::IN_TRANSIT: return "In Transit";
        case DeliveryStatus::ARRIVED: return "Arrived";
        case DeliveryStatus::UNLOADING: return "Unloading";
        case DeliveryStatus::COMPLETED: return "Completed";
        case DeliveryStatus::CANCELLED: return "Cancelled";
        case DeliveryStatus::DELAYED: return "Delayed";
        default: return "Unknown";
    }
}

bool Delivery::operator==(const Delivery& other) const noexcept {
    return deliveryId == other.deliveryId &&
           supplierName == other.supplierName &&
           books == other.books &&
           scheduledDate == other.scheduledDate &&
           actualDate == other.actualDate &&
           status == other.status &&
           trackingNumber == other.trackingNumber &&
           carrier == other.carrier &&
           shippingCost == other.shippingCost &&
           stockReceipt == other.stockReceipt;
}

bool Delivery::operator!=(const Delivery& other) const noexcept {
    return !(*this == other);
}