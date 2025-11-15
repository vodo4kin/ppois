/**
 * @file DietarySpecificMeal.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the DietarySpecificMeal class for dietary-specific meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class DietarySpecificMeal
 * @brief Class representing dietary-specific type meal
 * 
 * Extends Meal with dietary-specific properties like diet type,
 * nutritionist approval, and allergen exclusions. Provides methods for
 * strict diet classification and allergen-free assessment.
 */
class DietarySpecificMeal : public Meal {
private:
    std::string dietType;                                   ///< Type of diet followed
    bool nutritionistApproved;                              ///< Nutritionist approval flag
    std::string portionControl;                             ///< Portion control description
    std::vector<std::string> allergensExcluded;             ///< List of excluded allergens

public:
    /**
     * @brief Construct a new DietarySpecificMeal object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param dietType constant reference to the string containing diet type
     * @param approved boolean value indicating nutritionist approval
     * @param portion constant reference to the string containing portion control
     * @param allergens constant reference to the vector containing excluded allergens
     */
    DietarySpecificMeal(const std::string& name, const std::string& description,
                        double price, int calories, const std::vector<std::string>& tags,
                        const std::string& dietType, bool approved, 
                        const std::string& portion, const std::vector<std::string>& allergens);
    
    /**
     * @brief Get the dietary-specific meal type
     * 
     * @return std::string containing "DietarySpecificMeal"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive dietary-specific meal information
     * 
     * @return std::string containing formatted dietary-specific meal details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Get the diet type
     * 
     * @return std::string containing diet type description
     */
    std::string getDietType() const;
    
    /**
     * @brief Check if meal is nutritionist approved
     * 
     * @return true if nutritionist approved
     * @return false if not nutritionist approved
     */
    bool isNutritionistApproved() const;
    
    /**
     * @brief Get the portion control description
     * 
     * @return std::string containing portion control information
     */
    std::string getPortionControl() const;
    
    /**
     * @brief Get the excluded allergens
     * 
     * @return std::vector<std::string> containing all excluded allergens
     */
    std::vector<std::string> getAllergensExcluded() const;
    
    /**
     * @brief Check if meal follows strict diet
     * 
     * @return true if strict diet is followed
     * @return false if flexible diet is followed
     */
    bool isStrictDiet() const;
    
    /**
     * @brief Check if meal is allergen free
     * 
     * @return true if all common allergens are excluded
     * @return false if some allergens may be present
     */
    bool isAllergenFree() const;
    
    /**
     * @brief Get dietary meal category
     * 
     * @return std::string containing dietary meal category
     */
    std::string getDietCategory() const;
};