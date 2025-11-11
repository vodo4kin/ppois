#include "Resort.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Resort::Resort(const std::string& name, const std::string& location,
               double price, int capacity, double rating,
               bool beach, int restaurants, bool spa, const std::vector<std::string>& activities)
    : Accommodation(name, location, price, capacity, rating),
      hasPrivateBeach(beach), numberOfRestaurants(restaurants), 
      hasSpa(spa), activities(activities) {
    if (numberOfRestaurants < AccommodationConfig::Resort::MIN_RESTAURANTS || 
        numberOfRestaurants > AccommodationConfig::Resort::MAX_RESTAURANTS) {
        throw InvalidDataException("numberOfRestaurants", "must be between " + 
            std::to_string(AccommodationConfig::Resort::MIN_RESTAURANTS) + " and " + 
            std::to_string(AccommodationConfig::Resort::MAX_RESTAURANTS));
    }
    if (activities.size() > AccommodationConfig::Resort::MAX_ACTIVITIES_COUNT) {
        throw InvalidDataException("activities", "cannot exceed maximum count of " + 
            std::to_string(AccommodationConfig::Resort::MAX_ACTIVITIES_COUNT));
    }
    for (const auto& activity : activities) {
        if (!StringValidation::isValidName(activity) || 
            activity.length() > AccommodationConfig::Resort::MAX_ACTIVITY_NAME_LENGTH) {
            throw InvalidDataException("activity", "must be valid and not longer than " + 
                std::to_string(AccommodationConfig::Resort::MAX_ACTIVITY_NAME_LENGTH) + " characters");
        }
    }
    if (hasPrivateBeach) {
        addAmenity("Private Beach");
    }
    if (hasSpa) {
        addAmenity("Spa Services");
    }
    if (numberOfRestaurants >= AccommodationConfig::Resort::MULTIPLE_RESTAURANTS_THRESHOLD) {
        addAmenity("Multiple Dining Options");
    }
    if (!activities.empty()) {
        addAmenity("Recreational Activities");
    }
    if (hasPrivateBeach && hasSpa) {
        addAmenity("Luxury Resort Features");
    }
}

std::string Resort::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Private Beach: " + std::string(hasPrivateBeach ? "Yes" : "No") + "\n" +
           "Restaurants: " + std::to_string(numberOfRestaurants) + "\n" +
           "Spa: " + std::string(hasSpa ? "Yes" : "No") + "\n" +
           "Activities Available: " + std::to_string(activities.size()) + "\n";
    if (!activities.empty()) {
        info += "Featured Activities: ";
        for (size_t i = 0; i < std::min(activities.size(), static_cast<size_t>(3)); ++i) {
            info += activities[i];
            if (i < std::min(activities.size(), static_cast<size_t>(3)) - 1) {
                info += ", ";
            }
        }
        info += "\n";
    }
    if (isLuxuryResort()) {
        info += "Category: Luxury resort\n";
    } else if (isBeachResort()) {
        info += "Category: Beach resort\n";
    } else {
        info += "Category: Standard resort\n";
    }
    return info;
}

bool Resort::isLuxuryResort() const {
    return hasPrivateBeach && hasSpa && 
           numberOfRestaurants >= AccommodationConfig::Resort::LUXURY_RESTAURANT_THRESHOLD;
}

bool Resort::hasComprehensiveAmenities() const {
    return hasSpa && numberOfRestaurants >= AccommodationConfig::Resort::COMPREHENSIVE_RESTAURANT_THRESHOLD;
}

int Resort::getActivityCount() const {
    return static_cast<int>(activities.size());
}

std::string Resort::getResortCategory() const {
    if (isLuxuryResort()) {
        return "Luxury";
    } else if (isBeachResort()) {
        return "Beach";
    } else if (hasSpa && !activities.empty()) {
        return "Wellness";
    } else {
        return "Standard";
    }
}

bool Resort::isBeachResort() const {
    return hasPrivateBeach;
}