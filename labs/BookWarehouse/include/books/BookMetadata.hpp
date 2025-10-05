/**
 * @file BookMetadata.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookMetadata class for working with book metadata
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class BookMetadata
 * @brief Class for working with book metadata
 * 
 * Stores book metadata information including publication year, language,
 * edition, and description. Provides edition formatting and validation.
 */
class BookMetadata {
private:
    int publicationYear;   ///< Year of publication
    std::string language;  ///< Language of the book
    int edition;           ///< Edition number
    std::string description; ///< Book description

    /**
     * @brief Private method to validate publication year
     * 
     * @param year integer value containing publication year to validate
     * 
     * @return true if year is valid
     * @return false if year is invalid
     */
    bool isValidYear(int year) const;

    /**
     * @brief Private method to validate edition number
     * 
     * @param edition integer value containing edition number to validate
     * 
     * @return true if edition is valid
     * @return false if edition is invalid
     */
    bool isValidEdition(int edition) const;

    /**
     * @brief Private method to validate description
     * 
     * @param desc constant reference to the string containing description to validate
     * 
     * @return true if description is valid
     * @return false if description is invalid
     */
    bool isValidDescription(const std::string& desc) const;

public:
    /**
     * @brief Construct a new BookMetadata object
     * 
     * @param publicationYear integer value containing publication year
     * @param language constant reference to the string containing language
     * @param edition integer value containing edition number
     * @param description constant reference to the string containing description
     */
    BookMetadata(int publicationYear, const std::string& language, 
                 int edition = 1, const std::string& description = "");

    /**
     * @brief Get the publication year
     * 
     * @return int containing publication year
     */
    int getPublicationYear() const noexcept;

    /**
     * @brief Get the language
     * 
     * @return std::string containing language
     */
    std::string getLanguage() const noexcept;

    /**
     * @brief Get the edition number
     * 
     * @return int containing edition number
     */
    int getEdition() const noexcept;

    /**
     * @brief Get the description
     * 
     * @return std::string containing description
     */
    std::string getDescription() const noexcept;

    /**
     * @brief Equality comparison operator for book metadata
     * 
     * @param other constant reference to the book metadata to compare with
     * 
     * @return true if book metadata are equal
     * @return false if book metadata are not equal
     */
    bool operator==(const BookMetadata& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book metadata
     * 
     * @param other constant reference to the book metadata to compare with
     * 
     * @return true if book metadata are not equal
     * @return false if book metadata are equal
     */
    bool operator!=(const BookMetadata& other) const noexcept;

    /**
     * @brief Check if book is first edition
     * 
     * @return true if book is first edition
     * @return false if book is not first edition
     */
    bool isFirstEdition() const noexcept;

    /**
     * @brief Get edition as formatted string
     * 
     * @return std::string containing formatted edition string
     */
    std::string getEditionString() const noexcept;
};