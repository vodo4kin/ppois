#include <string>

class BookStatistics {
private:
    static constexpr int MAX_VIEWS = 1000000;
    static constexpr int MAX_SALES = 100000;
    int viewCount;          // количество просмотров
    int salesCount;         // количество продаж
    double averageRating;   // средний рейтинг (0.0-5.0)
    int reviewCount;        // количество отзывов
    std::string lastSaleDate; // дата последней продажи
    bool isValidViewCount(int views) const;
    bool isValidSalesCount(int sales) const;
    bool isValidRating(double rating) const;
    bool isValidReviewCount(int reviews) const;
    bool isValidDate(const std::string& date) const;
public:
    BookStatistics(int viewCount = 0, int salesCount = 0, 
                   double averageRating = 0.0, int reviewCount = 0,
                   const std::string& lastSaleDate = "");
    int getViewCount() const noexcept;
    int getSalesCount() const noexcept;
    double getAverageRating() const noexcept;
    int getReviewCount() const noexcept;
    std::string getLastSaleDate() const noexcept;
    void setViewCount(int views);
    void setSalesCount(int sales);
    void setAverageRating(double rating);
    void setReviewCount(int reviews);
    void setLastSaleDate(const std::string& date);
    void incrementViews(int amount = 1);
    void incrementSales(int amount = 1);
    void incrementReviews(int amount = 1);
    void updateRating(double newRating); // пересчет среднего
    double getPopularityScore() const noexcept; // комбинированный показатель
    bool isBestseller() const noexcept;         // продажи > 1000
    bool isHighlyRated() const noexcept;        // рейтинг >= 4.0
    bool operator==(const BookStatistics& other) const noexcept;
    bool operator!=(const BookStatistics& other) const noexcept;
    std::string getSummary() const noexcept;
};