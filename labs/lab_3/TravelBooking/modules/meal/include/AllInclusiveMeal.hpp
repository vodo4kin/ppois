#pragma once
#include "Meal.hpp"

class AllInclusiveMeal : public Meal {
private:
    bool includesAlcoholicDrinks;
    bool includesSnacks;
    int mealsPerDay;
    std::vector<std::string> availableRestaurants;
public:
    AllInclusiveMeal(const std::string& name, const std::string& description,
                     double price, int calories, const std::vector<std::string>& tags,
                     bool alcoholicDrinks, bool snacks, int meals, 
                     const std::vector<std::string>& restaurants);
    std::string getType() const override;
    std::string getMealInfo() const override;
    bool hasAlcoholicDrinks() const;
    bool hasSnacks() const;
    int getMealsPerDay() const;
    std::vector<std::string> getAvailableRestaurants() const;
    bool isPremiumAllInclusive() const;
    bool isUnlimitedMeals() const;
    std::string getAllInclusiveCategory() const;
};