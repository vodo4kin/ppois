#include "BoutiqueHotel.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/AccommodationConfig.hpp"
#include "utils/Utils.hpp"

BoutiqueHotel::BoutiqueHotel(const std::string& name, const std::string& location,
                             double price, int capacity, double rating,
                             const std::string& theme, int year, bool concierge, const std::string& style)
    : Accommodation(name, location, price, capacity, rating),
      theme(theme), yearBuilt(year), hasConcierge(concierge), architecturalStyle(style) {
    if (yearBuilt < AccommodationConfig::BoutiqueHotel::MIN_YEAR_BUILT) {
        throw InvalidDataException("yearBuilt", "must be after " + 
            std::to_string(AccommodationConfig::BoutiqueHotel::MIN_YEAR_BUILT));
    }
    if (!StringValidation::isValidName(theme) || 
        theme.length() > AccommodationConfig::BoutiqueHotel::MAX_THEME_LENGTH) {
        throw InvalidDataException("theme", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::BoutiqueHotel::MAX_THEME_LENGTH) + " characters");
    }
    if (!StringValidation::isValidName(architecturalStyle) || 
        architecturalStyle.length() > AccommodationConfig::BoutiqueHotel::MAX_ARCH_STYLE_LENGTH) {
        throw InvalidDataException("architecturalStyle", "must be valid and not longer than " + 
            std::to_string(AccommodationConfig::BoutiqueHotel::MAX_ARCH_STYLE_LENGTH) + " characters");
    }
    if (hasConcierge) {
        addAmenity("Concierge Service");
    }
    if (isHistoric()) {
        addAmenity("Historic Building");
    }
    if (isDesignHotel()) {
        addAmenity("Design Concept");
    }
    if (!theme.empty()) {
        addAmenity("Themed Experience");
    }
    if (hasConcierge && isDesignHotel()) {
        addAmenity("Premium Boutique");
    }
}

std::string BoutiqueHotel::getAccommodationInfo() const {
    std::string info = Accommodation::getAccommodationInfo();
    info += "Theme: " + theme + "\n" +
           "Year Built: " + std::to_string(yearBuilt) + "\n" +
           "Concierge: " + std::string(hasConcierge ? "Yes" : "No") + "\n" +
           "Architectural Style: " + architecturalStyle + "\n" +
           "Hotel Age: " + std::to_string(calculateHotelAge()) + " years\n";
    if (isHistoric() && hasConcierge) {
        info += "Category: Historic luxury boutique\n";
    } else if (isDesignHotel()) {
        info += "Category: Design boutique hotel\n";
    } else {
        info += "Category: Standard boutique hotel\n";
    }
    return info;
}

bool BoutiqueHotel::isHistoric() const {
    return calculateHotelAge() >= AccommodationConfig::BoutiqueHotel::HISTORIC_AGE_THRESHOLD;
}

bool BoutiqueHotel::isDesignHotel() const {
    return !theme.empty() && yearBuilt >= AccommodationConfig::BoutiqueHotel::MODERN_YEAR_THRESHOLD;
}

bool BoutiqueHotel::hasPremiumServices() const {
    return hasConcierge;
}

std::string BoutiqueHotel::getBoutiqueCategory() const {
    if (isHistoric() && hasConcierge) {
        return "Historic Luxury";
    } else if (isDesignHotel() && hasConcierge) {
        return "Design Premium";
    } else if (isHistoric()) {
        return "Historic Charm";
    } else {
        return "Boutique Standard";
    }
}

int BoutiqueHotel::calculateHotelAge() const {
    std::string currentYearStr = DateUtils::getCurrentDate().substr(0, 4);
    int currentYear = std::stoi(currentYearStr);
    return currentYear - yearBuilt;
}