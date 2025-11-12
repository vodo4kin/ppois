#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Accommodation.hpp"
#include "Meal.hpp"

class Tour {
public:
    enum class Type {
        ADVENTURE,
        CULTURAL,
        RELAXATION,
        FAMILY,
        BUSINESS
    };
private:
    std::string title;
    std::string description;
    std::string startDate;
    std::string endDate;
    double price;
    Type tourType;
    std::vector<std::shared_ptr<Accommodation>> accommodations;
    std::vector<std::shared_ptr<Meal>> meals;
public:
    Tour(const std::string& title,
         const std::string& description,
         const std::string& startDate,
         const std::string& endDate,
         double price,
         Type type);
    int getTourId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getStartDate() const;
    std::string getEndDate() const;
    double getStartPrice() const;
    Type getTourType() const;
    std::string getTourTypeStr() const;
    std::string getTourInfo() const;
    void addAccommodation(std::shared_ptr<Accommodation> accommodation);
    void removeAccommodation(int index);
    void clearAccommodations();
    std::vector<std::shared_ptr<Accommodation>> getAccommodations() const;
    std::shared_ptr<Accommodation> getAccommodation(int index) const;
    int getAccommodationCount() const;
    double calculateTotalAccommodationCost() const;
    std::vector<std::shared_ptr<Accommodation>> getAccommodationsByType(const std::string& type) const;
    bool hasAccommodationForGroup(int groupSize) const;
    std::string getAccommodationSummary() const;
    void addMeal(std::shared_ptr<Meal> meal);
    void removeMeal(int index);
    void clearMeals();
    std::vector<std::shared_ptr<Meal>> getMeals() const;
    std::shared_ptr<Meal> getMeal(int index) const;
    int getMealCount() const;
    double calculateTotalMealCost() const;
    double calculateTotalTourCost() const;
    std::vector<std::shared_ptr<Meal>> getMealsByType(const std::string& type) const;
    std::vector<std::shared_ptr<Meal>> getMealsByDiet(const std::string& diet) const;
    std::vector<std::shared_ptr<Meal>> getMealsInCalorieRange(int minCalories, int maxCalories) const;
    std::string getMealSummary() const;
    std::string getFullTourSummary() const;
};