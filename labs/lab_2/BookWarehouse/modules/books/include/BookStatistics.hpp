/**
 * @file BookStatistics.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookStatistics class for working with book statistics
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class BookStatistics
 * @brief Class for working with book statistics
 * 
 * Stores and manages statistical data for books including views, sales,
 * ratings, and reviews. Provides calculations for popularity and bestseller status.
 */
class BookStatistics {
private:
    int viewCount;          ///< Number of book views
    int salesCount;         ///< Number of book sales
    double averageRating;   ///< Average rating (0.0-5.0)
    int reviewCount;        ///< Number of reviews
    std::string lastSaleDate; ///< Date of last sale
    
    /**
     * @brief Private method to validate view count
     * 
     * @param views integer value containing view count to validate
     * 
     * @return true if view count is valid
     * @return false if view count is invalid
     */
    bool isValidViewCount(int views) const;

    /**
     * @brief Private method to validate sales count
     * 
     * @param sales integer value containing sales count to validate
     * 
     * @return true if sales count is valid
     * @return false if sales count is invalid
     */
    bool isValidSalesCount(int sales) const;

    /**
     * @brief Private method to validate rating value
     * 
     * @param rating double value containing rating to validate
     * 
     * @return true if rating is valid
     * @return false if rating is invalid
     */
    bool isValidRating(double rating) const;

    /**
     * @brief Private method to validate review count
     * 
     * @param reviews integer value containing review count to validate
     * 
     * @return true if review count is valid
     * @return false if review count is invalid
     */
    bool isValidReviewCount(int reviews) const;

public:
    /**
     * @brief Remove rating and update statistics
     * 
     * @param rating double value containing rating to remove
     */
    void removeRating(double rating);

    /**
     * @brief Construct a new BookStatistics object
     * 
     * @param viewCount integer value containing initial view count
     * @param salesCount integer value containing initial sales count
     * @param averageRating double value containing initial average rating
     * @param reviewCount integer value containing initial review count
     * @param lastSaleDate constant reference to the string containing last sale date
     */
    BookStatistics(int viewCount = 0, int salesCount = 0, 
                   double averageRating = 0.0, int reviewCount = 0,
                   const std::string& lastSaleDate = "");

    /**
     * @brief Get the view count
     * 
     * @return int containing view count
     */
    int getViewCount() const noexcept;

    /**
     * @brief Get the sales count
     * 
     * @return int containing sales count
     */
    int getSalesCount() const noexcept;

    /**
     * @brief Get the average rating
     * 
     * @return double containing average rating
     */
    double getAverageRating() const noexcept;

    /**
     * @brief Get the review count
     * 
     * @return int containing review count
     */
    int getReviewCount() const noexcept;

    /**
     * @brief Get the last sale date
     * 
     * @return std::string containing last sale date
     */
    std::string getLastSaleDate() const noexcept;

    /**
     * @brief Set the view count
     * 
     * @param views integer value containing new view count
     */
    void setViewCount(int views);

    /**
     * @brief Set the sales count
     * 
     * @param sales integer value containing new sales count
     */
    void setSalesCount(int sales);

    /**
     * @brief Set the average rating
     * 
     * @param rating double value containing new average rating
     */
    void setAverageRating(double rating);

    /**
     * @brief Set the review count
     * 
     * @param reviews integer value containing new review count
     */
    void setReviewCount(int reviews);

    /**
     * @brief Set the last sale date
     * 
     * @param date constant reference to the string containing new last sale date
     */
    void setLastSaleDate(const std::string& date);

    /**
     * @brief Increment view count
     * 
     * @param amount integer value containing amount to increment (default 1)
     */
    void incrementViews(int amount = 1);

    /**
     * @brief Increment sales count
     * 
     * @param amount integer value containing amount to increment (default 1)
     */
    void incrementSales(int amount = 1);

    /**
     * @brief Increment review count
     * 
     * @param amount integer value containing amount to increment (default 1)
     */
    void incrementReviews(int amount = 1);

    /**
     * @brief Update average rating with new review
     * 
     * @param newRating double value containing new review rating
     */
    void updateRating(double newRating);

    /**
     * @brief Calculate popularity score
     * 
     * @return double containing calculated popularity score
     */
    double getPopularityScore() const noexcept;

    /**
     * @brief Check if book is bestseller
     * 
     * @return true if book is bestseller
     * @return false if book is not bestseller
     */
    bool isBestseller() const noexcept;

    /**
     * @brief Check if book is highly rated
     * 
     * @return true if book is highly rated
     * @return false if book is not highly rated
     */
    bool isHighlyRated() const noexcept;

    /**
     * @brief Equality comparison operator for book statistics
     * 
     * @param other constant reference to the book statistics to compare with
     * 
     * @return true if book statistics are equal
     * @return false if book statistics are not equal
     */
    bool operator==(const BookStatistics& other) const noexcept;

    /**
     * @brief Inequality comparison operator for book statistics
     * 
     * @param other constant reference to the book statistics to compare with
     * 
     * @return true if book statistics are not equal
     * @return false if book statistics are equal
     */
    bool operator!=(const BookStatistics& other) const noexcept;

    /**
     * @brief Get statistics summary
     * 
     * @return std::string containing formatted statistics summary
     */
    std::string getSummary() const noexcept;
};