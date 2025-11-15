/**
 * @file Customer.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Customer class for customer management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "User.hpp"
#include <vector>
#include <memory>
class Booking;

/**
 * @class Customer
 * @brief Class representing customer type user
 * 
 * Extends User with customer-specific properties like bookings and spending.
 * Provides functionality for booking management and customer analytics.
 */
class Customer : public User {
private:
    std::vector<std::weak_ptr<Booking>> bookings;           ///< Collection of customer bookings

protected:
    int totalBookingsCount;                                 ///< Total number of bookings made
    double totalSpent;                                      ///< Total amount spent by customer

public:
    /**
     * @brief Construct a new Customer object
     * 
     * @param name constant reference to the string containing customer name
     * @param email constant reference to the string containing email address
     * @param password constant reference to the string containing password
     * @param birthDate constant reference to the string containing birth date
     */
    Customer(const std::string& name, const std::string& email, 
             const std::string& password, const std::string& birthDate);
    
    /**
     * @brief Get the customer role
     * 
     * @return std::string containing "Customer"
     */
    std::string getUserRole() const override;
    
    /**
     * @brief Add booking to customer
     * 
     * @param booking weak pointer to the Booking object to add
     */
    virtual void addBooking(const std::weak_ptr<Booking>& booking);
    
    /**
     * @brief Cancel booking by identifier
     * 
     * @param bookingId integer value containing booking ID to cancel
     */
    virtual void cancelBooking(int bookingId);
    
    /**
     * @brief Get all bookings
     * 
     * @return const std::vector<std::weak_ptr<Booking>>& containing all customer bookings
     */
    const std::vector<std::weak_ptr<Booking>>& getBookings() const noexcept;
    
    /**
     * @brief Get bookings count
     * 
     * @return size_t containing number of bookings
     */
    size_t getBookingsCount() const noexcept;
    
    /**
     * @brief Get total amount spent
     * 
     * @return double containing total spending amount
     */
    virtual double getTotalSpent() const noexcept;
    
    /**
     * @brief Get comprehensive customer information
     * 
     * @return std::string containing formatted customer details
     */
    virtual std::string getCustomerInfo() const noexcept;
    
    /**
     * @brief Get membership duration
     * 
     * @return int containing membership duration in days
     */
    int getMembershipDuration() const noexcept;
    
    /**
     * @brief Check if customer has active bookings
     * 
     * @return true if active bookings exist
     * @return false if no active bookings
     */
    virtual bool hasActiveBookings() const noexcept;
};