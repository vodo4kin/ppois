/**
 * @file Publisher.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Publisher class for working with book publishers
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class Publisher
 * @brief Class for working with book publishers
 * 
 * Stores publisher information including name, contact email, 
 * and foundation year. Provides validation for all fields
 * and comparison operations.
 */
class Publisher {
private:
    std::string name;           ///< Name of the publisher
    std::string contactEmail;   ///< Contact email address of the publisher
    int foundationYear;         ///< Year when publisher was founded

    /**
     * @brief Private method to validate publisher name
     * 
     * @param name constant reference to the string containing publisher name to validate
     * 
     * @return true if name is valid
     * @return false if name is invalid
     */
    bool isValidName(const std::string& name) const;

    /**
     * @brief Private method to validate email format
     * 
     * @param email constant reference to the string containing email to validate
     * 
     * @return true if email format is valid
     * @return false if email format is invalid
     */
    bool isValidEmail(const std::string& email) const;

    /**
     * @brief Private method to validate foundation year
     * 
     * @param year integer value containing foundation year to validate
     * 
     * @return true if year is valid
     * @return false if year is invalid
     */
    bool isValidYear(int year) const;

public:
    /**
     * @brief Construct a new Publisher object
     * 
     * @param name constant reference to the string containing publisher name
     * @param contactEmail constant reference to the string containing contact email
     * @param foundationYear integer value containing foundation year
     */
    Publisher(const std::string& name, const std::string& contactEmail, int foundationYear);

    /**
     * @brief Get the publisher name
     * 
     * @return std::string containing publisher name
     */
    std::string getName() const noexcept;

    /**
     * @brief Get the contact email
     * 
     * @return std::string containing contact email
     */
    std::string getContactEmail() const noexcept;

    /**
     * @brief Get the foundation year
     * 
     * @return int containing foundation year
     */
    int getFoundationYear() const noexcept;

    /**
     * @brief Get formatted information about publisher
     * 
     * @return std::string containing formatted publisher information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for publishers
     * 
     * @param other constant reference to the publisher to compare with
     * 
     * @return true if publishers are equal
     * @return false if publishers are not equal
     */
    bool operator==(const Publisher& other) const noexcept;

    /**
     * @brief Inequality comparison operator for publishers
     * 
     * @param other constant reference to the publisher to compare with
     * 
     * @return true if publishers are not equal
     * @return false if publishers are equal
     */
    bool operator!=(const Publisher& other) const noexcept;
};