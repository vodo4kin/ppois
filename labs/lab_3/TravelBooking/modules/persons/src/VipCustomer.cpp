#include "VipCustomer.hpp"
#include "configs/PersonsConfig.hpp"
#include "exceptions/TravelBookingExceptions.hpp"

VipCustomer::VipCustomer(const std::string& name, const std::string& email, 
                         const std::string& password, const std::string& birthDate)
    : Customer(name, email, password, birthDate), loyaltyPoints(0.0), vipTier(Tier::SILVER) {}

std::string VipCustomer::getUserRole() const {
    return "VIP Customer";
}

void VipCustomer::addLoyaltyPoints(double points) noexcept {
    if (points > 0) {
        loyaltyPoints += points;
        updateVIPTier();
    }
}

double VipCustomer::getLoyaltyPoints() const noexcept {
    return loyaltyPoints;
}

bool VipCustomer::useLoyaltyPoints(double points) {
    if (points <= 0 || points > loyaltyPoints) {
        return false;
    }
    loyaltyPoints -= points;
    updateVIPTier();
    return true;
}

std::string VipCustomer::getVIPTierStr() const noexcept {
    switch (vipTier) {
        case Tier::SILVER: return "SILVER";
        case Tier::GOLD: return "GOLD";
        case Tier::PLATINUM: return "PLATINUM";
        default: return "UNKNOWN";
    }
}

VipCustomer::Tier VipCustomer::getVIPTier() const noexcept {
    return vipTier;
}

std::string VipCustomer::getLoyaltyStatus() const noexcept {
    return getVIPTierStr() + " Tier - " + std::to_string(static_cast<int>(loyaltyPoints)) + " points";
}

void VipCustomer::updateVIPTier() {
    if (loyaltyPoints >= PersonsConfig::VipCustomer::PLATINUM_THRESHOLD) {
        vipTier = Tier::PLATINUM;
    } else if (loyaltyPoints >= PersonsConfig::VipCustomer::GOLD_THRESHOLD) {
        vipTier = Tier::GOLD;
    } else {
        vipTier = Tier::SILVER;
    }
}

double VipCustomer::calculateDiscount() const noexcept {
    switch (vipTier) {
        case Tier::PLATINUM: return PersonsConfig::VipCustomer::PLATINUM_DISCOUNT;
        case Tier::GOLD: return PersonsConfig::VipCustomer::GOLD_DISCOUNT;
        case Tier::SILVER: return PersonsConfig::VipCustomer::SILVER_DISCOUNT;
        default: return 0.0;
    }
}

bool VipCustomer::isEligibleForPremiumSupport() const noexcept {
    return vipTier == Tier::GOLD || vipTier == Tier::PLATINUM;
}

bool VipCustomer::hasFreeCancellation() const noexcept {
    return vipTier == Tier::PLATINUM;
}

void VipCustomer::addBooking(const std::weak_ptr<Booking>& booking) {
    auto sharedBooking = booking.lock();
    if (!sharedBooking) {
        throw InvalidDataException("booking", "cannot be null or expired");
    }
    Customer::addBooking(booking);
    double pointsEarned = sharedBooking->getTotalPrice() * PersonsConfig::VipCustomer::POINTS_EARN_RATE;
    addLoyaltyPoints(pointsEarned);
}

std::string VipCustomer::getCustomerInfo() const noexcept {
    std::string info = Customer::getCustomerInfo();
    size_t rolePos = info.find("Role: Customer");
    if (rolePos != std::string::npos) {
        info.replace(rolePos, 14, "Role: VIP Customer");
    }
    info += "\n--- VIP Benefits ---\n";
    info += "VIP Tier: " + getVIPTierStr() + "\n";
    info += "Loyalty Points: " + std::to_string(static_cast<int>(loyaltyPoints)) + "\n";
    info += "Current Discount: " + std::to_string(static_cast<int>(calculateDiscount() * 100)) + "%\n";
    info += "Premium Support: " + std::string(isEligibleForPremiumSupport() ? "Yes" : "No") + "\n";
    info += "Free Cancellation: " + std::string(hasFreeCancellation() ? "Yes" : "No");
    return info;
}