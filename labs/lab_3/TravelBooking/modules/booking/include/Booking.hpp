/**
 * @file Booking.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Booking class for booking management system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Customer.hpp"
#include "Tour.hpp"
#include "Transport.hpp"

/**
 * @class Booking
 * @brief Main class for booking management
 * 
 * Represents a booking that combines customer, tour, and transport information.
 * Provides business logic for booking status management and price calculation.
 */
class Booking {
public:
    /**
     * @enum Status
     * @brief Enumeration of booking statuses
     */
    enum class Status {
        PENDING,                                            ///< Booking is pending confirmation
        CONFIRMED,                                          ///< Booking is confirmed
        CANCELLED                                           ///< Booking is cancelled
    };

private:
    std::shared_ptr<Customer> customer;                     ///< Shared pointer to customer object
    std::shared_ptr<Tour> tour;                             ///< Shared pointer to tour object
    std::shared_ptr<Transport> transport;                   ///< Shared pointer to transport object
    std::string bookingDate;                                ///< Date when booking was made
    Status status;                                          ///< Current booking status
    double totalPrice;                                      ///< Total booking price
    
    /**
     * @brief Update total price based on tour and transport
     */
    void updateTotalPrice();

public:
    /**
     * @brief Construct a new Booking object
     * 
     * @param customer shared pointer to the Customer object
     * @param tour shared pointer to the Tour object
     * @param transport shared pointer to the Transport object
     */
    Booking(std::shared_ptr<Customer> customer,
                 std::shared_ptr<Tour> tour,
                 std::shared_ptr<Transport> transport);
    
    /**
     * @brief Get the booking identifier
     * 
     * @return int containing unique booking identifier
     */
    int getBookingId() const;
    
    /**
     * @brief Get the booking date
     * 
     * @return std::string containing booking date
     */
    std::string getBookingDate() const;
    
    /**
     * @brief Get the booking status
     * 
     * @return Status containing booking status enum value
     */
    Status getStatus() const;
    
    /**
     * @brief Get the booking status as string
     * 
     * @return std::string containing booking status description
     */
    std::string getStatusStr() const;
    
    /**
     * @brief Get the total price
     * 
     * @return double containing total booking price
     */
    double getTotalPrice();
    
    /**
     * @brief Check if booking is active
     * 
     * @return true if booking is active (pending or confirmed)
     * @return false if booking is cancelled
     */
    bool isActive() const;
    
    /**
     * @brief Confirm the booking
     */
    void confirm();
    
    /**
     * @brief Cancel the booking
     */
    void cancel();
    
    /**
     * @brief Set the booking status
     * 
     * @param newStatus Status value containing new status
     */
    void setStatus(Status newStatus);
    
    /**
     * @brief Get comprehensive booking information
     * 
     * @return std::string containing formatted booking details
     */
    std::string getBookingInfo();
};