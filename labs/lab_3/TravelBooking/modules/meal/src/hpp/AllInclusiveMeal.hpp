/**
 * @file AllInclusiveMeal.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the AllInclusiveMeal class for all-inclusive meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class AllInclusiveMeal
 * @brief Class representing all-inclusive type meal
 * 
 * Extends Meal with all-inclusive-specific properties like drink inclusions,
 * snack availability, and restaurant access. Provides methods for premium
 * classification and meal frequency assessment.
 */
class AllInclusiveMeal : public Meal {
private:
    bool includesAlcoholicDrinks;                           ///< Alcoholic drinks inclusion flag
    bool includesSnacks;                                    ///< Snacks inclusion flag
    int mealsPerDay;                                        ///< Number of meals per day
    std::vector<std::string> availableRestaurants;          ///< List of available restaurants

public:
    /**
     * @brief Construct a new AllInclusiveMeal object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param alcoholicDrinks boolean value indicating alcoholic drinks inclusion
     * @param snacks boolean value indicating snacks inclusion
     * @param meals integer value containing meals per day count
     * @param restaurants constant reference to the vector containing restaurant list
     */
    AllInclusiveMeal(const std::string& name, const std::string& description,
                     double price, int calories, const std::vector<std::string>& tags,
                     bool alcoholicDrinks, bool snacks, int meals, 
                     const std::vector<std::string>& restaurants);
    
    /**
     * @brief Get the all-inclusive meal type
     * 
     * @return std::string containing "AllInclusiveMeal"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive all-inclusive meal information
     * 
     * @return std::string containing formatted all-inclusive meal details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Check if meal includes alcoholic drinks
     * 
     * @return true if alcoholic drinks are included
     * @return false if alcoholic drinks are not included
     */
    bool hasAlcoholicDrinks() const;
    
    /**
     * @brief Check if meal includes snacks
     * 
     * @return true if snacks are included
     * @return false if snacks are not included
     */
    bool hasSnacks() const;
    
    /**
     * @brief Get the meals per day count
     * 
     * @return int containing number of meals per day
     */
    int getMealsPerDay() const;
    
    /**
     * @brief Get the available restaurants
     * 
     * @return std::vector<std::string> containing all available restaurants
     */
    std::vector<std::string> getAvailableRestaurants() const;
    
    /**
     * @brief Check if meal is premium all-inclusive
     * 
     * @return true if meal is premium category
     * @return false if meal is not premium category
     */
    bool isPremiumAllInclusive() const;
    
    /**
     * @brief Check if meal offers unlimited meals
     * 
     * @return true if unlimited meals are offered
     * @return false if limited meals are offered
     */
    bool isUnlimitedMeals() const;
    
    /**
     * @brief Get all-inclusive meal category
     * 
     * @return std::string containing all-inclusive meal category
     */
    std::string getAllInclusiveCategory() const;
};