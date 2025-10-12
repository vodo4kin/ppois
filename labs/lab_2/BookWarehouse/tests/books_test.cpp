#include <gtest/gtest.h>
#include <memory>
#include "books/Book.hpp"
#include "books/ISBN.hpp"
#include "books/BookTitle.hpp"
#include "books/BookMetadata.hpp"
#include "books/PhysicalProperties.hpp"
#include "books/Genre.hpp"
#include "books/Publisher.hpp"
#include "books/BookSeries.hpp"
#include "books/BookCondition.hpp"
#include "books/BookReview.hpp"
#include "books/BookStatistics.hpp"
#include "books/BookCollection.hpp"
#include "exceptions/WarehouseExceptions.hpp"

// ==================== ISBN Tests ====================
TEST(ISBNTest, ValidISBN13) {
    EXPECT_NO_THROW(ISBN isbn("978-3-161-48410-0"));
    ISBN isbn("9783161484100");
    EXPECT_EQ(isbn.getCode(), "9783161484100");
    EXPECT_TRUE(isbn.isISBNThirteen());
    std::cout << isbn.getFormattedCode();
    EXPECT_EQ(isbn.getFormattedCode(), "978-3-161-48410-0");
}

TEST(ISBNTest, ValidISBN10) {
    EXPECT_NO_THROW(ISBN isbn("0-306-40615-2"));
    ISBN isbn("0306406152");
    EXPECT_EQ(isbn.getCode(), "0306406152");
    EXPECT_FALSE(isbn.isISBNThirteen());
}

TEST(ISBNTest, InvalidISBN) {
    EXPECT_THROW(ISBN isbn("invalid"), InvalidISBNException);
    EXPECT_THROW(ISBN isbn("123"), InvalidISBNException);
    EXPECT_THROW(ISBN isbn("978-3-16-148410-1"), InvalidISBNException); // wrong check digit
}

TEST(ISBNTest, Equality) {
    ISBN isbn1("9783161484100");
    ISBN isbn2("978-3-16-148410-0");
    ISBN isbn3("0306406152");
    EXPECT_EQ(isbn1, isbn2);
    EXPECT_NE(isbn1, isbn3);
}

// ==================== BookTitle Tests ====================
TEST(BookTitleTest, ValidTitle) {
    EXPECT_NO_THROW(BookTitle title("The Great Gatsby", "A Novel", "EN"));
    BookTitle title("Test", "", "RU");
    EXPECT_EQ(title.getTitle(), "Test");
    EXPECT_EQ(title.getSubtitle(), "");
    EXPECT_EQ(title.getLanguage(), "RU");
    EXPECT_EQ(title.getFullTitle(), "Test (RU)");
}

TEST(BookTitleTest, InvalidTitle) {
    EXPECT_THROW(BookTitle title("", "Sub", "EN"), DataValidationException);
    EXPECT_THROW(BookTitle title("   ", "Sub", "EN"), DataValidationException);
    EXPECT_THROW(BookTitle title("Valid", "Sub", "English"), DataValidationException);
}

// ==================== BookMetadata Tests ====================
TEST(BookMetadataTest, ValidMetadata) {
    EXPECT_NO_THROW(BookMetadata metadata(2024, "EN", 2, "Description"));
    BookMetadata metadata(2000, "RU", 1, "");
    EXPECT_EQ(metadata.getPublicationYear(), 2000);
    EXPECT_EQ(metadata.getLanguage(), "RU");
    EXPECT_EQ(metadata.getEdition(), 1);
    EXPECT_TRUE(metadata.isFirstEdition());
    EXPECT_EQ(metadata.getEditionString(), "1st Edition");
}

TEST(BookMetadataTest, InvalidMetadata) {
    EXPECT_THROW(BookMetadata metadata(1300, "EN", 1, ""), DataValidationException);
    EXPECT_THROW(BookMetadata metadata(2024, "English", 1, ""), DataValidationException);
    EXPECT_THROW(BookMetadata metadata(2024, "EN", 0, ""), DataValidationException);
}

// ==================== Genre Tests ====================
TEST(GenreTest, GenreTypes) {
    Genre fantasy(Genre::Type::FANTASY);
    Genre mystery(Genre::Type::MYSTERY);
    EXPECT_EQ(fantasy.toString(), "Fantasy");
    EXPECT_EQ(mystery.toString(), "Mystery");
    EXPECT_EQ(fantasy.getGenre(), Genre::Type::FANTASY);
    EXPECT_NE(fantasy, mystery);
}

// ==================== Publisher Tests ====================
TEST(PublisherTest, ValidPublisher) {
    EXPECT_NO_THROW(Publisher pub("Test Publisher", "test@pub.com", 2000));
    Publisher pub("Penguin", "contact@penguin.com", 1935);
    EXPECT_EQ(pub.getName(), "Penguin");
    EXPECT_EQ(pub.getContactEmail(), "contact@penguin.com");
    EXPECT_EQ(pub.getFoundationYear(), 1935);
}

TEST(PublisherTest, InvalidPublisher) {
    EXPECT_THROW(Publisher pub("", "test@test.com", 2000), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "invalid-email", 2000), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "test@test.com", 1300), DataValidationException);
}

// ==================== BookCondition Tests ====================
TEST(BookConditionTest, Conditions) {
    BookCondition newCond(BookCondition::Condition::NEW);
    BookCondition poorCond(BookCondition::Condition::POOR);
    EXPECT_TRUE(newCond.isNew());
    EXPECT_FALSE(newCond.isUsed());
    EXPECT_FALSE(newCond.needsReplacement());
    EXPECT_FALSE(poorCond.isNew());
    EXPECT_TRUE(poorCond.isUsed());
    EXPECT_TRUE(poorCond.needsReplacement());
    EXPECT_EQ(newCond.toString(), "New");
}

// ==================== BookReview Tests ====================
TEST(BookReviewTest, ValidReview) {
    EXPECT_NO_THROW(BookReview review("John Doe", "Great!", "Excellent book", 5, "2024-01-15"));
    BookReview review("Jane", "Good", "Nice read", 4, "2024-01-20");
    EXPECT_EQ(review.getAuthor(), "Jane");
    EXPECT_EQ(review.getRating(), 4);
    EXPECT_TRUE(review.isPositiveReview());
    EXPECT_FALSE(review.isCriticalReview());
    EXPECT_EQ(review.getRatingStars(), "★★★★☆");
}

TEST(BookReviewTest, InvalidReview) {
    EXPECT_THROW(BookReview review("", "Title", "Text", 3, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 0, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 6, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 3, "invalid-date"), DataValidationException);
}

// ==================== BookStatistics Tests ====================
TEST(BookStatisticsTest, StatisticsOperations) {
    BookStatistics stats(100, 50, 4.5, 10, "2024-01-15");
    EXPECT_EQ(stats.getViewCount(), 100);
    EXPECT_EQ(stats.getSalesCount(), 50);
    EXPECT_DOUBLE_EQ(stats.getAverageRating(), 4.5);
    EXPECT_EQ(stats.getReviewCount(), 10);
    stats.incrementViews(50);
    stats.incrementSales(10);
    stats.incrementReviews(2);
    EXPECT_EQ(stats.getViewCount(), 150);
    EXPECT_EQ(stats.getSalesCount(), 60);
    EXPECT_EQ(stats.getReviewCount(), 12);
    EXPECT_FALSE(stats.isBestseller());
    EXPECT_TRUE(stats.isHighlyRated());
}

TEST(BookStatisticsTest, BestsellerCheck) {
    BookStatistics bestseller(1000, 1500, 4.2, 100, "2024-01-15");
    BookStatistics regular(1000, 500, 4.2, 100, "2024-01-15");
    EXPECT_TRUE(bestseller.isBestseller());
    EXPECT_FALSE(regular.isBestseller());
}

// ==================== PhysicalProperties Tests ====================
TEST(PhysicalPropertiesTest, ValidProperties) {
    EXPECT_NO_THROW(
        PhysicalProperties props(300, 200, 130, 20, 250, 
                               PhysicalProperties::CoverType::PAPERBACK, "Paper")
    );
    PhysicalProperties props(500, 240, 160, 40, 400, 
                           PhysicalProperties::CoverType::HARDCOVER, "Hardcover");
    EXPECT_EQ(props.getWeight(), 500);
    EXPECT_EQ(props.getPageCount(), 400);
    EXPECT_EQ(props.getCoverType(), PhysicalProperties::CoverType::HARDCOVER);
    EXPECT_GT(props.getVolume(), 0);
    EXPECT_GT(props.getDensity(), 0);
}

// ==================== BookSeries Tests ====================
TEST(BookSeriesTest, SeriesInfo) {
    BookSeries series("Harry Potter", "Magic series", 7, 1997, 2007);
    EXPECT_EQ(series.getName(), "Harry Potter");
    EXPECT_EQ(series.getBookCount(), 7);
    EXPECT_TRUE(series.isCompleted());
    EXPECT_FALSE(series.isOngoing());
}

// ==================== Book Tests ====================
TEST(BookTest, BasicBookCreation) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, "Test"),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    EXPECT_DOUBLE_EQ(book->getPrice(), 19.99);
}

TEST(BookTest, PriceAndDiscount) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        100.0
    );
    book->applyDiscount(10);
    EXPECT_DOUBLE_EQ(book->getPrice(), 90.0);
    book->setPrice(50.0);
    EXPECT_DOUBLE_EQ(book->getPrice(), 50.0);
    EXPECT_THROW(book->setPrice(-10), DataValidationException);
    EXPECT_THROW(book->applyDiscount(110), DataValidationException);
}

TEST(BookTest, Reviews) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto review1 = std::make_shared<BookReview>("John", "Good", "Nice book", 4, "2024-01-15");
    auto review2 = std::make_shared<BookReview>("Jane", "Great", "Awesome book", 5, "2024-01-16");
    book->addReview(review1);
    book->addReview(review2);
    EXPECT_EQ(book->getReviewCount(), 2);
    EXPECT_DOUBLE_EQ(book->getAverageRating(), 4.5);
    book->removeReview(review1);
    EXPECT_EQ(book->getReviewCount(), 1);
    EXPECT_DOUBLE_EQ(book->getAverageRating(), 5.0);
}

TEST(BookTest, BookWithSeries) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto series = std::make_shared<BookSeries>("Test Series", "Desc", 5, 2020, 2024);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99,
        series
    );
    EXPECT_EQ(book->getSeries()->getName(), "Test Series");
}

TEST(BookTest, BookEquality) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Book 1", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto book2 = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Book 2", "", "EN"),
        BookMetadata(2023, "RU", 2, ""),
        PhysicalProperties(400, 210, 140, 25, 300, 
                         PhysicalProperties::CoverType::HARDCOVER, "Hardcover"),
        Genre(Genre::Type::MYSTERY),
        publisher,
        BookCondition(BookCondition::Condition::LIKE_NEW),
        29.99
    );
    auto book3 = std::make_shared<Book>(
        ISBN("0306406152"),
        BookTitle("Book 1", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    EXPECT_EQ(*book1, *book2);
    EXPECT_NE(*book1, *book3);
}

// ==================== BookCollection Tests ====================
TEST(BookCollectionTest, BasicOperations) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book1 = std::make_shared<Book>(
        ISBN("0306406152"),
        BookTitle("Book 1", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto book2 = std::make_shared<Book>(
        ISBN("0451524934"),
        BookTitle("Book 2", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        24.99
    );
    BookCollection collection("My Books", "Test collection", "Science");
    EXPECT_TRUE(collection.isEmpty());
    collection.addBook(book1);
    collection.addBook(book2);
    EXPECT_FALSE(collection.isEmpty());
    EXPECT_EQ(collection.getBookCount(), 2);
    EXPECT_TRUE(collection.containsBook(book1));
    collection.removeBook(book1);
    EXPECT_EQ(collection.getBookCount(), 1);
    EXPECT_FALSE(collection.containsBook(book1));
}

TEST(BookCollectionTest, DuplicateBook) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    BookCollection collection("Collection", "Desc", "Category");
    collection.addBook(book);
    EXPECT_THROW(collection.addBook(book), DuplicateBookException);
}

// ==================== Integration Test ====================
TEST(IntegrationTest, CompleteFlow) {
    auto publisher = std::make_shared<Publisher>("Big Publisher", "big@pub.com", 1990);
    auto series = std::make_shared<BookSeries>("Fantasy Series", "Epic fantasy", 3, 2020, 2023);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Dragon Quest", "The Beginning", "EN"),
        BookMetadata(2024, "EN", 1, "Epic fantasy novel"),
        PhysicalProperties(450, 220, 150, 30, 400, 
                         PhysicalProperties::CoverType::HARDCOVER, "Hardcover"),
        Genre(Genre::Type::FANTASY),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        29.99,
        series
    );
    auto review1 = std::make_shared<BookReview>("Alice", "Amazing", "Loved it!", 5, "2024-01-10");
    auto review2 = std::make_shared<BookReview>("Bob", "Good", "Enjoyable read", 4, "2024-01-11");
    book->addReview(review1);
    book->addReview(review2);
    book->applyDiscount(20);
    EXPECT_DOUBLE_EQ(book->getPrice(), 29.99 * 0.8);
    EXPECT_DOUBLE_EQ(book->getAverageRating(), 4.5);
    EXPECT_TRUE(book->isHighlyRated());
    BookCollection collection("Bestsellers", "Popular books", "Fantasy");
    collection.addBook(book);
    EXPECT_EQ(collection.getBookCount(), 1);
    EXPECT_TRUE(collection.containsBook(book));
}