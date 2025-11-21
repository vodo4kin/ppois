#include "TourGuide.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "utils/Utils.hpp"

TourGuide::TourGuide(const std::string& name,
                     const std::string& language,
                     int experienceYears)
    : name(name), language(language), experienceYears(experienceYears) {
    if (!StringValidation::isValidName(name)) throw InvalidDataException("name", "must be valid");
    if (language.empty()) throw InvalidDataException("language", "cannot be empty");
    if (experienceYears < 0) throw InvalidDataException("experienceYears", "must be non-negative");
}

std::string TourGuide::getName() const {
    return name;
}

std::string TourGuide::getLanguage() const {
    return language;
}

int TourGuide::getExperienceYears() const {
    return experienceYears;
}

std::string TourGuide::getGuideInfo() const {
    return "Guide: " + name + "\n"
         + "Language: " + language + "\n"
         + "Experience: " + std::to_string(experienceYears) + " years";
}
