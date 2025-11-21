/**
 * @file FixedMenuDinner.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the FixedMenuDinner class for fixed menu dinner meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class FixedMenuDinner
 * @brief Class representing fixed menu dinner type meal
 * 
 * Extends Meal with fixed menu dinner-specific properties like menu items,
 * wine pairing, and ambiance. Provides methods for fine dining classification
 * and course count assessment.
 */
class FixedMenuDinner : public Meal {
private:
    std::vector<std::string> menuItems;                     ///< List of menu items
    bool includesWinePairing;                               ///< Wine pairing inclusion flag
    std::string ambiance;                                   ///< Dining ambiance description

public:
    /**
     * @brief Construct a new FixedMenuDinner object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param items constant reference to the vector containing menu items
     * @param wine boolean value indicating wine pairing inclusion
     * @param ambiance constant reference to the string containing ambiance description
     */
    FixedMenuDinner(const std::string& name, const std::string& description,
                    double price, int calories, const std::vector<std::string>& tags,
                    const std::vector<std::string>& items, bool wine, const std::string& ambiance);
    
    /**
     * @brief Get the fixed menu dinner type
     * 
     * @return std::string containing "FixedMenuDinner"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive fixed menu dinner information
     * 
     * @return std::string containing formatted fixed menu dinner details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Get the menu items
     * 
     * @return std::vector<std::string> containing all menu items
     */
    std::vector<std::string> getMenuItems() const;
    
    /**
     * @brief Check if dinner includes wine pairing
     * 
     * @return true if wine pairing is included
     * @return false if wine pairing is not included
     */
    bool hasWinePairing() const;
    
    /**
     * @brief Get the ambiance description
     * 
     * @return std::string containing ambiance description
     */
    std::string getAmbiance() const;
    
    /**
     * @brief Check if dinner is fine dining category
     * 
     * @return true if fine dining experience
     * @return false if casual dining experience
     */
    bool isFineDining() const;
    
    /**
     * @brief Check if dinner has multiple courses
     * 
     * @return true if multiple courses are served
     * @return false if single course is served
     */
    bool hasMultipleCourses() const;
    
    /**
     * @brief Get fixed menu dinner category
     * 
     * @return std::string containing fixed menu dinner category
     */
    std::string getDinnerCategory() const;
};