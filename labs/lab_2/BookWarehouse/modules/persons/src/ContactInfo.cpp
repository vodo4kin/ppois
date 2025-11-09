#include "ContactInfo.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/PersonConfig.hpp"

bool ContactInfo::isValidEmail(const std::string& email) const {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0 || atPos == email.length() - 1) {
        return false;
    }
    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos || dotPos == email.length() - 1) {
        return false;
    }
    return true;
}

bool ContactInfo::isValidPhoneNumber(const std::string& phone) const {
    if (phone.empty()) return false;
    for (char c : phone) {
        if (!std::isdigit(c) && c != '+' && c != '-' && c != ' ' && c != '(' && c != ')') {
            return false;
        }
    }
    return phone.length() >= PersonConfig::ContactInfo::MIN_PHONE_LENGTH && 
           phone.length() <= PersonConfig::ContactInfo::MAX_PHONE_LENGTH;
}

ContactInfo::ContactInfo(const std::string& email, const std::string& phoneNumber,
                        const std::string& secondaryEmail, const std::string& secondaryPhone) {
    if (!email.empty() && !isValidEmail(email)) {
        throw DataValidationException("Invalid email format: " + email);
    }
    if (!phoneNumber.empty() && !isValidPhoneNumber(phoneNumber)) {
        throw DataValidationException("Invalid phone number: " + phoneNumber);
    }
    if (!secondaryEmail.empty() && !isValidEmail(secondaryEmail)) {
        throw DataValidationException("Invalid secondary email: " + secondaryEmail);
    }
    if (!secondaryPhone.empty() && !isValidPhoneNumber(secondaryPhone)) {
        throw DataValidationException("Invalid secondary phone: " + secondaryPhone);
    }
    this->email = email;
    this->phoneNumber = phoneNumber;
    this->secondaryEmail = secondaryEmail;
    this->secondaryPhone = secondaryPhone;
}

std::string ContactInfo::getEmail() const noexcept {
    return email;
}

std::string ContactInfo::getPhoneNumber() const noexcept {
    return phoneNumber;
}

std::string ContactInfo::getSecondaryEmail() const noexcept {
    return secondaryEmail;
}

std::string ContactInfo::getSecondaryPhone() const noexcept {
    return secondaryPhone;
}

void ContactInfo::setEmail(const std::string& email) {
    if (!email.empty() && !isValidEmail(email)) {
        throw DataValidationException("Invalid email format: " + email);
    }
    this->email = email;
}

void ContactInfo::setPhoneNumber(const std::string& phoneNumber) {
    if (!phoneNumber.empty() && !isValidPhoneNumber(phoneNumber)) {
        throw DataValidationException("Invalid phone number: " + phoneNumber);
    }
    this->phoneNumber = phoneNumber;
}

void ContactInfo::setSecondaryEmail(const std::string& secondaryEmail) {
    if (!secondaryEmail.empty() && !isValidEmail(secondaryEmail)) {
        throw DataValidationException("Invalid secondary email: " + secondaryEmail);
    }
    this->secondaryEmail = secondaryEmail;
}

void ContactInfo::setSecondaryPhone(const std::string& secondaryPhone) {
    if (!secondaryPhone.empty() && !isValidPhoneNumber(secondaryPhone)) {
        throw DataValidationException("Invalid secondary phone: " + secondaryPhone);
    }
    this->secondaryPhone = secondaryPhone;
}

std::string ContactInfo::getPrimaryContact() const noexcept {
    if (!email.empty()) return email;
    if (!phoneNumber.empty()) return phoneNumber;
    return "No contact information";
}

bool ContactInfo::hasValidContact() const noexcept {
    return !email.empty() || !phoneNumber.empty();
}

bool ContactInfo::hasEmail() const noexcept {
    return !email.empty();
}

bool ContactInfo::hasPhoneNumber() const noexcept {
    return !phoneNumber.empty();
}

std::string ContactInfo::getInfo() const noexcept {
    std::string info = "Primary: " + getPrimaryContact();
    if (!secondaryEmail.empty()) {
        info += ", Secondary Email: " + secondaryEmail;
    }
    if (!secondaryPhone.empty()) {
        info += ", Secondary Phone: " + secondaryPhone;
    }
    return info;
}

bool ContactInfo::operator==(const ContactInfo& other) const noexcept {
    return email == other.email && 
           phoneNumber == other.phoneNumber && 
           secondaryEmail == other.secondaryEmail && 
           secondaryPhone == other.secondaryPhone;
}

bool ContactInfo::operator!=(const ContactInfo& other) const noexcept {
    return !(*this == other);
}