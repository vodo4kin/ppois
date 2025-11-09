/**
 * @file Book.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Book class for working with books
 * @version 0.1
 * @date 2025-10-01
 * 
 * 
 */

#pragma once
#include "ISBN.hpp"
#include "BookTitle.hpp"
#include "Genre.hpp"
#include "Publisher.hpp"
#include "PhysicalProperties.hpp"
#include "BookMetadata.hpp"
#include "BookSeries.hpp"
#include "BookCondition.hpp"
#include "BookReview.hpp"
#include "BookStatistics.hpp"
#include <vector>
#include <memory>

/**
 * @class Book
 * @brief Main class for working with books
 * 
 * Represents a book with comprehensive information including identification,
 * physical properties, metadata, reviews, and statistics. Provides business
 * logic for stock management, pricing, and book analysis.
 */
class Book {
private:
    ISBN isbn;                                      ///< International Standard Book Number
    BookTitle title;                                ///< Book title information
    BookMetadata metadata;                          ///< Book metadata
    PhysicalProperties physicalProps;               ///< Physical properties
    Genre genre;                                    ///< Book genre
    std::shared_ptr<Publisher> publisher;           ///< Publisher information
    BookCondition condition;                        ///< Physical condition
    std::shared_ptr<BookSeries> series;             ///< Book series information
    std::vector<std::shared_ptr<BookReview>> reviews; ///< Collection of reviews
    BookStatistics statistics;                      ///< Statistical data
    double price;                                   ///< Current price

    /**
     * @brief Private method to get current date
     * 
     * @return std::string containing current date in YYYY-MM-DD format
     */
    std::string getCurrentDate();

public:
    /**
     * @brief Construct a new Book object
     * 
     * @param isbn constant reference to the ISBN object
     * @param title constant reference to the BookTitle object
     * @param metadata constant reference to the BookMetadata object
     * @param physicalProps constant reference to the PhysicalProperties object
     * @param genre constant reference to the Genre object
     * @param publisher shared pointer to the Publisher object
     * @param condition constant reference to the BookCondition object
     * @param price double value containing book price
     * @param stockQuantity integer value containing stock quantity
     * @param series shared pointer to the BookSeries object
     */
    Book(const ISBN& isbn, const BookTitle& title, const BookMetadata& metadata,
         const PhysicalProperties& physicalProps, const Genre& genre,
         std::shared_ptr<Publisher> publisher, const BookCondition& condition,
         double price, std::shared_ptr<BookSeries> series = nullptr);

    /**
     * @brief Construct a new Book object (min num of param)
     * 
     * @param isbn constant reference to the ISBN object
     * @param title constant reference to the BookTitle object
     */
    Book(const ISBN& isbn, const BookTitle& title);

    /**
     * @brief Get the ISBN
     * 
     * @return ISBN containing book ISBN
     */
    ISBN getISBN() const noexcept;

    /**
     * @brief Get the string withISBN
     * 
     * @return std::string with ISDN of book
     */
    std::string getISBNstring() const noexcept;

    /**
     * @brief Get the title information
     * 
     * @return BookTitle containing book title
     */
    BookTitle getTitle() const noexcept;

    /**
     * @brief Get the metadata
     * 
     * @return BookMetadata containing book metadata
     */
    BookMetadata getMetadata() const noexcept;

    /**
     * @brief Get the physical properties
     * 
     * @return PhysicalProperties containing physical properties
     */
    PhysicalProperties getPhysicalProperties() const noexcept;

    /**
     * @brief Get the genre
     * 
     * @return Genre containing book genre
     */
    Genre getGenre() const noexcept;

    /**
     * @brief Get the publisher
     * 
     * @return std::shared_ptr<Publisher> containing publisher information
     */
    std::shared_ptr<Publisher> getPublisher() const noexcept;

    /**
     * @brief Get the condition
     * 
     * @return BookCondition containing book condition
     */
    BookCondition getCondition() const noexcept;

    /**
     * @brief Get the series information
     * 
     * @return std::shared_ptr<BookSeries> containing series information
     */
    std::shared_ptr<BookSeries> getSeries() const noexcept;

    /**
     * @brief Get the price
     * 
     * @return double containing book price
     */
    double getPrice() const noexcept;

    /**
     * @brief Get the statistics
     * 
     * @return BookStatistics containing book statistics
     */
    BookStatistics getStatistics() const noexcept;

    /**
     * @brief Set the price
     * 
     * @param newPrice double value containing new price
     */
    void setPrice(double newPrice);

    /**
     * @brief Set the series information
     * 
     * @param newSeries shared pointer to the BookSeries object
     */
    void setSeries(std::shared_ptr<BookSeries> newSeries);

    /**
     * @brief Set the condition
     * 
     * @param newCondition BookCondition value containing new condition
     */
    void setCondition(BookCondition newCondition);

    /**
     * @brief Add review to book
     * 
     * @param review shared pointer to the BookReview object to add
     */
    void addReview(std::shared_ptr<BookReview> review);

    /**
     * @brief Remove review from book
     * 
     * @param review shared pointer to the BookReview object to remove
     */
    void removeReview(std::shared_ptr<BookReview> review);

    /**
     * @brief Get all reviews
     * 
     * @return std::vector<std::shared_ptr<BookReview>> containing all reviews
     */
    std::vector<std::shared_ptr<BookReview>> getReviews() const noexcept;

    /**
     * @brief Get review count
     * 
     * @return size_t containing number of reviews
     */
    size_t getReviewCount() const noexcept;

    /**
     * @brief Get average rating
     * 
     * @return double containing average rating
     */
    double getAverageRating() const noexcept;

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
     * @brief Apply discount to price
     * 
     * @param percent double value containing discount percentage
     */
    void applyDiscount(double percent);

    /**
     * @brief Get full book information
     * 
     * @return std::string containing detailed book information
     */
    std::string getFullInfo() const noexcept;

    /**
     * @brief Get short book information
     * 
     * @return std::string containing brief book information
     */
    std::string getShortInfo() const noexcept;

    /**
     * @brief Equality comparison operator for books
     * 
     * @param other constant reference to the book to compare with
     * 
     * @return true if books are equal
     * @return false if books are not equal
     */
    bool operator==(const Book& other) const noexcept;

    /**
     * @brief Inequality comparison operator for books
     * 
     * @param other constant reference to the book to compare with
     * 
     * @return true if books are not equal
     * @return false if books are equal
     */
    bool operator!=(const Book& other) const noexcept;
};