#include "books/BookCollection.hpp"
#include "exceptions/WarehouseExceptions.hpp"

bool BookCollection::isValidName(const std::string& name) const {
    if (name.empty() || name.length() > MAX_NAME_LENGTH) {
        return false;
    }
    bool hasNonSpace = false;
    for (char c : name) {
        if (c == '\t' || c == '\n' || c == '\r') return false;
        if (c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
}

bool BookCollection::isValidDescription(const std::string& desc) const {
    return desc.length() <= MAX_DESCRIPTION_LENGTH;
}

bool BookCollection::isValidCategory(const std::string& category) const {
    if (category.empty()) return false;
    bool hasNonSpace = false;
    for (char c : category) {
        if (c == '\t' || c == '\n' || c == '\r') return false;
        if (c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
}

BookCollection::BookCollection(const std::string& name, const std::string& description,
                   const std::string& category) {
    if (!isValidName(name)) {
        throw DataValidationException("Invalid collection name: '" + name + "'");
    }
    if (!isValidDescription(description)) {
        throw DataValidationException("Description too long");
    }
    if (!isValidCategory(category)) {
        throw DataValidationException("Invalid category: '" + category + "'");
    }
    this->name = name;
    this->description = description;
    this->category = category;
}

std::string BookCollection::getName() const noexcept {
    return name;
}

std::string BookCollection::getDescription() const noexcept {
    return description;
}

std::string BookCollection::getCategory() const noexcept {
    return category;
}

void BookCollection::addBook(/* Book* book */) {
    // заглушка
    // books.push_back(book);
}

void BookCollection::removeBook(/* Book* book */) {
    // заглушка
    // auto it = std::find(books.begin(), books.end(), book);
    // if (it != books.end()) books.erase(it);
}

size_t BookCollection::getBookCount() const noexcept {
    return books.size();  // заглушка
}

bool BookCollection::containsBook(/* Book* book */) const {
    // заглушка
    // return std::find(books.begin(), books.end(), book) != books.end();
    return false;
}

bool BookCollection::isEmpty() const noexcept {
    return books.empty();  // заглушка
}

std::string BookCollection::getInfo() const noexcept {
    std::string info = "Collection: " + name + " (" + category + ")";
    if (!description.empty()) {
        info += " - " + description;
    }
    info += " [" + std::to_string(books.size()) + " books]";
    return info;
}

bool BookCollection::operator==(const BookCollection& other) const noexcept {
    return name == other.name &&
           description == other.description &&
           category == other.category;
           // books == other.books  // заглушка
}

bool BookCollection::operator!=(const BookCollection& other) const noexcept {
    return !(*this == other);
}