#include "MountainLodge.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

MountainLodge::MountainLodge(const std::string& name, const std::string& location,
                             double price, int capacity, double rating,
                             int altitude, bool heating, bool fireplace, const std::string& accessibility)
    : Accommodation(name, location, price, capacity, rating),
      altitude(altitude), hasHeating(heating), 
      hasFireplace(fireplace), accessibility(accessibility) {
    if (altitude < AccommodationConfig::MountainLodge::MIN_ALTITUDE || 
        altitude > AccommodationConfig::MountainLodge::MAX_ALTITUDE) {
        throw InvalidDataException("altitude", "must be between " + 
            std::to_string(AccommodationConfig::MountainLodge::MIN_ALTITUDE) + " and " + 
            std::to_string(AccommodationConfig::MountainLodge::MAX_ALTITUDE) + " meters");
    }
    if (!StringValidation::isValidName(accessibility) || 
        accessibility.length() > AccommodationConfig::MountainLodge::MAX_ACCESSIBILITY_LENGTH) {
        throw InvalidDataException("accessibility", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::MountainLodge::MAX_ACCESSIBILITY_LENGTH) + " characters");
    }
    if (hasHeating) {
        addAmenity("Heating System");
    }
    if (hasFireplace) {
        addAmenity("Fireplace");
    }
    if (altitude >= AccommodationConfig::MountainLodge::HIGH_ALTITUDE_THRESHOLD) {
        addAmenity("High Altitude");
    }
    if (hasHeating && hasFireplace) {
        addAmenity("Winter Comfort");
    }
    if (accessibility == "hard" || accessibility == "expert") {
        addAmenity("Adventure Location");
    }
}

std::string MountainLodge::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Altitude: " + std::to_string(altitude) + " meters\n" +
           "Heating: " + std::string(hasHeating ? "Yes" : "No") + "\n" +
           "Fireplace: " + std::string(hasFireplace ? "Yes" : "No") + "\n" +
           "Accessibility: " + accessibility + "\n";
    if (isHighAltitude() && requiresExperience()) {
        info += "Type: High-altitude adventure lodge\n";
    } else if (isWinterReady() && !isRemoteLocation()) {
        info += "Type: Comfort mountain lodge\n";
    } else {
        info += "Type: Standard mountain lodge\n";
    }
    return info;
}

bool MountainLodge::isHighAltitude() const {
    return altitude >= AccommodationConfig::MountainLodge::HIGH_ALTITUDE_THRESHOLD;
}

bool MountainLodge::isWinterReady() const {
    return hasHeating && hasFireplace;
}

std::string MountainLodge::getLodgeCategory() const {
    if (isHighAltitude() && requiresExperience()) {
        return "Adventure";
    } else if (isWinterReady() && altitude >= AccommodationConfig::MountainLodge::COMFORT_ALTITUDE_THRESHOLD) {
        return "Comfort";
    } else {
        return "Basic";
    }
}

bool MountainLodge::isRemoteLocation() const {
    return accessibility == "hard" || accessibility == "expert";
}

bool MountainLodge::requiresExperience() const {
    return accessibility == "expert";
}

std::string MountainLodge::getType() const { return "Mountain Lodge"; }
int MountainLodge::getAltitude() const { return altitude; }
bool MountainLodge::hasHeatingSystem() const { return hasHeating; }
bool MountainLodge::hasFireplaceFeature() const { return hasFireplace; }
std::string MountainLodge::getAccessibilityLevel() const { return accessibility; }