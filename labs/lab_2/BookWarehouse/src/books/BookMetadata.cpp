#include "books/BookMetadata.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"

bool BookMetadata::isValidYear(int year) const {
    return year >= MIN_YEAR && year <= MAX_YEAR;
}

bool BookMetadata::isValidEdition(int edition) const {
    return edition >= 1;
}

bool BookMetadata::isValidDescription(const std::string& desc) const {
    return desc.length() <= MAX_DESCRIPTION_LENGTH;
}

BookMetadata::BookMetadata(int publicationYear, const std::string& language, 
                 int edition, const std::string& description) {
    
    if (!isValidYear(publicationYear)) {
        throw DataValidationException("Invalid publication year: " + std::to_string(publicationYear));
    }
    std::string newLanguage = StringValidation::normalizeLanguage(language);
    if (newLanguage.length() != 2) {
        throw DataValidationException("Language must be 2 letters: '" + language + "'");
    }
    if (!isValidEdition(edition)) {
        throw DataValidationException("Invalid edition: " + std::to_string(edition));
    }
    if (!isValidDescription(description)) {
        throw DataValidationException("Description too long");
    }
    this->publicationYear = publicationYear;
    this->language = newLanguage; 
    this->edition = edition;
    this->description = description;
}

int BookMetadata::getPublicationYear() const noexcept {
    return publicationYear;
}

std::string BookMetadata::getLanguage() const noexcept {
    return language;
}

int BookMetadata::getEdition() const noexcept {
    return edition;
}

std::string BookMetadata::getDescription() const noexcept {
    return description;
}

bool BookMetadata::operator==(const BookMetadata& other) const noexcept {
    return publicationYear == other.publicationYear &&
           language == other.language &&
           edition == other.edition &&
           description == other.description;
}

bool BookMetadata::operator!=(const BookMetadata& other) const noexcept {
    return !(*this == other);
}

bool BookMetadata::isFirstEdition() const noexcept {
    return edition == 1;
}

std::string BookMetadata::getEditionString() const noexcept {
    switch(edition) {
        case 1: return "1st Edition";
        case 2: return "2nd Edition"; 
        case 3: return "3rd Edition";
        default: return std::to_string(edition) + "th Edition";
    }
}