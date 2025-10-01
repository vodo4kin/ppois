#include "books/Book.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>

std::string Book::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
}

Book::Book(const ISBN& isbn, const BookTitle& title, const BookMetadata& metadata,
         const PhysicalProperties& physicalProps, const Genre& genre,
         std::shared_ptr<Publisher> publisher, const BookCondition& condition,
         double price, int stockQuantity, std::shared_ptr<BookSeries> series)
    : isbn(isbn), title(title), metadata(metadata), physicalProps(physicalProps),
      genre(genre), publisher(publisher), condition(condition), series(series),
      price(price), stockQuantity(stockQuantity),
      statistics(0, 0, 0.0, 0, "2024-01-01")
{
    if (price < 0) {
        throw DataValidationException("Price cannot be negative: " + std::to_string(price));
    }
    if (stockQuantity < 0) {
        throw DataValidationException("Stock quantity cannot be negative: " + std::to_string(stockQuantity));
    }
    if (!publisher) {
        throw DataValidationException("Publisher cannot be null");
    }
}

ISBN Book::getISBN() const noexcept {
    return isbn;
}

BookTitle Book::getTitle() const noexcept {
    return title;
}

BookMetadata Book::getMetadata() const noexcept {
    return metadata;
}

PhysicalProperties Book::getPhysicalProperties() const noexcept {
    return physicalProps;
}

Genre Book::getGenre() const noexcept {
    return genre;
}

std::shared_ptr<Publisher> Book::getPublisher() const noexcept {
    return publisher;
}

BookCondition Book::getCondition() const noexcept {
    return condition;
}

std::shared_ptr<BookSeries> Book::getSeries() const noexcept {
    return series;
}

double Book::getPrice() const noexcept {
    return price;
}

int Book::getStockQuantity() const noexcept {
    return stockQuantity;
}

BookStatistics Book::getStatistics() const noexcept {
    return statistics;
}

void Book::setPrice(double newPrice) {
    if (newPrice < 0) {
        throw DataValidationException("Price cannot be negative: " + std::to_string(newPrice));
    }
    price = newPrice;
}

void Book::setStockQuantity(int quantity) {
    if (quantity < 0) {
        throw DataValidationException("Stock quantity cannot be negative: " + std::to_string(quantity));
    }
    stockQuantity = quantity;
}

void Book::setSeries(std::shared_ptr<BookSeries> newSeries) {
    series = newSeries;
}

void Book::setCondition(BookCondition newCondition) {
    condition = newCondition;
}

void Book::addReview(std::shared_ptr<BookReview> review) {
    if (!review) {
        throw DataValidationException("Review cannot be null");
    }
    reviews.push_back(review);
    statistics.updateRating(review->getRating());
}

void Book::removeReview(std::shared_ptr<BookReview> review) {
    if (!review) return;
    auto it = std::find(reviews.begin(), reviews.end(), review);
    if (it != reviews.end()) {
        reviews.erase(it);
        if (reviews.empty()) {
            statistics.setAverageRating(0.0);
            statistics.setReviewCount(0);
        } else {
            double totalRating = 0.0;
            for (const auto& rev : reviews) {
                totalRating += rev->getRating();
            }
            statistics.setAverageRating(totalRating / reviews.size());
            statistics.setReviewCount(reviews.size());
        }
    }
}

std::vector<std::shared_ptr<BookReview>> Book::getReviews() const noexcept {
    return reviews;
}

size_t Book::getReviewCount() const noexcept {
    return reviews.size();
}

double Book::getAverageRating() const noexcept {
    return statistics.getAverageRating();
}

bool Book::isInStock() const noexcept {
    return stockQuantity > 0;
}

bool Book::isBestseller() const noexcept {
    return statistics.isBestseller();
}

bool Book::isHighlyRated() const noexcept {
    return statistics.isHighlyRated();
}

void Book::applyDiscount(double percent) {
    if (percent < 0 || percent > 100) {
        throw DataValidationException("Discount must be between 0 and 100: " + std::to_string(percent));
    }
    price = price * (100 - percent) / 100;
}

void Book::updateStock(int delta) {
    int newQuantity = stockQuantity + delta;
    if (newQuantity < 0) {
        throw InsufficientStockException(
            "Cannot reduce stock by " + std::to_string(-delta) + 
            ". Current stock: " + std::to_string(stockQuantity) +
            " for book: " + title.getFullTitle()
        );
    }
    stockQuantity = newQuantity;
    if (delta < 0) {
        statistics.incrementSales(-delta);
        statistics.setLastSaleDate(getCurrentDate());
    }
}

std::string Book::getFullInfo() const noexcept {
    std::string info = "Book: " + title.getFullTitle() + "\n";
    info += "ISBN: " + isbn.getFormattedCode() + "\n";
    info += "Genre: " + genre.toString() + "\n";
    info += "Publisher: " + publisher->getName() + "\n";
    info += "Condition: " + condition.toString() + "\n";
    info += "Price: $" + std::to_string(price) + "\n";
    info += "Stock: " + std::to_string(stockQuantity) + " units\n";
    info += "Rating: " + std::to_string(statistics.getAverageRating()) + "/5.0";
    if (series) {
        info += "\nSeries: " + series->getName();
    }
    return info;
}

std::string Book::getShortInfo() const noexcept {
    return title.getFullTitle() + " (" + isbn.getFormattedCode() + ") - $" + 
           std::to_string(price) + " [" + std::to_string(stockQuantity) + " in stock]";
}

bool Book::operator==(const Book& other) const noexcept {
    return isbn == other.isbn;
}

bool Book::operator!=(const Book& other) const noexcept {
    return !(*this == other);
}