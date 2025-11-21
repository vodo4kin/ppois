#include "Apartment.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Apartment::Apartment(const std::string& name, const std::string& location,
                     double price, int capacity, double rating,
                     int rooms, bool kitchen, bool washingMachine, double area)
    : Accommodation(name, location, price, capacity, rating),
      numberOfRooms(rooms), hasKitchen(kitchen), 
      hasWashingMachine(washingMachine), area(area) {
    if (numberOfRooms < AccommodationConfig::Apartment::MIN_ROOMS || 
        numberOfRooms > AccommodationConfig::Apartment::MAX_ROOMS) {
        throw InvalidDataException("numberOfRooms", "must be between " + 
            std::to_string(AccommodationConfig::Apartment::MIN_ROOMS) + " and " + 
            std::to_string(AccommodationConfig::Apartment::MAX_ROOMS));
    }
    if (area < AccommodationConfig::Apartment::MIN_AREA || 
        area > AccommodationConfig::Apartment::MAX_AREA) {
        throw InvalidDataException("area", "must be between " + 
            std::to_string(AccommodationConfig::Apartment::MIN_AREA) + " and " + 
            std::to_string(AccommodationConfig::Apartment::MAX_AREA) + " square meters");
    }
    if (hasKitchen) {
        addAmenity("Kitchen");
    }
    if (hasWashingMachine) {
        addAmenity("Washing Machine");
    }
    if (numberOfRooms >= AccommodationConfig::Apartment::SPACIOUS_ROOM_THRESHOLD) {
        addAmenity("Spacious Living");
    }
    if (area > AccommodationConfig::Apartment::LARGE_AREA_THRESHOLD) {
        addAmenity("Large Area");
    }
}

std::string Apartment::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Rooms: " + std::to_string(numberOfRooms) + "\n" +
           "Area: " + std::to_string(static_cast<int>(area)) + " sqm\n" +
           "Kitchen: " + std::string(hasKitchen ? "Yes" : "No") + "\n" +
           "Washing Machine: " + std::string(hasWashingMachine ? "Yes" : "No") + "\n";
    if (numberOfRooms >= AccommodationConfig::Apartment::FAMILY_ROOM_THRESHOLD && 
        area > AccommodationConfig::Apartment::FAMILY_AREA_THRESHOLD) {
        info += "Comfort: Spacious family apartment\n";
    } else if (numberOfRooms == AccommodationConfig::Apartment::STUDIO_ROOM_COUNT && 
               area < AccommodationConfig::Apartment::STUDIO_AREA_THRESHOLD) {
        info += "Comfort: Compact studio apartment\n";
    } else {
        info += "Comfort: Standard apartment\n";
    }
    
    return info;
}

bool Apartment::isSuitableForFamily() const {
    return numberOfRooms >= AccommodationConfig::Apartment::FAMILY_ROOM_THRESHOLD && 
           area > AccommodationConfig::Apartment::FAMILY_AREA_THRESHOLD;
}

bool Apartment::isStudio() const {
    return numberOfRooms == AccommodationConfig::Apartment::STUDIO_ROOM_COUNT;
}

double Apartment::calculatePricePerPerson() const {
    if (capacity > 0) {
        return pricePerNight / capacity;
    }
    return pricePerNight;
}

std::string Apartment::getApartmentCategory() const {
    if (area > AccommodationConfig::Apartment::LUXURY_AREA_THRESHOLD && 
        numberOfRooms >= AccommodationConfig::Apartment::LUXURY_ROOM_THRESHOLD) {
        return "Luxury";
    } else if (area > AccommodationConfig::Apartment::COMFORT_AREA_THRESHOLD && 
               numberOfRooms >= AccommodationConfig::Apartment::COMFORT_ROOM_THRESHOLD) {
        return "Comfort";
    } else {
        return "Standard";
    }
}

bool Apartment::hasFullAmenities() const {
    return hasKitchen && hasWashingMachine;
}

std::string Apartment::getType() const { return "Apartment"; }
int Apartment::getNumberOfRooms() const { return numberOfRooms; }
bool Apartment::hasFullKitchen() const { return hasKitchen; }
bool Apartment::hasLaundry() const { return hasWashingMachine; }
double Apartment::getArea() const { return area; }