/**
 * @file CustomerCategory.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with customer category enumeration and utilities
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class CustomerCategory
 * @brief Class for working with customer categories and loyalty levels
 * 
 * Defines customer categories with associated discounts and benefits.
 * Provides category validation, discount calculation, and status checking.
 */
class CustomerCategory {
public:
    /**
     * @enum Category
     * @brief Enumeration of customer categories
     */
    enum class Category {
        REGULAR,        ///< Regular customer with no special benefits
        SILVER,         ///< Silver level customer with basic benefits
        GOLD,           ///< Gold level customer with enhanced benefits  
        PLATINUM,       ///< Platinum level customer with premium benefits
        STUDENT,        ///< Student customer with educational discounts
        CORPORATE       ///< Corporate customer with business benefits
    };

private:
    Category category;  ///< Current customer category

public:
    /**
     * @brief Construct a new CustomerCategory object
     * 
     * @param category Category value containing customer category
     */
    explicit CustomerCategory(Category category) noexcept;

    /**
     * @brief Get the category
     * 
     * @return Category containing current customer category
     */
    Category getCategory() const noexcept;

    /**
     * @brief Convert category to string representation
     * 
     * @return std::string containing category description
     */
    std::string toString() const noexcept;

    /**
     * @brief Get discount percentage for the category
     * 
     * @return double containing discount percentage (0-100)
     */
    double getDiscountPercentage() const noexcept;

    /**
     * @brief Check if category has free shipping benefits
     * 
     * @return true if category has free shipping
     * @return false if category does not have free shipping
     */
    bool hasFreeShipping() const noexcept;

    /**
     * @brief Check if category has priority support
     * 
     * @return true if category has priority support
     * @return false if category does not have priority support
     */
    bool hasPrioritySupport() const noexcept;

    /**
     * @brief Check if category is eligible for loyalty program
     * 
     * @return true if category is eligible
     * @return false if category is not eligible
     */
    bool isEligibleForLoyaltyProgram() const noexcept;

    /**
     * @brief Get minimum purchase amount for category upgrade
     * 
     * @return double containing minimum purchase amount for upgrade
     */
    double getUpgradeThreshold() const noexcept;

    /**
     * @brief Check if category can be upgraded
     * 
     * @param totalPurchases double value containing total purchase amount
     * 
     * @return true if category can be upgraded
     * @return false if category cannot be upgraded
     */
    bool canUpgrade(double totalPurchases) const noexcept;

    /**
     * @brief Get next category in hierarchy
     * 
     * @return Category containing next category or current if at highest level
     */
    Category getNextCategory() const noexcept;

    /**
     * @brief Equality comparison operator for customer categories
     * 
     * @param other constant reference to the customer category to compare with
     * 
     * @return true if customer categories are equal
     * @return false if customer categories are not equal
     */
    bool operator==(const CustomerCategory& other) const noexcept;

    /**
     * @brief Inequality comparison operator for customer categories
     * 
     * @param other constant reference to the customer category to compare with
     * 
     * @return true if customer categories are not equal
     * @return false if customer categories are equal
     */
    bool operator!=(const CustomerCategory& other) const noexcept;
};