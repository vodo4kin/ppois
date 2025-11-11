#pragma once
#include "Meal.hpp"

class EthnicDinner : public Meal {
private:
    std::string cuisine;
    bool cookingDemo;
    bool includesTraditionalDrinks;
    std::string servingStyle;
public:
    EthnicDinner(const std::string& name, const std::string& description,
                 double price, int calories, const std::vector<std::string>& tags,
                 const std::string& cuisine, bool demo, bool traditionalDrinks, 
                 const std::string& servingStyle);
    std::string getType() const override;
    std::string getMealInfo() const override;
    std::string getCuisine() const;
    bool hasCookingDemo() const;
    bool hasTraditionalDrinks() const;
    std::string getServingStyle() const;
    bool isAuthenticExperience() const;
    bool isFamilyStyle() const;
    std::string getEthnicCategory() const;
};