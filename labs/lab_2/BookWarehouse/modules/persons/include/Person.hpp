/**
 * @file Person.hpp  
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Person base class for all person entities in the system
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Address.hpp"
#include "ContactInfo.hpp"

// Forward declarations
class Address;
class ContactInfo;

/**
 * @class Person
 * @brief Base class for all person entities in the system
 * 
 * Provides common functionality for customers and employees including
 * personal information, addresses, and contact details. Serves as foundation
 * for all human entities in the book warehouse system.
 */
class Person {
private:
    std::string id;                         ///< Unique identifier for the person
    std::string firstName;                  ///< First name of the person
    std::string lastName;                   ///< Last name of the person
    std::string dateOfBirth;                ///< Date of birth in YYYY-MM-DD format
    std::shared_ptr<Address> address;       ///< Physical address of the person
    std::shared_ptr<ContactInfo> contactInfo; ///< Contact information

    /**
     * @brief Private method to validate person ID format
     * 
     * @param id constant reference to the string containing ID to validate
     * 
     * @return true if ID format is valid
     * @return false if ID format is invalid
     */
    bool isValidId(const std::string& id) const;

    /**
     * @brief Private method to validate name components
     * 
     * @param name constant reference to the string containing name to validate
     * 
     * @return true if name is valid
     * @return false if name is invalid
     */
    bool isValidName(const std::string& name) const;

    /**
     * @brief Private method to validate date of birth
     * 
     * @param date constant reference to the string containing date to validate
     * 
     * @return true if date is valid
     * @return false if date is invalid
     */
    bool isValidDateOfBirth(const std::string& date) const;

public:
    /**
     * @brief Construct a new Person object
     * 
     * @param id constant reference to the string containing unique identifier
     * @param firstName constant reference to the string containing first name
     * @param lastName constant reference to the string containing last name
     * @param dateOfBirth constant reference to the string containing date of birth
     * @param address shared pointer to the Address object
     * @param contactInfo shared pointer to the ContactInfo object
     */
    Person(const std::string& id, const std::string& firstName, const std::string& lastName,
           const std::string& dateOfBirth, std::shared_ptr<Address> address,
           std::shared_ptr<ContactInfo> contactInfo);

    /**
     * @brief Destroy the Person object
     */
    virtual ~Person() = default;

    /**
     * @brief Get the person identifier
     * 
     * @return std::string containing unique identifier
     */
    std::string getId() const noexcept;

    /**
     * @brief Get the first name
     * 
     * @return std::string containing first name
     */
    std::string getFirstName() const noexcept;

    /**
     * @brief Get the last name
     * 
     * @return std::string containing last name
     */
    std::string getLastName() const noexcept;

    /**
     * @brief Get the full name
     * 
     * @return std::string containing full name (first + last)
     */
    std::string getFullName() const noexcept;

    /**
     * @brief Get the date of birth
     * 
     * @return std::string containing date of birth
     */
    std::string getDateOfBirth() const noexcept;

    /**
     * @brief Get the address
     * 
     * @return std::shared_ptr<Address> containing address information
     */
    std::shared_ptr<Address> getAddress() const noexcept;

    /**
     * @brief Get the contact information
     * 
     * @return std::shared_ptr<ContactInfo> containing contact information
     */
    std::shared_ptr<ContactInfo> getContactInfo() const noexcept;

    /**
     * @brief Set the first name
     * 
     * @param firstName constant reference to the string containing new first name
     */
    void setFirstName(const std::string& firstName);

    /**
     * @brief Set the last name
     * 
     * @param lastName constant reference to the string containing new last name
     */
    void setLastName(const std::string& lastName);

    /**
     * @brief Set the address
     * 
     * @param address shared pointer to the Address object
     */
    void setAddress(std::shared_ptr<Address> address);

    /**
     * @brief Set the contact information
     * 
     * @param contactInfo shared pointer to the ContactInfo object
     */
    void setContactInfo(std::shared_ptr<ContactInfo> contactInfo);

    /**
     * @brief Calculate current age of the person
     * 
     * @return int containing current age in years
     */
    int calculateAge() const;

    /**
     * @brief Check if person is adult (18+ years)
     * 
     * @return true if person is adult
     * @return false if person is not adult
     */
    bool isAdult() const noexcept;

    /**
     * @brief Get person information
     * 
     * @return std::string containing formatted person information
     */
    virtual std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for persons
     * 
     * @param other constant reference to the person to compare with
     * 
     * @return true if persons are equal
     * @return false if persons are not equal
     */
    bool operator==(const Person& other) const noexcept;

    /**
     * @brief Inequality comparison operator for persons
     * 
     * @param other constant reference to the person to compare with
     * 
     * @return true if persons are not equal
     * @return false if persons are equal
     */
    bool operator!=(const Person& other) const noexcept;
};