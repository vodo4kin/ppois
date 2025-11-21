/**
 * @file BoutiqueHotel.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BoutiqueHotel class for boutique hotel accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class BoutiqueHotel
 * @brief Class representing boutique hotel type accommodation
 * 
 * Extends Accommodation with boutique hotel-specific properties like theme,
 * construction year, and architectural style. Provides methods for historic
 * classification and premium service assessment.
 */
class BoutiqueHotel : public Accommodation {
private:
    std::string theme;                                       ///< Hotel theme or concept
    int yearBuilt;                                           ///< Year of construction
    bool hasConcierge;                                       ///< Concierge service availability flag
    std::string architecturalStyle;                          ///< Architectural style description

public:
    /**
     * @brief Construct a new BoutiqueHotel object
     * 
     * @param name constant reference to the string containing hotel name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing hotel rating
     * @param theme constant reference to the string containing hotel theme
     * @param year integer value containing construction year
     * @param concierge boolean value indicating concierge service availability
     * @param style constant reference to the string containing architectural style
     */
    BoutiqueHotel(const std::string& name, const std::string& location,
                  double price, int capacity, double rating,
                  const std::string& theme, int year, bool concierge, const std::string& style);
    
    /**
     * @brief Get the boutique hotel type
     * 
     * @return std::string containing "BoutiqueHotel"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive boutique hotel information
     * 
     * @return std::string containing formatted boutique hotel details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the hotel theme
     * 
     * @return std::string containing hotel theme
     */
    std::string getTheme() const;
    
    /**
     * @brief Get the construction year
     * 
     * @return int containing year built
     */
    int getYearBuilt() const;
    
    /**
     * @brief Check if hotel has concierge service
     * 
     * @return true if concierge service is available
     * @return false if concierge service is not available
     */
    bool hasConciergeService() const;
    
    /**
     * @brief Get the architectural style
     * 
     * @return std::string containing architectural style
     */
    std::string getArchitecturalStyle() const;
    
    /**
     * @brief Check if hotel is historic
     * 
     * @return true if hotel is considered historic
     * @return false if hotel is not historic
     */
    bool isHistoric() const;
    
    /**
     * @brief Check if hotel is design hotel
     * 
     * @return true if hotel is design-focused
     * @return false if hotel is not design-focused
     */
    bool isDesignHotel() const;
    
    /**
     * @brief Check if hotel has premium services
     * 
     * @return true if hotel offers premium services
     * @return false if hotel does not offer premium services
     */
    bool hasPremiumServices() const;
    
    /**
     * @brief Get boutique hotel category
     * 
     * @return std::string containing boutique hotel category
     */
    std::string getBoutiqueCategory() const;
    
    /**
     * @brief Calculate hotel age
     * 
     * @return int containing hotel age in years
     */
    int calculateHotelAge() const;
};