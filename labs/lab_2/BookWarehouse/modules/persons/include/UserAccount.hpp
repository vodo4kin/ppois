/**
 * @file UserAccount.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the UserAccount class for managing user authentication and accounts
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Person.hpp"

/**
 * @class UserAccount
 * @brief Class for managing user authentication and account information
 * 
 * Handles user authentication, password management, and account status.
 * Provides secure password validation and account locking functionality.
 */
class UserAccount {
private:
    std::string username;                    ///< Unique username for login
    std::string passwordHash;                ///< Hashed password for security
    std::shared_ptr<Person> person;          ///< Associated person information
    std::string accountCreated;              ///< Date when account was created
    bool isLocked;                           ///< Account lock status
    int failedLoginAttempts;                 ///< Count of consecutive failed login attempts

    /**
     * @brief Private method to validate username format
     * 
     * @param username constant reference to the string containing username to validate
     * 
     * @return true if username is valid
     * @return false if username is invalid
     */
    bool isValidUsername(const std::string& username) const;

    /**
     * @brief Private method to validate password strength
     * 
     * @param password constant reference to the string containing password to validate
     * 
     * @return true if password meets strength requirements
     * @return false if password does not meet strength requirements
     */
    bool isValidPassword(const std::string& password) const;

    /**
     * @brief Private method to hash password
     * 
     * @param password constant reference to the string containing password to hash
     * 
     * @return std::string containing hashed password
     */
    std::string hashPassword(const std::string& password) const;

public:
    /**
     * @brief Construct a new UserAccount object
     * 
     * @param username constant reference to the string containing username
     * @param password constant reference to the string containing plain text password
     * @param person shared pointer to the Person object
     */
    UserAccount(const std::string& username, const std::string& password, 
                std::shared_ptr<Person> person);

    /**
     * @brief Get the username
     * 
     * @return std::string containing username
     */
    std::string getUsername() const noexcept;

    /**
     * @brief Get the associated person
     * 
     * @return std::shared_ptr<Person> containing person information
     */
    std::shared_ptr<Person> getPerson() const noexcept;

    /**
     * @brief Get the account creation date
     * 
     * @return std::string containing account creation date
     */
    std::string getAccountCreated() const noexcept;

    /**
     * @brief Check if account is locked
     * 
     * @return true if account is locked
     * @return false if account is not locked
     */
    bool isAccountLocked() const noexcept;

    /**
     * @brief Get the failed login attempts count
     * 
     * @return int containing number of failed login attempts
     */
    int getFailedLoginAttempts() const noexcept;

    /**
     * @brief Authenticate user with password
     * 
     * @param password constant reference to the string containing password to verify
     * 
     * @return true if authentication successful
     * @return false if authentication failed
     */
    bool authenticate(const std::string& password) const;

    /**
     * @brief Change user password
     * 
     * @param oldPassword constant reference to the string containing current password
     * @param newPassword constant reference to the string containing new password
     */
    void changePassword(const std::string& oldPassword, const std::string& newPassword);

    /**
     * @brief Reset password (admin function)
     * 
     * @param newPassword constant reference to the string containing new password
     */
    void resetPassword(const std::string& newPassword);

    /**
     * @brief Lock the account
     */
    void lockAccount() noexcept;

    /**
     * @brief Unlock the account
     */
    void unlockAccount() noexcept;

    /**
     * @brief Reset failed login attempts counter
     */
    void resetFailedAttempts() noexcept;

    /**
     * @brief Check if password needs to be changed (expired)
     * 
     * @return true if password needs to be changed
     * @return false if password is still valid
     */
    bool isPasswordExpired() const;

    /**
     * @brief Get account information
     * 
     * @return std::string containing formatted account information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for user accounts
     * 
     * @param other constant reference to the user account to compare with
     * 
     * @return true if user accounts are equal
     * @return false if user accounts are not equal
     */
    bool operator==(const UserAccount& other) const noexcept;

    /**
     * @brief Inequality comparison operator for user accounts
     * 
     * @param other constant reference to the user account to compare with
     * 
     * @return true if user accounts are not equal
     * @return false if user accounts are equal
     */
    bool operator!=(const UserAccount& other) const noexcept;
};