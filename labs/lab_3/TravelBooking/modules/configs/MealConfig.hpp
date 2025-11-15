/**
 * @file MealConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Meal system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <cstddef>

/**
 * @namespace MealConfig
 * @brief Namespace containing all configuration constants for the Meal system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the meal management system.
 */
namespace MealConfig {
    /**
     * @namespace Meal
     * @brief Configuration constants for base Meal class
     */
    namespace Meal {
        static constexpr size_t MAX_NAME_LENGTH = 100;          ///< Maximum allowed length for meal name
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 300;   ///< Maximum allowed length for description
        static constexpr double MIN_PRICE = 0.0;                ///< Minimum allowed meal price
        static constexpr double MAX_PRICE = 500.0;              ///< Maximum allowed meal price
        static constexpr int MIN_CALORIES = 0;                  ///< Minimum allowed calorie count
        static constexpr int MAX_CALORIES = 3000;               ///< Maximum allowed calorie count
        static constexpr size_t MAX_TAG_LENGTH = 30;            ///< Maximum allowed dietary tag length
        static constexpr size_t MAX_TAGS_COUNT = 10;            ///< Maximum allowed number of dietary tags
        static constexpr double MAX_PRICE_PER_CALORIE = 0.1;    ///< Maximum allowed price per calorie ratio
    }

    /**
     * @namespace Breakfast
     * @brief Configuration constants for BreakfastBuffet class
     */
    namespace Breakfast {
        static constexpr int MIN_CALORIES = 300;                ///< Minimum allowed breakfast calories
        static constexpr int MAX_CALORIES = 800;                ///< Maximum allowed breakfast calories
        static constexpr size_t MAX_CUISINE_STYLES = 10;        ///< Maximum allowed cuisine styles
        static constexpr size_t MAX_CUISINE_NAME_LENGTH = 20;   ///< Maximum allowed cuisine name length
        static constexpr int INTERNATIONAL_CUISINE_THRESHOLD = 3; ///< Threshold for international classification
    }

    /**
     * @namespace Lunch
     * @brief Configuration constants for lunch meal types
     */
    namespace Lunch {
        static constexpr int MIN_CALORIES = 400;                ///< Minimum allowed lunch calories
        static constexpr int MAX_CALORIES = 1000;               ///< Maximum allowed lunch calories
        static constexpr int MIN_COURSES = 1;                   ///< Minimum allowed lunch courses
        static constexpr int MAX_COURSES = 5;                   ///< Maximum allowed lunch courses
        static constexpr size_t MAX_RESTAURANT_TYPE_LENGTH = 30; ///< Maximum allowed restaurant type length
        static constexpr int FULL_COURSE_THRESHOLD = 3;         ///< Threshold for full course classification
        static constexpr int BUSINESS_COURSE_COUNT = 2;         ///< Course count for business lunch
    }

    /**
     * @namespace Dinner
     * @brief Configuration constants for dinner meal types
     */
    namespace Dinner {
        static constexpr int MIN_CALORIES = 500;                ///< Minimum allowed dinner calories
        static constexpr int MAX_CALORIES = 1200;               ///< Maximum allowed dinner calories
        static constexpr size_t MAX_MENU_ITEMS = 10;            ///< Maximum allowed menu items
        static constexpr size_t MAX_MENU_ITEM_LENGTH = 50;      ///< Maximum allowed menu item length
        static constexpr size_t MAX_AMBIANCE_LENGTH = 20;       ///< Maximum allowed ambiance description length
        static constexpr int FINE_DINING_COURSE_THRESHOLD = 4;  ///< Threshold for fine dining classification
        static constexpr int MULTI_COURSE_THRESHOLD = 2;        ///< Threshold for multi-course classification
    }

    /**
     * @namespace AllInclusive
     * @brief Configuration constants for AllInclusiveMeal class
     */
    namespace AllInclusive {
        static constexpr int MIN_MEALS_PER_DAY = 1;             ///< Minimum allowed meals per day
        static constexpr int MAX_MEALS_PER_DAY = 6;             ///< Maximum allowed meals per day
        static constexpr size_t MAX_RESTAURANTS = 15;           ///< Maximum allowed restaurants
        static constexpr int PREMIUM_MEAL_THRESHOLD = 4;        ///< Threshold for premium classification
        static constexpr int UNLIMITED_MEAL_THRESHOLD = 5;      ///< Threshold for unlimited classification
    }

    /**
     * @namespace Picnic
     * @brief Configuration constants for PicnicLunch class
     */
    namespace Picnic {
        static constexpr int MIN_CALORIES = 300;                ///< Minimum allowed picnic calories
        static constexpr int MAX_CALORIES = 800;                ///< Maximum allowed picnic calories
        static constexpr size_t MAX_CONTAINER_TYPES = 5;        ///< Maximum allowed container types
        static constexpr int MULTIPLE_CONTAINER_THRESHOLD = 2;  ///< Threshold for multiple containers
        static constexpr int OUTDOOR_CONTAINER_THRESHOLD = 3;   ///< Threshold for outdoor-friendly containers
    }

    /**
     * @namespace Ethnic
     * @brief Configuration constants for EthnicDinner class
     */
    namespace Ethnic {
        static constexpr int MIN_CALORIES = 500;                ///< Minimum allowed ethnic dinner calories
        static constexpr int MAX_CALORIES = 1200;               ///< Maximum allowed ethnic dinner calories
        static constexpr size_t MAX_CUISINE_LENGTH = 25;        ///< Maximum allowed cuisine name length
        static constexpr size_t MAX_SERVING_STYLE_LENGTH = 20;  ///< Maximum allowed serving style length
    }

    /**
     * @namespace Barbecue
     * @brief Configuration constants for BarbecueMeal class
     */
    namespace Barbecue {
        static constexpr int MIN_CALORIES = 600;                ///< Minimum allowed barbecue calories
        static constexpr int MAX_CALORIES = 1500;               ///< Maximum allowed barbecue calories
        static constexpr size_t MAX_MEAT_TYPES = 8;             ///< Maximum allowed meat types
        static constexpr size_t MAX_LOCATION_TYPE_LENGTH = 20;  ///< Maximum allowed location type length
        static constexpr int MULTIPLE_MEAT_THRESHOLD = 3;       ///< Threshold for multiple meat options
    }

    /**
     * @namespace Tasting
     * @brief Configuration constants for TastingMenu class
     */
    namespace Tasting {
        static constexpr int MIN_CALORIES = 400;                ///< Minimum allowed tasting menu calories
        static constexpr int MAX_CALORIES = 1000;               ///< Maximum allowed tasting menu calories
        static constexpr int MIN_DISHES = 3;                    ///< Minimum allowed number of dishes
        static constexpr int MAX_DISHES = 12;                   ///< Maximum allowed number of dishes
        static constexpr size_t MAX_CHEF_SPECIALTY_LENGTH = 30; ///< Maximum allowed chef specialty length
        static constexpr size_t MAX_PAIRING_NOTES_LENGTH = 100; ///< Maximum allowed pairing notes length
        static constexpr int PREMIUM_DISH_THRESHOLD = 6;        ///< Threshold for premium tasting classification
    }

    /**
     * @namespace EventCatering
     * @brief Configuration constants for EventCatering class
     */
    namespace EventCatering {
        static constexpr int MIN_CALORIES = 400;                ///< Minimum allowed catering calories
        static constexpr int MAX_CALORIES = 1200;               ///< Maximum allowed catering calories
        static constexpr int MIN_GUESTS = 10;                   ///< Minimum allowed guest count
        static constexpr int MAX_GUESTS = 500;                  ///< Maximum allowed guest count
        static constexpr size_t MAX_SERVICE_TYPE_LENGTH = 20;   ///< Maximum allowed service type length
        static constexpr size_t MAX_EVENT_TYPE_LENGTH = 25;     ///< Maximum allowed event type length
        static constexpr int LARGE_EVENT_THRESHOLD = 100;       ///< Threshold for large event classification
    }

    /**
     * @namespace Dietary
     * @brief Configuration constants for DietarySpecificMeal class
     */
    namespace Dietary {
        static constexpr int MIN_CALORIES = 200;                ///< Minimum allowed dietary meal calories
        static constexpr int MAX_CALORIES = 800;                ///< Maximum allowed dietary meal calories
        static constexpr size_t MAX_DIET_TYPE_LENGTH = 20;      ///< Maximum allowed diet type length
        static constexpr size_t MAX_PORTION_LENGTH = 15;        ///< Maximum allowed portion description length
        static constexpr size_t MAX_ALLERGENS = 10;             ///< Maximum allowed excluded allergens
        static constexpr int MULTIPLE_ALLERGEN_THRESHOLD = 3;   ///< Threshold for multiple allergen exclusion
    }
}