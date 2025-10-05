/**
 * @file BookReview.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookReview class for working with book reviews
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class BookReview
 * @brief Class for working with book reviews
 * 
 * Stores book review information including author, title, text,
 * rating, and date. Provides rating analysis and summary generation.
 */
class BookReview {
private:
    std::string author;   ///< Author of the review
    std::string title;    ///< Title of the review
    std::string text;     ///< Text content of the review
    int rating;           ///< Rating value (1-5)
    std::string date;     ///< Date when review was written

    /**
     * @brief Private method to validate review author
     * 
     * @param author constant reference to the string containing author to validate
     * 
     * @return true if author is valid
     * @return false if author is invalid
     */
    bool isValidAuthor(const std::string& author) const;

    /**
     * @brief Private method to validate review title
     * 
     * @param title constant reference to the string containing title to validate
     * 
     * @return true if title is valid
     * @return false if title is invalid
     */
    bool isValidTitle(const std::string& title) const;

    /**
     * @brief Private method to validate review text
     * 
     * @param text constant reference to the string containing text to validate
     * 
     * @return true if text is valid
     * @return false if text is invalid
     */
    bool isValidText(const std::string& text) const;

    /**
     * @brief Private method to validate rating value
     * 
     * @param rating integer value containing rating to validate
     * 
     * @return true if rating is valid
     * @return false if rating is invalid
     */
    bool isValidRating(int rating) const;

public:
    /**
     * @brief Construct a new BookReview object
     * 
     * @param author constant reference to the string containing review author
     * @param title constant reference to the string containing review title
     * @param text constant reference to the string containing review text
     * @param rating integer value containing review rating
     * @param date constant reference to the string containing review date
     */
    BookReview(const std::string& author, const std::string& title, 
               const std::string& text, int rating, const std::string& date);

    /**
     * @brief Get the review author
     * 
     * @return std::string containing review author
     */
    std::string getAuthor() const noexcept;

    /**
     * @brief Get the review title
     * 
     * @return std::string containing review title
     */
    std::string getTitle() const noexcept;

    /**
     * @brief Get the review text
     * 
     * @return std::string containing review text
     */
    std::string getText() const noexcept;

    /**
     * @brief Get the review rating
     * 
     * @return int containing review rating
     */
    int getRating() const noexcept;

    /**
     * @brief Get the review date
     * 
     * @return std::string containing review date
     */
    std::string getDate() const noexcept;

    /**
     * @brief Get rating as star symbols
     * 
     * @return std::string containing star rating representation
     */
    std::string getRatingStars() const noexcept;

    /**
     * @brief Check if review is positive
     * 
     * @return true if review is positive (rating >= 4)
     * @return false if review is not positive
     */
    bool isPositiveReview() const noexcept;

    /**
     * @brief Check if review is critical
     * 
     * @return true if review is critical (rating <= 2)
     * @return false if review is not critical
     */
    bool isCriticalReview() const noexcept;

    /**
     * @brief Equality comparison operator for book reviews
     * 
     * @param other constant reference to the book review to compare with
     * 
     * @return true if book reviews are equal
     * @return false if book reviews are not equal
     */
    bool operator==(const BookReview& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book reviews
     * 
     * @param other constant reference to the book review to compare with
     * 
     * @return true if book reviews are not equal
     * @return false if book reviews are equal
     */
    bool operator!=(const BookReview& other) const noexcept;

    /**
     * @brief Get review summary
     * 
     * @return std::string containing formatted review summary
     */
    std::string getSummary() const noexcept;
};