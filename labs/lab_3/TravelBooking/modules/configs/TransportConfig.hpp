/**
 * @file TransportConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Transport system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <cstddef>

/**
 * @namespace TransportConfig
 * @brief Namespace containing all configuration constants for the Transport system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the transportation management system.
 */
namespace TransportConfig {
    /**
     * @namespace Transport
     * @brief Configuration constants for base Transport class
     */
    namespace Transport {
        static constexpr size_t MAX_COMPANY_NAME_LENGTH = 40;   ///< Maximum allowed length for company name
        static constexpr double MIN_TRANSPORT_PRICE = 5.0;      ///< Minimum allowed transport price
        static constexpr double MAX_TRANSPORT_PRICE = 5000.0;   ///< Maximum allowed transport price
    }

    /**
     * @namespace TransportReview
     * @brief Configuration constants for TransportReview class
     */
    namespace TransportReview {
        static constexpr int MIN_RATING = 1;                    ///< Minimum allowed rating value
        static constexpr int MAX_RATING = 5;                    ///< Maximum allowed rating value
    }
}