#include "BookSeries.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"
#include "config/BookConfig.hpp"

bool BookSeries::isValidName(const std::string& name) const {
    return StringValidation::isValidName(name, BookConfig::BookSeries::MAX_NAME_LENGTH);
}

bool BookSeries::isValidDescription(const std::string& desc) const {
    return desc.length() <= BookConfig::BookSeries::MAX_DESCRIPTION_LENGTH;
}

bool BookSeries::isValidYear(int year) const {
    return (year >= BookConfig::BookSeries::YEAR_MIN && year 
        <= BookConfig::BookSeries::YEAR_MAX) || year == 0;
}

bool BookSeries::isValidBookCount(int count) const {
    return count >= 0;
}

BookSeries::BookSeries(const std::string& name, const std::string& description,
               int bookCount, int startYear, int endYear) {
    
    if (!isValidName(name)) {
        throw DataValidationException("Invalid series name: '" + name + "'");
    }
    if (!isValidDescription(description)) {
        throw DataValidationException("Description too long");
    }
    if (!isValidBookCount(bookCount)) {
        throw DataValidationException("Invalid book count: " + std::to_string(bookCount));
    }
    if (!isValidYear(startYear)) {
        throw DataValidationException("Invalid start year: " + std::to_string(startYear));
    }
    if (!isValidYear(endYear)) {
        throw DataValidationException("Invalid end year: " + std::to_string(endYear));
    }
    if (endYear != 0 && endYear < startYear) {
        throw DataValidationException("End year cannot be before start year");
    }
    this->name = name;
    this->description = description;
    this->bookCount = bookCount;
    this->startYear = startYear;
    this->endYear = endYear;
}

std::string BookSeries::getName() const noexcept {
    return name;
}

std::string BookSeries::getDescription() const noexcept {
    return description;
}

int BookSeries::getBookCount() const noexcept {
    return bookCount;
}

int BookSeries::getStartYear() const noexcept {
    return startYear;
}

int BookSeries::getEndYear() const noexcept {
    return endYear;
}

bool BookSeries::isCompleted() const noexcept {
    return endYear != 0;
}

bool BookSeries::isOngoing() const noexcept {
    return endYear == 0;
}

bool BookSeries::operator==(const BookSeries& other) const noexcept {
    return name == other.name &&
           description == other.description &&
           bookCount == other.bookCount &&
           startYear == other.startYear &&
           endYear == other.endYear;
}

bool BookSeries::operator!=(const BookSeries& other) const noexcept {
    return !(*this == other);
}

std::string BookSeries::getInfo() const noexcept {
    std::string info = "Series: " + name;
    if (!description.empty()) {
        info += " - " + description;
    }
    if (bookCount > 0) {
        info += " (" + std::to_string(bookCount) + " books";
    }
    if (startYear > 0) {
        info += ", " + std::to_string(startYear);
        if (endYear > 0) {
            info += "-" + std::to_string(endYear);
        } else if (isOngoing()) {
            info += "-present";
        }
        info += ")";
    } else if (bookCount > 0) {
        info += ")";
    }
    return info;
}