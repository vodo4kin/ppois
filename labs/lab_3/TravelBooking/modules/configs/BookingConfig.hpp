/**
 * @file BookingConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Booking system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <cstddef>

/**
 * @namespace BookingConfig
 * @brief Namespace containing all configuration constants for the Booking system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the booking and payment management system.
 */
namespace BookingConfig {
    /**
     * @namespace Booking
     * @brief Configuration constants for Booking class
     */
    namespace Booking {
        static constexpr double MIN_PRICE = 50;                 ///< Minimum allowed booking price
        static constexpr double MAX_PRICE = 50000;              ///< Maximum allowed booking price
    }

    /**
     * @namespace Payment
     * @brief Configuration constants for Payment class
     */
    namespace Payment {
        constexpr size_t MAX_PAYER_NAME = 50;                   ///< Maximum allowed payer name length
        constexpr int MAX_AMOUNT = 50000;                       ///< Maximum allowed payment amount
        constexpr int MIN_AMOUNT = 1;                           ///< Minimum allowed payment amount
    }
}