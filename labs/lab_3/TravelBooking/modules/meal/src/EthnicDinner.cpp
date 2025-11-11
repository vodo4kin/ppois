#include "EthnicDinner.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

EthnicDinner::EthnicDinner(const std::string& name, const std::string& description,
                           double price, int calories, const std::vector<std::string>& tags,
                           const std::string& cuisine, bool demo, bool traditionalDrinks, 
                           const std::string& servingStyle)
    : Meal(name, description, price, calories, tags),
      cuisine(cuisine), cookingDemo(demo), 
      includesTraditionalDrinks(traditionalDrinks), servingStyle(servingStyle) {
    if (calories < MealConfig::Ethnic::MIN_CALORIES || 
        calories > MealConfig::Ethnic::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Ethnic::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Ethnic::MAX_CALORIES));
    }
    if (!StringValidation::isValidName(cuisine) || 
        cuisine.length() > MealConfig::Ethnic::MAX_CUISINE_LENGTH) {
        throw InvalidDataException("cuisine", "must be valid and not longer than " + 
            std::to_string(MealConfig::Ethnic::MAX_CUISINE_LENGTH));
    }
    if (!StringValidation::isValidName(servingStyle) || 
        servingStyle.length() > MealConfig::Ethnic::MAX_SERVING_STYLE_LENGTH) {
        throw InvalidDataException("servingStyle", "must be valid and not longer than " + 
            std::to_string(MealConfig::Ethnic::MAX_SERVING_STYLE_LENGTH));
    }
    if (cookingDemo) addDietaryTag("cooking-demo");
    if (includesTraditionalDrinks) addDietaryTag("traditional-drinks");
    addDietaryTag(cuisine + "-cuisine");
}

std::string EthnicDinner::getType() const {
    return "Ethnic Dinner";
}

std::string EthnicDinner::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Cuisine: " + cuisine + "\n" +
           "Cooking Demo: " + std::string(cookingDemo ? "Yes" : "No") + "\n" +
           "Traditional Drinks: " + std::string(includesTraditionalDrinks ? "Yes" : "No") + "\n" +
           "Serving Style: " + servingStyle + "\n";
    return info;
}

std::string EthnicDinner::getCuisine() const {
    return cuisine;
}

bool EthnicDinner::hasCookingDemo() const {
    return cookingDemo;
}

bool EthnicDinner::hasTraditionalDrinks() const {
    return includesTraditionalDrinks;
}

std::string EthnicDinner::getServingStyle() const {
    return servingStyle;
}

bool EthnicDinner::isAuthenticExperience() const {
    return cookingDemo && includesTraditionalDrinks;
}

bool EthnicDinner::isFamilyStyle() const {
    return servingStyle == "family-style";
}

std::string EthnicDinner::getEthnicCategory() const {
    if (isAuthenticExperience()) return "Authentic Cultural Experience";
    else if (isFamilyStyle()) return "Family Style Ethnic Dinner";
    else return "Standard Ethnic Dinner";
}