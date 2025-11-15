/**
 * @file PersonsConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Persons system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <cstddef>

/**
 * @namespace PersonsConfig
 * @brief Namespace containing all configuration constants for the Persons system
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the user management system including customers, admins, and VIP users.
 */
namespace PersonsConfig {
    /**
     * @namespace User
     * @brief Configuration constants for base User class
     */
    namespace User {
        static constexpr size_t MAX_NAME_LENGTH = 20;           ///< Maximum allowed length for user name
        static constexpr size_t MIN_PASSWORD_LENGTH = 8;        ///< Minimum allowed password length
        static constexpr size_t MIN_PHONE_NUMBER_LENGTH = 7;    ///< Minimum allowed phone number length
        static constexpr size_t MAX_PHONE_NUMBER_LENGTH = 15;   ///< Maximum allowed phone number length
        static constexpr size_t MAX_ADDRESS_LENGTH = 100;       ///< Maximum allowed address length
    }

    /**
     * @namespace VipCustomer
     * @brief Configuration constants for VipCustomer class
     */
    namespace VipCustomer {
        constexpr double SILVER_THRESHOLD = 0;                  ///< Loyalty points threshold for Silver tier
        constexpr double GOLD_THRESHOLD = 1000;                 ///< Loyalty points threshold for Gold tier
        constexpr double PLATINUM_THRESHOLD = 5000;             ///< Loyalty points threshold for Platinum tier
        constexpr double SILVER_DISCOUNT = 0.05;                ///< Discount percentage for Silver tier
        constexpr double GOLD_DISCOUNT = 0.10;                  ///< Discount percentage for Gold tier
        constexpr double PLATINUM_DISCOUNT = 0.15;              ///< Discount percentage for Platinum tier
        constexpr double POINTS_EARN_RATE = 0.10;               ///< Points earning rate per currency unit spent
    }

    /**
     * @namespace Admin
     * @brief Configuration constants for Admin class
     */
    namespace Admin {
        constexpr int MAX_DEPARTMENT_LENGTH = 50;               ///< Maximum allowed department name length
        constexpr int MAX_PERMISSIONS = 10;                     ///< Maximum allowed permissions per admin
        constexpr int MAX_ALLOWED_ADMIN_USERS = 5;              ///< Maximum allowed admin users in system
    }
}