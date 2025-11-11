#include "TastingMenu.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

TastingMenu::TastingMenu(const std::string& name, const std::string& description,
                         double price, int calories, const std::vector<std::string>& tags,
                         int dishes, const std::string& chefSpecialty, bool wineTasting, 
                         const std::string& pairingNotes)
    : Meal(name, description, price, calories, tags),
      numberOfDishes(dishes), chefSpecialty(chefSpecialty), 
      includesWineTasting(wineTasting), pairingNotes(pairingNotes) {
    if (calories < MealConfig::Tasting::MIN_CALORIES || 
        calories > MealConfig::Tasting::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Tasting::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Tasting::MAX_CALORIES));
    }
    if (numberOfDishes < MealConfig::Tasting::MIN_DISHES || 
        numberOfDishes > MealConfig::Tasting::MAX_DISHES) {
        throw InvalidDataException("numberOfDishes", "must be between " + 
            std::to_string(MealConfig::Tasting::MIN_DISHES) + " and " + 
            std::to_string(MealConfig::Tasting::MAX_DISHES));
    }
    if (!StringValidation::isValidName(chefSpecialty) || 
        chefSpecialty.length() > MealConfig::Tasting::MAX_CHEF_SPECIALTY_LENGTH) {
        throw InvalidDataException("chefSpecialty", "must be valid and not longer than " + 
            std::to_string(MealConfig::Tasting::MAX_CHEF_SPECIALTY_LENGTH));
    }
    if (!StringValidation::isValidName(pairingNotes) || 
        pairingNotes.length() > MealConfig::Tasting::MAX_PAIRING_NOTES_LENGTH) {
        throw InvalidDataException("pairingNotes", "must be valid and not longer than " + 
            std::to_string(MealConfig::Tasting::MAX_PAIRING_NOTES_LENGTH));
    }
    if (includesWineTasting) addDietaryTag("wine-tasting");
    if (numberOfDishes >= MealConfig::Tasting::PREMIUM_DISH_THRESHOLD) addDietaryTag("premium-tasting");
    addDietaryTag("chef-specialty");
}

std::string TastingMenu::getType() const {
    return "Tasting Menu";
}

std::string TastingMenu::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Number of Dishes: " + std::to_string(numberOfDishes) + "\n" +
           "Chef Specialty: " + chefSpecialty + "\n" +
           "Wine Tasting: " + std::string(includesWineTasting ? "Yes" : "No") + "\n" +
           "Pairing Notes: " + pairingNotes + "\n";
    return info;
}

int TastingMenu::getNumberOfDishes() const {
    return numberOfDishes;
}

std::string TastingMenu::getChefSpecialty() const {
    return chefSpecialty;
}

bool TastingMenu::hasWineTasting() const {
    return includesWineTasting;
}

std::string TastingMenu::getPairingNotes() const {
    return pairingNotes;
}

bool TastingMenu::isPremiumTasting() const {
    return numberOfDishes >= MealConfig::Tasting::PREMIUM_DISH_THRESHOLD && includesWineTasting;
}

bool TastingMenu::isWinePaired() const {
    return includesWineTasting && !pairingNotes.empty();
}

std::string TastingMenu::getTastingCategory() const {
    if (isPremiumTasting()) return "Premium Tasting Experience";
    else if (isWinePaired()) return "Wine Paired Tasting";
    else return "Standard Tasting Menu";
}