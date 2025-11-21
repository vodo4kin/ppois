#include "DietarySpecificMeal.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

DietarySpecificMeal::DietarySpecificMeal(const std::string& name, const std::string& description,
                                         double price, int calories, const std::vector<std::string>& tags,
                                         const std::string& dietType, bool approved, 
                                         const std::string& portion, const std::vector<std::string>& allergens)
    : Meal(name, description, price, calories, tags),
      dietType(dietType), nutritionistApproved(approved), 
      portionControl(portion), allergensExcluded(allergens) {
    if (calories < MealConfig::Dietary::MIN_CALORIES || 
        calories > MealConfig::Dietary::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Dietary::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Dietary::MAX_CALORIES));
    }
    if (!StringValidation::isValidName(dietType) || 
        dietType.length() > MealConfig::Dietary::MAX_DIET_TYPE_LENGTH) {
        throw InvalidDataException("dietType", "must be valid and not longer than " + 
            std::to_string(MealConfig::Dietary::MAX_DIET_TYPE_LENGTH));
    }
    if (!StringValidation::isValidName(portionControl) || 
        portionControl.length() > MealConfig::Dietary::MAX_PORTION_LENGTH) {
        throw InvalidDataException("portionControl", "must be valid and not longer than " + 
            std::to_string(MealConfig::Dietary::MAX_PORTION_LENGTH));
    }
    if (allergensExcluded.size() > MealConfig::Dietary::MAX_ALLERGENS) {
        throw InvalidDataException("allergensExcluded", "cannot exceed maximum of " + 
            std::to_string(MealConfig::Dietary::MAX_ALLERGENS));
    }
    for (const auto& allergen : allergensExcluded) {
        if (!StringValidation::isValidName(allergen)) {
            throw InvalidDataException("allergen", "must be valid allergen name");
        }
    }
    if (nutritionistApproved) addDietaryTag("nutritionist-approved");
    addDietaryTag(dietType);
    for (const auto& allergen : allergensExcluded) {
        addDietaryTag("no-" + allergen);
    }
}

std::string DietarySpecificMeal::getType() const {
    return "Dietary Specific Meal";
}

std::string DietarySpecificMeal::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Diet Type: " + dietType + "\n" +
           "Nutritionist Approved: " + std::string(nutritionistApproved ? "Yes" : "No") + "\n" +
           "Portion Control: " + portionControl + "\n" +
           "Allergens Excluded: " + std::to_string(allergensExcluded.size()) + "\n";
    if (!allergensExcluded.empty()) {
        info += "Excludes: ";
        for (size_t i = 0; i < allergensExcluded.size(); ++i) {
            info += allergensExcluded[i];
            if (i < allergensExcluded.size() - 1) info += ", ";
        }
        info += "\n";
    }
    return info;
}

std::string DietarySpecificMeal::getDietType() const {
    return dietType;
}

bool DietarySpecificMeal::isNutritionistApproved() const {
    return nutritionistApproved;
}

std::string DietarySpecificMeal::getPortionControl() const {
    return portionControl;
}

std::vector<std::string> DietarySpecificMeal::getAllergensExcluded() const {
    return allergensExcluded;
}

bool DietarySpecificMeal::isStrictDiet() const {
    return nutritionistApproved && portionControl == "controlled";
}

bool DietarySpecificMeal::isAllergenFree() const {
    return allergensExcluded.size() >= MealConfig::Dietary::MULTIPLE_ALLERGEN_THRESHOLD;
}

std::string DietarySpecificMeal::getDietCategory() const {
    if (isStrictDiet() && isAllergenFree()) return "Medical Grade Diet";
    else if (isStrictDiet()) return "Strict Diet Plan";
    else return "Standard Dietary Meal";
}