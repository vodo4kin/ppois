#include "BarbecueMeal.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

BarbecueMeal::BarbecueMeal(const std::string& name, const std::string& description,
                           double price, int calories, const std::vector<std::string>& tags,
                           const std::vector<std::string>& meats, bool veggie, bool selfService, 
                           const std::string& location)
    : Meal(name, description, price, calories, tags),
      meatTypes(meats), vegetarianOptions(veggie), 
      selfService(selfService), locationType(location) {
    if (calories < MealConfig::Barbecue::MIN_CALORIES || 
        calories > MealConfig::Barbecue::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Barbecue::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Barbecue::MAX_CALORIES));
    }
    if (meatTypes.size() > MealConfig::Barbecue::MAX_MEAT_TYPES) {
        throw InvalidDataException("meatTypes", "cannot exceed maximum of " + 
            std::to_string(MealConfig::Barbecue::MAX_MEAT_TYPES));
    }
    for (const auto& meat : meatTypes) {
        if (!StringValidation::isValidName(meat)) {
            throw InvalidDataException("meat", "must be valid meat type");
        }
    }
    if (!StringValidation::isValidName(locationType) || 
        locationType.length() > MealConfig::Barbecue::MAX_LOCATION_TYPE_LENGTH) {
        throw InvalidDataException("locationType", "must be valid and not longer than " + 
            std::to_string(MealConfig::Barbecue::MAX_LOCATION_TYPE_LENGTH));
    }
    if (vegetarianOptions) addDietaryTag("vegetarian-options");
    if (selfService) addDietaryTag("self-service");
    if (meatTypes.size() >= MealConfig::Barbecue::MULTIPLE_MEAT_THRESHOLD) addDietaryTag("multiple-meats");
    if (locationType == "beach" || locationType == "garden") addDietaryTag("outdoor-dining");
}

std::string BarbecueMeal::getType() const {
    return "Barbecue Meal";
}

std::string BarbecueMeal::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Vegetarian Options: " + std::string(vegetarianOptions ? "Yes" : "No") + "\n" +
           "Self Service: " + std::string(selfService ? "Yes" : "No") + "\n" +
           "Location: " + locationType + "\n" +
           "Meat Types: " + std::to_string(meatTypes.size()) + "\n";
    if (!meatTypes.empty()) {
        info += "Includes: ";
        for (size_t i = 0; i < meatTypes.size(); ++i) {
            info += meatTypes[i];
            if (i < meatTypes.size() - 1) info += ", ";
        }
        info += "\n";
    }
    return info;
}

std::vector<std::string> BarbecueMeal::getMeatTypes() const {
    return meatTypes;
}

bool BarbecueMeal::hasVegetarianOptions() const {
    return vegetarianOptions;
}

bool BarbecueMeal::isSelfService() const {
    return selfService;
}

std::string BarbecueMeal::getLocationType() const {
    return locationType;
}

bool BarbecueMeal::isOutdoorBarbecue() const {
    return locationType == "beach" || locationType == "garden" || locationType == "rooftop";
}

bool BarbecueMeal::hasMultipleMeatOptions() const {
    return meatTypes.size() >= MealConfig::Barbecue::MULTIPLE_MEAT_THRESHOLD;
}

std::string BarbecueMeal::getBarbecueCategory() const {
    if (isOutdoorBarbecue() && hasMultipleMeatOptions()) return "Premium Outdoor Barbecue";
    else if (isOutdoorBarbecue()) return "Outdoor Barbecue";
    else return "Standard Barbecue";
}