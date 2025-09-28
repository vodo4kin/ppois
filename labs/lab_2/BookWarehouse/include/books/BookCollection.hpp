#include <string>
#include <vector>

class BookCollection {
private:
    static constexpr size_t MAX_NAME_LENGTH = 100;
    static constexpr size_t MAX_DESCRIPTION_LENGTH = 500;
    std::string name;
    std::string description;
    std::string category;
    std::vector</* Book* */> books;
    bool isValidName(const std::string& name) const;
    bool isValidDescription(const std::string& desc) const;
    bool isValidCategory(const std::string& category) const;
public:
    BookCollection(const std::string& name, const std::string& description = "",
                   const std::string& category = "General");
    std::string getName() const noexcept;
    std::string getDescription() const noexcept;
    std::string getCategory() const noexcept;
    void addBook(/* Book* book */);
    void removeBook(/* Book* book */);
    size_t getBookCount() const noexcept;
    bool containsBook(/* Book* book */) const;
    bool isEmpty() const noexcept;
    std::string getInfo() const noexcept;
    bool operator==(const BookCollection& other) const noexcept;
    bool operator!=(const BookCollection& other) const noexcept;
};