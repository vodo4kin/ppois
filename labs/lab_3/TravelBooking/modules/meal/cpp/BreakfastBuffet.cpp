#include "BreakfastBuffet.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

BreakfastBuffet::BreakfastBuffet(const std::string& name, const std::string& description,
                                 double price, int calories, const std::vector<std::string>& tags,
                                 bool hotItems, bool beverages, const std::vector<std::string>& cuisines)
    : Meal(name, description, price, calories, tags),
      includesHotItems(hotItems), includesBeverages(beverages), cuisineStyles(cuisines) {
    if (calories < MealConfig::Breakfast::MIN_CALORIES || 
        calories > MealConfig::Breakfast::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Breakfast::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Breakfast::MAX_CALORIES));
    }
    if (cuisineStyles.size() > MealConfig::Breakfast::MAX_CUISINE_STYLES) {
        throw InvalidDataException("cuisineStyles", "cannot exceed maximum of " + 
            std::to_string(MealConfig::Breakfast::MAX_CUISINE_STYLES));
    }
    for (const auto& cuisine : cuisineStyles) {
        if (!StringValidation::isValidName(cuisine) || 
            cuisine.length() > MealConfig::Breakfast::MAX_CUISINE_NAME_LENGTH) {
            throw InvalidDataException("cuisine", "must be valid and not longer than " + 
                std::to_string(MealConfig::Breakfast::MAX_CUISINE_NAME_LENGTH));
        }
    }
    if (includesHotItems) addDietaryTag("hot-breakfast");
    if (includesBeverages) addDietaryTag("beverages-included");
    if (cuisineStyles.size() >= MealConfig::Breakfast::INTERNATIONAL_CUISINE_THRESHOLD) addDietaryTag("international");
}

std::string BreakfastBuffet::getType() const {
    return "Breakfast Buffet";
}

std::string BreakfastBuffet::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Hot Items: " + std::string(includesHotItems ? "Yes" : "No") + "\n" +
           "Beverages: " + std::string(includesBeverages ? "Yes" : "No") + "\n" +
           "Cuisine Styles: " + std::to_string(cuisineStyles.size()) + "\n";
    if (!cuisineStyles.empty()) {
        info += "Available Cuisines: ";
        for (size_t i = 0; i < cuisineStyles.size(); ++i) {
            info += cuisineStyles[i];
            if (i < cuisineStyles.size() - 1) info += ", ";
        }
        info += "\n";
    }
    return info;
}

bool BreakfastBuffet::hasHotItems() const {
    return includesHotItems;
}

bool BreakfastBuffet::hasBeverages() const {
    return includesBeverages;
}

std::vector<std::string> BreakfastBuffet::getCuisineStyles() const {
    return cuisineStyles;
}

bool BreakfastBuffet::isInternationalBreakfast() const {
    return cuisineStyles.size() >= MealConfig::Breakfast::INTERNATIONAL_CUISINE_THRESHOLD;
}

bool BreakfastBuffet::isContinentalBreakfast() const {
    return !includesHotItems && includesBeverages;
}

std::string BreakfastBuffet::getBreakfastCategory() const {
    if (isInternationalBreakfast() && includesHotItems) return "International Full Breakfast";
    else if (includesHotItems) return "Full Breakfast";
    else return "Continental Breakfast";
}