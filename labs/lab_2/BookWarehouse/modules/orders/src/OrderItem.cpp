#include "OrderItem.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"

bool OrderItem::isValidQuantity(int quantity) const {
    return quantity > 0 && quantity <= OrderConfig::OrderItem::MAX_QUANTITY;
}

bool OrderItem::isValidUnitPrice(double price) const {
    return price >= 0.0 && price <= OrderConfig::OrderItem::MAX_UNIT_PRICE;
}

bool OrderItem::isValidDiscount(double discount) const {
    return discount >= 0.0 && discount <= OrderConfig::OrderItem::MAX_DISCOUNT_PERCENTAGE;
}

OrderItem::OrderItem(std::shared_ptr<Book> book, int quantity, double unitPrice, double discountPercentage) {
    if (!book) {
        throw DataValidationException("Book cannot be null");
    }
    if (!isValidQuantity(quantity)) {
        throw DataValidationException("Invalid quantity: " + std::to_string(quantity));
    }
    if (!isValidUnitPrice(unitPrice)) {
        throw DataValidationException("Invalid unit price: " + std::to_string(unitPrice));
    }
    if (!isValidDiscount(discountPercentage)) {
        throw DataValidationException("Invalid discount percentage: " + std::to_string(discountPercentage));
    }
    this->book = book;
    this->quantity = quantity;
    this->unitPrice = unitPrice;
    this->discountPercentage = discountPercentage;
}

std::shared_ptr<Book> OrderItem::getBook() const noexcept {
    return book;
}

int OrderItem::getQuantity() const noexcept {
    return quantity;
}

double OrderItem::getUnitPrice() const noexcept {
    return unitPrice;
}

double OrderItem::getDiscountPercentage() const noexcept {
    return discountPercentage;
}

void OrderItem::setQuantity(int quantity) {
    if (!isValidQuantity(quantity)) {
        throw DataValidationException("Invalid quantity: " + std::to_string(quantity));
    }
    this->quantity = quantity;
}

void OrderItem::setDiscountPercentage(double discount) {
    if (!isValidDiscount(discount)) {
        throw DataValidationException("Invalid discount percentage: " + std::to_string(discount));
    }
    this->discountPercentage = discount;
}

double OrderItem::getDiscountedUnitPrice() const noexcept {
    return unitPrice * (1.0 - discountPercentage / 100.0);
}

double OrderItem::getTotalPrice() const noexcept {
    return quantity * getDiscountedUnitPrice();
}

double OrderItem::getTotalDiscount() const noexcept {
    return quantity * (unitPrice - getDiscountedUnitPrice());
}

bool OrderItem::hasDiscount() const noexcept {
    return discountPercentage > 0.0;
}

void OrderItem::increaseQuantity(int amount) {
    if (amount <= 0) {
        throw DataValidationException("Increase amount must be positive: " + std::to_string(amount));
    }
    if (!isValidQuantity(quantity + amount)) {
        throw DataValidationException("Resulting quantity would be invalid");
    }
    quantity += amount;
}

void OrderItem::decreaseQuantity(int amount) {
    if (amount <= 0) {
        throw DataValidationException("Decrease amount must be positive: " + std::to_string(amount));
    }
    if (amount > quantity) {
        throw DataValidationException("Cannot decrease quantity below zero");
    }
    quantity -= amount;
}

std::string OrderItem::getInfo() const noexcept {
    return "Book: " + book->getTitle().getTitle() + 
           ", Quantity: " + std::to_string(quantity) +
           ", Unit Price: " + std::to_string(unitPrice) +
           ", Discount: " + std::to_string(discountPercentage) + "%" +
           ", Total: " + std::to_string(getTotalPrice());
}

bool OrderItem::operator==(const OrderItem& other) const noexcept {
    return book == other.book && 
           quantity == other.quantity && 
           unitPrice == other.unitPrice && 
           discountPercentage == other.discountPercentage;
}

bool OrderItem::operator!=(const OrderItem& other) const noexcept {
    return !(*this == other);
}