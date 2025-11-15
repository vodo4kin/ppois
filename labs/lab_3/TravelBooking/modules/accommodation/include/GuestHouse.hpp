/**
 * @file GuestHouse.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the GuestHouse class for guest house accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class GuestHouse
 * @brief Class representing guest house type accommodation
 * 
 * Extends Accommodation with guest house-specific properties like ownership type,
 * total room count, and common areas. Provides methods for service assessment
 * and long-stay suitability.
 */
class GuestHouse : public Accommodation {
private:
    bool isFamilyOwned;                                      ///< Family ownership flag
    int totalRooms;                                          ///< Total number of rooms in guest house
    std::string hostLanguage;                                ///< Primary language spoken by hosts
    bool hasCommonArea;                                      ///< Common area availability flag

public:
    /**
     * @brief Construct a new GuestHouse object
     * 
     * @param name constant reference to the string containing guest house name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing guest house rating
     * @param familyOwned boolean value indicating family ownership
     * @param totalRooms integer value containing total room count
     * @param language constant reference to the string containing host language
     * @param commonArea boolean value indicating common area availability
     */
    GuestHouse(const std::string& name, const std::string& location,
               double price, int capacity, double rating,
               bool familyOwned, int totalRooms, const std::string& language, bool commonArea);
    
    /**
     * @brief Get the guest house type
     * 
     * @return std::string containing "GuestHouse"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive guest house information
     * 
     * @return std::string containing formatted guest house details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Check if guest house is family business
     * 
     * @return true if guest house is family-owned
     * @return false if guest house is not family-owned
     */
    bool isFamilyBusiness() const;
    
    /**
     * @brief Get the total number of rooms
     * 
     * @return int containing total room count
     */
    int getTotalRooms() const;
    
    /**
     * @brief Get the host language
     * 
     * @return std::string containing primary host language
     */
    std::string getHostLanguage() const;
    
    /**
     * @brief Check if guest house has common space
     * 
     * @return true if common area is available
     * @return false if common area is not available
     */
    bool hasCommonSpace() const;
    
    /**
     * @brief Check if guest house is small size
     * 
     * @return true if guest house is small
     * @return false if guest house is not small
     */
    bool isSmallGuestHouse() const;
    
    /**
     * @brief Check if guest house offers personal service
     * 
     * @return true if personal service is offered
     * @return false if personal service is not offered
     */
    bool offersPersonalService() const;
    
    /**
     * @brief Get guest house type classification
     * 
     * @return std::string containing guest house type
     */
    std::string getGuestHouseType() const;
    
    /**
     * @brief Check if guest house is suitable for long stay
     * 
     * @return true if suitable for long stay
     * @return false if not suitable for long stay
     */
    bool isSuitableForLongStay() const;
    
    /**
     * @brief Check if guest house has community atmosphere
     * 
     * @return true if community atmosphere is present
     * @return false if community atmosphere is not present
     */
    bool hasCommunityAtmosphere() const;
};