#include "Villa.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Villa::Villa(const std::string& name, const std::string& location,
             double price, int capacity, double rating,
             int floors, bool pool, bool garden, bool parking)
    : Accommodation(name, location, price, capacity, rating),
      numberOfFloors(floors), hasPrivatePool(pool), 
      hasGarden(garden), hasParking(parking) {
    if (numberOfFloors < AccommodationConfig::Villa::MIN_FLOORS || 
        numberOfFloors > AccommodationConfig::Villa::MAX_FLOORS) {
        throw InvalidDataException("numberOfFloors", "must be between " + 
            std::to_string(AccommodationConfig::Villa::MIN_FLOORS) + " and " + 
            std::to_string(AccommodationConfig::Villa::MAX_FLOORS));
    }
    if (hasPrivatePool) {
        addAmenity("Private Pool");
    }
    if (hasGarden) {
        addAmenity("Garden");
    }
    if (hasParking) {
        addAmenity("Parking");
    }
    if (numberOfFloors >= AccommodationConfig::Villa::MULTISTORY_THRESHOLD) {
        addAmenity("Multi-story");
    }
    if (hasPrivatePool && hasGarden) {
        addAmenity("Luxury Outdoor");
    }
}

std::string Villa::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Floors: " + std::to_string(numberOfFloors) + "\n" +
           "Private Pool: " + std::string(hasPrivatePool ? "Yes" : "No") + "\n" +
           "Garden: " + std::string(hasGarden ? "Yes" : "No") + "\n" +
           "Parking: " + std::string(hasParking ? "Yes" : "No") + "\n";
    
    if (isLuxuryVilla()) {
        info += "Category: Luxury villa\n";
    } else if (numberOfFloors >= AccommodationConfig::Villa::MULTISTORY_THRESHOLD) {
        info += "Category: Multi-story villa\n";
    } else {
        info += "Category: Standard villa\n";
    }
    return info;
}

bool Villa::isLuxuryVilla() const {
    return hasPrivatePool && hasGarden && hasParking && 
           numberOfFloors >= AccommodationConfig::Villa::LUXURY_FLOOR_THRESHOLD;
}

bool Villa::hasFullPrivacy() const {
    return hasGarden && hasPrivatePool;
}

double Villa::calculateLuxurySurcharge() const {
    double surcharge = 0.0;
    if (hasPrivatePool) surcharge += AccommodationConfig::Villa::POOL_SURCHARGE;
    if (hasGarden) surcharge += AccommodationConfig::Villa::GARDEN_SURCHARGE;
    if (numberOfFloors > 1) surcharge += AccommodationConfig::Villa::FLOOR_SURCHARGE;
    return surcharge;
}

std::string Villa::getVillaCategory() const {
    if (isLuxuryVilla()) {
        return "Luxury";
    } else if (hasPrivatePool || hasGarden) {
        return "Comfort";
    } else {
        return "Standard";
    }
}

bool Villa::isSuitableForEvents() const {
    return hasGarden && capacity >= AccommodationConfig::Villa::MIN_EVENT_CAPACITY;
}