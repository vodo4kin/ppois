/**
 * @file Camping.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Camping class for camping accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class Camping
 * @brief Class representing camping type accommodation
 * 
 * Extends Accommodation with camping-specific properties like accommodation type,
 * shared facilities, and campfire permissions. Provides methods for glamping
 * classification and family suitability assessment.
 */
class Camping : public Accommodation {
private:
    std::string accommodationType;                           ///< Type of camping accommodation
    bool hasSharedBathroom;                                  ///< Shared bathroom availability flag
    bool hasElectricity;                                     ///< Electricity availability flag
    bool campfireAllowed;                                    ///< Campfire permission flag

public:
    /**
     * @brief Construct a new Camping object
     * 
     * @param name constant reference to the string containing camping name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing camping rating
     * @param accType constant reference to the string containing accommodation type
     * @param sharedBath boolean value indicating shared bathroom availability
     * @param electricity boolean value indicating electricity availability
     * @param campfire boolean value indicating campfire permission
     */
    Camping(const std::string& name, const std::string& location,
            double price, int capacity, double rating,
            const std::string& accType, bool sharedBath, bool electricity, bool campfire);
    
    /**
     * @brief Get the camping type
     * 
     * @return std::string containing "Camping"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive camping information
     * 
     * @return std::string containing formatted camping details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the accommodation type
     * 
     * @return std::string containing camping accommodation type
     */
    std::string getAccommodationType() const;
    
    /**
     * @brief Check if camping has shared bathrooms
     * 
     * @return true if shared bathrooms are available
     * @return false if shared bathrooms are not available
     */
    bool hasSharedBathrooms() const;
    
    /**
     * @brief Check if camping has electrical access
     * 
     * @return true if electricity is available
     * @return false if electricity is not available
     */
    bool hasElectricalAccess() const;
    
    /**
     * @brief Check if campfire is allowed
     * 
     * @return true if campfire is permitted
     * @return false if campfire is not permitted
     */
    bool isCampfireAllowed() const;
    
    /**
     * @brief Check if camping is glamping type
     * 
     * @return true if camping is glamping
     * @return false if camping is not glamping
     */
    bool isGlamping() const;
    
    /**
     * @brief Check if camping is basic type
     * 
     * @return true if camping is basic
     * @return false if camping is not basic
     */
    bool isBasicCamping() const;
    
    /**
     * @brief Check if camping has essential amenities
     * 
     * @return true if essential amenities are available
     * @return false if essential amenities are not available
     */
    bool hasEssentialAmenities() const;
    
    /**
     * @brief Get camping category
     * 
     * @return std::string containing camping category
     */
    std::string getCampingCategory() const;
    
    /**
     * @brief Check if camping is family friendly
     * 
     * @return true if camping is suitable for families
     * @return false if camping is not suitable for families
     */
    bool isFamilyFriendly() const;
};