/**
 * @file Hotel.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Hotel class for hotel accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class Hotel
 * @brief Class representing hotel type accommodation
 * 
 * Extends Accommodation with hotel-specific properties like star rating,
 * pool availability, and spa services. Provides methods for luxury
 * service assessment and room type classification.
 */
class Hotel : public Accommodation {
private:
    int starRating;                                          ///< Hotel star rating
    bool hasPool;                                            ///< Swimming pool availability flag
    bool hasSpa;                                             ///< Spa service availability flag
    std::string roomType;                                    ///< Type of hotel room

public:
    /**
     * @brief Construct a new Hotel object
     * 
     * @param name constant reference to the string containing hotel name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing hotel rating
     * @param stars integer value containing star rating
     * @param pool boolean value indicating pool availability
     * @param spa boolean value indicating spa availability
     * @param roomType constant reference to the string containing room type
     */
    Hotel(const std::string& name, const std::string& location, 
          double price, int capacity, double rating,
          int stars, bool pool, bool spa, const std::string& roomType);
    
    /**
     * @brief Get the hotel type
     * 
     * @return std::string containing "Hotel"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive hotel information
     * 
     * @return std::string containing formatted hotel details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the star rating
     * 
     * @return int containing star rating value
     */
    int getStarRating() const;
    
    /**
     * @brief Check if hotel has swimming pool
     * 
     * @return true if swimming pool is available
     * @return false if swimming pool is not available
     */
    bool hasSwimmingPool() const;
    
    /**
     * @brief Check if hotel has spa service
     * 
     * @return true if spa service is available
     * @return false if spa service is not available
     */
    bool hasSpaService() const;
    
    /**
     * @brief Get the room type
     * 
     * @return std::string containing room type description
     */
    std::string getRoomType() const;
};