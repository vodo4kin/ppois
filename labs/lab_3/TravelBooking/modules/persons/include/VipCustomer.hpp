#pragma once
#include "Customer.hpp"

class VipCustomer : public Customer {
private:
    double loyaltyPoints;
    enum class Tier {
        SILVER,
        GOLD,
        PLATINUM
    } vipTier;
    void updateVIPTier();
public:
    VipCustomer(const std::string& name, const std::string& email, 
                const std::string& password, const std::string& birthDate);
    std::string getUserRole() const override;
    std::string getCustomerInfo() const noexcept override;
    void addLoyaltyPoints(double points) noexcept;
    double getLoyaltyPoints() const noexcept;
    bool useLoyaltyPoints(double points);
    std::string getVIPTierStr() const noexcept;
    Tier getVIPTier() const noexcept;
    std::string getLoyaltyStatus() const noexcept;
    double calculateDiscount() const noexcept;
    bool isEligibleForPremiumSupport() const noexcept;
    bool hasFreeCancellation() const noexcept;
    void addBooking(const std::weak_ptr<Booking>& booking) override;
};