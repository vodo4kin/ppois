/**
 * @file BreakfastBuffet.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BreakfastBuffet class for breakfast buffet meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class BreakfastBuffet
 * @brief Class representing breakfast buffet type meal
 * 
 * Extends Meal with breakfast buffet-specific properties like hot items,
 * beverage inclusions, and cuisine styles. Provides methods for international
 * classification and breakfast type assessment.
 */
class BreakfastBuffet : public Meal {
private:
    bool includesHotItems;                                  ///< Hot food items inclusion flag
    bool includesBeverages;                                 ///< Beverages inclusion flag
    std::vector<std::string> cuisineStyles;                 ///< Styles of cuisine available

public:
    /**
     * @brief Construct a new BreakfastBuffet object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param hotItems boolean value indicating hot items inclusion
     * @param beverages boolean value indicating beverages inclusion
     * @param cuisines constant reference to the vector containing cuisine styles
     */
    BreakfastBuffet(const std::string& name, const std::string& description,
                    double price, int calories, const std::vector<std::string>& tags,
                    bool hotItems, bool beverages, const std::vector<std::string>& cuisines);
    
    /**
     * @brief Get the breakfast buffet type
     * 
     * @return std::string containing "BreakfastBuffet"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive breakfast buffet information
     * 
     * @return std::string containing formatted breakfast buffet details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Check if buffet includes hot items
     * 
     * @return true if hot items are included
     * @return false if hot items are not included
     */
    bool hasHotItems() const;
    
    /**
     * @brief Check if buffet includes beverages
     * 
     * @return true if beverages are included
     * @return false if beverages are not included
     */
    bool hasBeverages() const;
    
    /**
     * @brief Get the cuisine styles
     * 
     * @return std::vector<std::string> containing all cuisine styles
     */
    std::vector<std::string> getCuisineStyles() const;
    
    /**
     * @brief Check if buffet is international style
     * 
     * @return true if international cuisine is offered
     * @return false if single cuisine style is offered
     */
    bool isInternationalBreakfast() const;
    
    /**
     * @brief Check if buffet is continental style
     * 
     * @return true if continental breakfast style
     * @return false if not continental breakfast style
     */
    bool isContinentalBreakfast() const;
    
    /**
     * @brief Get breakfast buffet category
     * 
     * @return std::string containing breakfast buffet category
     */
    std::string getBreakfastCategory() const;
};