#include "User.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/PersonsConfig.hpp"
#include <atomic>

static std::atomic<int> nextUserId{1};

int User::generateUserId() {
	return nextUserId++;
}

bool User::isValidEmail(const std::string& email) const {
	if (email.empty()) return false;
	size_t at_pos = email.find('@');
	if (at_pos == std::string::npos || at_pos == 0) return false;
	if (at_pos >= email.length() - 1) return false;
	size_t dot_pos = email.find('.', at_pos);
	if (dot_pos == std::string::npos) return false;
	if (dot_pos >= email.length() - 1) return false;
	if (dot_pos - at_pos <= 1) return false;
	if (email.find(' ') != std::string::npos) return false;
	if (email.find("..") != std::string::npos) return false;
	return true;
}

bool User::isValidPassword(const std::string& password, size_t minLength) const {
	if (password.length() < minLength) {
		return false;
	}
	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasSpecial = false;
	for (char c : password) {
		if (std::isupper(c)) hasUpper = true;
		else if (std::islower(c)) hasLower = true;
		else if (std::isdigit(c)) hasDigit = true;
		else if (!std::isspace(c)) hasSpecial = true;
	}
	return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool User::isValidPhoneNumber(const std::string& phoneNumber) const {
    if (phoneNumber.empty()) {
        return false;
    }
    if (phoneNumber[0] != '+') {
        return false;
    }
    if (phoneNumber.length() < 2) {
        return false;
    }
    for (size_t i = 1; i < phoneNumber.length(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(phoneNumber[i]))) {
            return false;
        }
    }
    size_t digitCount = phoneNumber.length() - 1;
    if (digitCount < PersonsConfig::User::MIN_PHONE_NUMBER_LENGTH
		|| digitCount > PersonsConfig::User::MAX_PHONE_NUMBER_LENGTH) {
        return false;
    }
    return true;
}

User::User(const std::string& name, const std::string& email,
    const std::string& password, const std::string& birthDate) {
    if(!StringValidation::isValidName(name, PersonsConfig::User::MAX_NAME_LENGTH)) {
        throw InvalidDataException("name", "must be valid and not exceed " 
            + std::to_string(PersonsConfig::User::MAX_NAME_LENGTH) + " characters");
    }
    if(!isValidEmail(email)) {
        throw InvalidDataException("email", "must be valid (example@i.o)");
    }
    if (!isValidPassword(password, PersonsConfig::User::MIN_PASSWORD_LENGTH)) {
        throw InvalidDataException("password", "must be at least " + std::to_string(PersonsConfig::User::MIN_PASSWORD_LENGTH) + " characters long");
    }
	if(!StringValidation::isValidDate(birthDate)) {
		throw InvalidDataException("birthDate", "must be valid (Example: 2024-01-01)");
	}
	if(DateUtils::calculateAge(birthDate) < 14) {
		throw UnderageException(DateUtils::calculateAge(birthDate), 14);
	}
	this->name = name;
	this->email = email;
	this->password = password;
	this->dateOfBirth = birthDate;
	this->userId = generateUserId();
	this->phoneNumber = "not specified";
	this->address = "not specified";
	this->gender = Male::NOT_SPECIFIED;
	this->isActive = true;
	this->registrationDate = DateUtils::getCurrentDate();
}

int User::getUserId() const noexcept {
	return userId;
}

std::string User::getName() const noexcept {
	return name;
}

std::string User::getEmail() const noexcept {
	return email;
}

std::string User::getDateOfBirth() const noexcept {
	return dateOfBirth;
}

std::string User::getPhoneNumber() const noexcept {
	return phoneNumber;
}

std::string User::getAddress() const noexcept {
	return address;
}

User::Male User::getGender() const noexcept {
	return gender;
}

std::string User::getGenderStr() const noexcept {
	return gender == Male::MAN ? "Man" : gender == Male::WOMAN ? "Woman" : "not specified";
}

bool User::getIsActive() const noexcept {
	return isActive;
}

std::string User::getRegistrationDate() const noexcept {
	return registrationDate;
}

int User::getAge() const noexcept {
	return DateUtils::calculateAge(dateOfBirth);
}

std::string User::getInfo() const noexcept {
    return "User ID: " + std::to_string(userId) + "\n"
                     + "Name: " + name + "\n"
                     + "Email: " + email + "\n"
                     + "Gender: " + getGenderStr() + "\n"
                     + "Date of birth: " + dateOfBirth + " (" + std::to_string(getAge()) + " years)\n"
                     + "Address: " + address + "\n"
                     + "Phone: " + phoneNumber + "\n"
                     + "Registered: " + registrationDate + "\n"
                     + "Status: " + (isActive ? "Active" : "Inactive");
}

void User::setName(const std::string& newName) {
	if(!StringValidation::isValidName(newName, PersonsConfig::User::MAX_NAME_LENGTH)) {
        throw InvalidDataException("name", "must be valid and not exceed " 
            + std::to_string(PersonsConfig::User::MAX_NAME_LENGTH) + " characters");
    }
	this->name = newName;
}

void User::setEmail(const std::string& newEmail) {
    if(!isValidEmail(newEmail)) {
        throw InvalidDataException("email", "must be valid (example@i.o)");
    }
	this->email = newEmail;
}

void User::setPhoneNumber(const std::string& newPhone) {
    if (!isValidPhoneNumber(newPhone)) {
        throw InvalidDataException("phone number", "must be in format +digits (7-15 digits)");
    }
    this->phoneNumber = newPhone;
}

void User::setAddress(const std::string& newAddress) {
	if (newAddress.empty()) {
        this->address = "not specified";
        return;
    }
    if (newAddress.length() > PersonsConfig::User::MAX_ADDRESS_LENGTH) {
        throw InvalidDataException("address", "must not exceed " + 
            std::to_string(PersonsConfig::User::MAX_ADDRESS_LENGTH) + " characters");
    }
    if (!StringValidation::isValidName(newAddress)) {
        throw InvalidDataException("address", "cannot be with only spaces");
    }
    this->address = newAddress;
}

void User::setMale(const Male& newGender) {
	this->gender = newGender;
}

void User::deactivate() {
    this->isActive = false;
}

void User::activate() {
    this->isActive = true;
}

bool User::verifyPassword(const std::string& inputPassword) const {
	return inputPassword == password;
}

void User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
	if(password != oldPassword) {
		throw(InvalidDataException("passwords", "old password must be correct"));
	}
	if (oldPassword == newPassword) {
		throw(InvalidDataException("passwords", "old and new passwords must be different"));
	}
	if (!isValidPassword(newPassword, PersonsConfig::User::MIN_PASSWORD_LENGTH)) {
        throw InvalidDataException("password", "must be at least " + std::to_string(PersonsConfig::User::MIN_PASSWORD_LENGTH) + " characters long");
    }
	this->password = newPassword;
}