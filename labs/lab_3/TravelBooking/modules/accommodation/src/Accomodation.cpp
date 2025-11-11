#include "Accommodation.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Accommodation::Accommodation(const std::string& name, const std::string& location, 
                             double price, int capacity, double rating)
    : name(name), location(location), pricePerNight(price), 
      capacity(capacity), rating(rating) {
    if (!StringValidation::isValidName(name) || name.length() > AccommodationConfig::Accommodation::MAX_NAME_LENGTH) {
        throw InvalidDataException("name", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_NAME_LENGTH) + " characters");
    }
    if (!StringValidation::isValidName(location) || location.length() > AccommodationConfig::Accommodation::MAX_LOCATION_LENGTH) {
        throw InvalidDataException("location", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_LOCATION_LENGTH) + " characters");
    }
    if (pricePerNight < AccommodationConfig::Accommodation::MIN_PRICE_PER_NIGHT || 
        pricePerNight > AccommodationConfig::Accommodation::MAX_PRICE_PER_NIGHT) {
        throw InvalidDataException("pricePerNight", "must be between " + 
            std::to_string(AccommodationConfig::Accommodation::MIN_PRICE_PER_NIGHT) + " and " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_PRICE_PER_NIGHT));
    }
    if (capacity < AccommodationConfig::Accommodation::MIN_CAPACITY || 
        capacity > AccommodationConfig::Accommodation::MAX_CAPACITY) {
        throw InvalidDataException("capacity", "must be between " + 
            std::to_string(AccommodationConfig::Accommodation::MIN_CAPACITY) + " and " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_CAPACITY));
    }
    if (rating < AccommodationConfig::Accommodation::MIN_RATING || 
        rating > AccommodationConfig::Accommodation::MAX_RATING) {
        throw InvalidDataException("rating", "must be between " + 
            std::to_string(AccommodationConfig::Accommodation::MIN_RATING) + " and " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_RATING));
    }
}

std::string Accommodation::getAccommodationInfo() const {
    std::string info = "Type: " + getType() + "\n" +
                      "Name: " + name + "\n" +
                      "Location: " + location + "\n" +
                      "Price per night: $" + std::to_string(static_cast<int>(pricePerNight)) + "\n" +
                      "Capacity: " + std::to_string(capacity) + " people\n" +
                      "Rating: " + std::to_string(rating) + "/5\n";
    if (!amenities.empty()) {
        info += "Amenities: ";
        for (size_t i = 0; i < amenities.size(); ++i) {
            info += amenities[i];
            if (i < amenities.size() - 1) {
                info += ", ";
            }
        }
        info += "\n";
    }
    return info;
}

void Accommodation::addAmenity(const std::string& amenity) {
    if (!StringValidation::isValidName(amenity) || amenity.length() > AccommodationConfig::Accommodation::MAX_AMENITY_LENGTH) {
        throw InvalidDataException("amenity", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_AMENITY_LENGTH) + " characters");
    }
    for (const auto& existingAmenity : amenities) {
        if (existingAmenity == amenity) {
            return;
        }
    }
    if (amenities.size() >= AccommodationConfig::Accommodation::MAX_AMENITIES_COUNT) {
        throw InvalidDataException("amenities", "cannot exceed maximum count of " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_AMENITIES_COUNT));
    }
    
    amenities.push_back(amenity);
}

void Accommodation::setPricePerNight(double price) {
    if (price < AccommodationConfig::Accommodation::MIN_PRICE_PER_NIGHT || 
        price > AccommodationConfig::Accommodation::MAX_PRICE_PER_NIGHT) {
        throw InvalidDataException("pricePerNight", "must be between " + 
            std::to_string(AccommodationConfig::Accommodation::MIN_PRICE_PER_NIGHT) + " and " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_PRICE_PER_NIGHT));
    }
    pricePerNight = price;
}

void Accommodation::setRating(double newRating) {
    if (newRating < AccommodationConfig::Accommodation::MIN_RATING || 
        newRating > AccommodationConfig::Accommodation::MAX_RATING) {
        throw InvalidDataException("rating", "must be between " + 
            std::to_string(AccommodationConfig::Accommodation::MIN_RATING) + " and " + 
            std::to_string(AccommodationConfig::Accommodation::MAX_RATING));
    }
    rating = newRating;
}

bool Accommodation::canAccommodate(int guests) const {
    return guests > 0 && guests <= capacity;
}

bool Accommodation::isAvailableForDates(const std::string& startDate, const std::string& endDate) const {
    if (!StringValidation::isValidDate(startDate) || !StringValidation::isValidDate(endDate)) {
        throw InvalidDateException("date range");
    }
    // database query
    return true;
}

void Accommodation::validateBooking(int guests, const std::string& startDate, const std::string& endDate) const {
    if (!canAccommodate(guests)) {
        throw AccommodationCapacityExceededException(name, guests, capacity);
    }
    if (!isAvailableForDates(startDate, endDate)) {
        throw AccommodationUnavailableException(name, startDate + " to " + endDate);
    }
    if (guests <= 0) {
        throw InvalidDataException("guests", "must be positive number");
    }
}