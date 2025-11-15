/**
 * @file User.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the User base abstract class for user management system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class User
 * @brief Base abstract class for all types of users
 * 
 * Provides common interface and properties for various user types
 * including customers, admins, and VIP customers. Implements core
 * functionality for user authentication, profile management, and validation.
 */
class User {
private:
    /**
     * @brief Generate unique user identifier
     * 
     * @return int containing generated user ID
     */
    int generateUserId();
    
    /**
     * @brief Validate password strength
     * 
     * @param password constant reference to the string containing password to validate
     * @param minLength minimum required password length
     * 
     * @return true if password is valid
     * @return false if password is invalid
     */
    bool isValidPassword(const std::string& password, size_t minLength = 8) const;
    
    /**
     * @brief Validate email format
     * 
     * @param email constant reference to the string containing email to validate
     * 
     * @return true if email is valid
     * @return false if email is invalid
     */
    bool isValidEmail(const std::string& email) const;
    
    /**
     * @brief Validate phone number format
     * 
     * @param phoneNumber constant reference to the string containing phone number to validate
     * 
     * @return true if phone number is valid
     * @return false if phone number is invalid
     */
    bool isValidPhoneNumber(const std::string& phoneNumber) const;

protected:
    int userId;                                             ///< Unique user identifier
    std::string name;                                       ///< User's full name
    std::string email;                                      ///< User's email address
    std::string password;                                   ///< User's password (hashed)
    std::string dateOfBirth;                                ///< User's date of birth
    std::string phoneNumber;                                ///< User's phone number
    std::string address;                                    ///< User's physical address
    
    /**
     * @enum Male
     * @brief Enumeration of gender options
     */
    enum class Male {
        MAN,                                                ///< Male gender
        WOMAN,                                              ///< Female gender
        NOT_SPECIFIED                                       ///< Gender not specified
    } gender;                                               ///< User's gender
    
    bool isActive;                                          ///< Account activation status
    std::string registrationDate;                           ///< Account registration date

public:
    /**
     * @brief Construct a new User object
     * 
     * @param name constant reference to the string containing user name
     * @param email constant reference to the string containing email address
     * @param password constant reference to the string containing password
     * @param birthDate constant reference to the string containing birth date
     */
    User(const std::string& name, const std::string& email, 
        const std::string& password, const std::string& birthDate);
    
    /**
     * @brief Deactivate user account
     */
    void deactivate();
    
    /**
     * @brief Activate user account
     */
    void activate();
    
    /**
     * @brief Get the user role
     * 
     * Pure virtual method that must be implemented by derived classes
     * 
     * @return std::string containing user role
     */
    virtual std::string getUserRole() const = 0;
    
    /**
     * @brief Destroy the User object
     */
    virtual ~User() = default;
    
    /**
     * @brief Get the user identifier
     * 
     * @return int containing user ID
     */
    int getUserId() const noexcept;
    
    /**
     * @brief Get the user name
     * 
     * @return std::string containing user name
     */
    std::string getName() const noexcept;
    
    /**
     * @brief Get the email address
     * 
     * @return std::string containing email address
     */
    std::string getEmail() const noexcept;
    
    /**
     * @brief Get the date of birth
     * 
     * @return std::string containing date of birth
     */
    std::string getDateOfBirth() const noexcept;
    
    /**
     * @brief Get the phone number
     * 
     * @return std::string containing phone number
     */
    std::string getPhoneNumber() const noexcept;
    
    /**
     * @brief Get the address
     * 
     * @return std::string containing physical address
     */
    std::string getAddress() const noexcept;
    
    /**
     * @brief Get the gender enum value
     * 
     * @return Male containing gender enum value
     */
    Male getGender() const noexcept;
    
    /**
     * @brief Get the gender as string
     * 
     * @return std::string containing gender description
     */
    std::string getGenderStr() const noexcept;
    
    /**
     * @brief Get the account activation status
     * 
     * @return true if account is active
     * @return false if account is inactive
     */
    bool getIsActive() const noexcept;
    
    /**
     * @brief Get the registration date
     * 
     * @return std::string containing registration date
     */
    std::string getRegistrationDate() const noexcept;
    
    /**
     * @brief Get the user age
     * 
     * @return int containing calculated age in years
     */
    int getAge() const noexcept;
    
    /**
     * @brief Get comprehensive user information
     * 
     * @return std::string containing formatted user details
     */
    std::string getInfo() const noexcept;
    
    /**
     * @brief Set the user name
     * 
     * @param newName constant reference to the string containing new name
     */
    void setName(const std::string& newName);
    
    /**
     * @brief Set the email address
     * 
     * @param newEmail constant reference to the string containing new email
     */
    void setEmail(const std::string& newEmail);
    
    /**
     * @brief Set the phone number
     * 
     * @param newPhone constant reference to the string containing new phone number
     */
    void setPhoneNumber(const std::string& newPhone);
    
    /**
     * @brief Set the address
     * 
     * @param newAddress constant reference to the string containing new address
     */
    void setAddress(const std::string& newAddress);
    
    /**
     * @brief Set the gender
     * 
     * @param newGender constant reference to the Male enum value containing new gender
     */
    void setMale(const Male& newGender);
    
    /**
     * @brief Verify password against stored hash
     * 
     * @param inputPassword constant reference to the string containing password to verify
     * 
     * @return true if password matches
     * @return false if password does not match
     */
    bool verifyPassword(const std::string& inputPassword) const;
    
    /**
     * @brief Change user password
     * 
     * @param oldPassword constant reference to the string containing current password
     * @param newPassword constant reference to the string containing new password
     */
    void changePassword(const std::string& oldPassword, const std::string& newPassword);
};