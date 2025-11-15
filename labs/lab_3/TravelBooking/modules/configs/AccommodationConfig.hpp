/**
 * @file AccommodationConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Accommodation system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <vector>
#include <string>

/**
 * @namespace AccommodationConfig
 * @brief Namespace containing all configuration constants for the Accommodation system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the accommodation management system.
 */
namespace AccommodationConfig {
    /**
     * @namespace Accommodation
     * @brief Configuration constants for base Accommodation class
     */
    namespace Accommodation {
        static constexpr size_t MAX_NAME_LENGTH = 150;          ///< Maximum allowed length for accommodation name
        static constexpr size_t MAX_LOCATION_LENGTH = 150;      ///< Maximum allowed length for location
        static constexpr double MIN_PRICE_PER_NIGHT = 0;        ///< Minimum allowed price per night
        static constexpr double MAX_PRICE_PER_NIGHT = 500;      ///< Maximum allowed price per night
        static constexpr size_t MIN_CAPACITY = 1;               ///< Minimum allowed guest capacity
        static constexpr size_t MAX_CAPACITY = 300;             ///< Maximum allowed guest capacity
        static constexpr int MIN_RATING = 1;                    ///< Minimum allowed rating value
        static constexpr int MAX_RATING = 5;                    ///< Maximum allowed rating value
        static constexpr size_t MAX_AMENITY_LENGTH = 30;        ///< Maximum allowed amenity name length
        static constexpr size_t MAX_AMENITIES_COUNT = 30;       ///< Maximum allowed number of amenities
    }

    /**
     * @namespace Hotel
     * @brief Configuration constants for Hotel class
     */
    namespace Hotel {
        static constexpr int MIN_STARS = 1;                     ///< Minimum allowed star rating
        static constexpr int MAX_STARS = 5;                     ///< Maximum allowed star rating
        static constexpr size_t MAX_ROOMTYPE_LENGTH = 150;      ///< Maximum allowed room type length
    }

    /**
     * @namespace Apartment
     * @brief Configuration constants for Apartment class
     */
    namespace Apartment {
        static constexpr int MIN_ROOMS = 1;                     ///< Minimum allowed number of rooms
        static constexpr int MAX_ROOMS = 10;                    ///< Maximum allowed number of rooms
        static constexpr double MIN_AREA = 20.0;                ///< Minimum allowed apartment area
        static constexpr double MAX_AREA = 500.0;               ///< Maximum allowed apartment area
        static constexpr int SPACIOUS_ROOM_THRESHOLD = 3;       ///< Threshold for spacious room classification
        static constexpr double LARGE_AREA_THRESHOLD = 80.0;    ///< Threshold for large area classification
        static constexpr int FAMILY_ROOM_THRESHOLD = 2;         ///< Threshold for family room classification
        static constexpr double FAMILY_AREA_THRESHOLD = 60.0;   ///< Threshold for family area classification
        static constexpr int STUDIO_ROOM_COUNT = 1;             ///< Room count for studio apartments
        static constexpr double STUDIO_AREA_THRESHOLD = 40.0;   ///< Area threshold for studio apartments
        static constexpr double LUXURY_AREA_THRESHOLD = 100.0;  ///< Area threshold for luxury classification
        static constexpr int LUXURY_ROOM_THRESHOLD = 3;         ///< Room threshold for luxury classification
        static constexpr double COMFORT_AREA_THRESHOLD = 60.0;  ///< Area threshold for comfort classification
        static constexpr int COMFORT_ROOM_THRESHOLD = 2;        ///< Room threshold for comfort classification
    }

    /**
     * @namespace Hostel
     * @brief Configuration constants for Hostel class
     */
    namespace Hostel {
        static constexpr int MIN_BEDS = 1;                      ///< Minimum allowed beds per room
        static constexpr int MAX_BEDS = 12;                     ///< Maximum allowed beds per room
        static constexpr size_t MAX_BATHROOM_TYPE_LENGTH = 20;  ///< Maximum allowed bathroom type length
        static constexpr int SMALL_DORM_THRESHOLD = 4;          ///< Threshold for small dormitory classification
        static constexpr int LARGE_DORM_THRESHOLD = 8;          ///< Threshold for large dormitory classification
        static constexpr int MAX_GROUP_MULTIPLIER = 2;          ///< Maximum group size multiplier
    }

    /**
     * @namespace Villa
     * @brief Configuration constants for Villa class
     */
    namespace Villa {
        static constexpr int MIN_FLOORS = 1;                    ///< Minimum allowed number of floors
        static constexpr int MAX_FLOORS = 4;                    ///< Maximum allowed number of floors
        static constexpr double MIN_VILLA_AREA = 100.0;         ///< Minimum allowed villa area
        static constexpr double MAX_VILLA_AREA = 2000.0;        ///< Maximum allowed villa area
        static constexpr int MULTISTORY_THRESHOLD = 2;          ///< Threshold for multi-story classification
        static constexpr int LUXURY_FLOOR_THRESHOLD = 2;        ///< Floor threshold for luxury classification
        static constexpr double POOL_SURCHARGE = 50.0;          ///< Surcharge for pool availability
        static constexpr double GARDEN_SURCHARGE = 30.0;        ///< Surcharge for garden availability
        static constexpr double FLOOR_SURCHARGE = 20.0;         ///< Surcharge per additional floor
        static constexpr int MIN_EVENT_CAPACITY = 10;           ///< Minimum capacity for event suitability
    }

    /**
     * @namespace GuestHouse
     * @brief Configuration constants for GuestHouse class
     */
    namespace GuestHouse {
        static constexpr int MIN_TOTAL_ROOMS = 1;               ///< Minimum allowed total rooms
        static constexpr int MAX_TOTAL_ROOMS = 20;              ///< Maximum allowed total rooms
        static constexpr size_t MAX_HOST_LANGUAGE_LENGTH = 20;  ///< Maximum allowed host language length
        static constexpr int SMALL_HOUSE_THRESHOLD = 5;         ///< Threshold for small guest house
        static constexpr int MEDIUM_HOUSE_THRESHOLD = 10;       ///< Threshold for medium guest house
        static constexpr int COMMUNITY_MIN_ROOMS = 3;           ///< Minimum rooms for community atmosphere
    }

    /**
     * @namespace Resort
     * @brief Configuration constants for Resort class
     */
    namespace Resort {
        static constexpr int MIN_RESTAURANTS = 1;               ///< Minimum allowed number of restaurants
        static constexpr int MAX_RESTAURANTS = 20;              ///< Maximum allowed number of restaurants
        static constexpr int MAX_ACTIVITIES_COUNT = 50;         ///< Maximum allowed activities count
        static constexpr size_t MAX_ACTIVITY_NAME_LENGTH = 30;  ///< Maximum allowed activity name length
        static constexpr int MULTIPLE_RESTAURANTS_THRESHOLD = 3;///< Threshold for multiple restaurants
        static constexpr int LUXURY_RESTAURANT_THRESHOLD = 5;   ///< Threshold for luxury restaurant count
        static constexpr int COMPREHENSIVE_RESTAURANT_THRESHOLD = 2; ///< Threshold for comprehensive services
    }

    /**
     * @namespace MountainLodge
     * @brief Configuration constants for MountainLodge class
     */
    namespace MountainLodge {
        static constexpr int MIN_ALTITUDE = 500;                ///< Minimum allowed altitude
        static constexpr int MAX_ALTITUDE = 5000;               ///< Maximum allowed altitude
        static constexpr size_t MAX_ACCESSIBILITY_LENGTH = 20;  ///< Maximum allowed accessibility description length
        static constexpr int HIGH_ALTITUDE_THRESHOLD = 2000;    ///< Threshold for high altitude classification
        static constexpr int COMFORT_ALTITUDE_THRESHOLD = 1000; ///< Threshold for comfort altitude
    }

    /**
     * @namespace Camping
     * @brief Configuration constants for Camping class
     */
    namespace Camping {
        static constexpr size_t MAX_CAMPING_TYPE_LENGTH = 20;   ///< Maximum allowed camping type length
    }

    /**
     * @namespace BoutiqueHotel
     * @brief Configuration constants for BoutiqueHotel class
     */
    namespace BoutiqueHotel {
        static constexpr int MIN_YEAR_BUILT = 1800;             ///< Minimum allowed construction year
        static constexpr size_t MAX_THEME_LENGTH = 50;          ///< Maximum allowed theme length
        static constexpr size_t MAX_ARCH_STYLE_LENGTH = 30;     ///< Maximum allowed architectural style length
        static constexpr int HISTORIC_AGE_THRESHOLD = 50;       ///< Age threshold for historic classification
        static constexpr int MODERN_YEAR_THRESHOLD = 2000;      ///< Year threshold for modern classification
    }

    /**
     * @namespace CruiseCabin
     * @brief Configuration constants for CruiseCabin class
     */
    namespace CruiseCabin {
        static constexpr int MIN_DECK_NUMBER = 1;               ///< Minimum allowed deck number
        static constexpr int MAX_DECK_NUMBER = 20;              ///< Maximum allowed deck number
        static constexpr size_t MAX_SHIP_NAME_LENGTH = 50;      ///< Maximum allowed ship name length
        static constexpr size_t MAX_CABIN_TYPE_LENGTH = 20;     ///< Maximum allowed cabin type length
        static constexpr int UPPER_DECK_THRESHOLD = 10;         ///< Threshold for upper deck classification
    }
}