/**
 * @file Meal.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Meal base class for meal system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

/**
 * @class Meal
 * @brief Base abstract class for all types of meals
 * 
 * Provides common interface and properties for various meal types
 * including catering, ethnic dinners, and dietary-specific meals.
 * Implements core functionality for dietary suitability and calorie management.
 */
class Meal {
protected:
    std::string name;                                       ///< Name of the meal
    std::string description;                                ///< Description of the meal
    double price;                                           ///< Price in currency units
    int calories;                                           ///< Calorie count
    std::vector<std::string> dietaryTags;                   ///< List of dietary tags

public:
    /**
     * @brief Construct a new Meal object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     */
    Meal(const std::string& name, const std::string& description, 
         double price, int calories, const std::vector<std::string>& tags);
    
    /**
     * @brief Get the meal type
     * 
     * Pure virtual method that must be implemented by derived classes
     * 
     * @return std::string containing meal type
     */
    virtual std::string getType() const = 0;
    
    /**
     * @brief Get comprehensive meal information
     * 
     * @return std::string containing formatted meal details
     */
    virtual std::string getMealInfo() const;
    
    /**
     * @brief Destroy the Meal object
     */
    virtual ~Meal() = default;
    
    /**
     * @brief Get the meal name
     * 
     * @return std::string containing meal name
     */
    std::string getName() const;
    
    /**
     * @brief Get the meal description
     * 
     * @return std::string containing meal description
     */
    std::string getDescription() const;
    
    /**
     * @brief Get the meal price
     * 
     * @return double containing meal price
     */
    double getPrice() const;
    
    /**
     * @brief Get the calorie count
     * 
     * @return int containing calorie count
     */
    int getCalories() const;
    
    /**
     * @brief Get the dietary tags
     * 
     * @return std::vector<std::string> containing all dietary tags
     */
    std::vector<std::string> getDietaryTags() const;
    
    /**
     * @brief Add new dietary tag to meal
     * 
     * @param tag constant reference to the string containing dietary tag
     */
    void addDietaryTag(const std::string& tag);
    
    /**
     * @brief Set the meal price
     * 
     * @param newPrice double value containing new price
     */
    void setPrice(double newPrice);
    
    /**
     * @brief Set the calorie count
     * 
     * @param newCalories integer value containing new calorie count
     */
    void setCalories(int newCalories);
    
    /**
     * @brief Check if meal is suitable for specific diet
     * 
     * @param diet constant reference to the string containing diet type
     * 
     * @return true if meal is suitable for specified diet
     * @return false if meal is not suitable for specified diet
     */
    bool isSuitableForDiet(const std::string& diet) const;
    
    /**
     * @brief Check if meal is within calorie range
     * 
     * @param minCalories integer value containing minimum calorie limit
     * @param maxCalories integer value containing maximum calorie limit
     * 
     * @return true if meal calories are within specified range
     * @return false if meal calories are outside specified range
     */
    bool isWithinCalorieRange(int minCalories, int maxCalories) const;
};