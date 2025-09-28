#include <string>

class Publisher {
private:
    static constexpr size_t MAX_NAME_LENGTH = 100;
    static constexpr size_t MIN_NAME_LENGTH = 1;
    static constexpr size_t YEAR = 2025;
    std::string name;
    std::string contactEmail;
    int foundationYear;
    bool isValidName(const std::string& name) const;
    bool isValidEmail(const std::string& email) const;
    bool isValidYear(int year) const;
public:
    Publisher(const std::string& name, const std::string& contactEmail, int foundationYear);
    std::string getName() const noexcept;
    std::string getContactEmail() const noexcept;
    int getFoundationYear() const noexcept;
    std::string getInfo() const noexcept;
    bool operator==(const Publisher& other) const noexcept;
    bool operator!=(const Publisher& other) const noexcept;
};