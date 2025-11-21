/**
 * @file CruiseCabin.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the CruiseCabin class for cruise cabin accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class CruiseCabin
 * @brief Class representing cruise cabin type accommodation
 * 
 * Extends Accommodation with cruise cabin-specific properties like cabin type,
 * deck number, and ocean view availability. Provides methods for premium
 * classification and deck level assessment.
 */
class CruiseCabin : public Accommodation {
private:
    std::string cabinType;                                   ///< Type of cruise cabin
    int deckNumber;                                          ///< Deck number location
    bool hasWindow;                                          ///< Window or ocean view availability flag
    std::string shipName;                                    ///< Name of the cruise ship

public:
    /**
     * @brief Construct a new CruiseCabin object
     * 
     * @param name constant reference to the string containing cabin name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing cabin rating
     * @param cabinType constant reference to the string containing cabin type
     * @param deck integer value containing deck number
     * @param window boolean value indicating window availability
     * @param ship constant reference to the string containing ship name
     */
    CruiseCabin(const std::string& name, const std::string& location,
                double price, int capacity, double rating,
                const std::string& cabinType, int deck, bool window, const std::string& ship);
    
    /**
     * @brief Get the cruise cabin type
     * 
     * @return std::string containing "CruiseCabin"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive cruise cabin information
     * 
     * @return std::string containing formatted cruise cabin details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the cabin type
     * 
     * @return std::string containing cabin type
     */
    std::string getCabinType() const;
    
    /**
     * @brief Get the deck number
     * 
     * @return int containing deck number
     */
    int getDeckNumber() const;
    
    /**
     * @brief Check if cabin has ocean view
     * 
     * @return true if cabin has ocean view
     * @return false if cabin does not have ocean view
     */
    bool hasOceanView() const;
    
    /**
     * @brief Get the ship name
     * 
     * @return std::string containing cruise ship name
     */
    std::string getShipName() const;
    
    /**
     * @brief Check if cabin is premium category
     * 
     * @return true if cabin is premium
     * @return false if cabin is not premium
     */
    bool isPremiumCabin() const;
    
    /**
     * @brief Check if cabin is interior type
     * 
     * @return true if cabin is interior
     * @return false if cabin is not interior
     */
    bool isInteriorCabin() const;
    
    /**
     * @brief Check if cabin has any view
     * 
     * @return true if cabin has view
     * @return false if cabin has no view
     */
    bool hasView() const;
    
    /**
     * @brief Get cabin category
     * 
     * @return std::string containing cabin category
     */
    std::string getCabinCategory() const;
    
    /**
     * @brief Check if cabin is on upper deck
     * 
     * @return true if cabin is on upper deck
     * @return false if cabin is not on upper deck
     */
    bool isOnUpperDeck() const;
};