#include "GuestHouse.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

GuestHouse::GuestHouse(const std::string& name, const std::string& location,
                       double price, int capacity, double rating,
                       bool familyOwned, int totalRooms, const std::string& language, bool commonArea)
    : Accommodation(name, location, price, capacity, rating),
      isFamilyOwned(familyOwned), totalRooms(totalRooms), 
      hostLanguage(language), hasCommonArea(commonArea) {
    if (totalRooms < AccommodationConfig::GuestHouse::MIN_TOTAL_ROOMS || 
        totalRooms > AccommodationConfig::GuestHouse::MAX_TOTAL_ROOMS) {
        throw InvalidDataException("totalRooms", "must be between " + 
            std::to_string(AccommodationConfig::GuestHouse::MIN_TOTAL_ROOMS) + " and " + 
            std::to_string(AccommodationConfig::GuestHouse::MAX_TOTAL_ROOMS));
    }
    if (!StringValidation::isValidName(hostLanguage) || 
        hostLanguage.length() > AccommodationConfig::GuestHouse::MAX_HOST_LANGUAGE_LENGTH) {
        throw InvalidDataException("hostLanguage", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::GuestHouse::MAX_HOST_LANGUAGE_LENGTH) + " characters");
    }
    if (isFamilyOwned) {
        addAmenity("Family Owned");
    }
    if (hasCommonArea) {
        addAmenity("Common Area");
    }
    if (totalRooms <= AccommodationConfig::GuestHouse::SMALL_HOUSE_THRESHOLD) {
        addAmenity("Cozy Atmosphere");
    }
    if (isFamilyOwned && hasCommonArea) {
        addAmenity("Community Feel");
    }
}

std::string GuestHouse::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Family Owned: " + std::string(isFamilyOwned ? "Yes" : "No") + "\n" +
           "Total Rooms: " + std::to_string(totalRooms) + "\n" +
           "Host Language: " + hostLanguage + "\n" +
           "Common Area: " + std::string(hasCommonArea ? "Yes" : "No") + "\n";
    if (isSmallGuestHouse() && isFamilyOwned) {
        info += "Type: Family-run guest house\n";
    } else if (hasCommonArea && totalRooms > AccommodationConfig::GuestHouse::SMALL_HOUSE_THRESHOLD) {
        info += "Type: Community guest house\n";
    } else {
        info += "Type: Standard guest house\n";
    }
    return info;
}

bool GuestHouse::isSmallGuestHouse() const {
    return totalRooms <= AccommodationConfig::GuestHouse::SMALL_HOUSE_THRESHOLD;
}

bool GuestHouse::offersPersonalService() const {
    return isFamilyOwned && isSmallGuestHouse();
}

std::string GuestHouse::getGuestHouseType() const {
    if (isFamilyOwned && isSmallGuestHouse()) {
        return "Boutique Family";
    } else if (hasCommonArea && totalRooms > AccommodationConfig::GuestHouse::MEDIUM_HOUSE_THRESHOLD) {
        return "Community Hub";
    } else {
        return "Standard";
    }
}

bool GuestHouse::isSuitableForLongStay() const {
    return hasCommonArea && isFamilyOwned;
}

bool GuestHouse::hasCommunityAtmosphere() const {
    return hasCommonArea && totalRooms >= AccommodationConfig::GuestHouse::COMMUNITY_MIN_ROOMS;
}

std::string GuestHouse::getType() const { return "Guest House"; }
bool GuestHouse::isFamilyBusiness() const { return isFamilyOwned; }
int GuestHouse::getTotalRooms() const { return totalRooms; }
std::string GuestHouse::getHostLanguage() const { return hostLanguage; }
bool GuestHouse::hasCommonSpace() const { return hasCommonArea; }