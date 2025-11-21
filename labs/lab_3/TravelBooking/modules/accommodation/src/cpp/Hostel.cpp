#include "Hostel.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Hostel::Hostel(const std::string& name, const std::string& location,
               double price, int capacity, double rating,
               bool privateRoom, int beds, bool sharedKitchen, const std::string& bathroom)
    : Accommodation(name, location, price, capacity, rating),
      isPrivateRoom(privateRoom), bedsPerRoom(beds),
      hasSharedKitchen(sharedKitchen), bathroomType(bathroom) {
    if (bedsPerRoom < AccommodationConfig::Hostel::MIN_BEDS || 
        bedsPerRoom > AccommodationConfig::Hostel::MAX_BEDS) {
        throw InvalidDataException("bedsPerRoom", "must be between " + 
            std::to_string(AccommodationConfig::Hostel::MIN_BEDS) + " and " + 
            std::to_string(AccommodationConfig::Hostel::MAX_BEDS));
    }
    if (!StringValidation::isValidName(bathroomType) || 
        bathroomType.length() > AccommodationConfig::Hostel::MAX_BATHROOM_TYPE_LENGTH) {
        throw InvalidDataException("bathroomType", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::Hostel::MAX_BATHROOM_TYPE_LENGTH) + " characters");
    }
    if (isPrivateRoom) {
        addAmenity("Private Room");
    } else {
        addAmenity("Dormitory Room");
    }
    if (hasSharedKitchen) {
        addAmenity("Shared Kitchen");
    }
    if (bathroomType == "private" || bathroomType == "ensuite") {
        addAmenity("Private Bathroom");
    } else {
        addAmenity("Shared Bathroom");
    }
    if (bedsPerRoom <= AccommodationConfig::Hostel::SMALL_DORM_THRESHOLD) {
        addAmenity("Small Dormitory");
    }
    if (hasSharedKitchen && !isPrivateRoom) {
        addAmenity("Community Living");
    }
}

std::string Hostel::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Room Type: " + std::string(isPrivateRoom ? "Private" : "Dormitory") + "\n" +
           "Beds per Room: " + std::to_string(bedsPerRoom) + "\n" +
           "Shared Kitchen: " + std::string(hasSharedKitchen ? "Yes" : "No") + "\n" +
           "Bathroom: " + bathroomType + "\n";
    if (isPrivateRoom && hasPrivateBathroom()) {
        info += "Category: Private room hostel\n";
    } else if (!isPrivateRoom && bedsPerRoom <= AccommodationConfig::Hostel::SMALL_DORM_THRESHOLD) {
        info += "Category: Small dormitory hostel\n";
    } else if (!isPrivateRoom && bedsPerRoom > AccommodationConfig::Hostel::LARGE_DORM_THRESHOLD) {
        info += "Category: Large dormitory hostel\n";
    } else {
        info += "Category: Standard hostel\n";
    }
    return info;
}

bool Hostel::isDormitory() const {
    return !isPrivateRoom;
}

double Hostel::calculatePricePerBed() const {
    if (bedsPerRoom > 0) {
        return pricePerNight / bedsPerRoom;
    }
    return pricePerNight;
}

bool Hostel::hasPrivateBathroom() const {
    return bathroomType == "private" || bathroomType == "ensuite";
}

std::string Hostel::getHostelCategory() const {
    if (isPrivateRoom && hasPrivateBathroom()) {
        return "Premium Private";
    } else if (isPrivateRoom) {
        return "Standard Private";
    } else if (bedsPerRoom <= AccommodationConfig::Hostel::SMALL_DORM_THRESHOLD) {
        return "Small Dormitory";
    } else if (bedsPerRoom >= AccommodationConfig::Hostel::LARGE_DORM_THRESHOLD) {
        return "Large Dormitory";
    } else {
        return "Standard Dormitory";
    }
}

bool Hostel::isSuitableForGroup(int groupSize) const {
    if (isPrivateRoom) {
        return groupSize <= bedsPerRoom;
    } else {
        return groupSize <= bedsPerRoom * AccommodationConfig::Hostel::MAX_GROUP_MULTIPLIER;
    }
}

std::string Hostel::getType() const { return "Hostel"; }
bool Hostel::isPrivate() const { return isPrivateRoom; }
int Hostel::getBedsPerRoom() const { return bedsPerRoom; }
bool Hostel::hasCommonKitchen() const { return hasSharedKitchen; }
std::string Hostel::getBathroomType() const { return bathroomType; }