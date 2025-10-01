#pragma once
#include <string>

class BookReview {
private:
    static constexpr int MIN_RATING = 1;
    static constexpr int MAX_RATING = 5;
    static constexpr size_t MAX_TEXT_LENGTH = 2000;
    static constexpr size_t MAX_AUTHOR_LENGTH = 100;
    static constexpr size_t MAX_TITLE_LENGTH = 200;
    std::string author;
    std::string title;
    std::string text;
    int rating;
    std::string date;
    bool isValidAuthor(const std::string& author) const;
    bool isValidTitle(const std::string& title) const;
    bool isValidText(const std::string& text) const;
    bool isValidRating(int rating) const;
public:
    BookReview(const std::string& author, const std::string& title, 
               const std::string& text, int rating, const std::string& date);
    std::string getAuthor() const noexcept;
    std::string getTitle() const noexcept;
    std::string getText() const noexcept;
    int getRating() const noexcept;
    std::string getDate() const noexcept;
    std::string getRatingStars() const noexcept; // "★★★★☆"
    bool isPositiveReview() const noexcept;      // rating >= 4
    bool isCriticalReview() const noexcept;      // rating <= 2
    bool operator==(const BookReview& other) const noexcept;
    bool operator!=(const BookReview& other) const noexcept;
    std::string getSummary() const noexcept;
};