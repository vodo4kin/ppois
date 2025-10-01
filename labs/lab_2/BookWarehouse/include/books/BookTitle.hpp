/**
 * @file BookTitle.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookTitle class for working with book titles
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class BookTitle
 * @brief Class for working with book titles
 * 
 * Stores book title information including main title, subtitle,
 * and language. Provides validation and full title formatting.
 */
class BookTitle{
    private:
    std::string title;     ///< Main title of the book
    std::string subtitle;  ///< Subtitle of the book (optional)
    std::string language;  ///< Language of the book

    /**
     * @brief Private method to validate title
     * 
     * @param title constant reference to the string containing title to validate
     * 
     * @return true if title is valid
     * @return false if title is invalid
     */
    bool isValidTitle(const std::string& title) const;

    public:
    /**
     * @brief Construct a new BookTitle object
     * 
     * @param title constant reference to the string containing main title
     * @param subtitle constant reference to the string containing subtitle
     * @param language constant reference to the string containing language
     */
    explicit BookTitle(const std::string& title, const std::string& subtitle, const std::string& language);

    /**
     * @brief Get the main title
     * 
     * @return std::string containing main title
     */
    std::string getTitle() const noexcept;

    /**
     * @brief Get the subtitle
     * 
     * @return std::string containing subtitle
     */
    std::string getSubtitle() const noexcept;

    /**
     * @brief Get the language
     * 
     * @return std::string containing language
     */
    std::string getLanguage() const noexcept;

    /**
     * @brief Get the full formatted title
     * 
     * @return std::string containing full title with subtitle and language
     */
    std::string getFullTitle() const noexcept;

    /**
     * @brief Equality comparison operator for book titles
     * 
     * @param other constant reference to the book title to compare with
     * 
     * @return true if book titles are equal
     * @return false if book titles are not equal
     */
    bool operator==(const BookTitle& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book titles
     * 
     * @param other constant reference to the book title to compare with
     * 
     * @return true if book titles are not equal
     * @return false if book titles are equal
     */
    bool operator!=(const BookTitle& other) const noexcept;
};