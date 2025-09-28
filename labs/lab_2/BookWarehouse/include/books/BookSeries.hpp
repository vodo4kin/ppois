#include <string>

class BookSeries {
private:
    static constexpr size_t MAX_NAME_LENGTH = 100;
    static constexpr size_t MAX_DESCRIPTION_LENGTH = 500;
    std::string name;
    std::string description;
    int bookCount;
    int startYear;
    int endYear;
    bool isValidName(const std::string& name) const;
    bool isValidDescription(const std::string& desc) const;
    bool isValidYear(int year) const;
    bool isValidBookCount(int count) const;
public:
    BookSeries(const std::string& name, const std::string& description = "",
               int bookCount = 0, int startYear = 0, int endYear = 0);
    
    std::string getName() const noexcept;
    std::string getDescription() const noexcept;
    int getBookCount() const noexcept;
    int getStartYear() const noexcept;
    int getEndYear() const noexcept;
    bool isCompleted() const noexcept;
    bool isOngoing() const noexcept;
    bool operator==(const BookSeries& other) const noexcept;
    bool operator!=(const BookSeries& other) const noexcept;
    std::string getInfo() const noexcept;
};