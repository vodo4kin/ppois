/**
 * @file BarbecueMeal.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BarbecueMeal class for barbecue meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class BarbecueMeal
 * @brief Class representing barbecue type meal
 * 
 * Extends Meal with barbecue-specific properties like meat varieties,
 * vegetarian options, and service style. Provides methods for outdoor
 * classification and option variety assessment.
 */
class BarbecueMeal : public Meal {
private:
    std::vector<std::string> meatTypes;                     ///< Types of meat available
    bool vegetarianOptions;                                 ///< Vegetarian options availability flag
    bool selfService;                                       ///< Self-service style flag
    std::string locationType;                               ///< Type of barbecue location

public:
    /**
     * @brief Construct a new BarbecueMeal object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param meats constant reference to the vector containing meat types
     * @param veggie boolean value indicating vegetarian options availability
     * @param selfService boolean value indicating self-service style
     * @param location constant reference to the string containing location type
     */
    BarbecueMeal(const std::string& name, const std::string& description,
                 double price, int calories, const std::vector<std::string>& tags,
                 const std::vector<std::string>& meats, bool veggie, bool selfService, 
                 const std::string& location);
    
    /**
     * @brief Get the barbecue meal type
     * 
     * @return std::string containing "BarbecueMeal"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive barbecue meal information
     * 
     * @return std::string containing formatted barbecue meal details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Get the meat types
     * 
     * @return std::vector<std::string> containing all meat types
     */
    std::vector<std::string> getMeatTypes() const;
    
    /**
     * @brief Check if meal has vegetarian options
     * 
     * @return true if vegetarian options are available
     * @return false if vegetarian options are not available
     */
    bool hasVegetarianOptions() const;
    
    /**
     * @brief Check if meal is self-service
     * 
     * @return true if self-service style
     * @return false if full-service style
     */
    bool isSelfService() const;
    
    /**
     * @brief Get the location type
     * 
     * @return std::string containing location type description
     */
    std::string getLocationType() const;
    
    /**
     * @brief Check if barbecue is outdoor type
     * 
     * @return true if outdoor barbecue
     * @return false if indoor barbecue
     */
    bool isOutdoorBarbecue() const;
    
    /**
     * @brief Check if barbecue has multiple meat options
     * 
     * @return true if multiple meat options available
     * @return false if limited meat options available
     */
    bool hasMultipleMeatOptions() const;
    
    /**
     * @brief Get barbecue meal category
     * 
     * @return std::string containing barbecue meal category
     */
    std::string getBarbecueCategory() const;
};