/**
 * @file ISBN.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the ISBN class for working with International Standard Book Numbers
 * @version 0.1
 * @date 2025-01-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class ISBN
 * @brief Class for working with International Standard Book Numbers
 * 
 * Handles ISBN validation, normalization, formatting and comparison.
 * Supports both ISBN-10 and ISBN-13 formats with check digit verification.
 */
class ISBN{
    private:
    std::string code;   ///< Normalized ISBN code without formatting

    /**
     * @brief Private method to validate ISBN format
     * 
     * @param str constant reference to the string containing ISBN to validate
     * 
     * @return true if ISBN format is valid
     * @return false if ISBN format is invalid
     */
    bool isValidFormat(const std::string& str) const;

    /**
     * @brief Private method to normalize ISBN string
     * 
     * Removes hyphens and converts to uppercase
     * 
     * @param str constant reference to the string containing ISBN to normalize
     * @return std::string containing normalized ISBN code
     */
    std::string normalizeISBN(const std::string& str) const;

    /**
     * @brief Private method to calculate check digit
     * 
     * @param str constant reference to the string containing ISBN for calculation
     * @return char containing calculated check digit
     */
    char calculateCheckDigit(const std::string& str) const;

    public:
    /**
     * @brief Construct a new ISBN object
     * 
     * @param str constant reference to the string containing ISBN code
     */
    explicit ISBN(const std::string& str);

    /**
     * @brief Get the normalized ISBN code
     * 
     * @return std::string containing normalized ISBN code
     */
    std::string getCode() const noexcept;

    /**
     * @brief Get the formatted ISBN code
     * 
     * @return std::string containing formatted ISBN code with hyphens
     */
    std::string getFormattedCode() const noexcept;

    /**
     * @brief Check if ISBN is 13-digit format
     * 
     * @return true if ISBN is 13-digit format
     * @return false if ISBN is 10-digit format
     */
    bool isISBNThirteen() const;

    /**
     * @brief Equality comparison operator for ISBN codes
     * 
     * @param other constant reference to the ISBN to compare with
     * 
     * @return true if ISBN codes are equal
     * @return false if ISBN codes are not equal
     */
    bool operator==(const ISBN& other) const noexcept;

    /**
     * @brief Inequality comparison operator for ISBN codes
     * 
     * @param other constant reference to the ISBN to compare with
     * 
     * @return true if ISBN codes are not equal
     * @return false if ISBN codes are equal
     */
    bool operator!=(const ISBN& other) const noexcept;
};