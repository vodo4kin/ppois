/**
 * @file BookConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the BookWarehouse system
 * @version 0.1
 * @date 2025-01-15
 * 
 * 
 */

#pragma once

#include <cstddef>

/**
 * @namespace BookConfig
 * @brief Namespace containing all configuration constants for the BookWarehouse system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the book warehouse system.
 */
namespace BookConfig {
    /**
     * @namespace BookTitle
     * @brief Configuration constants for BookTitle class
     */
    namespace BookTitle {
        static constexpr size_t MAX_LENGTH = 128;   ///< Maximum allowed length for book title
        static constexpr size_t MIN_LENGTH = 1;     ///< Minimum allowed length for book title
    }

    /**
     * @namespace BookMetadata
     * @brief Configuration constants for BookMetadata class
     */
    namespace BookMetadata {
        static constexpr int MIN_YEAR = 1400;                 ///< Minimum allowed publication year
        static constexpr int MAX_YEAR = 2025;                 ///< Maximum allowed publication year
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 500; ///< Maximum allowed description length
    }

    /**
     * @namespace BookReview
     * @brief Configuration constants for BookReview class
     */
    namespace BookReview {
        static constexpr int MIN_RATING = 1;                  ///< Minimum allowed rating value
        static constexpr int MAX_RATING = 5;                  ///< Maximum allowed rating value
        static constexpr size_t MAX_TEXT_LENGTH = 2000;       ///< Maximum allowed review text length
        static constexpr size_t MAX_AUTHOR_LENGTH = 100;      ///< Maximum allowed author name length
        static constexpr size_t MAX_TITLE_LENGTH = 200;       ///< Maximum allowed review title length
    }

    /**
     * @namespace BookSeries
     * @brief Configuration constants for BookSeries class
     */
    namespace BookSeries {
        static constexpr size_t MAX_NAME_LENGTH = 100;        ///< Maximum allowed series name length
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 500; ///< Maximum allowed series description length
    }

    /**
     * @namespace BookStatistics
     * @brief Configuration constants for BookStatistics class
     */
    namespace BookStatistics {
        static constexpr int MAX_VIEWS = 1000000;             ///< Maximum allowed view count
        static constexpr int MAX_SALES = 100000;              ///< Maximum allowed sales count
    }

    /**
     * @namespace PhysicalProperties
     * @brief Configuration constants for PhysicalProperties class
     */
    namespace PhysicalProperties {
        static constexpr int MAX_WEIGHT = 5000;               ///< Maximum allowed weight in grams
        static constexpr int MAX_PAGES = 5000;                ///< Maximum allowed page count
        static constexpr int MAX_DIMENSION = 500;             ///< Maximum allowed dimension in millimeters
    }

    /**
     * @namespace Publisher
     * @brief Configuration constants for Publisher class
     */
    namespace Publisher {
        static constexpr size_t MAX_NAME_LENGTH = 100;        ///< Maximum allowed publisher name length
        static constexpr size_t MIN_NAME_LENGTH = 1;          ///< Minimum allowed publisher name length
        static constexpr size_t YEAR = 2025;                  ///< Current year for validation
    }

    /**
     * @namespace BookCollection
     * @brief Configuration constants for BookCollection class
     */
    namespace BookCollection {
        static constexpr size_t MAX_NAME_LENGTH = 100;        ///< Maximum allowed collection name length
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 500; ///< Maximum allowed collection description length
    }

    /**
     * @namespace StringValidation
     * @brief Configuration constants for StringValidation utilities
     */
    namespace StringValidation {
        static constexpr size_t DEFAULT_MAX_LENGTH = 100;     ///< Default maximum string length for validation
    }
}