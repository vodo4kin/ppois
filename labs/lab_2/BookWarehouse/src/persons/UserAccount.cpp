#include "persons/UserAccount.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/PersonConfig.hpp"
#include <ctime>

bool UserAccount::isValidUsername(const std::string& username) const {
    if (username.empty() || username.length() < PersonConfig::UserAccount::MIN_USERNAME_LENGTH || 
        username.length() > PersonConfig::UserAccount::MAX_USERNAME_LENGTH) {
        return false;
    }
    for (char c : username) {
        if (!std::isalnum(c) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool UserAccount::isValidPassword(const std::string& password) const {
    if (password.length() < PersonConfig::UserAccount::MIN_PASSWORD_LENGTH) {
        return false;
    }
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        if (std::islower(c)) hasLower = true;
        if (std::isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

std::string UserAccount::hashPassword(const std::string& password) const {
    //bcrypt, Argon2, у нас дефолт
    std::string hash;
    for (char c : password) {
        hash += std::to_string(static_cast<int>(c * 31) % 1000);
    }
    return hash;
}

UserAccount::UserAccount(const std::string& username, const std::string& password, 
                        std::shared_ptr<Person> person) {
    if (!isValidUsername(username)) {
        throw DataValidationException("Invalid username: " + username);
    }
    if (!isValidPassword(password)) {
        throw DataValidationException("Password does not meet security requirements");
    }
    if (!person) {
        throw DataValidationException("Person cannot be null");
    }
    this->username = username;
    this->passwordHash = hashPassword(password);
    this->person = person;
    this->accountCreated = DateUtils::getCurrentDate();
    this->isLocked = false;
    this->failedLoginAttempts = 0;
}

std::string UserAccount::getUsername() const noexcept {
    return username;
}

std::shared_ptr<Person> UserAccount::getPerson() const noexcept {
    return person;
}

std::string UserAccount::getAccountCreated() const noexcept {
    return accountCreated;
}

bool UserAccount::isAccountLocked() const noexcept {
    return isLocked;
}

int UserAccount::getFailedLoginAttempts() const noexcept {
    return failedLoginAttempts;
}

bool UserAccount::authenticate(const std::string& password) const {
    if (isLocked) {
        throw AuthenticationException("Account is locked");
    }
    bool authenticated = (hashPassword(password) == passwordHash);
    if (!authenticated) {
        const_cast<UserAccount*>(this)->failedLoginAttempts++;
        if (failedLoginAttempts >= PersonConfig::UserAccount::MAX_LOGIN_ATTEMPTS) {
            const_cast<UserAccount*>(this)->lockAccount();
            throw AuthenticationException("Too many failed attempts - account locked");
        }
        throw AuthenticationException("Invalid password");
    }    
    const_cast<UserAccount*>(this)->resetFailedAttempts();
    return true;
}

void UserAccount::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (!authenticate(oldPassword)) {
        throw AuthenticationException("Current password is incorrect");
    }
    if (!isValidPassword(newPassword)) {
        throw DataValidationException("New password does not meet security requirements");
    }
    passwordHash = hashPassword(newPassword);
    resetFailedAttempts();
}

void UserAccount::resetPassword(const std::string& newPassword) {
    if (!isValidPassword(newPassword)) {
        throw DataValidationException("New password does not meet security requirements");
    }
    passwordHash = hashPassword(newPassword);
    unlockAccount();
    resetFailedAttempts();
}

void UserAccount::lockAccount() noexcept {
    isLocked = true;
}

void UserAccount::unlockAccount() noexcept {
    isLocked = false;
    resetFailedAttempts();
}

void UserAccount::resetFailedAttempts() noexcept {
    failedLoginAttempts = 0;
}

bool UserAccount::isPasswordExpired() const {
    std::string currentDate = DateUtils::getCurrentDate();
    int accountYear = std::stoi(accountCreated.substr(0, 4));
    int currentYear = std::stoi(currentDate.substr(0, 4));
    return (currentYear - accountYear) >= PersonConfig::UserAccount::PASSWORD_EXPIRY_YEARS;
}

std::string UserAccount::getInfo() const noexcept {
    std::string info = "Username: " + username;
    info += ", Account Created: " + accountCreated;
    info += ", Locked: " + std::string(isLocked ? "Yes" : "No");
    info += ", Failed Attempts: " + std::to_string(failedLoginAttempts);
    if (person) {
        info += ", Person: " + person->getFullName();
    }
    return info;
}

bool UserAccount::operator==(const UserAccount& other) const noexcept {
    return username == other.username;
}

bool UserAccount::operator!=(const UserAccount& other) const noexcept {
    return !(*this == other);
}