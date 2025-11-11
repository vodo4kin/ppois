#include "AllInclusiveMeal.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/MealConfig.hpp"
#include "utils/Utils.hpp"

AllInclusiveMeal::AllInclusiveMeal(const std::string& name, const std::string& description,
                                   double price, int calories, const std::vector<std::string>& tags,
                                   bool alcoholicDrinks, bool snacks, int meals, 
                                   const std::vector<std::string>& restaurants)
    : Meal(name, description, price, calories, tags),
      includesAlcoholicDrinks(alcoholicDrinks), includesSnacks(snacks),
      mealsPerDay(meals), availableRestaurants(restaurants) {
    if (mealsPerDay < MealConfig::AllInclusive::MIN_MEALS_PER_DAY || 
        mealsPerDay > MealConfig::AllInclusive::MAX_MEALS_PER_DAY) {
        throw InvalidDataException("mealsPerDay", "must be between " + 
            std::to_string(MealConfig::AllInclusive::MIN_MEALS_PER_DAY) + " and " + 
            std::to_string(MealConfig::AllInclusive::MAX_MEALS_PER_DAY));
    }
    if (availableRestaurants.size() > MealConfig::AllInclusive::MAX_RESTAURANTS) {
        throw InvalidDataException("availableRestaurants", "cannot exceed maximum of " + 
            std::to_string(MealConfig::AllInclusive::MAX_RESTAURANTS));
    }
    for (const auto& restaurant : availableRestaurants) {
        if (!StringValidation::isValidName(restaurant)) {
            throw InvalidDataException("restaurant", "must be valid restaurant name");
        }
    }
    if (includesAlcoholicDrinks) addDietaryTag("alcoholic-drinks");
    if (includesSnacks) addDietaryTag("snacks-included");
    if (mealsPerDay >= MealConfig::AllInclusive::PREMIUM_MEAL_THRESHOLD) addDietaryTag("premium-all-inclusive");
}

std::string AllInclusiveMeal::getType() const {
    return "All Inclusive Meal";
}

std::string AllInclusiveMeal::getMealInfo() const {
    std::string info = Meal::getMealInfo();
    info += "Alcoholic Drinks: " + std::string(includesAlcoholicDrinks ? "Yes" : "No") + "\n" +
           "Snacks: " + std::string(includesSnacks ? "Yes" : "No") + "\n" +
           "Meals Per Day: " + std::to_string(mealsPerDay) + "\n" +
           "Available Restaurants: " + std::to_string(availableRestaurants.size()) + "\n";
    return info;
}

bool AllInclusiveMeal::hasAlcoholicDrinks() const {
    return includesAlcoholicDrinks;
}

bool AllInclusiveMeal::hasSnacks() const {
    return includesSnacks;
}

int AllInclusiveMeal::getMealsPerDay() const {
    return mealsPerDay;
}

std::vector<std::string> AllInclusiveMeal::getAvailableRestaurants() const {
    return availableRestaurants;
}

bool AllInclusiveMeal::isPremiumAllInclusive() const {
    return includesAlcoholicDrinks && includesSnacks && 
           mealsPerDay >= MealConfig::AllInclusive::PREMIUM_MEAL_THRESHOLD;
}

bool AllInclusiveMeal::isUnlimitedMeals() const {
    return mealsPerDay >= MealConfig::AllInclusive::UNLIMITED_MEAL_THRESHOLD;
}

std::string AllInclusiveMeal::getAllInclusiveCategory() const {
    if (isPremiumAllInclusive()) return "Premium All Inclusive";
    else if (isUnlimitedMeals()) return "Unlimited Dining";
    else return "Standard All Inclusive";
}