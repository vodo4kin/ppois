#include "persons/Address.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/PersonConfig.hpp"

bool Address::isValidStreet(const std::string& street) const {
    return StringValidation::isValidName(street, PersonConfig::Address::MAX_STREET_LENGTH);
}

bool Address::isValidCity(const std::string& city) const {
    return StringValidation::isValidName(city, PersonConfig::Address::MAX_CITY_LENGTH);
}

bool Address::isValidPostalCode(const std::string& postalCode) const {
    return !postalCode.empty() && postalCode.length() <= PersonConfig::Address::MAX_POSTAL_CODE_LENGTH;
}

bool Address::isValidCountry(const std::string& country) const {
    return StringValidation::isValidName(country, PersonConfig::Address::MAX_COUNTRY_LENGTH);
}

Address::Address(const std::string& street, const std::string& city, 
                const std::string& postalCode, const std::string& country) {
    
    if (!isValidStreet(street)) {
        throw DataValidationException("Invalid street address: " + street);
    }
    if (!isValidCity(city)) {
        throw DataValidationException("Invalid city: " + city);
    }
    if (!isValidPostalCode(postalCode)) {
        throw DataValidationException("Invalid postal code: " + postalCode);
    }
    if (!isValidCountry(country)) {
        throw DataValidationException("Invalid country: " + country);
    }
    
    this->street = street;
    this->city = city;
    this->postalCode = postalCode;
    this->country = country;
}

std::string Address::getStreet() const noexcept {
    return street;
}

std::string Address::getCity() const noexcept {
    return city;
}

std::string Address::getPostalCode() const noexcept {
    return postalCode;
}

std::string Address::getCountry() const noexcept {
    return country;
}

std::string Address::getFullAddress() const noexcept {
    return street + ", " + city + ", " + postalCode + ", " + country;
}

void Address::setStreet(const std::string& street) {
    if (!isValidStreet(street)) {
        throw DataValidationException("Invalid street address: " + street);
    }
    this->street = street;
}

void Address::setCity(const std::string& city) {
    if (!isValidCity(city)) {
        throw DataValidationException("Invalid city: " + city);
    }
    this->city = city;
}

void Address::setPostalCode(const std::string& postalCode) {
    if (!isValidPostalCode(postalCode)) {
        throw DataValidationException("Invalid postal code: " + postalCode);
    }
    this->postalCode = postalCode;
}

void Address::setCountry(const std::string& country) {
    if (!isValidCountry(country)) {
        throw DataValidationException("Invalid country: " + country);
    }
    this->country = country;
}

bool Address::isComplete() const noexcept {
    return !street.empty() && !city.empty() && !postalCode.empty() && !country.empty();
}

std::string Address::getInfo() const noexcept {
    return getFullAddress();
}

bool Address::operator==(const Address& other) const noexcept {
    return street == other.street && 
           city == other.city && 
           postalCode == other.postalCode && 
           country == other.country;
}

bool Address::operator!=(const Address& other) const noexcept {
    return !(*this == other);
}