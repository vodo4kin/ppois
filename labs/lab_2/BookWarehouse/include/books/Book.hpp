#pragma once
#include "books/ISBN.hpp"
#include "books/BookTitle.hpp"
#include "books/Genre.hpp"
#include "books/Publisher.hpp"
#include "books/PhysicalProperties.hpp"
#include "books/BookMetadata.hpp"
#include "books/BookSeries.hpp"
#include "books/BookCondition.hpp"
#include "books/BookReview.hpp"
#include "books/BookStatistics.hpp"
#include <vector>
#include <memory>

class Book {
private:
    ISBN isbn;
    BookTitle title;
    BookMetadata metadata;
    PhysicalProperties physicalProps;
    Genre genre;
    std::shared_ptr<Publisher> publisher;      // ассоциация (многие книги - один издатель)
    BookCondition condition;
    std::shared_ptr<BookSeries> series;        // (многие книги - одна серия)
    std::vector<std::shared_ptr<BookReview>> reviews; // ассоциация (одна книга - много рецензий)
    BookStatistics statistics;
    double price;
    int stockQuantity;                         // количество на складе
    std::string getCurrentDate();
public:
    Book(const ISBN& isbn, const BookTitle& title, const BookMetadata& metadata,
         const PhysicalProperties& physicalProps, const Genre& genre,
         std::shared_ptr<Publisher> publisher, const BookCondition& condition,
         double price, int stockQuantity = 0,
         std::shared_ptr<BookSeries> series = nullptr);
    // геттеры
    ISBN getISBN() const noexcept;
    BookTitle getTitle() const noexcept;
    BookMetadata getMetadata() const noexcept;
    PhysicalProperties getPhysicalProperties() const noexcept;
    Genre getGenre() const noexcept;
    std::shared_ptr<Publisher> getPublisher() const noexcept;
    BookCondition getCondition() const noexcept;
    std::shared_ptr<BookSeries> getSeries() const noexcept;
    double getPrice() const noexcept;
    int getStockQuantity() const noexcept;
    BookStatistics getStatistics() const noexcept;
    // сеттеры
    void setPrice(double newPrice);
    void setStockQuantity(int quantity);
    void setSeries(std::shared_ptr<BookSeries> newSeries);
    void setCondition(BookCondition newCondition);
    // работа с рецензиями
    void addReview(std::shared_ptr<BookReview> review);
    void removeReview(std::shared_ptr<BookReview> review);
    std::vector<std::shared_ptr<BookReview>> getReviews() const noexcept;
    size_t getReviewCount() const noexcept;
    double getAverageRating() const noexcept; // из статистики
    // бизнес-логика
    bool isInStock() const noexcept;
    bool isBestseller() const noexcept;
    bool isHighlyRated() const noexcept;
    void applyDiscount(double percent);
    void updateStock(int delta); // + для пополнения, - для продажи
    // информация
    std::string getFullInfo() const noexcept;
    std::string getShortInfo() const noexcept;
    // операторы сравнения
    bool operator==(const Book& other) const noexcept;
    bool operator!=(const Book& other) const noexcept;
};