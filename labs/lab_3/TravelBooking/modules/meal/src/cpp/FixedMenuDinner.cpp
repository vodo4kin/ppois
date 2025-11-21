#include "FixedMenuDinner.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

FixedMenuDinner::FixedMenuDinner(const std::string& name, const std::string& description,
                                 double price, int calories, const std::vector<std::string>& tags,
                                 const std::vector<std::string>& items, bool wine, const std::string& ambiance)
    : Meal(name, description, price, calories, tags),
      menuItems(items), includesWinePairing(wine), ambiance(ambiance) {
    if (calories < MealConfig::Dinner::MIN_CALORIES || 
        calories > MealConfig::Dinner::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Dinner::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Dinner::MAX_CALORIES));
    }
    if (menuItems.size() > MealConfig::Dinner::MAX_MENU_ITEMS) {
        throw InvalidDataException("menuItems", "cannot exceed maximum of " + 
            std::to_string(MealConfig::Dinner::MAX_MENU_ITEMS));
    }
    for (const auto& item : menuItems) {
        if (!StringValidation::isValidName(item) || 
            item.length() > MealConfig::Dinner::MAX_MENU_ITEM_LENGTH) {
            throw InvalidDataException("menuItem", "must be valid and not longer than " + 
                std::to_string(MealConfig::Dinner::MAX_MENU_ITEM_LENGTH));
        }
    }
    if (!StringValidation::isValidName(ambiance) || 
        ambiance.length() > MealConfig::Dinner::MAX_AMBIANCE_LENGTH) {
        throw InvalidDataException("ambiance", "must be valid and not longer than " + 
            std::to_string(MealConfig::Dinner::MAX_AMBIANCE_LENGTH));
    }
    if (includesWinePairing) addDietaryTag("wine-pairing");
    if (menuItems.size() >= MealConfig::Dinner::FINE_DINING_COURSE_THRESHOLD) addDietaryTag("fine-dining");
}

std::string FixedMenuDinner::getType() const {
    return "Fixed Menu Dinner";
}

std::string FixedMenuDinner::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Wine Pairing: " + std::string(includesWinePairing ? "Yes" : "No") + "\n" +
           "Ambiance: " + ambiance + "\n" +
           "Menu Items: " + std::to_string(menuItems.size()) + "\n";
    if (!menuItems.empty()) {
        info += "Includes: ";
        for (size_t i = 0; i < menuItems.size(); ++i) {
            info += menuItems[i];
            if (i < menuItems.size() - 1) info += ", ";
        }
        info += "\n";
    }
    return info;
}

std::vector<std::string> FixedMenuDinner::getMenuItems() const {
    return menuItems;
}

bool FixedMenuDinner::hasWinePairing() const {
    return includesWinePairing;
}

std::string FixedMenuDinner::getAmbiance() const {
    return ambiance;
}

bool FixedMenuDinner::isFineDining() const {
    return menuItems.size() >= MealConfig::Dinner::FINE_DINING_COURSE_THRESHOLD && includesWinePairing;
}

bool FixedMenuDinner::hasMultipleCourses() const {
    return menuItems.size() >= MealConfig::Dinner::MULTI_COURSE_THRESHOLD;
}

std::string FixedMenuDinner::getDinnerCategory() const {
    if (isFineDining()) return "Fine Dining Experience";
    else if (hasMultipleCourses()) return "Multi-Course Dinner";
    else return "Standard Dinner";
}