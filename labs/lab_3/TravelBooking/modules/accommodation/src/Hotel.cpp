#include "Hotel.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Hotel::Hotel(const std::string& name, const std::string& location,
             double price, int capacity, double rating,
             int stars, bool pool, bool spa, const std::string& roomType)
    : Accommodation(name, location, price, capacity, rating),
      starRating(stars), hasPool(pool), hasSpa(spa), roomType(roomType) {
    if (starRating < AccommodationConfig::Hotel::MIN_STARS || starRating > AccommodationConfig::Hotel::MAX_STARS) {
        throw InvalidDataException("starRating", "must be between " + 
            std::to_string(AccommodationConfig::Hotel::MIN_STARS) + " and " + 
            std::to_string(AccommodationConfig::Hotel::MAX_STARS));
    }
    if (!StringValidation::isValidName(roomType) || roomType.length() > AccommodationConfig::Hotel::MAX_ROOMTYPE_LENGTH) {
        throw InvalidDataException("roomType", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::Hotel::MAX_ROOMTYPE_LENGTH) + " characters");
    }
}

std::string Hotel::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Star Rating: " + std::to_string(starRating) + " stars\n" +
           "Room Type: " + roomType + "\n" +
           "Swimming Pool: " + std::string(hasPool ? "Yes" : "No") + "\n" +
           "Spa: " + std::string(hasSpa ? "Yes" : "No") + "\n";
    return info;
}