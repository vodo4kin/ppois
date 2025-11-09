/**
 * @file Utils.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with utility classes for string validation and date operations
 * @version 0.1
 * @date 2025-01-15
 * 
 * 
 */

#pragma once
#include <string>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <sstream>

/**
 * @class StringValidation
 * @brief Utility class for string validation operations
 * 
 * Provides static methods for validating names, languages, dates
 * and other string formats used throughout the system.
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
     * @brief Normalize language string to uppercase
     * 
     * Converts language code to uppercase (e.g., "en" → "EN")
     * for consistent storage and comparison.
     * 
     * @param language constant reference to the string containing language code
     * 
     * @return std::string containing normalized uppercase language code
     */
    static std::string normalizeLanguage(const std::string& language) {
        std::string result;
        for(char c : language){
            result += std::toupper(static_cast<unsigned char>(c));
        }
        return result;
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
 * in standardized formats.
 */
class DateUtils {
public:
    /**
     * @brief Get current date as formatted string
     * 
     * Returns current system date in ISO 8601 format (YYYY-MM-DD).
     * Used for timestamps, movement dates, and other date tracking.
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
};