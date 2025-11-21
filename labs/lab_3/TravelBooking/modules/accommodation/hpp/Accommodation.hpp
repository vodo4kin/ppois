/**
 * @file Accommodation.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Accommodation base class for accommodation system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

/**
 * @class Accommodation
 * @brief Base abstract class for all types of accommodations
 * 
 * Provides common interface and properties for various accommodation types
 * including hotels, apartments, villas, etc. Implements core functionality
 * for booking validation, pricing, and accommodation management.
 */
class Accommodation {
protected:
    std::string name;                                       ///< Name of the accommodation
    std::string location;                                   ///< Location address
    double pricePerNight;                                   ///< Price per night in currency units
    int capacity;                                           ///< Maximum number of guests
    double rating;                                          ///< User rating from 1 to 5
    std::vector<std::string> amenities;                     ///< List of available amenities

public:
    /**
     * @brief Construct a new Accommodation object
     * 
     * @param name constant reference to the string containing accommodation name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing accommodation rating
     */
    Accommodation(const std::string& name, const std::string& location, 
                  double price, int capacity, double rating);
    
    /**
     * @brief Get the accommodation type
     * 
     * Pure virtual method that must be implemented by derived classes
     * 
     * @return std::string containing accommodation type
     */
    virtual std::string getType() const = 0;
    
    /**
     * @brief Get comprehensive accommodation information
     * 
     * @return std::string containing formatted accommodation details
     */
    virtual std::string getAccommodationInfo() const;
    
    /**
     * @brief Destroy the Accommodation object
     */
    virtual ~Accommodation() = default;
    
    /**
     * @brief Get the accommodation name
     * 
     * @return std::string containing accommodation name
     */
    std::string getName() const;
    
    /**
     * @brief Get the accommodation location
     * 
     * @return std::string containing location address
     */
    std::string getLocation() const;
    
    /**
     * @brief Get the price per night
     * 
     * @return double containing price per night
     */
    double getPricePerNight() const;
    
    /**
     * @brief Get the maximum guest capacity
     * 
     * @return int containing maximum number of guests
     */
    int getCapacity() const;
    
    /**
     * @brief Get the accommodation rating
     * 
     * @return double containing rating value
     */
    double getRating() const;
    
    /**
     * @brief Get the list of amenities
     * 
     * @return std::vector<std::string> containing all amenities
     */
    std::vector<std::string> getAmenities() const;
    
    /**
     * @brief Add new amenity to accommodation
     * 
     * @param amenity constant reference to the string containing amenity name
     */
    void addAmenity(const std::string& amenity);
    
    /**
     * @brief Set the price per night
     * 
     * @param price double value containing new price
     */
    void setPricePerNight(double price);
    
    /**
     * @brief Set the accommodation rating
     * 
     * @param newRating double value containing new rating
     */
    void setRating(double newRating);
    
    /**
     * @brief Check if accommodation can accommodate specified number of guests
     * 
     * @param guests integer value containing number of guests to check
     * 
     * @return true if accommodation can accommodate guests
     * @return false if accommodation cannot accommodate guests
     */
    bool canAccommodate(int guests) const;
    
    /**
     * @brief Check if accommodation is available for specified dates
     * 
     * @param startDate constant reference to the string containing start date
     * @param endDate constant reference to the string containing end date
     * 
     * @return true if accommodation is available
     * @return false if accommodation is not available
     */
    bool isAvailableForDates(const std::string& startDate, const std::string& endDate) const;
    
    /**
     * @brief Validate booking parameters
     * 
     * @param guests integer value containing number of guests
     * @param startDate constant reference to the string containing start date
     * @param endDate constant reference to the string containing end date
     */
    void validateBooking(int guests, const std::string& startDate, const std::string& endDate) const;
};