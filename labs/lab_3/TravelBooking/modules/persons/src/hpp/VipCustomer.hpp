/**
 * @file VipCustomer.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the VipCustomer class for VIP customer management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Customer.hpp"
#include "Booking.hpp"

/**
 * @class VipCustomer
 * @brief Class representing VIP customer type user
 * 
 * Extends Customer with VIP-specific properties like loyalty points and tiers.
 * Provides functionality for premium benefits and loyalty program management.
 */
class VipCustomer : public Customer {
private:
    double loyaltyPoints;                                   ///< Accumulated loyalty points
    
    /**
     * @enum Tier
     * @brief Enumeration of VIP tiers
     */
    enum class Tier {
        SILVER,                                             ///< Silver VIP tier
        GOLD,                                               ///< Gold VIP tier
        PLATINUM                                            ///< Platinum VIP tier
    } vipTier;                                              ///< Current VIP tier
    
    /**
     * @brief Update VIP tier based on loyalty points
     */
    void updateVIPTier();

public:
    /**
     * @brief Construct a new VipCustomer object
     * 
     * @param name constant reference to the string containing customer name
     * @param email constant reference to the string containing email address
     * @param password constant reference to the string containing password
     * @param birthDate constant reference to the string containing birth date
     */
    VipCustomer(const std::string& name, const std::string& email, 
                const std::string& password, const std::string& birthDate);
    
    /**
     * @brief Get the VIP customer role
     * 
     * @return std::string containing "VIP Customer"
     */
    std::string getUserRole() const override;
    
    /**
     * @brief Get comprehensive VIP customer information
     * 
     * @return std::string containing formatted VIP customer details
     */
    std::string getCustomerInfo() const noexcept override;
    
    /**
     * @brief Add loyalty points
     * 
     * @param points double value containing points to add
     */
    void addLoyaltyPoints(double points) noexcept;
    
    /**
     * @brief Get loyalty points
     * 
     * @return double containing current loyalty points
     */
    double getLoyaltyPoints() const noexcept;
    
    /**
     * @brief Use loyalty points for benefits
     * 
     * @param points double value containing points to use
     * 
     * @return true if points were used successfully
     * @return false if insufficient points
     */
    bool useLoyaltyPoints(double points);
    
    /**
     * @brief Get VIP tier as string
     * 
     * @return std::string containing VIP tier description
     */
    std::string getVIPTierStr() const noexcept;
    
    /**
     * @brief Get VIP tier
     * 
     * @return Tier containing VIP tier enum value
     */
    Tier getVIPTier() const noexcept;
    
    /**
     * @brief Get loyalty status
     * 
     * @return std::string containing loyalty status description
     */
    std::string getLoyaltyStatus() const noexcept;
    
    /**
     * @brief Calculate discount percentage
     * 
     * @return double containing discount percentage
     */
    double calculateDiscount() const noexcept;
    
    /**
     * @brief Check if eligible for premium support
     * 
     * @return true if eligible for premium support
     * @return false if not eligible for premium support
     */
    bool isEligibleForPremiumSupport() const noexcept;
    
    /**
     * @brief Check if has free cancellation privilege
     * 
     * @return true if free cancellation available
     * @return false if free cancellation not available
     */
    bool hasFreeCancellation() const noexcept;
    
    /**
     * @brief Add booking with VIP benefits
     * 
     * @param booking weak pointer to the Booking object to add
     */
    void addBooking(const std::weak_ptr<Booking>& booking) override;
};