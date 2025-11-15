/**
 * @file Resort.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Resort class for resort accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class Resort
 * @brief Class representing resort type accommodation
 * 
 * Extends Accommodation with resort-specific properties like beach access,
 * restaurant count, and activity offerings. Provides methods for luxury
 * classification and comprehensive amenity assessment.
 */
class Resort : public Accommodation {
private:
    bool hasPrivateBeach;                                    ///< Private beach access flag
    int numberOfRestaurants;                                 ///< Number of restaurants on site
    bool hasSpa;                                             ///< Spa service availability flag
    std::vector<std::string> activities;                     ///< List of available activities

public:
    /**
     * @brief Construct a new Resort object
     * 
     * @param name constant reference to the string containing resort name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing resort rating
     * @param beach boolean value indicating private beach access
     * @param restaurants integer value containing restaurant count
     * @param spa boolean value indicating spa availability
     * @param activities constant reference to the vector containing activity list
     */
    Resort(const std::string& name, const std::string& location,
           double price, int capacity, double rating,
           bool beach, int restaurants, bool spa, const std::vector<std::string>& activities);
    
    /**
     * @brief Get the resort type
     * 
     * @return std::string containing "Resort"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive resort information
     * 
     * @return std::string containing formatted resort details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Check if resort has beach access
     * 
     * @return true if private beach access is available
     * @return false if private beach access is not available
     */
    bool hasBeachAccess() const;
    
    /**
     * @brief Get the restaurant count
     * 
     * @return int containing number of restaurants
     */
    int getRestaurantCount() const;
    
    /**
     * @brief Check if resort has spa services
     * 
     * @return true if spa services are available
     * @return false if spa services are not available
     */
    bool hasSpaServices() const;
    
    /**
     * @brief Get the list of activities
     * 
     * @return std::vector<std::string> containing all available activities
     */
    std::vector<std::string> getActivities() const;
    
    /**
     * @brief Check if resort is luxury category
     * 
     * @return true if resort is luxury
     * @return false if resort is not luxury
     */
    bool isLuxuryResort() const;
    
    /**
     * @brief Check if resort has comprehensive amenities
     * 
     * @return true if comprehensive amenities are available
     * @return false if comprehensive amenities are not available
     */
    bool hasComprehensiveAmenities() const;
    
    /**
     * @brief Get the activity count
     * 
     * @return int containing number of activities
     */
    int getActivityCount() const;
    
    /**
     * @brief Get resort category
     * 
     * @return std::string containing resort category
     */
    std::string getResortCategory() const;
    
    /**
     * @brief Check if resort is beach resort type
     * 
     * @return true if resort is beach-focused
     * @return false if resort is not beach-focused
     */
    bool isBeachResort() const;
};