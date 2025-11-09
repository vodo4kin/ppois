/**
 * @file ContactInfo.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the ContactInfo class for working with contact information
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class ContactInfo
 * @brief Class for working with contact information
 * 
 * Stores and manages various contact methods including email, phone numbers,
 * and alternative contacts. Provides validation for email and phone formats.
 */
class ContactInfo {
private:
    std::string email;              ///< Primary email address
    std::string phoneNumber;        ///< Primary phone number
    std::string secondaryEmail;     ///< Secondary email address (optional)
    std::string secondaryPhone;     ///< Secondary phone number (optional)

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
     * @brief Private method to validate phone number format
     * 
     * @param phone constant reference to the string containing phone number to validate
     * 
     * @return true if phone number format is valid
     * @return false if phone number format is invalid
     */
    bool isValidPhoneNumber(const std::string& phone) const;

public:
    /**
     * @brief Construct a new ContactInfo object
     * 
     * @param email constant reference to the string containing primary email
     * @param phoneNumber constant reference to the string containing primary phone number
     * @param secondaryEmail constant reference to the string containing secondary email
     * @param secondaryPhone constant reference to the string containing secondary phone
     */
    ContactInfo(const std::string& email, const std::string& phoneNumber,
                const std::string& secondaryEmail = "", const std::string& secondaryPhone = "");

    /**
     * @brief Get the primary email
     * 
     * @return std::string containing primary email
     */
    std::string getEmail() const noexcept;

    /**
     * @brief Get the primary phone number
     * 
     * @return std::string containing primary phone number
     */
    std::string getPhoneNumber() const noexcept;

    /**
     * @brief Get the secondary email
     * 
     * @return std::string containing secondary email
     */
    std::string getSecondaryEmail() const noexcept;

    /**
     * @brief Get the secondary phone number
     * 
     * @return std::string containing secondary phone number
     */
    std::string getSecondaryPhone() const noexcept;

    /**
     * @brief Set the primary email
     * 
     * @param email constant reference to the string containing new primary email
     */
    void setEmail(const std::string& email);

    /**
     * @brief Set the primary phone number
     * 
     * @param phoneNumber constant reference to the string containing new primary phone number
     */
    void setPhoneNumber(const std::string& phoneNumber);

    /**
     * @brief Set the secondary email
     * 
     * @param secondaryEmail constant reference to the string containing new secondary email
     */
    void setSecondaryEmail(const std::string& secondaryEmail);

    /**
     * @brief Set the secondary phone number
     * 
     * @param secondaryPhone constant reference to the string containing new secondary phone number
     */
    void setSecondaryPhone(const std::string& secondaryPhone);

    /**
     * @brief Get the primary contact method
     * 
     * @return std::string containing primary contact (email if available, otherwise phone)
     */
    std::string getPrimaryContact() const noexcept;

    /**
     * @brief Check if contact info has valid primary contact
     * 
     * @return true if has valid email or phone number
     * @return false if no valid primary contact
     */
    bool hasValidContact() const noexcept;

    /**
     * @brief Check if contact info has email
     * 
     * @return true if has valid email
     * @return false if no valid email
     */
    bool hasEmail() const noexcept;

    /**
     * @brief Check if contact info has phone number
     * 
     * @return true if has valid phone number
     * @return false if no valid phone number
     */
    bool hasPhoneNumber() const noexcept;

    /**
     * @brief Get contact information
     * 
     * @return std::string containing formatted contact information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for contact info
     * 
     * @param other constant reference to the contact info to compare with
     * 
     * @return true if contact info are equal
     * @return false if contact info are not equal
     */
    bool operator==(const ContactInfo& other) const noexcept;

    /**
     * @brief Inequality comparison operator for contact info
     * 
     * @param other constant reference to the contact info to compare with
     * 
     * @return true if contact info are not equal
     * @return false if contact info are equal
     */
    bool operator!=(const ContactInfo& other) const noexcept;
};