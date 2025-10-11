#include "persons/Customer.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/PersonConfig.hpp"

bool Customer::isValidCustomerId(const std::string& customerId) const {
    return !customerId.empty() && customerId.length() <= PersonConfig::Customer::MAX_CUSTOMER_ID_LENGTH 
    && StringValidation::isValidName(customerId);
}

bool Customer::isValidPurchaseAmount(double amount) const {
    return amount >= 0.0;
}

bool Customer::isValidLoyaltyPoints(int points) const {
    return points >= 0;
}

Customer::Customer(const std::string& personId, const std::string& firstName, const std::string& lastName,
                   const std::string& dateOfBirth, std::shared_ptr<Address> address,
                   std::shared_ptr<ContactInfo> contactInfo, const std::string& customerId,
                   CustomerCategory category, const std::string& registrationDate)
    : Person(personId, firstName, lastName, dateOfBirth, address, contactInfo),
      category(category){
    if (!isValidCustomerId(customerId)) {
        throw DataValidationException("Invalid customer ID: " + customerId);
    }
    if (!StringValidation::isValidDate(registrationDate)) {
        throw DataValidationException("Invalid registration date: " + registrationDate);
    }
    
    this->customerId = customerId;
    this->registrationDate = registrationDate;
    this->totalPurchases = 0.0;
    this->loyaltyPoints = 0;
    this->isActive = true;
}

std::string Customer::getCustomerId() const noexcept {
    return customerId;
}

CustomerCategory Customer::getCategory() const noexcept {
    return category;
}

double Customer::getTotalPurchases() const noexcept {
    return totalPurchases;
}

int Customer::getLoyaltyPoints() const noexcept {
    return loyaltyPoints;
}

std::string Customer::getRegistrationDate() const noexcept {
    return registrationDate;
}

bool Customer::isCustActive() const noexcept {
    return isActive;
}

void Customer::setCategory(CustomerCategory category) noexcept {
    this->category = category;
}

void Customer::setActive(bool active) noexcept {
    this->isActive = active;
}

void Customer::addPurchase(double amount) {
    if (!isValidPurchaseAmount(amount)) {
        throw DataValidationException("Invalid purchase amount: " + std::to_string(amount));
    }
    totalPurchases += amount;
    int pointsEarned = static_cast<int>(amount);
    addLoyaltyPoints(pointsEarned);
}

void Customer::addLoyaltyPoints(int points) {
    if (!isValidLoyaltyPoints(points)) {
        throw DataValidationException("Invalid loyalty points: " + std::to_string(points));
    }
    
    loyaltyPoints += points;
}

void Customer::redeemLoyaltyPoints(int points) {
    if (!isValidLoyaltyPoints(points)) {
        throw DataValidationException("Invalid loyalty points to redeem: " + std::to_string(points));
    }
    if (points > loyaltyPoints) {
        throw InsufficientStockException("Not enough loyalty points to redeem");
    }
    
    loyaltyPoints -= points;
}

double Customer::calculateDiscount() const noexcept {
    return category.getDiscountPercentage();
}

bool Customer::isEligibleForUpgrade() const noexcept {
    return category.canUpgrade(totalPurchases);
}

void Customer::upgradeCategory() {
    if (isEligibleForUpgrade()) {
        CustomerCategory::Category nextCategory = category.getNextCategory();
        category = CustomerCategory(nextCategory);
    }
}

std::string Customer::getInfo() const noexcept {
    std::string info = Person::getInfo();
    info += ", Customer ID: " + customerId;
    info += ", Category: " + category.toString();
    info += ", Total Purchases: " + std::to_string(totalPurchases);
    info += ", Loyalty Points: " + std::to_string(loyaltyPoints);
    info += ", Active: " + std::string(isActive ? "Yes" : "No");
    return info;
}

bool Customer::operator==(const Customer& other) const noexcept {
    return customerId == other.customerId;
}

bool Customer::operator!=(const Customer& other) const noexcept {
    return !(*this == other);
}