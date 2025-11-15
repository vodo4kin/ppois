/**
 * @file Utils.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with utility classes for string validation, date operations and logging
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <iostream>

/**
 * @class StringValidation
 * @brief Utility class for string validation operations
 * 
 * Provides static methods for validating names, dates and other string formats
 * used throughout the system. Includes length constraints and format checking.
 */
class StringValidation {
public:
    /**
     * @brief Validate if string is a valid name
     * 
     * Checks if string is not empty, contains no control characters,
     * and has at least one non-space character.
     * 
     * @param str constant reference to the string to validate
     * 
     * @return true if string is a valid name
     * @return false if string is not a valid name
     */
    static bool isValidName(const std::string& str) {
        if (str.empty()) return false;
        bool hasNonSpace = false;
        for (char c : str) {
            if (c == '\t' || c == '\n' || c == '\r') return false;
            if (c != ' ') hasNonSpace = true;
        }
        return hasNonSpace;
    }

    /**
     * @brief Validate if string is a valid name with length constraint
     * 
     * Combines basic name validation with maximum length check.
     * 
     * @param str constant reference to the string to validate
     * @param maxLength maximum allowed length for the string
     * 
     * @return true if string is a valid name and within length limit
     * @return false if string is not valid or exceeds length limit
     */
    static bool isValidName(const std::string& str, size_t maxLength) {
        return str.length() <= maxLength && isValidName(str);
    }

    /**
     * @brief Validate date string format
     * 
     * Checks if string matches YYYY-MM-DD format with valid separators
     * and digit positions.
     * 
     * @param date constant reference to the string containing date to validate
     * 
     * @return true if date format is valid
     * @return false if date format is invalid
     */
    static bool isValidDate(const std::string& date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;
        
        for (int i = 0; i < 10; i++) {
            if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i]))) {
                return false;
            }
        }
        return true;
    }
};

/**
 * @class DateUtils
 * @brief Utility class for date-related operations
 * 
 * Provides static methods for working with dates and timestamps
 * in standardized formats. Includes age calculation and current date retrieval.
 */
class DateUtils {
public:
    /**
     * @brief Get current date as formatted string
     * 
     * Returns current system date in ISO 8601 format (YYYY-MM-DD).
     * Used for timestamps, booking dates, and other date tracking.
     * 
     * @return std::string containing current date in YYYY-MM-DD format
     */
    static std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
        return ss.str();
    }

    /**
     * @brief Calculate age from birth date
     * 
     * Computes current age based on birth date considering month and day
     * for accurate age calculation.
     * 
     * @param birthDate constant reference to the string containing birth date in YYYY-MM-DD format
     * 
     * @return int containing calculated age in years
     */
    static int calculateAge(const std::string& birthDate) {
        std::string currentDate = getCurrentDate();
        int currentYear = std::stoi(currentDate.substr(0, 4));
        int currentMonth = std::stoi(currentDate.substr(5, 2));
        int currentDay = std::stoi(currentDate.substr(8, 2));
        int birthYear = std::stoi(birthDate.substr(0, 4));
        int birthMonth = std::stoi(birthDate.substr(5, 2));
        int birthDay = std::stoi(birthDate.substr(8, 2));
        int age = currentYear - birthYear;
        if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
            age--;
        }
        return age;
    }
};

/**
 * @class Logger
 * @brief Utility class for logging operations
 * 
 * Provides static methods for different logging levels with formatted output.
 * Used for system monitoring, debugging, and error tracking.
 */
class Logger {
public:
    /**
     * @brief Log informational message
     * 
     * Outputs informational messages to standard output with [INFO] prefix.
     * Used for general system status and operation tracking.
     * 
     * @param message constant reference to the string containing message to log
     */
    static void logInfo(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }

    /**
     * @brief Log warning message
     * 
     * Outputs warning messages to standard output with [WARNING] prefix.
     * Used for non-critical issues and potential problems.
     * 
     * @param message constant reference to the string containing message to log
     */
    static void logWarning(const std::string& message) {
        std::cout << "[WARNING] " << message << std::endl;
    }

    /**
     * @brief Log error message
     * 
     * Outputs error messages to standard error with [ERROR] prefix.
     * Used for critical errors and system failures.
     * 
     * @param message constant reference to the string containing message to log
     */
    static void logError(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
};