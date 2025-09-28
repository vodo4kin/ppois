#include <string>

class BookMetadata {
private:
    static constexpr int MIN_YEAR = 1400;
    static constexpr int MAX_YEAR = 2025;
    static constexpr int MAX_DESCRIPTION_LENGTH = 500;
    int publicationYear;
    std::string language;
    int edition;
    std::string description;
    std::string validationLanguage(const std::string& language) const;
    bool isValidYear(int year) const;
    bool isValidEdition(int edition) const;
    bool isValidDescription(const std::string& desc) const;
public:
    BookMetadata(int publicationYear, const std::string& language, 
                 int edition = 1, const std::string& description = "");
    int getPublicationYear() const noexcept;
    std::string getLanguage() const noexcept;
    int getEdition() const noexcept;
    std::string getDescription() const noexcept;
    bool operator==(const BookMetadata& other) const noexcept;
    bool operator!=(const BookMetadata& other) const noexcept;
    bool isFirstEdition() const noexcept;
    std::string getEditionString() const noexcept;
};