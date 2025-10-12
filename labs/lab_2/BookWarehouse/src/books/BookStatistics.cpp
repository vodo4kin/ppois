#include "books/BookStatistics.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "utils/Utils.hpp"
#include "config/BookConfig.hpp"


bool BookStatistics::isValidViewCount(int views) const {
    return views >= 0 && views <= BookConfig::BookStatistics::MAX_VIEWS;
}

bool BookStatistics::isValidSalesCount(int sales) const {
    return sales >= 0 && sales <= BookConfig::BookStatistics::MAX_SALES;
}

bool BookStatistics::isValidRating(double rating) const {
    return rating >= 0.0 && rating <= 5.0;
}

bool BookStatistics::isValidReviewCount(int reviews) const {
    return reviews >= 0;
}

void BookStatistics::removeRating(double rating) {
    if (reviewCount <= 0) {
        setAverageRating(0.0);
        setReviewCount(0);
        return;
    }
    double totalRating = averageRating * reviewCount;
    totalRating -= rating;
    reviewCount--;
    if (reviewCount > 0) {
        averageRating = totalRating / reviewCount;
    } else {
        averageRating = 0.0;
    }
}

BookStatistics::BookStatistics(int viewCount, int salesCount, 
    double averageRating, int reviewCount,
    const std::string& lastSaleDate) {
        if (!isValidViewCount(viewCount)) {
            throw DataValidationException("Invalid view count: " + std::to_string(viewCount));
    }
    if (!isValidSalesCount(salesCount)) {
        throw DataValidationException("Invalid sales count: " + std::to_string(salesCount));
    }
    if (!isValidRating(averageRating)) {
        throw DataValidationException("Invalid rating: " + std::to_string(averageRating));
    }
    if (!isValidReviewCount(reviewCount)) {
        throw DataValidationException("Invalid review count: " + std::to_string(reviewCount));
    }
    if (!StringValidation::isValidDate(lastSaleDate)) {
        throw DataValidationException("Invalid date format: '" + lastSaleDate + "'");
    }
    this->viewCount = viewCount;
    this->salesCount = salesCount;
    this->averageRating = averageRating;
    this->reviewCount = reviewCount;
    this->lastSaleDate = lastSaleDate;
}

int BookStatistics::getViewCount() const noexcept {
    return viewCount;
}

int BookStatistics::getSalesCount() const noexcept {
    return salesCount;
}

double BookStatistics::getAverageRating() const noexcept {
    return averageRating;
}

int BookStatistics::getReviewCount() const noexcept {
    return reviewCount;
}

std::string BookStatistics::getLastSaleDate() const noexcept {
    return lastSaleDate;
}

void BookStatistics::setViewCount(int views) {
    if (!isValidViewCount(views)) {
        throw DataValidationException("Invalid view count: " + std::to_string(views));
    }
    viewCount = views;
}

void BookStatistics::setSalesCount(int sales) {
    if (!isValidSalesCount(sales)) {
        throw DataValidationException("Invalid sales count: " + std::to_string(sales));
    }
    salesCount = sales;
}

void BookStatistics::setAverageRating(double rating) {
    if (!isValidRating(rating)) {
        throw DataValidationException("Invalid rating: " + std::to_string(rating));
    }
    averageRating = rating;
}

void BookStatistics::setReviewCount(int reviews) {
    if (!isValidReviewCount(reviews)) {
        throw DataValidationException("Invalid review count: " + std::to_string(reviews));
    }
    reviewCount = reviews;
}

void BookStatistics::setLastSaleDate(const std::string& date) {
    if (!StringValidation::isValidDate(date)) {
        throw DataValidationException("Invalid date format: '" + lastSaleDate + "'");
    }
    lastSaleDate = date;
}

void BookStatistics::incrementViews(int amount) {
    if (amount < 0) {
        throw DataValidationException("Increment amount cannot be negative");
    }
    int newViews = viewCount + amount;
    if (!isValidViewCount(newViews)) {
        throw DataValidationException("View count would exceed maximum");
    }
    viewCount = newViews;
}

void BookStatistics::incrementSales(int amount) {
    if (amount < 0) {
        throw DataValidationException("Increment amount cannot be negative");
    }
    int newSales = salesCount + amount;
    if (!isValidSalesCount(newSales)) {
        throw DataValidationException("Sales count would exceed maximum");
    }
    salesCount = newSales;
}

void BookStatistics::incrementReviews(int amount) {
    if (amount < 0) {
        throw DataValidationException("Increment amount cannot be negative");
    }
    int newReviews = reviewCount + amount;
    if (!isValidReviewCount(newReviews)) {
        throw DataValidationException("Invalid review count");
    }
    reviewCount = newReviews;
}

void BookStatistics::updateRating(double newRating) {
    if (!isValidRating(newRating)) {
        throw DataValidationException("Invalid rating: " + std::to_string(newRating));
    }
    double totalRating = averageRating * reviewCount + newRating;
    reviewCount++;
    averageRating = totalRating / reviewCount;
}

double BookStatistics::getPopularityScore() const noexcept {
    // 40% продажи + 30% просмотры + 30% рейтинг
    double salesScore = static_cast<double>(salesCount) / BookConfig::BookStatistics::MAX_SALES * 100.0;
    double viewsScore = static_cast<double>(viewCount) / BookConfig::BookStatistics::MAX_VIEWS * 100.0;
    double ratingScore = averageRating * 20.0;
    
    return (salesScore * 0.4) + (viewsScore * 0.3) + (ratingScore * 0.3);
}

bool BookStatistics::isBestseller() const noexcept {
    return salesCount > 1000;
}

bool BookStatistics::isHighlyRated() const noexcept {
    return averageRating >= 4.0;
}

bool BookStatistics::operator==(const BookStatistics& other) const noexcept {
    return viewCount == other.viewCount &&
           salesCount == other.salesCount &&
           std::abs(averageRating - other.averageRating) < 0.001 &&
           reviewCount == other.reviewCount &&
           lastSaleDate == other.lastSaleDate;
}

bool BookStatistics::operator!=(const BookStatistics& other) const noexcept {
    return !(*this == other);
}

std::string BookStatistics::getSummary() const noexcept {
    return "Views: " + std::to_string(viewCount) + 
           ", Sales: " + std::to_string(salesCount) +
           ", Rating: " + std::to_string(averageRating) + "/5.0" +
           ", Reviews: " + std::to_string(reviewCount) +
           (lastSaleDate.empty() ? "" : ", Last sale: " + lastSaleDate);
}