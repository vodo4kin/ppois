#include "CruiseCabin.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

CruiseCabin::CruiseCabin(const std::string& name, const std::string& location,
                         double price, int capacity, double rating,
                         const std::string& cabinType, int deck, bool window, const std::string& ship)
    : Accommodation(name, location, price, capacity, rating),
      cabinType(cabinType), deckNumber(deck), hasWindow(window), shipName(ship) {
    if (deckNumber < AccommodationConfig::CruiseCabin::MIN_DECK_NUMBER || 
        deckNumber > AccommodationConfig::CruiseCabin::MAX_DECK_NUMBER) {
        throw InvalidDataException("deckNumber", "must be between " + 
            std::to_string(AccommodationConfig::CruiseCabin::MIN_DECK_NUMBER) + " and " + 
            std::to_string(AccommodationConfig::CruiseCabin::MAX_DECK_NUMBER));
    }
    if (!StringValidation::isValidName(cabinType) || 
        cabinType.length() > AccommodationConfig::CruiseCabin::MAX_CABIN_TYPE_LENGTH) {
        throw InvalidDataException("cabinType", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::CruiseCabin::MAX_CABIN_TYPE_LENGTH) + " characters");
    }
    if (!StringValidation::isValidName(shipName) || 
        shipName.length() > AccommodationConfig::CruiseCabin::MAX_SHIP_NAME_LENGTH) {
        throw InvalidDataException("shipName", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::CruiseCabin::MAX_SHIP_NAME_LENGTH) + " characters");
    }
    if (hasWindow) {
        addAmenity("Ocean View");
    }
    if (isPremiumCabin()) {
        addAmenity("Premium Cabin");
    }
    if (isOnUpperDeck()) {
        addAmenity("Upper Deck Location");
    }
    if (cabinType == "suite" || cabinType == "balcony") {
        addAmenity("Spacious Cabin");
    }
    if (hasWindow && isOnUpperDeck()) {
        addAmenity("Premium View");
    }
}

std::string CruiseCabin::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Cabin Type: " + cabinType + "\n" +
           "Deck Number: " + std::to_string(deckNumber) + "\n" +
           "Window: " + std::string(hasWindow ? "Yes" : "No") + "\n" +
           "Ship: " + shipName + "\n";
    if (isPremiumCabin()) {
        info += "Category: Premium cruise cabin\n";
    } else if (isInteriorCabin()) {
        info += "Category: Interior cabin\n";
    } else {
        info += "Category: Standard cruise cabin\n";
    }
    return info;
}

bool CruiseCabin::isPremiumCabin() const {
    return (cabinType == "suite" || cabinType == "balcony") && 
           hasWindow && isOnUpperDeck();
}

bool CruiseCabin::isInteriorCabin() const {
    return cabinType == "interior" && !hasWindow;
}

bool CruiseCabin::hasView() const {
    return hasWindow;
}

std::string CruiseCabin::getCabinCategory() const {
    if (isPremiumCabin()) {
        return "Premium";
    } else if (hasView() && !isInteriorCabin()) {
        return "Ocean View";
    } else if (isInteriorCabin()) {
        return "Interior";
    } else {
        return "Standard";
    }
}

bool CruiseCabin::isOnUpperDeck() const {
    return deckNumber >= AccommodationConfig::CruiseCabin::UPPER_DECK_THRESHOLD;
}

std::string CruiseCabin::getType() const { return "Cruise Cabin"; }
std::string CruiseCabin::getCabinType() const { return cabinType; }
int CruiseCabin::getDeckNumber() const { return deckNumber; }
bool CruiseCabin::hasOceanView() const { return hasWindow; }
std::string CruiseCabin::getShipName() const { return shipName; }