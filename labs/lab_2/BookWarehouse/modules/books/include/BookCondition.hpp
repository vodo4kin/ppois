/**
 * @file BookCondition.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookCondition class for working with book conditions
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class BookCondition
 * @brief Class for working with book conditions
 * 
 * Represents physical condition of books with standardized condition levels.
 * Provides condition analysis and string conversion.
 */
class BookCondition {
public:
    /**
     * @enum Condition
     * @brief Enumeration of book condition levels
     */
    enum class Condition {
        NEW,        ///< New condition
        LIKE_NEW,   ///< Like new condition
        VERY_GOOD,  ///< Very good condition
        GOOD,       ///< Good condition
        FAIR,       ///< Fair condition
        POOR        ///< Poor condition
    };

private:
    Condition condition;   ///< Current book condition

public:
    /**
     * @brief Construct a new BookCondition object
     * 
     * @param condition Condition value containing book condition
     */
    explicit BookCondition(Condition condition) noexcept;

    /**
     * @brief Get the condition value
     * 
     * @return Condition containing current book condition
     */
    Condition getCondition() const noexcept;

    /**
     * @brief Convert condition to string representation
     * 
     * @return std::string containing condition description
     */
    std::string toString() const noexcept;

    /**
     * @brief Check if book is in new condition
     * 
     * @return true if book is new
     * @return false if book is used
     */
    bool isNew() const noexcept;

    /**
     * @brief Check if book is used
     * 
     * @return true if book is used
     * @return false if book is new
     */
    bool isUsed() const noexcept;

    /**
     * @brief Check if book needs replacement
     * 
     * @return true if book needs replacement
     * @return false if book does not need replacement
     */
    bool needsReplacement() const noexcept;

    /**
     * @brief Equality comparison operator for book conditions
     * 
     * @param other constant reference to the book condition to compare with
     * 
     * @return true if book conditions are equal
     * @return false if book conditions are not equal
     */
    bool operator==(const BookCondition& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book conditions
     * 
     * @param other constant reference to the book condition to compare with
     * 
     * @return true if book conditions are not equal
     * @return false if book conditions are equal
     */
    bool operator!=(const BookCondition& other) const noexcept;
};