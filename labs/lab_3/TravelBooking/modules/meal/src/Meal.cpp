#include "Meal.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

Meal::Meal(const std::string& name, const std::string& description, 
           double price, int calories, const std::vector<std::string>& tags)
    : name(name), description(description), price(price), 
      calories(calories), dietaryTags(tags) {
    if (!StringValidation::isValidName(name) || name.length() > MealConfig::Meal::MAX_NAME_LENGTH) {
        throw InvalidDataException("name", "must be valid and not longer than " + 
            std::to_string(MealConfig::Meal::MAX_NAME_LENGTH) + " characters");
    }
    if (description.length() > MealConfig::Meal::MAX_DESCRIPTION_LENGTH) {
        throw InvalidDataException("description", "cannot be longer than " + 
            std::to_string(MealConfig::Meal::MAX_DESCRIPTION_LENGTH) + " characters");
    }
    if (price < MealConfig::Meal::MIN_PRICE || price > MealConfig::Meal::MAX_PRICE) {
        throw InvalidDataException("price", "must be between " + 
            std::to_string(MealConfig::Meal::MIN_PRICE) + " and " + 
            std::to_string(MealConfig::Meal::MAX_PRICE));
    }
    if (calories < MealConfig::Meal::MIN_CALORIES || calories > MealConfig::Meal::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Meal::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Meal::MAX_CALORIES));
    }
    for (const auto& tag : dietaryTags) {
        if (!StringValidation::isValidName(tag) || tag.length() > MealConfig::Meal::MAX_TAG_LENGTH) {
            throw InvalidDataException("dietaryTag", "must be valid and not longer than " + 
                std::to_string(MealConfig::Meal::MAX_TAG_LENGTH) + " characters");
        }
    }
    if (dietaryTags.size() > MealConfig::Meal::MAX_TAGS_COUNT) {
        throw InvalidDataException("dietaryTags", "cannot exceed maximum count of " + 
            std::to_string(MealConfig::Meal::MAX_TAGS_COUNT));
    }
}

std::string Meal::getMealInfo() const {
    std::string info = "Type: " + getType() + "\n" +
                      "Name: " + name + "\n" +
                      "Description: " + description + "\n" +
                      "Price: $" + std::to_string(static_cast<int>(price)) + "\n" +
                      "Calories: " + std::to_string(calories) + "\n";
    if (!dietaryTags.empty()) {
        info += "Dietary Tags: ";
        for (size_t i = 0; i < dietaryTags.size(); ++i) {
            info += dietaryTags[i];
            if (i < dietaryTags.size() - 1) {
                info += ", ";
            }
        }
        info += "\n";
    }
    return info;
}

std::string Meal::getName() const {
    return name;
}

std::string Meal::getDescription() const {
    return description;
}

double Meal::getPrice() const {
    return price;
}

int Meal::getCalories() const {
    return calories;
}

std::vector<std::string> Meal::getDietaryTags() const {
    return dietaryTags;
}

void Meal::addDietaryTag(const std::string& tag) {
    if (!StringValidation::isValidName(tag) || tag.length() > MealConfig::Meal::MAX_TAG_LENGTH) {
        throw InvalidDataException("tag", "must be valid and not longer than " + 
            std::to_string(MealConfig::Meal::MAX_TAG_LENGTH) + " characters");
    }
    for (const auto& existingTag : dietaryTags) {
        if (existingTag == tag) {
            return;
        }
    }
    if (dietaryTags.size() >= MealConfig::Meal::MAX_TAGS_COUNT) {
        throw InvalidDataException("dietaryTags", "cannot exceed maximum count of " + 
            std::to_string(MealConfig::Meal::MAX_TAGS_COUNT));
    }
    dietaryTags.push_back(tag);
}

void Meal::setPrice(double newPrice) {
    if (newPrice < MealConfig::Meal::MIN_PRICE || newPrice > MealConfig::Meal::MAX_PRICE) {
        throw InvalidDataException("price", "must be between " + 
            std::to_string(MealConfig::Meal::MIN_PRICE) + " and " + 
            std::to_string(MealConfig::Meal::MAX_PRICE));
    }
    price = newPrice;
}

void Meal::setCalories(int newCalories) {
    if (newCalories < MealConfig::Meal::MIN_CALORIES || newCalories > MealConfig::Meal::MAX_CALORIES) {
        throw InvalidDataException("calories", "must be between " + 
            std::to_string(MealConfig::Meal::MIN_CALORIES) + " and " + 
            std::to_string(MealConfig::Meal::MAX_CALORIES));
    }
    calories = newCalories;
}

bool Meal::isSuitableForDiet(const std::string& diet) const {
    for (const auto& tag : dietaryTags) {
        if (tag == diet) {
            return true;
        }
    }
    return false;
}

bool Meal::isWithinCalorieRange(int minCalories, int maxCalories) const {
    return calories >= minCalories && calories <= maxCalories;
}

void Meal::validateMeal() const {
    bool hasVegan = false;
    bool hasMeat = false;
    for (const auto& tag : dietaryTags) {
        if (tag == "vegan" || tag == "vegetarian") hasVegan = true;
        if (tag == "meat" || tag == "poultry" || tag == "seafood") hasMeat = true;
    }
    if (hasVegan && hasMeat) {
        throw MealCompatibilityException(name, "Cannot be both vegan and contain meat products");
    }
    double pricePerCalorie = price / calories;
    if (pricePerCalorie > MealConfig::Meal::MAX_PRICE_PER_CALORIE) {
        throw MealPricingException(name, price, calories, 
            MealConfig::Meal::MAX_PRICE_PER_CALORIE);
    }
}