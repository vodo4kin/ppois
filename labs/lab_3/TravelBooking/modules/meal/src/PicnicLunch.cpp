#include "PicnicLunch.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

PicnicLunch::PicnicLunch(const std::string& name, const std::string& description,
                         double price, int calories, const std::vector<std::string>& tags,
                         bool prePackaged, bool heating, const std::vector<std::string>& containers)
    : Meal(name, description, price, calories, tags),
      isPrePackaged(prePackaged), needsHeating(heating), containerTypes(containers) {
    if (calories < MealConfig::Picnic::MIN_CALORIES || 
        calories > MealConfig::Picnic::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Picnic::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Picnic::MAX_CALORIES));
    }
    if (containerTypes.size() > MealConfig::Picnic::MAX_CONTAINER_TYPES) {
        throw InvalidDataException("containerTypes", "cannot exceed maximum of " + 
            std::to_string(MealConfig::Picnic::MAX_CONTAINER_TYPES));
    }
    for (const auto& container : containerTypes) {
        if (!StringValidation::isValidName(container)) {
            throw InvalidDataException("container", "must be valid container type");
        }
    }
    if (isPrePackaged) addDietaryTag("pre-packaged");
    if (!needsHeating) addDietaryTag("ready-to-eat");
    if (containerTypes.size() >= MealConfig::Picnic::MULTIPLE_CONTAINER_THRESHOLD) addDietaryTag("multiple-containers");
}

std::string PicnicLunch::getType() const {
    return "Picnic Lunch";
}

std::string PicnicLunch::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Pre-packaged: " + std::string(isPrePackaged ? "Yes" : "No") + "\n" +
           "Needs Heating: " + std::string(needsHeating ? "Yes" : "No") + "\n" +
           "Container Types: " + std::to_string(containerTypes.size()) + "\n";
    if (!containerTypes.empty()) {
        info += "Containers: ";
        for (size_t i = 0; i < containerTypes.size(); ++i) {
            info += containerTypes[i];
            if (i < containerTypes.size() - 1) info += ", ";
        }
        info += "\n";
    }
    return info;
}

bool PicnicLunch::isPrePackagedMeal() const {
    return isPrePackaged;
}

bool PicnicLunch::needsHeatings() const {
    return needsHeating;
}

std::vector<std::string> PicnicLunch::getContainerTypes() const {
    return containerTypes;
}

bool PicnicLunch::isReadyToEat() const {
    return !needsHeating;
}

bool PicnicLunch::isOutdoorFriendly() const {
    return isPrePackaged && !needsHeating;
}

std::string PicnicLunch::getPicnicCategory() const {
    if (isOutdoorFriendly() && containerTypes.size() >= MealConfig::Picnic::OUTDOOR_CONTAINER_THRESHOLD) return "Outdoor Picnic";
    else if (isPrePackaged) return "Packaged Lunch";
    else return "Standard Picnic";
}