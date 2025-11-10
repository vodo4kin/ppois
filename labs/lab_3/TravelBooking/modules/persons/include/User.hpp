#pragma once
#include <string>

class User{
private:
    int generateUserId();
    bool isValidPassword(const std::string& password, size_t minLength = 8) const;
    bool isValidEmail(const std::string& email) const;
    bool isValidPhoneNumber(const std::string& email) const;
protected:
    int userId;
    std::string name;
    std::string email;
    std::string password;
    std::string dateOfBirth;
    std::string phoneNumber;
    std::string address;
    enum class Male{
        MAN,
        WOMAN,
        NOT_SPECIFIED
    } gender;
    bool isActive;
    std::string registrationDate;
    User(const std::string& name, const std::string& email, 
        const std::string& password, const std::string& birthDate);
public:
    void deactivate();
    void activate();
    virtual std::string getUserRole() const = 0;
    virtual ~User() = default;
    int getUserId() const noexcept;
    std::string getName() const noexcept;
    std::string getEmail() const noexcept;
    std::string getDateOfBirth() const noexcept;
    std::string getPhoneNumber() const noexcept;
    std::string getAddress() const noexcept;
    Male getGender() const noexcept;
    std::string getGenderStr() const noexcept;
    bool getIsActive() const noexcept;
    std::string getRegistrationDate() const noexcept;
    int getAge() const noexcept;
    std::string getInfo() const noexcept;
    void setName(const std::string& newName);
    void setEmail(const std::string& newEmail);
    void setPhoneNumber(const std::string& newPhone);
    void setAddress(const std::string& newAddress);
    void setMale(const Male& newGender);
    bool verifyPassword(const std::string& inputPassword) const;
    void changePassword(const std::string& oldPassword, const std::string& newPassword);
};