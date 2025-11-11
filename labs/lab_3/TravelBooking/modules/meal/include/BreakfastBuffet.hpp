#pragma once
#include "Meal.hpp"

class BreakfastBuffet : public Meal {
private:
    bool includesHotItems;
    bool includesBeverages;
    std::vector<std::string> cuisineStyles;
public:
    BreakfastBuffet(const std::string& name, const std::string& description,
                    double price, int calories, const std::vector<std::string>& tags,
                    bool hotItems, bool beverages, const std::vector<std::string>& cuisines);
    std::string getType() const override;
    std::string getMealInfo() const override;
    bool hasHotItems() const;
    bool hasBeverages() const;
    std::vector<std::string> getCuisineStyles() const;
    bool isInternationalBreakfast() const;
    bool isContinentalBreakfast() const;
    std::string getBreakfastCategory() const;
};