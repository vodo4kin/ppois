/**
 * @file Address.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Address class for working with physical addresses
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class Address
 * @brief Class for working with physical addresses
 * 
 * Represents a complete physical address with street, city, postal code,
 * and country components. Provides validation and formatting operations.
 */
class Address {
private:
    std::string street;         ///< Street address with house number
    std::string city;           ///< City name
    std::string postalCode;     ///< Postal/ZIP code
    std::string country;        ///< Country name

    /**
     * @brief Private method to validate street address
     * 
     * @param street constant reference to the string containing street to validate
     * 
     * @return true if street is valid
     * @return false if street is invalid
     */
    bool isValidStreet(const std::string& street) const;

    /**
     * @brief Private method to validate city name
     * 
     * @param city constant reference to the string containing city to validate
     * 
     * @return true if city is valid
     * @return false if city is invalid
     */
    bool isValidCity(const std::string& city) const;

    /**
     * @brief Private method to validate postal code
     * 
     * @param postalCode constant reference to the string containing postal code to validate
     * 
     * @return true if postal code is valid
     * @return false if postal code is invalid
     */
    bool isValidPostalCode(const std::string& postalCode) const;

    /**
     * @brief Private method to validate country name
     * 
     * @param country constant reference to the string containing country to validate
     * 
     * @return true if country is valid
     * @return false if country is invalid
     */
    bool isValidCountry(const std::string& country) const;

public:
    /**
     * @brief Construct a new Address object
     * 
     * @param street constant reference to the string containing street address
     * @param city constant reference to the string containing city name
     * @param postalCode constant reference to the string containing postal code
     * @param country constant reference to the string containing country name
     */
    Address(const std::string& street, const std::string& city, 
            const std::string& postalCode, const std::string& country);

    /**
     * @brief Get the street address
     * 
     * @return std::string containing street address
     */
    std::string getStreet() const noexcept;

    /**
     * @brief Get the city name
     * 
     * @return std::string containing city name
     */
    std::string getCity() const noexcept;

    /**
     * @brief Get the postal code
     * 
     * @return std::string containing postal code
     */
    std::string getPostalCode() const noexcept;

    /**
     * @brief Get the country name
     * 
     * @return std::string containing country name
     */
    std::string getCountry() const noexcept;

    /**
     * @brief Get the full formatted address
     * 
     * @return std::string containing complete formatted address
     */
    std::string getFullAddress() const noexcept;

    /**
     * @brief Set the street address
     * 
     * @param street constant reference to the string containing new street address
     */
    void setStreet(const std::string& street);

    /**
     * @brief Set the city name
     * 
     * @param city constant reference to the string containing new city name
     */
    void setCity(const std::string& city);

    /**
     * @brief Set the postal code
     * 
     * @param postalCode constant reference to the string containing new postal code
     */
    void setPostalCode(const std::string& postalCode);

    /**
     * @brief Set the country name
     * 
     * @param country constant reference to the string containing new country name
     */
    void setCountry(const std::string& country);

    /**
     * @brief Check if address is complete (all fields filled)
     * 
     * @return true if address is complete
     * @return false if address is incomplete
     */
    bool isComplete() const noexcept;

    /**
     * @brief Get address information
     * 
     * @return std::string containing formatted address information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for addresses
     * 
     * @param other constant reference to the address to compare with
     * 
     * @return true if addresses are equal
     * @return false if addresses are not equal
     */
    bool operator==(const Address& other) const noexcept;

    /**
     * @brief Inequality comparison operator for addresses
     * 
     * @param other constant reference to the address to compare with
     * 
     * @return true if addresses are not equal
     * @return false if addresses are equal
     */
    bool operator!=(const Address& other) const noexcept;
};