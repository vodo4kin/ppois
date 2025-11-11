#include "Camping.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

Camping::Camping(const std::string& name, const std::string& location,
                 double price, int capacity, double rating,
                 const std::string& accType, bool sharedBath, bool electricity, bool campfire)
    : Accommodation(name, location, price, capacity, rating),
      accommodationType(accType), hasSharedBathroom(sharedBath),
      hasElectricity(electricity), campfireAllowed(campfire) {
    if (!StringValidation::isValidName(accommodationType) || 
        accommodationType.length() > AccommodationConfig::Camping::MAX_CAMPING_TYPE_LENGTH) {
        throw InvalidDataException("accommodationType", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::Camping::MAX_CAMPING_TYPE_LENGTH) + " characters");
    }
    if (hasElectricity) {
        addAmenity("Electrical Access");
    }
    if (hasSharedBathroom) {
        addAmenity("Shared Bathroom");
    }
    if (campfireAllowed) {
        addAmenity("Campfire Allowed");
    }
    if (isGlamping()) {
        addAmenity("Glamping Experience");
    }
    if (accommodationType == "cabin" || accommodationType == "yurt") {
        addAmenity("Structured Shelter");
    }
}

std::string Camping::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Accommodation Type: " + accommodationType + "\n" +
           "Shared Bathroom: " + std::string(hasSharedBathroom ? "Yes" : "No") + "\n" +
           "Electricity: " + std::string(hasElectricity ? "Yes" : "No") + "\n" +
           "Campfire Allowed: " + std::string(campfireAllowed ? "Yes" : "No") + "\n";
    if (isGlamping()) {
        info += "Category: Glamping site\n";
    } else if (isBasicCamping()) {
        info += "Category: Basic camping\n";
    } else {
        info += "Category: Standard camping\n";
    }
    return info;
}

bool Camping::isGlamping() const {
    return (accommodationType == "cabin" || accommodationType == "yurt") && 
           hasElectricity && hasSharedBathroom;
}

bool Camping::isBasicCamping() const {
    return accommodationType == "tent" && !hasElectricity;
}

bool Camping::hasEssentialAmenities() const {
    return hasSharedBathroom && hasElectricity;
}

std::string Camping::getCampingCategory() const {
    if (isGlamping()) {
        return "Glamping";
    } else if (hasEssentialAmenities()) {
        return "Comfort Camping";
    } else {
        return "Basic Camping";
    }
}

bool Camping::isFamilyFriendly() const {
    return hasEssentialAmenities() && campfireAllowed;
}