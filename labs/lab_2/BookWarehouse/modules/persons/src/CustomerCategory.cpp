#include "CustomerCategory.hpp"

CustomerCategory::CustomerCategory(Category category) noexcept : category(category) {}

CustomerCategory::Category CustomerCategory::getCategory() const noexcept {
    return category;
}

std::string CustomerCategory::toString() const noexcept {
    switch(category) {
        case Category::REGULAR: return "Regular";
        case Category::SILVER: return "Silver";
        case Category::GOLD: return "Gold";
        case Category::PLATINUM: return "Platinum";
        case Category::STUDENT: return "Student";
        case Category::CORPORATE: return "Corporate";
        default: return "Unknown";
    }
}

double CustomerCategory::getDiscountPercentage() const noexcept {
    switch(category) {
        case Category::REGULAR: return 0.0;
        case Category::SILVER: return 5.0;
        case Category::GOLD: return 10.0;
        case Category::PLATINUM: return 15.0;
        case Category::STUDENT: return 10.0;
        case Category::CORPORATE: return 12.0;
        default: return 0.0;
    }
}

bool CustomerCategory::hasFreeShipping() const noexcept {
    return category == Category::GOLD || category == Category::PLATINUM || category == Category::CORPORATE;
}

bool CustomerCategory::hasPrioritySupport() const noexcept {
    return category == Category::PLATINUM || category == Category::CORPORATE;
}

bool CustomerCategory::isEligibleForLoyaltyProgram() const noexcept {
    return category != Category::REGULAR;
}

double CustomerCategory::getUpgradeThreshold() const noexcept {
    switch(category) {
        case Category::REGULAR: return 1000.0;
        case Category::SILVER: return 5000.0;
        case Category::GOLD: return 15000.0;
        case Category::PLATINUM: return 50000.0;
        case Category::STUDENT: return 2000.0;
        case Category::CORPORATE: return 100000.0;
        default: return 0.0;
    }
}

bool CustomerCategory::canUpgrade(double totalPurchases) const noexcept {
    return totalPurchases >= getUpgradeThreshold();
}

CustomerCategory::Category CustomerCategory::getNextCategory() const noexcept {
    switch(category) {
        case Category::REGULAR: return Category::SILVER;
        case Category::SILVER: return Category::GOLD;
        case Category::GOLD: return Category::PLATINUM;
        case Category::STUDENT: return Category::GOLD;
        case Category::CORPORATE: return Category::PLATINUM;
        default: return category;
    }
}

bool CustomerCategory::operator==(const CustomerCategory& other) const noexcept {
    return category == other.category;
}

bool CustomerCategory::operator!=(const CustomerCategory& other) const noexcept {
    return !(*this == other);
}