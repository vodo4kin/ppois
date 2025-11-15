/**
 * @file PicnicLunch.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the PicnicLunch class for picnic lunch meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class PicnicLunch
 * @brief Class representing picnic lunch type meal
 * 
 * Extends Meal with picnic-specific properties like packaging,
 * heating requirements, and container types. Provides methods for
 * outdoor suitability and readiness assessment.
 */
class PicnicLunch : public Meal {
private:
    bool isPrePackaged;                                     ///< Pre-packaged meal flag
    bool needsHeating;                                      ///< Heating requirement flag
    std::vector<std::string> containerTypes;                ///< Types of containers used

public:
    /**
     * @brief Construct a new PicnicLunch object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param prePackaged boolean value indicating pre-packaged status
     * @param heating boolean value indicating heating requirement
     * @param containers constant reference to the vector containing container types
     */
    PicnicLunch(const std::string& name, const std::string& description,
                double price, int calories, const std::vector<std::string>& tags,
                bool prePackaged, bool heating, const std::vector<std::string>& containers);
    
    /**
     * @brief Get the picnic lunch type
     * 
     * @return std::string containing "PicnicLunch"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive picnic lunch information
     * 
     * @return std::string containing formatted picnic lunch details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Check if meal is pre-packaged
     * 
     * @return true if meal is pre-packaged
     * @return false if meal is not pre-packaged
     */
    bool isPrePackagedMeal() const;
    
    /**
     * @brief Check if meal needs heating
     * 
     * @return true if heating is required
     * @return false if heating is not required
     */
    bool needsHeatings() const;
    
    /**
     * @brief Get the container types
     * 
     * @return std::vector<std::string> containing all container types
     */
    std::vector<std::string> getContainerTypes() const;
    
    /**
     * @brief Check if meal is ready to eat
     * 
     * @return true if meal is ready to eat without preparation
     * @return false if meal requires preparation
     */
    bool isReadyToEat() const;
    
    /**
     * @brief Check if meal is outdoor friendly
     * 
     * @return true if meal is suitable for outdoor consumption
     * @return false if meal is not suitable for outdoor consumption
     */
    bool isOutdoorFriendly() const;
    
    /**
     * @brief Get picnic lunch category
     * 
     * @return std::string containing picnic lunch category
     */
    std::string getPicnicCategory() const;
};