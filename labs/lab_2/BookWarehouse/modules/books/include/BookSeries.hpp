/**
 * @file BookSeries.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookSeries class for working with book series
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class BookSeries
 * @brief Class for working with book series
 * 
 * Stores information about book series including name, description,
 * book count, and publication years. Provides status checks for
 * completed or ongoing series.
 */
class BookSeries {
private:
    std::string name;        ///< Name of the book series
    std::string description; ///< Description of the book series
    int bookCount;           ///< Number of books in the series
    int startYear;           ///< Year when series started
    int endYear;             ///< Year when series ended (0 if ongoing)

    /**
     * @brief Private method to validate series name
     * 
     * @param name constant reference to the string containing series name to validate
     * 
     * @return true if name is valid
     * @return false if name is invalid
     */
    bool isValidName(const std::string& name) const;

    /**
     * @brief Private method to validate series description
     * 
     * @param desc constant reference to the string containing description to validate
     * 
     * @return true if description is valid
     * @return false if description is invalid
     */
    bool isValidDescription(const std::string& desc) const;

    /**
     * @brief Private method to validate year value
     * 
     * @param year integer value containing year to validate
     * 
     * @return true if year is valid
     * @return false if year is invalid
     */
    bool isValidYear(int year) const;

    /**
     * @brief Private method to validate book count
     * 
     * @param count integer value containing book count to validate
     * 
     * @return true if book count is valid
     * @return false if book count is invalid
     */
    bool isValidBookCount(int count) const;

public:
    /**
     * @brief Construct a new BookSeries object
     * 
     * @param name constant reference to the string containing series name
     * @param description constant reference to the string containing series description
     * @param bookCount integer value containing number of books in series
     * @param startYear integer value containing series start year
     * @param endYear integer value containing series end year
     */
    BookSeries(const std::string& name, const std::string& description = "",
               int bookCount = 0, int startYear = 0, int endYear = 0);
    
    /**
     * @brief Get the series name
     * 
     * @return std::string containing series name
     */
    std::string getName() const noexcept;

    /**
     * @brief Get the series description
     * 
     * @return std::string containing series description
     */
    std::string getDescription() const noexcept;

    /**
     * @brief Get the book count
     * 
     * @return int containing number of books in series
     */
    int getBookCount() const noexcept;

    /**
     * @brief Get the start year
     * 
     * @return int containing series start year
     */
    int getStartYear() const noexcept;

    /**
     * @brief Get the end year
     * 
     * @return int containing series end year
     */
    int getEndYear() const noexcept;

    /**
     * @brief Check if series is completed
     * 
     * @return true if series is completed
     * @return false if series is ongoing
     */
    bool isCompleted() const noexcept;

    /**
     * @brief Check if series is ongoing
     * 
     * @return true if series is ongoing
     * @return false if series is completed
     */
    bool isOngoing() const noexcept;

    /**
     * @brief Equality comparison operator for book series
     * 
     * @param other constant reference to the book series to compare with
     * 
     * @return true if book series are equal
     * @return false if book series are not equal
     */
    bool operator==(const BookSeries& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book series
     * 
     * @param other constant reference to the book series to compare with
     * 
     * @return true if book series are not equal
     * @return false if book series are equal
     */
    bool operator!=(const BookSeries& other) const noexcept;

    /**
     * @brief Get formatted series information
     * 
     * @return std::string containing formatted series information
     */
    std::string getInfo() const noexcept;
};