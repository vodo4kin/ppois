/**
 * @file BookingNotification.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookingNotification class for booking notifications
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Booking.hpp"

/**
 * @class BookingNotification
 * @brief Utility class for booking-related notifications
 * 
 * Provides static methods for sending notifications about booking status changes,
 * cancellations, and confirmations.
 */
class BookingNotification {
public:
    /**
     * @brief Notify about booking status change
     * 
     * @param booking shared pointer to the Booking object with status change
     */
    static void notifyStatusChange(const std::shared_ptr<Booking>& booking);
    
    /**
     * @brief Notify about booking cancellation
     * 
     * @param booking shared pointer to the Booking object that was cancelled
     */
    static void notifyCancellation(const std::shared_ptr<Booking>& booking);
    
    /**
     * @brief Notify about booking confirmation
     * 
     * @param booking shared pointer to the Booking object that was confirmed
     */
    static void notifyConfirmation(const std::shared_ptr<Booking>& booking);
};