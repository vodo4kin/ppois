#include "books/BookReview.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include <cctype>

bool BookReview::isValidAuthor(const std::string& author) const {
    if (author.empty() || author.length() > MAX_AUTHOR_LENGTH) {
        return false;
    }
    bool hasNonSpace = false;
    for (char c : author) {
        if (c == '\t' || c == '\n' || c == '\r') return false;
        if (c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
}

bool BookReview::isValidTitle(const std::string& title) const {
    if (title.empty() || title.length() > MAX_TITLE_LENGTH) {
        return false;
    }
    bool hasNonSpace = false;
    for (char c : title) {
        if (c == '\t' || c == '\n' || c == '\r') return false;
        if (c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
}

bool BookReview::isValidText(const std::string& text) const {
    if (text.empty() || text.length() > MAX_TEXT_LENGTH) {
        return false;
    }
    bool hasNonSpace = false;
    for (char c : text) {
        if (c == '\t' || c == '\n' || c == '\r') return false;
        if (c != ' ') hasNonSpace = true;
    }
    return hasNonSpace;
}

bool BookReview::isValidRating(int rating) const {
    return rating >= MIN_RATING && rating <= MAX_RATING;
}

bool BookReview::isValidDate(const std::string& date) const {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }
    return true;
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
    if (!isValidDate(date)) {
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
    for (int i = 1; i <= MAX_RATING; i++) {
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