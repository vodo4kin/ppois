#include "Tour.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/ToursConfig.hpp"
#include <atomic>

static std::atomic<int> nextTourId{1};

Tour::Tour(const std::string& title,
           const std::string& description,
           const std::string& startDate,
           const std::string& endDate,
           double price,
           Type type)
    : title(title), description(description),
      startDate(startDate), endDate(endDate),
      price(price), tourType(type) {
    if (!StringValidation::isValidName(title) || title.length() < ToursConfig::Tour::MIN_TITLE_LENGTH || title.length() > ToursConfig::Tour::MAX_TITLE_LENGTH) {
        throw InvalidDataException("title", "must be valid and between " + 
            std::to_string(ToursConfig::Tour::MIN_TITLE_LENGTH) + " and " + 
            std::to_string(ToursConfig::Tour::MAX_TITLE_LENGTH) + " characters");
    }
    if (description.length() > ToursConfig::Tour::MAX_DESCRIPTION_LENGTH) {
        throw InvalidDataException("description", "cannot be longer than " + 
            std::to_string(ToursConfig::Tour::MAX_DESCRIPTION_LENGTH) + " characters");
    }
    if (!StringValidation::isValidDate(startDate)) {
        throw InvalidDateException("startDate");
    }
    if (!StringValidation::isValidDate(endDate)) {
        throw InvalidDateException("endDate");
    }
    if (price < ToursConfig::Tour::MIN_TOUR_PRICE || price > ToursConfig::Tour::MAX_TOUR_PRICE) {
        throw InvalidDataException("price", "must be in range " + 
            std::to_string(ToursConfig::Tour::MIN_TOUR_PRICE) + " - " + 
            std::to_string(ToursConfig::Tour::MAX_TOUR_PRICE));
    }
    nextTourId++;
}

int Tour::getTourId() const {
    return nextTourId - 1;
}

std::string Tour::getTitle() const {
    return title;
}

std::string Tour::getDescription() const {
    return description;
}

std::string Tour::getStartDate() const {
    return startDate;
}

std::string Tour::getEndDate() const {
    return endDate;
}

double Tour::getPrice() const {
    return price;
}

Tour::Type Tour::getTourType() const {
    return tourType;
}

std::string Tour::getTourTypeStr() const {
    switch (tourType) {
        case Type::ADVENTURE: return "Adventure";
        case Type::CULTURAL: return "Cultural";
        case Type::RELAXATION: return "Relaxation";
        case Type::FAMILY: return "Family";
        case Type::BUSINESS: return "Business";
        default: return "Unknown";
    }
}

std::string Tour::getTourInfo() const {
    std::string info = "Tour ID: " + std::to_string(getTourId()) + "\n" +
                      "Title: " + title + "\n" +
                      "Type: " + getTourTypeStr() + "\n" +
                      "Start: " + startDate + "\n" +
                      "End: " + endDate + "\n" +
                      "Base Price: $" + std::to_string(static_cast<int>(price)) + "\n" +
                      "Description: " + description + "\n" +
                      "Accommodations: " + std::to_string(accommodations.size()) + "\n" +
                      "Meals: " + std::to_string(meals.size()) + "\n";
    if (!accommodations.empty() || !meals.empty()) {
        info += "Total with Services: $" + 
                std::to_string(static_cast<int>(calculateTotalTourCost())) + "\n";
    }
    return info;
}

void Tour::addAccommodation(std::shared_ptr<Accommodation> accommodation) {
    if (!accommodation) {
        throw InvalidDataException("accommodation", "cannot be null");
    }
    if (accommodations.size() >= ToursConfig::Tour::MAX_ACCOMMODATIONS_PER_TOUR) {
        throw InvalidDataException("accommodations", "cannot exceed maximum of " + 
            std::to_string(ToursConfig::Tour::MAX_ACCOMMODATIONS_PER_TOUR));
    }
    accommodations.push_back(accommodation);
}

void Tour::removeAccommodation(int index) {
    if (index < 0 || index >= static_cast<int>(accommodations.size())) {
        throw InvalidDataException("index", "must be valid accommodation index");
    }
    accommodations.erase(accommodations.begin() + index);
}

void Tour::clearAccommodations() {
    accommodations.clear();
}

std::vector<std::shared_ptr<Accommodation>> Tour::getAccommodations() const {
    return accommodations;
}

std::shared_ptr<Accommodation> Tour::getAccommodation(int index) const {
    if (index < 0 || index >= static_cast<int>(accommodations.size())) {
        throw InvalidDataException("index", "must be valid accommodation index");
    }
    return accommodations[index];
}

int Tour::getAccommodationCount() const {
    return static_cast<int>(accommodations.size());
}

double Tour::calculateTotalAccommodationCost() const {
    double total = 0.0;
    for (const auto& accommodation : accommodations) {
        total += accommodation->getPricePerNight();
    }
    return total;
}

std::vector<std::shared_ptr<Accommodation>> Tour::getAccommodationsByType(const std::string& type) const {
    std::vector<std::shared_ptr<Accommodation>> result;
    for (const auto& accommodation : accommodations) {
        if (accommodation->getType() == type) {
            result.push_back(accommodation);
        }
    }
    return result;
}

bool Tour::hasAccommodationForGroup(int groupSize) const {
    for (const auto& accommodation : accommodations) {
        if (accommodation->canAccommodate(groupSize)) {
            return true;
        }
    }
    return false;
}

std::string Tour::getAccommodationSummary() const {
    if (accommodations.empty()) {
        return "No accommodations included in this tour.";
    }
    std::string summary = "Accommodation Summary (" + std::to_string(accommodations.size()) + "):\n";
    for (size_t i = 0; i < accommodations.size(); ++i) {
        summary += std::to_string(i + 1) + ". " + accommodations[i]->getType() + 
                  " - " + accommodations[i]->getName() + 
                  " ($" + std::to_string(static_cast<int>(accommodations[i]->getPricePerNight())) + "/night)\n";
    }
    summary += "Total Accommodation Cost: $" + std::to_string(static_cast<int>(calculateTotalAccommodationCost())) + "/night\n";
    return summary;
}

void Tour::addMeal(std::shared_ptr<Meal> meal) {
    if (!meal) {
        throw InvalidDataException("meal", "cannot be null");
    }
    if (meals.size() >= ToursConfig::Tour::MAX_MEALS_PER_TOUR) {
        throw InvalidDataException("meals", "cannot exceed maximum of " + 
            std::to_string(ToursConfig::Tour::MAX_MEALS_PER_TOUR));
    }
    meals.push_back(meal);
}

void Tour::removeMeal(int index) {
    if (index < 0 || index >= static_cast<int>(meals.size())) {
        throw InvalidDataException("index", "must be valid meal index");
    }
    meals.erase(meals.begin() + index);
}

void Tour::clearMeals() {
    meals.clear();
}

std::vector<std::shared_ptr<Meal>> Tour::getMeals() const {
    return meals;
}

std::shared_ptr<Meal> Tour::getMeal(int index) const {
    if (index < 0 || index >= static_cast<int>(meals.size())) {
        throw InvalidDataException("index", "must be valid meal index");
    }
    return meals[index];
}

int Tour::getMealCount() const {
    return static_cast<int>(meals.size());
}

double Tour::calculateTotalMealCost() const {
    double total = 0.0;
    for (const auto& meal : meals) {
        total += meal->getPrice();
    }
    return total;
}

double Tour::calculateTotalTourCost() const {
    return price + calculateTotalAccommodationCost() + calculateTotalMealCost();
}

std::vector<std::shared_ptr<Meal>> Tour::getMealsByType(const std::string& type) const {
    std::vector<std::shared_ptr<Meal>> result;
    for (const auto& meal : meals) {
        if (meal->getType() == type) {
            result.push_back(meal);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Meal>> Tour::getMealsByDiet(const std::string& diet) const {
    std::vector<std::shared_ptr<Meal>> result;
    for (const auto& meal : meals) {
        if (meal->isSuitableForDiet(diet)) {
            result.push_back(meal);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Meal>> Tour::getMealsInCalorieRange(int minCalories, int maxCalories) const {
    std::vector<std::shared_ptr<Meal>> result;
    for (const auto& meal : meals) {
        if (meal->isWithinCalorieRange(minCalories, maxCalories)) {
            result.push_back(meal);
        }
    }
    return result;
}

std::string Tour::getMealSummary() const {
    if (meals.empty()) {
        return "No meals included in this tour.";
    }
    std::string summary = "Meal Summary (" + std::to_string(meals.size()) + "):\n";
    for (size_t i = 0; i < meals.size(); ++i) {
        summary += std::to_string(i + 1) + ". " + meals[i]->getType() + 
                  " - " + meals[i]->getName() + 
                  " ($" + std::to_string(static_cast<int>(meals[i]->getPrice())) + ")\n";
    }
    summary += "Total Meal Cost: $" + std::to_string(static_cast<int>(calculateTotalMealCost())) + "\n";
    return summary;
}

std::string Tour::getFullTourSummary() const {
    std::string summary = getTourInfo() + "\n";
    if (!accommodations.empty()) {
        summary += getAccommodationSummary() + "\n";
    }
    if (!meals.empty()) {
        summary += getMealSummary() + "\n";
    }
    return summary;
}