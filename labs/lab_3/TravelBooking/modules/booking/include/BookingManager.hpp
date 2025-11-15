/**
 * @file BookingManager.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookingManager class for booking management operations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Booking.hpp"

/**
 * @class BookingManager
 * @brief Main management class for booking operations
 * 
 * Provides centralized management for booking collections with functionality
 * for adding, cancelling, and analyzing bookings.
 */
class BookingManager {
private:
    std::vector<std::shared_ptr<Booking>> bookings;         ///< Collection of managed bookings

public:
    /**
     * @brief Add new booking to manager
     * 
     * @param booking shared pointer to the Booking object to add
     */
    void addBooking(const std::shared_ptr<Booking>& booking);
    
    /**
     * @brief Cancel booking by identifier
     * 
     * @param bookingId integer value containing booking ID to cancel
     * 
     * @return true if cancellation successful
     * @return false if booking not found
     */
    bool cancelBooking(int bookingId);
    
    /**
     * @brief Find booking by identifier
     * 
     * @param bookingId integer value containing booking ID to find
     * 
     * @return std::shared_ptr<Booking> containing found booking or nullptr
     */
    std::shared_ptr<Booking> findBookingById(int bookingId) const;
    
    /**
     * @brief Get all active bookings
     * 
     * @return std::vector<std::shared_ptr<Booking>> containing active bookings
     */
    std::vector<std::shared_ptr<Booking>> getActiveBookings() const;
    
    /**
     * @brief Calculate total revenue from bookings
     * 
     * @return double containing total revenue amount
     */
    double calculateTotalRevenue() const;
    
    /**
     * @brief Count bookings by status
     * 
     * @param status Booking::Status value containing status to count
     * 
     * @return int containing count of bookings with specified status
     */
    int countBookingsByStatus(Booking::Status status) const;
    
    /**
     * @brief Get booking manager summary
     * 
     * @return std::string containing formatted manager summary
     */
    std::string getSummary() const;
};