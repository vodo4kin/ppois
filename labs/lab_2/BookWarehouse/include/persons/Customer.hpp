/**
 * @file Customer.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Customer class for working with customers
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "persons/Person.hpp"
#include "persons/CustomerCategory.hpp"

/**
 * @class Customer
 * @brief Class for working with customers in the book warehouse system
 * 
 * Extends Person class with customer-specific functionality including
 * loyalty programs, purchase history, and customer category management.
 */
class Customer : public Person {
private:
    std::string customerId;                  ///< Unique customer identifier
    CustomerCategory category;               ///< Customer loyalty category
    double totalPurchases;                   ///< Total amount of purchases
    int loyaltyPoints;                       ///< Accumulated loyalty points
    std::string registrationDate;            ///< Date when customer registered
    bool isActive;                           ///< Customer account status

    /**
     * @brief Private method to validate customer ID
     * 
     * @param customerId constant reference to the string containing customer ID to validate
     * 
     * @return true if customer ID is valid
     * @return false if customer ID is invalid
     */
    bool isValidCustomerId(const std::string& customerId) const;

    /**
     * @brief Private method to validate purchase amount
     * 
     * @param amount double value containing purchase amount to validate
     * 
     * @return true if purchase amount is valid
     * @return false if purchase amount is invalid
     */
    bool isValidPurchaseAmount(double amount) const;

    /**
     * @brief Private method to validate loyalty points
     * 
     * @param points integer value containing loyalty points to validate
     * 
     * @return true if loyalty points are valid
     * @return false if loyalty points are invalid
     */
    bool isValidLoyaltyPoints(int points) const;

public:
    /**
     * @brief Construct a new Customer object
     * 
     * @param personId constant reference to the string containing person identifier
     * @param firstName constant reference to the string containing first name
     * @param lastName constant reference to the string containing last name
     * @param dateOfBirth constant reference to the string containing date of birth
     * @param address shared pointer to the Address object
     * @param contactInfo shared pointer to the ContactInfo object
     * @param customerId constant reference to the string containing customer identifier
     * @param category CustomerCategory value containing customer category
     * @param registrationDate constant reference to the string containing registration date
     */
    Customer(const std::string& personId, const std::string& firstName, const std::string& lastName,
             const std::string& dateOfBirth, std::shared_ptr<Address> address,
             std::shared_ptr<ContactInfo> contactInfo, const std::string& customerId,
             CustomerCategory category, const std::string& registrationDate);

    /**
     * @brief Get the customer identifier
     * 
     * @return std::string containing customer identifier
     */
    std::string getCustomerId() const noexcept;

    /**
     * @brief Get the customer category
     * 
     * @return CustomerCategory containing customer category
     */
    CustomerCategory getCategory() const noexcept;

    /**
     * @brief Get the total purchases amount
     * 
     * @return double containing total purchases amount
     */
    double getTotalPurchases() const noexcept;

    /**
     * @brief Get the loyalty points
     * 
     * @return int containing loyalty points
     */
    int getLoyaltyPoints() const noexcept;

    /**
     * @brief Get the registration date
     * 
     * @return std::string containing registration date
     */
    std::string getRegistrationDate() const noexcept;

    /**
     * @brief Check if customer is active
     * 
     * @return true if customer is active
     * @return false if customer is not active
     */
    bool isCustActive() const noexcept;

    /**
     * @brief Set the customer category
     * 
     * @param category CustomerCategory value containing new category
     */
    void setCategory(CustomerCategory category) noexcept;

    /**
     * @brief Set the customer active status
     * 
     * @param active boolean value containing new active status
     */
    void setActive(bool active) noexcept;

    /**
     * @brief Add purchase to customer history
     * 
     * @param amount double value containing purchase amount
     */
    void addPurchase(double amount);

    /**
     * @brief Add loyalty points
     * 
     * @param points integer value containing points to add
     */
    void addLoyaltyPoints(int points);

    /**
     * @brief Redeem loyalty points
     * 
     * @param points integer value containing points to redeem
     */
    void redeemLoyaltyPoints(int points);

    /**
     * @brief Calculate available discount for customer
     * 
     * @return double containing discount percentage
     */
    double calculateDiscount() const noexcept;

    /**
     * @brief Check if customer is eligible for upgrade
     * 
     * @return true if customer is eligible for upgrade
     * @return false if customer is not eligible for upgrade
     */
    bool isEligibleForUpgrade() const noexcept;

    /**
     * @brief Upgrade customer category if eligible
     */
    void upgradeCategory();

    /**
     * @brief Get customer information
     * 
     * @return std::string containing formatted customer information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Equality comparison operator for customers
     * 
     * @param other constant reference to the customer to compare with
     * 
     * @return true if customers are equal
     * @return false if customers are not equal
     */
    bool operator==(const Customer& other) const noexcept;

    /**
     * @brief Inequality comparison operator for customers
     * 
     * @param other constant reference to the customer to compare with
     * 
     * @return true if customers are not equal
     * @return false if customers are equal
     */
    bool operator!=(const Customer& other) const noexcept;
};