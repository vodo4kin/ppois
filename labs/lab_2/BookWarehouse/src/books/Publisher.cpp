#include "books/Publisher.hpp"
#include "exceptions/WarehouseExceptions.hpp"

bool Publisher::isValidName(const std::string& name) const{
    if(name.length() < MIN_NAME_LENGTH || name.length() > MAX_NAME_LENGTH) return false;
    bool hasNonSpace = false;
    for (char c : name) {
        if (c == '\t' || c == '\n' || c == '\r') return false;
        if (c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
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
    return year >=1400 && year <= YEAR;
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
    return name == other.getName() && contactEmail == other.getContactEmail()
        && foundationYear == other.getFoundationYear();
}

bool Publisher::operator!=(const Publisher& other) const noexcept{
    return !(*this == other);
}