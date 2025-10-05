#include "warehouse/InventoryItem.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/WarehouseConfig.hpp"
#include "utils/Utils.hpp"

bool InventoryItem::isValidQuantity(int quantity) const {
    return quantity >= WarehouseConfig::InventoryItem::MIN_QUANTITY && 
           quantity <= WarehouseConfig::InventoryItem::MAX_QUANTITY;
}

bool InventoryItem::isValidDate(const std::string& date) const {
    return StringValidation::isValidDate(date);
}

InventoryItem::InventoryItem(std::shared_ptr<Book> book, int quantity,
                           std::shared_ptr<StorageLocation> location, 
                           const std::string& dateAdded) {
    if (!book) {
        throw DataValidationException("Book cannot be null in InventoryItem");
    }
    if (!isValidQuantity(quantity)) {
        throw DataValidationException("Invalid quantity: " + std::to_string(quantity));
    }
    if (!location) {
        throw DataValidationException("Storage location cannot be null in InventoryItem");
    }
    if (!isValidDate(dateAdded)) {
        throw DataValidationException("Invalid date format: " + dateAdded);
    }
    
    this->book = book;
    this->quantity = quantity;
    this->location = location;
    this->dateAdded = dateAdded;
}

std::shared_ptr<Book> InventoryItem::getBook() const noexcept {
    return book;
}

int InventoryItem::getQuantity() const noexcept {
    return quantity;
}

std::shared_ptr<StorageLocation> InventoryItem::getLocation() const noexcept {
    return location;
}

std::string InventoryItem::getDateAdded() const noexcept {
    return dateAdded;
}

void InventoryItem::setQuantity(int quantity) {
    if (!isValidQuantity(quantity)) {
        throw DataValidationException("Invalid quantity: " + std::to_string(quantity));
    }
    this->quantity = quantity;
}

void InventoryItem::setLocation(std::shared_ptr<StorageLocation> location) {
    if (!location) {
        throw DataValidationException("Storage location cannot be null");
    }
    this->location = location;
}

void InventoryItem::increaseQuantity(int amount) {
    if (amount < 0) {
        throw DataValidationException("Increase amount cannot be negative: " + std::to_string(amount));
    }
    int newQuantity = quantity + amount;
    if (!isValidQuantity(newQuantity)) {
        throw DataValidationException("Quantity would exceed maximum: " + std::to_string(newQuantity));
    }
    quantity = newQuantity;
}

void InventoryItem::decreaseQuantity(int amount) {
    if (amount < 0) {
        throw DataValidationException("Decrease amount cannot be negative: " + std::to_string(amount));
    }
    if (amount > quantity) {
        throw WarehouseException("Cannot decrease quantity by " + std::to_string(amount) + 
                               " (current: " + std::to_string(quantity) + ")");
    }
    quantity -= amount;
}

bool InventoryItem::isInStock() const noexcept {
    return quantity > 0;
}

std::string InventoryItem::getInfo() const noexcept {
    return "Book: " + book->getTitle().getFullTitle() + 
           " | Quantity: " + std::to_string(quantity) +
           " | Location: " + location->getLocationId() +
           " | Date Added: " + (dateAdded.empty() ? "N/A" : dateAdded);
}

bool InventoryItem::operator==(const InventoryItem& other) const noexcept {
    return book == other.book &&
           quantity == other.quantity &&
           location == other.location &&
           dateAdded == other.dateAdded;
}

bool InventoryItem::operator!=(const InventoryItem& other) const noexcept {
    return !(*this == other);
}