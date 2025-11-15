/**
 * @file ToursConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Tours system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <cstddef>

/**
 * @namespace ToursConfig
 * @brief Namespace containing all configuration constants for the Tours system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the tour management system.
 */
namespace ToursConfig {
    /**
     * @namespace Tour
     * @brief Configuration constants for Tour class
     */
    namespace Tour {
        static constexpr size_t MIN_TITLE_LENGTH = 5;           ///< Minimum allowed tour title length
        static constexpr size_t MAX_TITLE_LENGTH = 100;         ///< Maximum allowed tour title length
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 500;   ///< Maximum allowed tour description length
        static constexpr double MIN_TOUR_PRICE = 0.0;           ///< Minimum allowed tour price
        static constexpr double MAX_TOUR_PRICE = 100000.0;      ///< Maximum allowed tour price
        static constexpr int MAX_ACCOMMODATIONS_PER_TOUR = 20;  ///< Maximum allowed accommodations per tour
        static constexpr int MAX_MEALS_PER_TOUR = 30;           ///< Maximum allowed meals per tour
    }
    
    /**
     * @namespace TourReview
     * @brief Configuration constants for TourReview class
     */
    namespace TourReview {
        static constexpr size_t MAX_REVIEW_LENGTH = 500;        ///< Maximum allowed review text length
        static constexpr int MIN_RATING = 1;                    ///< Minimum allowed rating value
        static constexpr int MAX_RATING = 5;                    ///< Maximum allowed rating value
    }
}