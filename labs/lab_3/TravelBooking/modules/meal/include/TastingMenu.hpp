/**
 * @file TastingMenu.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TastingMenu class for tasting menu meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class TastingMenu
 * @brief Class representing tasting menu type meal
 * 
 * Extends Meal with tasting menu-specific properties like dish count,
 * chef specialty, and wine pairing. Provides methods for premium
 * classification and wine pairing assessment.
 */
class TastingMenu : public Meal {
private:
    int numberOfDishes;                                     ///< Number of dishes in menu
    std::string chefSpecialty;                              ///< Chef's specialty description
    bool includesWineTasting;                               ///< Wine tasting inclusion flag
    std::string pairingNotes;                               ///< Food and wine pairing notes

public:
    /**
     * @brief Construct a new TastingMenu object
     * 
     * @param name constant reference to the string containing menu name
     * @param description constant reference to the string containing description
     * @param price double value containing menu price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param dishes integer value containing number of dishes
     * @param chefSpecialty constant reference to the string containing chef specialty
     * @param wineTasting boolean value indicating wine tasting inclusion
     * @param pairingNotes constant reference to the string containing pairing notes
     */
    TastingMenu(const std::string& name, const std::string& description,
                double price, int calories, const std::vector<std::string>& tags,
                int dishes, const std::string& chefSpecialty, bool wineTasting, 
                const std::string& pairingNotes);
    
    /**
     * @brief Get the tasting menu type
     * 
     * @return std::string containing "TastingMenu"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive tasting menu information
     * 
     * @return std::string containing formatted tasting menu details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Get the number of dishes
     * 
     * @return int containing dish count
     */
    int getNumberOfDishes() const;
    
    /**
     * @brief Get the chef specialty
     * 
     * @return std::string containing chef specialty description
     */
    std::string getChefSpecialty() const;
    
    /**
     * @brief Check if menu includes wine tasting
     * 
     * @return true if wine tasting is included
     * @return false if wine tasting is not included
     */
    bool hasWineTasting() const;
    
    /**
     * @brief Get the pairing notes
     * 
     * @return std::string containing food and wine pairing notes
     */
    std::string getPairingNotes() const;
    
    /**
     * @brief Check if menu is premium tasting
     * 
     * @return true if menu is premium category
     * @return false if menu is not premium category
     */
    bool isPremiumTasting() const;
    
    /**
     * @brief Check if menu is wine paired
     * 
     * @return true if wine pairing is included
     * @return false if wine pairing is not included
     */
    bool isWinePaired() const;
    
    /**
     * @brief Get tasting menu category
     * 
     * @return std::string containing tasting menu category
     */
    std::string getTastingCategory() const;
};