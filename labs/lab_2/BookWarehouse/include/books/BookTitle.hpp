#include <string>

class BookTitle{
    private:
    static constexpr size_t MAX_LENGTH = 128;
    static constexpr size_t MIN_LENGTH = 1;
    std::string title;
    std::string subtitle;
    std::string language;
    bool isValidTitle(const std::string& title) const;
    std::string validationLanguage(const std::string& language) const;
    public:
    explicit BookTitle(const std::string& title, const std::string& subtitle, const std::string& language);
    std::string getTitle() const noexcept;
    std::string getSubtitle() const noexcept;
    std::string getLanguage() const noexcept;
    std::string getFullTitle() const noexcept;
    bool operator==(const BookTitle& other) const noexcept;
    bool operator!=(const BookTitle& other) const noexcept;
};