/**
 * @file PersonConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Persons module
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once

#include <cstddef>

/**
 * @namespace PersonConfig
 * @brief Namespace containing all configuration constants for the Persons module
 * 
 * Provides centralized configuration for all validation limits and constraints
 * used throughout the persons management system.
 */
namespace PersonConfig {
    /**
     * @namespace Person
     * @brief Configuration constants for Person class
     */
    namespace Person {
        static constexpr size_t MAX_ID_LENGTH = 20;          ///< Maximum allowed length for person ID
        static constexpr size_t MAX_NAME_LENGTH = 50;        ///< Maximum allowed length for person names
        static constexpr int ADULT_AGE = 18;                 ///< Age considered as adult for legal purposes
    }

    /**
     * @namespace Address
     * @brief Configuration constants for Address class
     */
    namespace Address {
        static constexpr size_t MAX_STREET_LENGTH = 100;     ///< Maximum allowed length for street address
        static constexpr size_t MAX_CITY_LENGTH = 50;        ///< Maximum allowed length for city name
        static constexpr size_t MAX_POSTAL_CODE_LENGTH = 10; ///< Maximum allowed length for postal code
        static constexpr size_t MAX_COUNTRY_LENGTH = 50;     ///< Maximum allowed length for country name
    }

    /**
     * @namespace ContactInfo
     * @brief Configuration constants for ContactInfo class
     */
    namespace ContactInfo {
        static constexpr size_t MIN_PHONE_LENGTH = 7;        ///< Minimum allowed length for phone numbers
        static constexpr size_t MAX_PHONE_LENGTH = 20;       ///< Maximum allowed length for phone numbers
    }

    /**
     * @namespace Customer
     * @brief Configuration constants for Customer class
     */
    namespace Customer {
        static constexpr size_t MAX_CUSTOMER_ID_LENGTH = 20; ///< Maximum allowed length for customer ID
    }

    /**
     * @namespace Employee
     * @brief Configuration constants for Employee class
     */
    namespace Employee {
        static constexpr size_t MAX_EMPLOYEE_ID_LENGTH = 20; ///< Maximum allowed length for employee ID
        static constexpr size_t MAX_DEPARTMENT_LENGTH = 50;  ///< Maximum allowed length for department name
    }

    /**
     * @namespace UserAccount
     * @brief Configuration constants for UserAccount class
     */
    namespace UserAccount {
        static constexpr size_t MIN_USERNAME_LENGTH = 3;     ///< Minimum allowed length for username
        static constexpr size_t MAX_USERNAME_LENGTH = 20;    ///< Maximum allowed length for username
        static constexpr size_t MIN_PASSWORD_LENGTH = 8;     ///< Minimum allowed length for password
        static constexpr int MAX_LOGIN_ATTEMPTS = 5;         ///< Maximum allowed failed login attempts before lock
        static constexpr int PASSWORD_EXPIRY_YEARS = 1;      ///< Password expiration period in years
    }
}