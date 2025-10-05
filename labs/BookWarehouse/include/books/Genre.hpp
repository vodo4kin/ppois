/**
 * @file Genre.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Genre class for working with book genres
 * @version 0.1
 * @date 2025-01-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class Genre
 * @brief Class for working with book genres
 * 
 * Represents book genres with enumeration of common types.
 * Provides conversion to string representation and comparison operations.
 */
class Genre{
    public:
    /**
     * @enum Type
     * @brief Enumeration of book genre types
     */
    enum class Type{
        MYSTERY,            ///< Mystery genre
        THRILLER,           ///< Thriller genre  
        FANTASY,            ///< Fantasy genre
        SCIENCE_FICTION,    ///< Science fiction genre
        ROMANCE,            ///< Romance genre
        HISTORICAL_FICTION, ///< Historical fiction genre
        HORROR,             ///< Horror genre
        FOR_CHILDREN,       ///< Children's literature genre
        AUTOBIOGRAPHY,      ///< Autobiography genre
        DRAMA,              ///< Drama genre
        POETRY,             ///< Poetry genre
        OTHER               ///< Other genre category
    };

    private:
    Type genre;   ///< Current genre type

    public:
    /**
     * @brief Construct a new Genre object
     * 
     * @param genre Type value containing genre type
     */
    explicit Genre(Type genre) noexcept;

    /**
     * @brief Convert genre to string representation
     * 
     * @return std::string containing genre description
     */
    std::string toString() const noexcept;

    /**
     * @brief Get the genre type
     * 
     * @return Type containing current genre type
     */
    Type getGenre() const noexcept;

    /**
     * @brief Equality comparison operator for genres
     * 
     * @param other constant reference to the genre to compare with
     * 
     * @return true if genres are equal
     * @return false if genres are not equal
     */
    bool operator==(const Genre& other) const noexcept;

    /**
     * @brief Inequality comparison operator for genres
     * 
     * @param other constant reference to the genre to compare with
     * 
     * @return true if genres are not equal
     * @return false if genres are equal
     */
    bool operator!=(const Genre& other) const noexcept;
};