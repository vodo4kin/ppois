/**
 * @file Villa.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Villa class for villa accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class Villa
 * @brief Class representing villa type accommodation
 * 
 * Extends Accommodation with villa-specific properties like floor count,
 * private pool, and outdoor spaces. Provides methods for luxury classification
 * and event suitability assessment.
 */
class Villa : public Accommodation {
private:
    int numberOfFloors;                                      ///< Number of floors in villa
    bool hasPrivatePool;                                     ///< Private pool availability flag
    bool hasGarden;                                          ///< Garden area availability flag
    bool hasParking;                                         ///< Parking space availability flag

public:
    /**
     * @brief Construct a new Villa object
     * 
     * @param name constant reference to the string containing villa name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing villa rating
     * @param floors integer value containing number of floors
     * @param pool boolean value indicating private pool availability
     * @param garden boolean value indicating garden availability
     * @param parking boolean value indicating parking availability
     */
    Villa(const std::string& name, const std::string& location,
          double price, int capacity, double rating,
          int floors, bool pool, bool garden, bool parking);
    
    /**
     * @brief Get the villa type
     * 
     * @return std::string containing "Villa"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive villa information
     * 
     * @return std::string containing formatted villa details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the number of floors
     * 
     * @return int containing floor count
     */
    int getNumberOfFloors() const;
    
    /**
     * @brief Check if villa has private pool
     * 
     * @return true if private pool is available
     * @return false if private pool is not available
     */
    bool hasPool() const;
    
    /**
     * @brief Check if villa has garden area
     * 
     * @return true if garden area is available
     * @return false if garden area is not available
     */
    bool hasGardenArea() const;
    
    /**
     * @brief Check if villa has parking space
     * 
     * @return true if parking space is available
     * @return false if parking space is not available
     */
    bool hasParkingSpace() const;
    
    /**
     * @brief Check if villa is luxury category
     * 
     * @return true if villa is luxury
     * @return false if villa is not luxury
     */
    bool isLuxuryVilla() const;
    
    /**
     * @brief Check if villa has full privacy
     * 
     * @return true if villa offers full privacy
     * @return false if villa does not offer full privacy
     */
    bool hasFullPrivacy() const;
    
    /**
     * @brief Calculate luxury surcharge
     * 
     * @return double containing calculated luxury surcharge amount
     */
    double calculateLuxurySurcharge() const;
    
    /**
     * @brief Get villa category
     * 
     * @return std::string containing villa category
     */
    std::string getVillaCategory() const;
    
    /**
     * @brief Check if villa is suitable for events
     * 
     * @return true if suitable for events
     * @return false if not suitable for events
     */
    bool isSuitableForEvents() const;
};