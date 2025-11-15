/**
 * @file EthnicDinner.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the EthnicDinner class for ethnic dinner meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class EthnicDinner
 * @brief Class representing ethnic dinner type meal
 * 
 * Extends Meal with ethnic dinner-specific properties like cuisine type,
 * cooking demonstrations, and traditional drinks. Provides methods for
 * authenticity assessment and serving style classification.
 */
class EthnicDinner : public Meal {
private:
    std::string cuisine;                                    ///< Type of ethnic cuisine
    bool cookingDemo;                                       ///< Cooking demonstration flag
    bool includesTraditionalDrinks;                         ///< Traditional drinks inclusion flag
    std::string servingStyle;                               ///< Style of serving

public:
    /**
     * @brief Construct a new EthnicDinner object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param cuisine constant reference to the string containing cuisine type
     * @param demo boolean value indicating cooking demonstration
     * @param traditionalDrinks boolean value indicating traditional drinks inclusion
     * @param servingStyle constant reference to the string containing serving style
     */
    EthnicDinner(const std::string& name, const std::string& description,
                 double price, int calories, const std::vector<std::string>& tags,
                 const std::string& cuisine, bool demo, bool traditionalDrinks, 
                 const std::string& servingStyle);
    
    /**
     * @brief Get the ethnic dinner type
     * 
     * @return std::string containing "EthnicDinner"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive ethnic dinner information
     * 
     * @return std::string containing formatted ethnic dinner details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Get the cuisine type
     * 
     * @return std::string containing cuisine description
     */
    std::string getCuisine() const;
    
    /**
     * @brief Check if dinner includes cooking demo
     * 
     * @return true if cooking demonstration is included
     * @return false if cooking demonstration is not included
     */
    bool hasCookingDemo() const;
    
    /**
     * @brief Check if dinner includes traditional drinks
     * 
     * @return true if traditional drinks are included
     * @return false if traditional drinks are not included
     */
    bool hasTraditionalDrinks() const;
    
    /**
     * @brief Get the serving style
     * 
     * @return std::string containing serving style description
     */
    std::string getServingStyle() const;
    
    /**
     * @brief Check if dinner offers authentic experience
     * 
     * @return true if authentic cultural experience
     * @return false if modified cultural experience
     */
    bool isAuthenticExperience() const;
    
    /**
     * @brief Check if dinner is family style
     * 
     * @return true if family-style serving
     * @return false if individual serving
     */
    bool isFamilyStyle() const;
    
    /**
     * @brief Get ethnic dinner category
     * 
     * @return std::string containing ethnic dinner category
     */
    std::string getEthnicCategory() const;
};