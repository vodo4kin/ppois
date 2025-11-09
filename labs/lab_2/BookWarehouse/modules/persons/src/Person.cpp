#include "Person.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/PersonConfig.hpp"

bool Person::isValidId(const std::string& id) const {
    return !id.empty() && id.length() <= PersonConfig::Person::MAX_ID_LENGTH && StringValidation::isValidName(id);
}

bool Person::isValidName(const std::string& name) const {
    return StringValidation::isValidName(name, PersonConfig::Person::MAX_NAME_LENGTH);
}

bool Person::isValidDateOfBirth(const std::string& date) const {
    return StringValidation::isValidDate(date);
}

Person::Person(const std::string& id, const std::string& firstName, const std::string& lastName,
               const std::string& dateOfBirth, std::shared_ptr<Address> address,
               std::shared_ptr<ContactInfo> contactInfo) {
    
    if (!isValidId(id)) {
        throw DataValidationException("Invalid person ID: " + id);
    }
    if (!isValidName(firstName)) {
        throw DataValidationException("Invalid first name: " + firstName);
    }
    if (!isValidName(lastName)) {
        throw DataValidationException("Invalid last name: " + lastName);
    }
    if (!isValidDateOfBirth(dateOfBirth)) {
        throw DataValidationException("Invalid date of birth: " + dateOfBirth);
    }
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->dateOfBirth = dateOfBirth;
    this->address = address;
    this->contactInfo = contactInfo;
}

std::string Person::getId() const noexcept {
    return id;
}

std::string Person::getFirstName() const noexcept {
    return firstName;
}

std::string Person::getLastName() const noexcept {
    return lastName;
}

std::string Person::getFullName() const noexcept {
    return firstName + " " + lastName;
}

std::string Person::getDateOfBirth() const noexcept {
    return dateOfBirth;
}

std::shared_ptr<Address> Person::getAddress() const noexcept {
    return address;
}

std::shared_ptr<ContactInfo> Person::getContactInfo() const noexcept {
    return contactInfo;
}

void Person::setFirstName(const std::string& firstName) {
    if (!isValidName(firstName)) {
        throw DataValidationException("Invalid first name: " + firstName);
    }
    this->firstName = firstName;
}

void Person::setLastName(const std::string& lastName) {
    if (!isValidName(lastName)) {
        throw DataValidationException("Invalid last name: " + lastName);
    }
    this->lastName = lastName;
}

void Person::setAddress(std::shared_ptr<Address> address) {
    this->address = address;
}

void Person::setContactInfo(std::shared_ptr<ContactInfo> contactInfo) {
    this->contactInfo = contactInfo;
}

int Person::calculateAge() const {
    std::string currentDate = DateUtils::getCurrentDate();
    int birthYear = std::stoi(dateOfBirth.substr(0, 4));
    int currentYear = std::stoi(currentDate.substr(0, 4));
    return currentYear - birthYear;
}

bool Person::isAdult() const noexcept {
    return calculateAge() >= PersonConfig::Person::ADULT_AGE;
}

std::string Person::getInfo() const noexcept {
    std::string info = "ID: " + id + 
                      ", Name: " + getFullName() + 
                      ", Age: " + std::to_string(calculateAge());
    if (address) {
        info += ", Address: " + address->getFullAddress();
    }
    if (contactInfo) {
        info += ", Contact: " + contactInfo->getPrimaryContact();
    }
    return info;
}

bool Person::operator==(const Person& other) const noexcept {
    return id == other.id;
}

bool Person::operator!=(const Person& other) const noexcept {
    return !(*this == other);
}