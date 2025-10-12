#include "books/BookReview.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"
#include "config/BookConfig.hpp"

bool BookReview::isValidAuthor(const std::string& author) const {
    return StringValidation::isValidName(author, BookConfig::BookReview::MAX_AUTHOR_LENGTH);
}

bool BookReview::isValidTitle(const std::string& title) const {
    return StringValidation::isValidName(title, BookConfig::BookReview::MAX_TITLE_LENGTH);
}

bool BookReview::isValidText(const std::string& text) const {
    return StringValidation::isValidName(text, BookConfig::BookReview::MAX_TEXT_LENGTH);
}

bool BookReview::isValidRating(int rating) const {
    return rating >= BookConfig::BookReview::MIN_RATING && rating <= BookConfig::BookReview::MAX_RATING;
}

BookReview::BookReview(const std::string& author, const std::string& title, 
               const std::string& text, int rating, const std::string& date) {
    if (!isValidAuthor(author)) {
        throw DataValidationException("Invalid author: '" + author + "'");
    }
    if (!isValidTitle(title)) {
        throw DataValidationException("Invalid title: '" + title + "'");
    }
    if (!isValidText(text)) {
        throw DataValidationException("Review text must contain smth except spaces");
    }
    if (!isValidRating(rating)) {
        throw DataValidationException("Invalid rating: " + std::to_string(rating));
    }
    if (!StringValidation::isValidDate(date)) {
        throw DataValidationException("Invalid date format: '" + date + "' (expected YYYY-MM-DD)");
    }
    this->author = author;
    this->title = title;
    this->text = text;
    this->rating = rating;
    this->date = date;
}

std::string BookReview::getAuthor() const noexcept {
    return author;
}

std::string BookReview::getTitle() const noexcept {
    return title;
}

std::string BookReview::getText() const noexcept {
    return text;
}

int BookReview::getRating() const noexcept {
    return rating;
}

std::string BookReview::getDate() const noexcept {
    return date;
}

std::string BookReview::getRatingStars() const noexcept {
    std::string stars;
    for (int i = 1; i <= BookConfig::BookReview::MAX_RATING; i++) {
        stars += (i <= rating) ? "★" : "☆";
    }
    return stars;
}

bool BookReview::isPositiveReview() const noexcept {
    return rating >= 4;
}

bool BookReview::isCriticalReview() const noexcept {
    return rating <= 2;
}

bool BookReview::operator==(const BookReview& other) const noexcept {
    return author == other.author &&
           title == other.title &&
           text == other.text &&
           rating == other.rating &&
           date == other.date;
}

bool BookReview::operator!=(const BookReview& other) const noexcept {
    return !(*this == other);
}

std::string BookReview::getSummary() const noexcept {
    return "\"" + title + "\" by " + author + " - " + getRatingStars() + " (" + date + ")";
}