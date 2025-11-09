#include "Publisher.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"
#include "config/BookConfig.hpp"

bool Publisher::isValidName(const std::string& name) const{
    return StringValidation::isValidName(name, BookConfig::Publisher::MAX_NAME_LENGTH);
}

bool Publisher::isValidEmail(const std::string& email) const {
    if (email.empty()) return true;
    size_t atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0) return false;
    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos || dotPos == atPos + 1) return false;
    return true;
}

bool Publisher::isValidYear(int year) const{
    return year >=BookConfig::Publisher::YEAR_MIN && year <= BookConfig::Publisher::YEAR_MAX;
}

Publisher::Publisher(const std::string& name, const std::string& contactEmail, int foundationYear) {
    if (!isValidName(name)) {
        throw DataValidationException("Invalid publisher name: '" + name + "'");
    }
    if (!isValidEmail(contactEmail)) {
        throw DataValidationException("Invalid email format: '" + contactEmail + "'");
    }
    if (!isValidYear(foundationYear)) {
        throw DataValidationException("Invalid foundation year: " + std::to_string(foundationYear));
    }
    this->name = name;
    this->contactEmail = contactEmail;
    this->foundationYear = foundationYear;
}

std::string Publisher::getName() const noexcept{
    return name;
}

std::string Publisher::getContactEmail() const noexcept{
    return contactEmail;
}

int Publisher::getFoundationYear() const noexcept{
    return foundationYear;
}

std::string Publisher::getInfo() const noexcept{
    std::string result = "Publisher: " + name + "\nFounded: " + std::to_string(foundationYear);
    if(!contactEmail.empty()) result+= "\nEmail: " + contactEmail;
    return result;
}

bool Publisher::operator==(const Publisher& other) const noexcept{
    return name == other.name && contactEmail == other.contactEmail
        && foundationYear == other.foundationYear;
}

bool Publisher::operator!=(const Publisher& other) const noexcept{
    return !(*this == other);
}