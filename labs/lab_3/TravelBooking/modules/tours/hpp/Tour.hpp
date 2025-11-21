/**
 * @file Tour.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Tour class for tour management system
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Accommodation.hpp"
#include "Meal.hpp"

/**
 * @class Tour
 * @brief Main class for tour package management
 * 
 * Represents comprehensive tour packages with accommodations, meals, and scheduling.
 * Provides business logic for cost calculation, group suitability assessment,
 * and tour component management.
 */
class Tour {
public:
    /**
     * @enum Type
     * @brief Enumeration of tour types
     */
    enum class Type {
        ADVENTURE,                                          ///< Adventure and outdoor activities tour
        CULTURAL,                                           ///< Cultural and historical tour
        RELAXATION,                                         ///< Relaxation and wellness tour
        FAMILY,                                             ///< Family-friendly tour
        BUSINESS                                            ///< Business and corporate tour
    };

private:
    std::string title;                                      ///< Tour title
    std::string description;                                ///< Tour description
    std::string startDate;                                  ///< Tour start date
    std::string endDate;                                    ///< Tour end date
    double price;                                           ///< Base tour price
    Type tourType;                                          ///< Type of tour
    std::vector<std::shared_ptr<Accommodation>> accommodations; ///< Collection of accommodations
    std::vector<std::shared_ptr<Meal>> meals;               ///< Collection of meals

public:
    /**
     * @brief Construct a new Tour object
     * 
     * @param title constant reference to the string containing tour title
     * @param description constant reference to the string containing tour description
     * @param startDate constant reference to the string containing start date
     * @param endDate constant reference to the string containing end date
     * @param price double value containing base tour price
     * @param type Type value containing tour type
     */
    Tour(const std::string& title,
         const std::string& description,
         const std::string& startDate,
         const std::string& endDate,
         double price,
         Type type);
    
    /**
     * @brief Get the tour identifier
     * 
     * @return int containing unique tour identifier
     */
    int getTourId() const;
    
    /**
     * @brief Get the tour title
     * 
     * @return std::string containing tour title
     */
    std::string getTitle() const;
    
    /**
     * @brief Get the tour description
     * 
     * @return std::string containing tour description
     */
    std::string getDescription() const;
    
    /**
     * @brief Get the start date
     * 
     * @return std::string containing tour start date
     */
    std::string getStartDate() const;
    
    /**
     * @brief Get the end date
     * 
     * @return std::string containing tour end date
     */
    std::string getEndDate() const;
    
    /**
     * @brief Get the start price
     * 
     * @return double containing base tour price
     */
    double getStartPrice() const;
    
    /**
     * @brief Get the tour type
     * 
     * @return Type containing tour type enum value
     */
    Type getTourType() const;
    
    /**
     * @brief Get the tour type as string
     * 
     * @return std::string containing tour type description
     */
    std::string getTourTypeStr() const;
    
    /**
     * @brief Get comprehensive tour information
     * 
     * @return std::string containing formatted tour details
     */
    std::string getTourInfo() const;
    
    /**
     * @brief Add accommodation to tour
     * 
     * @param accommodation shared pointer to the Accommodation object to add
     */
    void addAccommodation(std::shared_ptr<Accommodation> accommodation);
    
    /**
     * @brief Remove accommodation from tour by index
     * 
     * @param index integer value containing accommodation index to remove
     */
    void removeAccommodation(int index);
    
    /**
     * @brief Clear all accommodations from tour
     */
    void clearAccommodations();
    
    /**
     * @brief Get all accommodations
     * 
     * @return std::vector<std::shared_ptr<Accommodation>> containing all accommodations
     */
    std::vector<std::shared_ptr<Accommodation>> getAccommodations() const;
    
    /**
     * @brief Get specific accommodation by index
     * 
     * @param index integer value containing accommodation index
     * 
     * @return std::shared_ptr<Accommodation> containing accommodation object
     */
    std::shared_ptr<Accommodation> getAccommodation(int index) const;
    
    /**
     * @brief Get accommodation count
     * 
     * @return int containing number of accommodations
     */
    int getAccommodationCount() const;
    
    /**
     * @brief Calculate total accommodation cost
     * 
     * @return double containing total accommodation cost
     */
    double calculateTotalAccommodationCost() const;
    
    /**
     * @brief Get accommodations by type
     * 
     * @param type constant reference to the string containing accommodation type
     * 
     * @return std::vector<std::shared_ptr<Accommodation>> containing matching accommodations
     */
    std::vector<std::shared_ptr<Accommodation>> getAccommodationsByType(const std::string& type) const;
    
    /**
     * @brief Check if tour has accommodation for group size
     * 
     * @param groupSize integer value containing group size to check
     * 
     * @return true if suitable accommodation exists
     * @return false if no suitable accommodation exists
     */
    bool hasAccommodationForGroup(int groupSize) const;
    
    /**
     * @brief Get accommodation summary
     * 
     * @return std::string containing formatted accommodation summary
     */
    std::string getAccommodationSummary() const;
    
    /**
     * @brief Add meal to tour
     * 
     * @param meal shared pointer to the Meal object to add
     */
    void addMeal(std::shared_ptr<Meal> meal);
    
    /**
     * @brief Remove meal from tour by index
     * 
     * @param index integer value containing meal index to remove
     */
    void removeMeal(int index);
    
    /**
     * @brief Clear all meals from tour
     */
    void clearMeals();
    
    /**
     * @brief Get all meals
     * 
     * @return std::vector<std::shared_ptr<Meal>> containing all meals
     */
    std::vector<std::shared_ptr<Meal>> getMeals() const;
    
    /**
     * @brief Get specific meal by index
     * 
     * @param index integer value containing meal index
     * 
     * @return std::shared_ptr<Meal> containing meal object
     */
    std::shared_ptr<Meal> getMeal(int index) const;
    
    /**
     * @brief Get meal count
     * 
     * @return int containing number of meals
     */
    int getMealCount() const;
    
    /**
     * @brief Calculate total meal cost
     * 
     * @return double containing total meal cost
     */
    double calculateTotalMealCost() const;
    
    /**
     * @brief Calculate total tour cost
     * 
     * @return double containing total tour cost including accommodations and meals
     */
    double calculateTotalTourCost() const;
    
    /**
     * @brief Get meals by type
     * 
     * @param type constant reference to the string containing meal type
     * 
     * @return std::vector<std::shared_ptr<Meal>> containing matching meals
     */
    std::vector<std::shared_ptr<Meal>> getMealsByType(const std::string& type) const;
    
    /**
     * @brief Get meals by dietary requirement
     * 
     * @param diet constant reference to the string containing diet type
     * 
     * @return std::vector<std::shared_ptr<Meal>> containing matching meals
     */
    std::vector<std::shared_ptr<Meal>> getMealsByDiet(const std::string& diet) const;
    
    /**
     * @brief Get meals within calorie range
     * 
     * @param minCalories integer value containing minimum calories
     * @param maxCalories integer value containing maximum calories
     * 
     * @return std::vector<std::shared_ptr<Meal>> containing meals within calorie range
     */
    std::vector<std::shared_ptr<Meal>> getMealsInCalorieRange(int minCalories, int maxCalories) const;
    
    /**
     * @brief Get meal summary
     * 
     * @return std::string containing formatted meal summary
     */
    std::string getMealSummary() const;
    
    /**
     * @brief Get full tour summary
     * 
     * @return std::string containing comprehensive tour summary
     */
    std::string getFullTourSummary() const;
};