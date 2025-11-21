/**
 * @file MountainLodge.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the MountainLodge class for mountain lodge accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class MountainLodge
 * @brief Class representing mountain lodge type accommodation
 * 
 * Extends Accommodation with mountain lodge-specific properties like altitude,
 * heating systems, and accessibility. Provides methods for winter readiness
 * assessment and experience requirement evaluation.
 */
class MountainLodge : public Accommodation {
private:
    int altitude;                                            ///< Altitude in meters above sea level
    bool hasHeating;                                         ///< Heating system availability flag
    bool hasFireplace;                                       ///< Fireplace availability flag
    std::string accessibility;                               ///< Accessibility level description

public:
    /**
     * @brief Construct a new MountainLodge object
     * 
     * @param name constant reference to the string containing lodge name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing lodge rating
     * @param altitude integer value containing altitude in meters
     * @param heating boolean value indicating heating system availability
     * @param fireplace boolean value indicating fireplace availability
     * @param accessibility constant reference to the string containing accessibility level
     */
    MountainLodge(const std::string& name, const std::string& location,
                  double price, int capacity, double rating,
                  int altitude, bool heating, bool fireplace, const std::string& accessibility);
    
    /**
     * @brief Get the mountain lodge type
     * 
     * @return std::string containing "MountainLodge"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive mountain lodge information
     * 
     * @return std::string containing formatted mountain lodge details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the altitude
     * 
     * @return int containing altitude in meters
     */
    int getAltitude() const;
    
    /**
     * @brief Check if lodge has heating system
     * 
     * @return true if heating system is available
     * @return false if heating system is not available
     */
    bool hasHeatingSystem() const;
    
    /**
     * @brief Check if lodge has fireplace feature
     * 
     * @return true if fireplace is available
     * @return false if fireplace is not available
     */
    bool hasFireplaceFeature() const;
    
    /**
     * @brief Get the accessibility level
     * 
     * @return std::string containing accessibility description
     */
    std::string getAccessibilityLevel() const;
    
    /**
     * @brief Check if lodge is at high altitude
     * 
     * @return true if altitude is considered high
     * @return false if altitude is not considered high
     */
    bool isHighAltitude() const;
    
    /**
     * @brief Check if lodge is winter ready
     * 
     * @return true if lodge is prepared for winter conditions
     * @return false if lodge is not prepared for winter conditions
     */
    bool isWinterReady() const;
    
    /**
     * @brief Get lodge category
     * 
     * @return std::string containing lodge category
     */
    std::string getLodgeCategory() const;
    
    /**
     * @brief Check if lodge is in remote location
     * 
     * @return true if location is remote
     * @return false if location is not remote
     */
    bool isRemoteLocation() const;
    
    /**
     * @brief Check if lodge requires outdoor experience
     * 
     * @return true if outdoor experience is recommended
     * @return false if outdoor experience is not required
     */
    bool requiresExperience() const;
};