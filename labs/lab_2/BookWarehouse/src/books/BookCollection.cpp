#include "books/BookCollection.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include <algorithm>
#include "utils/Utils.hpp"
#include "config/BookConfig.hpp"

bool BookCollection::isValidName(const std::string& name) const {
    return StringValidation::isValidName(name, BookConfig::BookCollection::MAX_NAME_LENGTH);
}

bool BookCollection::isValidDescription(const std::string& desc) const {
    return desc.length() <= BookConfig::BookCollection::MAX_DESCRIPTION_LENGTH;
}

bool BookCollection::isValidCategory(const std::string& category) const {
    return StringValidation::isValidName(category, BookConfig::BookCollection::MAX_NAME_LENGTH);
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

void BookCollection::addBook(std::shared_ptr<Book> book) {
    if (!book) {
        throw DataValidationException("Book cannot be null");
    }
    if (containsBook(book)) {
        throw DuplicateBookException("Book already in collection: " + book->getTitle().getFullTitle());
    }
    books.push_back(book);
}

void BookCollection::removeBook(std::shared_ptr<Book> book) {
    if (!book) return;
    auto it = std::find(books.begin(), books.end(), book);
    if (it != books.end()) {
        books.erase(it);
    }
}

size_t BookCollection::getBookCount() const noexcept {
    return books.size();
}

bool BookCollection::containsBook(std::shared_ptr<Book> book) const {
    return std::find(books.begin(), books.end(), book) != books.end();
}

bool BookCollection::isEmpty() const noexcept {
    return books.empty();
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
           category == other.category &&
           books == other.books; 
}

bool BookCollection::operator!=(const BookCollection& other) const noexcept {
    return !(*this == other);
}