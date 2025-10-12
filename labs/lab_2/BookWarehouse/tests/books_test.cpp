#include <gtest/gtest.h>
#include <memory>
#include <cmath>
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

// ==================== ISBN Tests (Extended) ====================
TEST(ISBNTest, ValidISBN13) {
    EXPECT_NO_THROW(ISBN isbn("978-3-161-48410-0"));
    ISBN isbn("9783161484100");
    EXPECT_EQ(isbn.getCode(), "9783161484100");
    EXPECT_TRUE(isbn.isISBNThirteen());
    EXPECT_EQ(isbn.getFormattedCode(), "978-3-161-48410-0");
}

TEST(ISBNTest, ValidISBN10) {
    EXPECT_NO_THROW(ISBN isbn("0-306-40615-2"));
    ISBN isbn("0306406152");
    EXPECT_EQ(isbn.getCode(), "0306406152");
    EXPECT_FALSE(isbn.isISBNThirteen());
    EXPECT_EQ(isbn.getFormattedCode(), "0-306-40615-2");
}

TEST(ISBNTest, InvalidISBN) {
    EXPECT_THROW(ISBN isbn("invalid"), InvalidISBNException);
    EXPECT_THROW(ISBN isbn("123"), InvalidISBNException);
    EXPECT_THROW(ISBN isbn("978-3-16-148410-1"), InvalidISBNException); // wrong check digit
    EXPECT_THROW(ISBN isbn("0306406153"), InvalidISBNException); // wrong check digit for ISBN10
    EXPECT_THROW(ISBN isbn("978316148410X"), InvalidISBNException); // invalid character
}

TEST(ISBNTest, EqualityAndInequality) {
    ISBN isbn1("9783161484100");
    ISBN isbn2("978-3-16-148410-0");
    ISBN isbn3("0306406152");
    ISBN isbn4("0306406152");
    
    EXPECT_EQ(isbn1, isbn2);
    EXPECT_NE(isbn1, isbn3);
    EXPECT_EQ(isbn3, isbn4);
    EXPECT_NE(isbn2, isbn3);
    
    // Test self-equality
    EXPECT_EQ(isbn1, isbn1);
    EXPECT_EQ(isbn3, isbn3);
}

TEST(ISBNTest, EdgeCases) {
    // ISBN-10 with X check digit
    EXPECT_NO_THROW(ISBN isbn("012000030X"));
    ISBN isbnWithX("012000030X");
    EXPECT_EQ(isbnWithX.getCode(), "012000030X");
    EXPECT_FALSE(isbnWithX.isISBNThirteen());
    
    // Mixed case X
    EXPECT_NO_THROW(ISBN isbn("012000030x"));
}

// ==================== BookTitle Tests (Extended) ====================
TEST(BookTitleTest, ValidTitle) {
    EXPECT_NO_THROW(BookTitle title("The Great Gatsby", "A Novel", "EN"));
    BookTitle title("Test", "", "RU");
    EXPECT_EQ(title.getTitle(), "Test");
    EXPECT_EQ(title.getSubtitle(), "");
    EXPECT_EQ(title.getLanguage(), "RU");
    EXPECT_EQ(title.getFullTitle(), "Test (RU)");
    
    // Title with subtitle
    BookTitle titleWithSub("Main", "Subtitle", "EN");
    EXPECT_EQ(titleWithSub.getFullTitle(), "Main: Subtitle (EN)");
}

TEST(BookTitleTest, InvalidTitle) {
    EXPECT_THROW(BookTitle title("", "Sub", "EN"), DataValidationException);
    EXPECT_THROW(BookTitle title("   ", "Sub", "EN"), DataValidationException);
    EXPECT_THROW(BookTitle title("Valid", "Sub", "English"), DataValidationException);
    EXPECT_THROW(BookTitle title("Valid", "   ", "EN"), DataValidationException);
    EXPECT_THROW(BookTitle title("Valid", "Sub", ""), DataValidationException);
    EXPECT_THROW(BookTitle title("Valid", "Sub", "E"), DataValidationException);
    
    // Test maximum length boundaries
    std::string longTitle(129, 'a'); // Exceeds MAX_LENGTH
    EXPECT_THROW(BookTitle title(longTitle, "", "EN"), DataValidationException);
}

TEST(BookTitleTest, EqualityAndInequality) {
    BookTitle title1("Same", "Sub", "EN");
    BookTitle title2("Same", "Sub", "EN");
    BookTitle title3("Different", "Sub", "EN");
    BookTitle title4("Same", "Different", "EN");
    BookTitle title5("Same", "Sub", "RU");
    
    EXPECT_EQ(title1, title2);
    EXPECT_NE(title1, title3);
    EXPECT_NE(title1, title4);
    EXPECT_NE(title1, title5);
    
    // Self-equality
    EXPECT_EQ(title1, title1);
}

// ==================== BookMetadata Tests (Extended) ====================
TEST(BookMetadataTest, ValidMetadata) {
    EXPECT_NO_THROW(BookMetadata metadata(2024, "EN", 2, "Description"));
    BookMetadata metadata(2000, "RU", 1, "");
    EXPECT_EQ(metadata.getPublicationYear(), 2000);
    EXPECT_EQ(metadata.getLanguage(), "RU");
    EXPECT_EQ(metadata.getEdition(), 1);
    EXPECT_TRUE(metadata.isFirstEdition());
    EXPECT_EQ(metadata.getEditionString(), "1st Edition");
    
    // Test different editions
    BookMetadata secondEd(2024, "EN", 2, "");
    EXPECT_EQ(secondEd.getEditionString(), "2nd Edition");
    
    BookMetadata thirdEd(2024, "EN", 3, "");
    EXPECT_EQ(thirdEd.getEditionString(), "3rd Edition");
    
    BookMetadata fourthEd(2024, "EN", 4, "");
    EXPECT_EQ(fourthEd.getEditionString(), "4th Edition");
}

TEST(BookMetadataTest, InvalidMetadata) {
    EXPECT_THROW(BookMetadata metadata(1300, "EN", 1, ""), DataValidationException);
    EXPECT_THROW(BookMetadata metadata(2026, "EN", 1, ""), DataValidationException); // Future year
    EXPECT_THROW(BookMetadata metadata(2024, "English", 1, ""), DataValidationException);
    EXPECT_THROW(BookMetadata metadata(2024, "EN", 0, ""), DataValidationException);
    EXPECT_THROW(BookMetadata metadata(2024, "EN", -1, ""), DataValidationException);
    
    // Test long description
    std::string longDesc(501, 'a');
    EXPECT_THROW(BookMetadata metadata(2024, "EN", 1, longDesc), DataValidationException);
}

TEST(BookMetadataTest, EqualityAndInequality) {
    BookMetadata meta1(2024, "EN", 1, "Desc");
    BookMetadata meta2(2024, "EN", 1, "Desc");
    BookMetadata meta3(2023, "EN", 1, "Desc");
    BookMetadata meta4(2024, "RU", 1, "Desc");
    BookMetadata meta5(2024, "EN", 2, "Desc");
    BookMetadata meta6(2024, "EN", 1, "Different");
    
    EXPECT_EQ(meta1, meta2);
    EXPECT_NE(meta1, meta3);
    EXPECT_NE(meta1, meta4);
    EXPECT_NE(meta1, meta5);
    EXPECT_NE(meta1, meta6);
}

// ==================== Genre Tests (Extended) ====================
TEST(GenreTest, AllGenreTypes) {
    // Test all genre types
    Genre fantasy(Genre::Type::FANTASY);
    Genre mystery(Genre::Type::MYSTERY);
    Genre thriller(Genre::Type::THRILLER);
    Genre scifi(Genre::Type::SCIENCE_FICTION);
    Genre romance(Genre::Type::ROMANCE);
    Genre historical(Genre::Type::HISTORICAL_FICTION);
    Genre horror(Genre::Type::HORROR);
    Genre children(Genre::Type::FOR_CHILDREN);
    Genre drama(Genre::Type::DRAMA);
    Genre poetry(Genre::Type::POETRY);
    Genre autobiography(Genre::Type::AUTOBIOGRAPHY);
    Genre other(Genre::Type::OTHER);
    
    EXPECT_EQ(fantasy.toString(), "Fantasy");
    EXPECT_EQ(mystery.toString(), "Mystery");
    EXPECT_EQ(thriller.toString(), "Thriller");
    EXPECT_EQ(scifi.toString(), "Science Fiction");
    EXPECT_EQ(romance.toString(), "Romance");
    EXPECT_EQ(historical.toString(), "Historical Fiction");
    EXPECT_EQ(horror.toString(), "Horror");
    EXPECT_EQ(children.toString(), "For Children");
    EXPECT_EQ(drama.toString(), "Drama");
    EXPECT_EQ(poetry.toString(), "Poetry");
    EXPECT_EQ(autobiography.toString(), "Autobiography");
    EXPECT_EQ(other.toString(), "Other");
    
    EXPECT_EQ(fantasy.getGenre(), Genre::Type::FANTASY);
    EXPECT_NE(fantasy, mystery);
}

TEST(GenreTest, EqualityAndInequality) {
    Genre genre1(Genre::Type::FANTASY);
    Genre genre2(Genre::Type::FANTASY);
    Genre genre3(Genre::Type::MYSTERY);
    
    EXPECT_EQ(genre1, genre2);
    EXPECT_NE(genre1, genre3);
    EXPECT_EQ(genre1, genre1); // Self-equality
}

// ==================== Publisher Tests (Extended) ====================
TEST(PublisherTest, ValidPublisher) {
    EXPECT_NO_THROW(Publisher pub("Test Publisher", "test@pub.com", 2000));
    Publisher pub("Penguin", "contact@penguin.com", 1935);
    EXPECT_EQ(pub.getName(), "Penguin");
    EXPECT_EQ(pub.getContactEmail(), "contact@penguin.com");
    EXPECT_EQ(pub.getFoundationYear(), 1935);
    
    // Publisher with empty email
    EXPECT_NO_THROW(Publisher pub2("No Email Pub", "", 2000));
    Publisher pub2("No Email", "", 2000);
    EXPECT_TRUE(pub2.getContactEmail().empty());
    
    // Test getInfo method
    std::string info = pub2.getInfo();
    EXPECT_FALSE(info.empty());
}

TEST(PublisherTest, InvalidPublisher) {
    EXPECT_THROW(Publisher pub("", "test@test.com", 2000), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "invalid-email", 2000), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "test@test.com", 1300), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "test@test.com", 2026), DataValidationException); // Future year
    
    // Test long name
    std::string longName(101, 'a');
    EXPECT_THROW(Publisher pub(longName, "test@test.com", 2000), DataValidationException);
    
    // Invalid email formats
    EXPECT_THROW(Publisher pub("Valid", "@test.com", 2000), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "test@", 2000), DataValidationException);
    EXPECT_THROW(Publisher pub("Valid", "test@test", 2000), DataValidationException);
}

TEST(PublisherTest, EqualityAndInequality) {
    Publisher pub1("Same", "email@test.com", 2000);
    Publisher pub2("Same", "email@test.com", 2000);
    Publisher pub3("Different", "email@test.com", 2000);
    Publisher pub4("Same", "different@test.com", 2000);
    Publisher pub5("Same", "email@test.com", 2001);
    
    EXPECT_EQ(pub1, pub2);
    EXPECT_NE(pub1, pub3);
    EXPECT_NE(pub1, pub4);
    EXPECT_NE(pub1, pub5);
}

// ==================== BookCondition Tests (Extended) ====================
TEST(BookConditionTest, AllConditions) {
    BookCondition newCond(BookCondition::Condition::NEW);
    BookCondition likeNew(BookCondition::Condition::LIKE_NEW);
    BookCondition veryGood(BookCondition::Condition::VERY_GOOD);
    BookCondition good(BookCondition::Condition::GOOD);
    BookCondition fair(BookCondition::Condition::FAIR);
    BookCondition poor(BookCondition::Condition::POOR);
    
    EXPECT_TRUE(newCond.isNew());
    EXPECT_FALSE(newCond.isUsed());
    EXPECT_FALSE(newCond.needsReplacement());
    EXPECT_EQ(newCond.toString(), "New");
    
    EXPECT_FALSE(likeNew.isNew());
    EXPECT_TRUE(likeNew.isUsed());
    EXPECT_FALSE(likeNew.needsReplacement());
    EXPECT_EQ(likeNew.toString(), "Like New");
    
    EXPECT_FALSE(veryGood.isNew());
    EXPECT_TRUE(veryGood.isUsed());
    EXPECT_FALSE(veryGood.needsReplacement());
    EXPECT_EQ(veryGood.toString(), "Very Good");
    
    EXPECT_FALSE(good.isNew());
    EXPECT_TRUE(good.isUsed());
    EXPECT_FALSE(good.needsReplacement());
    EXPECT_EQ(good.toString(), "Good");
    
    EXPECT_FALSE(fair.isNew());
    EXPECT_TRUE(fair.isUsed());
    EXPECT_FALSE(fair.needsReplacement());
    EXPECT_EQ(fair.toString(), "Fair");
    
    EXPECT_FALSE(poor.isNew());
    EXPECT_TRUE(poor.isUsed());
    EXPECT_TRUE(poor.needsReplacement());
    EXPECT_EQ(poor.toString(), "Poor");
}

TEST(BookConditionTest, EqualityAndInequality) {
    BookCondition cond1(BookCondition::Condition::NEW);
    BookCondition cond2(BookCondition::Condition::NEW);
    BookCondition cond3(BookCondition::Condition::GOOD);
    
    EXPECT_EQ(cond1, cond2);
    EXPECT_NE(cond1, cond3);
    EXPECT_EQ(cond1, cond1); // Self-equality
}

// ==================== BookReview Tests (Extended) ====================
TEST(BookReviewTest, ValidReview) {
    EXPECT_NO_THROW(BookReview review("John Doe", "Great!", "Excellent book", 5, "2024-01-15"));
    BookReview review("Jane", "Good", "Nice read", 4, "2024-01-20");
    EXPECT_EQ(review.getAuthor(), "Jane");
    EXPECT_EQ(review.getRating(), 4);
    EXPECT_TRUE(review.isPositiveReview());
    EXPECT_FALSE(review.isCriticalReview());
    EXPECT_EQ(review.getRatingStars(), "★★★★☆");
    
    // Test critical review
    BookReview critical("Critic", "Bad", "Not good", 2, "2024-01-25");
    EXPECT_FALSE(critical.isPositiveReview());
    EXPECT_TRUE(critical.isCriticalReview());
    EXPECT_EQ(critical.getRatingStars(), "★★☆☆☆");
    
    // Test getSummary
    std::string summary = review.getSummary();
    EXPECT_FALSE(summary.empty());
}

TEST(BookReviewTest, InvalidReview) {
    EXPECT_THROW(BookReview review("", "Title", "Text", 3, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 0, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 6, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 3, "invalid-date"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "   ", 3, "2024-01-15"), DataValidationException);
    
    // Test long fields
    std::string longAuthor(101, 'a');
    std::string longTitle(201, 'a');
    std::string longText(2001, 'a');
    
    EXPECT_THROW(BookReview review(longAuthor, "Title", "Text", 3, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", longTitle, "Text", 3, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", longText, 3, "2024-01-15"), DataValidationException);
}

TEST(BookReviewTest, EqualityAndInequality) {
    BookReview rev1("Author", "Title", "Text", 4, "2024-01-15");
    BookReview rev2("Author", "Title", "Text", 4, "2024-01-15");
    BookReview rev3("Different", "Title", "Text", 4, "2024-01-15");
    BookReview rev4("Author", "Different", "Text", 4, "2024-01-15");
    BookReview rev5("Author", "Title", "Different", 4, "2024-01-15");
    BookReview rev6("Author", "Title", "Text", 3, "2024-01-15");
    BookReview rev7("Author", "Title", "Text", 4, "2024-01-16");
    
    EXPECT_EQ(rev1, rev2);
    EXPECT_NE(rev1, rev3);
    EXPECT_NE(rev1, rev4);
    EXPECT_NE(rev1, rev5);
    EXPECT_NE(rev1, rev6);
    EXPECT_NE(rev1, rev7);
}

// ==================== BookStatistics Tests (Extended) ====================
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
    
    // Test setters
    stats.setViewCount(200);
    stats.setSalesCount(100);
    stats.setAverageRating(4.8);
    stats.setReviewCount(15);
    stats.setLastSaleDate("2024-02-01");
    
    EXPECT_EQ(stats.getViewCount(), 200);
    EXPECT_EQ(stats.getSalesCount(), 100);
    EXPECT_DOUBLE_EQ(stats.getAverageRating(), 4.8);
    EXPECT_EQ(stats.getReviewCount(), 15);
    EXPECT_EQ(stats.getLastSaleDate(), "2024-02-01");
    
    // Test popularity score
    double popularity = stats.getPopularityScore();
    EXPECT_GE(popularity, 0.0);
    EXPECT_LE(popularity, 100.0);
    
    // Test getSummary
    std::string summary = stats.getSummary();
    EXPECT_FALSE(summary.empty());
}

TEST(BookStatisticsTest, BestsellerAndRatingChecks) {
    BookStatistics bestseller(1000, 1500, 4.2, 100, "2024-01-15");
    BookStatistics regular(1000, 500, 4.2, 100, "2024-01-15");
    BookStatistics highlyRated(100, 50, 4.5, 10, "2024-01-15");
    BookStatistics lowRated(100, 50, 3.5, 10, "2024-01-15");
    
    EXPECT_TRUE(bestseller.isBestseller());
    EXPECT_FALSE(regular.isBestseller());
    EXPECT_TRUE(highlyRated.isHighlyRated());
    EXPECT_FALSE(lowRated.isHighlyRated());
}

TEST(BookStatisticsTest, RatingUpdates) {
    BookStatistics stats(0, 0, 0.0, 0, "2024-01-01");
    
    // Test updateRating
    stats.updateRating(5.0);
    EXPECT_DOUBLE_EQ(stats.getAverageRating(), 5.0);
    EXPECT_EQ(stats.getReviewCount(), 1);
    
    stats.updateRating(3.0);
    EXPECT_DOUBLE_EQ(stats.getAverageRating(), 4.0);
    EXPECT_EQ(stats.getReviewCount(), 2);
    
    // Test removeRating
    stats.removeRating(3.0);
    EXPECT_DOUBLE_EQ(stats.getAverageRating(), 5.0);
    EXPECT_EQ(stats.getReviewCount(), 1);
    
    stats.removeRating(5.0);
    EXPECT_DOUBLE_EQ(stats.getAverageRating(), 0.0);
    EXPECT_EQ(stats.getReviewCount(), 0);
}

TEST(BookStatisticsTest, InvalidStatistics) {
    EXPECT_THROW(BookStatistics stats(-1, 50, 4.5, 10, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookStatistics stats(100, -1, 4.5, 10, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookStatistics stats(100, 50, -0.1, 10, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookStatistics stats(100, 50, 5.1, 10, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookStatistics stats(100, 50, 4.5, -1, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookStatistics stats(100, 50, 4.5, 10, "invalid-date"), DataValidationException);
    
    // Test invalid increments
    BookStatistics stats(100, 50, 4.5, 10, "2024-01-15");
    EXPECT_THROW(stats.incrementViews(-1), DataValidationException);
    EXPECT_THROW(stats.incrementSales(-1), DataValidationException);
    EXPECT_THROW(stats.incrementReviews(-1), DataValidationException);
    
    // Test invalid setters
    EXPECT_THROW(stats.setViewCount(-1), DataValidationException);
    EXPECT_THROW(stats.setSalesCount(-1), DataValidationException);
    EXPECT_THROW(stats.setAverageRating(-0.1), DataValidationException);
    EXPECT_THROW(stats.setAverageRating(5.1), DataValidationException);
    EXPECT_THROW(stats.setReviewCount(-1), DataValidationException);
    EXPECT_THROW(stats.setLastSaleDate("invalid"), DataValidationException);
}

TEST(BookStatisticsTest, EqualityAndInequality) {
    BookStatistics stats1(100, 50, 4.5, 10, "2024-01-15");
    BookStatistics stats2(100, 50, 4.5, 10, "2024-01-15");
    BookStatistics stats3(200, 50, 4.5, 10, "2024-01-15");
    BookStatistics stats4(100, 60, 4.5, 10, "2024-01-15");
    BookStatistics stats5(100, 50, 4.0, 10, "2024-01-15");
    BookStatistics stats6(100, 50, 4.5, 15, "2024-01-15");
    BookStatistics stats7(100, 50, 4.5, 10, "2024-01-16");
    
    EXPECT_EQ(stats1, stats2);
    EXPECT_NE(stats1, stats3);
    EXPECT_NE(stats1, stats4);
    EXPECT_NE(stats1, stats5);
    EXPECT_NE(stats1, stats6);
    EXPECT_NE(stats1, stats7);
}

// ==================== PhysicalProperties Tests (Extended) ====================
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
    EXPECT_EQ(props.getCoverTypeString(), "Hardcover");
    EXPECT_GT(props.getVolume(), 0);
    EXPECT_GT(props.getDensity(), 0);
    
    // Test paperback
    PhysicalProperties paperback(300, 200, 130, 20, 250, 
                               PhysicalProperties::CoverType::PAPERBACK, "Paper");
    EXPECT_EQ(paperback.getCoverTypeString(), "Paperback");
}

TEST(PhysicalPropertiesTest, InvalidProperties) {
    EXPECT_THROW(PhysicalProperties props(0, 200, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(6000, 200, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 0, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 600, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 200, 0, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 200, 130, 0, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 200, 130, 20, 0, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 200, 130, 20, 6000, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 200, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, ""), 
                 DataValidationException);
}

TEST(PhysicalPropertiesTest, VolumeAndDensityCalculations) {
    PhysicalProperties props(1000, 100, 100, 10, 500, 
                           PhysicalProperties::CoverType::HARDCOVER, "Hardcover");
    
    // Volume in cm³: (100/10) * (100/10) * (10/10) = 10 * 10 * 1 = 100 cm³
    EXPECT_DOUBLE_EQ(props.getVolume(), 100.0);
    
    // Density: 1000g / 100cm³ = 10 g/cm³
    EXPECT_DOUBLE_EQ(props.getDensity(), 10.0);
    
    // Test zero volume case (shouldn't happen with validation, but test method)
    EXPECT_THROW(PhysicalProperties zeroProps(0, 1, 1, 1, 100, 
                               PhysicalProperties::CoverType::PAPERBACK, "Paper"), DataValidationException);
    // Note: This will throw due to validation, so we need to test density with normal values
}

TEST(PhysicalPropertiesTest, EqualityAndInequality) {
    PhysicalProperties props1(300, 200, 130, 20, 250, 
                            PhysicalProperties::CoverType::PAPERBACK, "Paper");
    PhysicalProperties props2(300, 200, 130, 20, 250, 
                            PhysicalProperties::CoverType::PAPERBACK, "Paper");
    PhysicalProperties props3(400, 200, 130, 20, 250, 
                            PhysicalProperties::CoverType::PAPERBACK, "Paper");
    
    EXPECT_EQ(props1, props2);
    EXPECT_NE(props1, props3);
}

// ==================== BookSeries Tests (Extended) ====================
TEST(BookSeriesTest, SeriesInfo) {
    BookSeries series("Harry Potter", "Magic series", 7, 1997, 2007);
    EXPECT_EQ(series.getName(), "Harry Potter");
    EXPECT_EQ(series.getBookCount(), 7);
    EXPECT_TRUE(series.isCompleted());
    EXPECT_FALSE(series.isOngoing());
    
    // Ongoing series
    BookSeries ongoing("Ongoing Series", "Still publishing", 3, 2020, 0);
    EXPECT_FALSE(ongoing.isCompleted());
    EXPECT_TRUE(ongoing.isOngoing());
    
    // Test getInfo
    std::string info = series.getInfo();
    std::string ongoingInfo = ongoing.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_FALSE(ongoingInfo.empty());
}

TEST(BookSeriesTest, InvalidSeries) {
    EXPECT_THROW(BookSeries series("", "Desc", 5, 2020, 2024), DataValidationException);
    EXPECT_THROW(BookSeries series("Valid", "Desc", -1, 2020, 2024), DataValidationException);
    EXPECT_THROW(BookSeries series("Valid", "Desc", 5, -1, 2024), DataValidationException);
    EXPECT_THROW(BookSeries series("Valid", "Desc", 5, 2020, -1), DataValidationException);
    EXPECT_THROW(BookSeries series("Valid", "Desc", 5, 2024, 2020), DataValidationException); // end before start
    
    // Test long name and description
    std::string longName(101, 'a');
    std::string longDesc(501, 'a');
    EXPECT_THROW(BookSeries series(longName, "Desc", 5, 2020, 2024), DataValidationException);
    EXPECT_THROW(BookSeries series("Valid", longDesc, 5, 2020, 2024), DataValidationException);
}

TEST(BookSeriesTest, EqualityAndInequality) {
    BookSeries series1("Same", "Desc", 5, 2020, 2024);
    BookSeries series2("Same", "Desc", 5, 2020, 2024);
    BookSeries series3("Different", "Desc", 5, 2020, 2024);
    BookSeries series4("Same", "Different", 5, 2020, 2024);
    BookSeries series5("Same", "Desc", 6, 2020, 2024);
    BookSeries series6("Same", "Desc", 5, 2021, 2024);
    BookSeries series7("Same", "Desc", 5, 2020, 2025);
    
    EXPECT_EQ(series1, series2);
    EXPECT_NE(series1, series3);
    EXPECT_NE(series1, series4);
    EXPECT_NE(series1, series5);
    EXPECT_NE(series1, series6);
    EXPECT_NE(series1, series7);
}

// ==================== Book Tests (Extended) ====================
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
    EXPECT_EQ(book->getPublisher(), publisher);
    EXPECT_EQ(book->getCondition().getCondition(), BookCondition::Condition::NEW);
    
    // Test getters
    EXPECT_NO_THROW(book->getISBN());
    EXPECT_NO_THROW(book->getTitle());
    EXPECT_NO_THROW(book->getMetadata());
    EXPECT_NO_THROW(book->getPhysicalProperties());
    EXPECT_NO_THROW(book->getGenre());
    EXPECT_NO_THROW(book->getStatistics());
}

TEST(BookTest, InvalidBookCreation) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    
    // Negative price
    EXPECT_THROW(auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        -10.0
    ), DataValidationException);
    
    // Null publisher
    EXPECT_THROW(auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        nullptr,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    ), DataValidationException);
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
    
    // Edge cases for discount
    book->applyDiscount(0); // 0% discount
    EXPECT_DOUBLE_EQ(book->getPrice(), 50.0);
    
    book->applyDiscount(100); // 100% discount (free)
    EXPECT_DOUBLE_EQ(book->getPrice(), 0.0);
    
    EXPECT_THROW(book->setPrice(-10), DataValidationException);
    EXPECT_THROW(book->applyDiscount(-10), DataValidationException);
    EXPECT_THROW(book->applyDiscount(110), DataValidationException);
}

TEST(BookTest, SeriesOperations) {
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
    
    // Initially no series
    EXPECT_EQ(book->getSeries(), nullptr);
    
    // Set series
    auto series = std::make_shared<BookSeries>("Test Series", "Desc", 5, 2020, 2024);
    book->setSeries(series);
    EXPECT_EQ(book->getSeries(), series);
    
    // Remove series
    book->setSeries(nullptr);
    EXPECT_EQ(book->getSeries(), nullptr);
}

TEST(BookTest, ConditionOperations) {
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
    
    EXPECT_TRUE(book->getCondition().isNew());
    
    book->setCondition(BookCondition(BookCondition::Condition::GOOD));
    EXPECT_FALSE(book->getCondition().isNew());
    EXPECT_TRUE(book->getCondition().isUsed());
}

TEST(BookTest, ReviewsManagement) {
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
    auto review3 = std::make_shared<BookReview>("Bob", "Average", "OK book", 3, "2024-01-17");
    
    // Add reviews
    book->addReview(review1);
    book->addReview(review2);
    book->addReview(review3);
    
    EXPECT_EQ(book->getReviewCount(), 3);
    EXPECT_DOUBLE_EQ(book->getAverageRating(), 4.0); // (4+5+3)/3 = 4.0
    EXPECT_EQ(book->getReviews().size(), 3);
    
    // Test highly rated
    EXPECT_TRUE(book->isHighlyRated());
    
    // Remove review
    book->removeReview(review3);
    EXPECT_EQ(book->getReviewCount(), 2);
    EXPECT_DOUBLE_EQ(book->getAverageRating(), 4.5); // (4+5)/2 = 4.5
    
    // Test removing non-existent review
    book->removeReview(review3); // Should not throw or affect anything
    EXPECT_EQ(book->getReviewCount(), 2);
    
    // Test adding null review
    EXPECT_THROW(book->addReview(nullptr), DataValidationException);
}

TEST(BookTest, BookInfoMethods) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "Subtitle", "EN"),
        BookMetadata(2024, "EN", 1, "Description"),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    
    // Test getFullInfo
    std::string fullInfo = book->getFullInfo();
    EXPECT_FALSE(fullInfo.empty());
    EXPECT_NE(fullInfo.find("Test Book"), std::string::npos);
    EXPECT_NE(fullInfo.find("978-3-161-48410-0"), std::string::npos);
    
    // Test getShortInfo
    std::string shortInfo = book->getShortInfo();
    EXPECT_FALSE(shortInfo.empty());
    EXPECT_NE(shortInfo.find("Test Book"), std::string::npos);
    EXPECT_NE(shortInfo.find("978-3-161-48410-0"), std::string::npos);
    
    // Test with series
    auto series = std::make_shared<BookSeries>("Series", "Desc", 3, 2020, 2024);
    book->setSeries(series);
    fullInfo = book->getFullInfo();
    EXPECT_NE(fullInfo.find("Series"), std::string::npos);
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
    
    EXPECT_EQ(*book1, *book2); // Same ISBN
    EXPECT_NE(*book1, *book3); // Different ISBN
    
    // Self-equality
    EXPECT_EQ(*book1, *book1);
    EXPECT_EQ(*book2, *book2);
    EXPECT_EQ(*book3, *book3);
}

TEST(BookTest, BestsellerStatus) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    
    // Create book with bestseller statistics
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Bestseller", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    
    // Add enough reviews to make it highly rated
    for (int i = 0; i < 10; i++) {
        auto review = std::make_shared<BookReview>(
            "Reader " + std::to_string(i), "Great", "Awesome", 5, "2024-01-15"
        );
        book->addReview(review);
    }
    
    EXPECT_TRUE(book->isHighlyRated());
    // Note: isBestseller depends on sales count which we can't directly set
    // This would require additional methods in Book to update statistics
}

// ==================== BookCollection Tests (Extended) ====================
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
    EXPECT_EQ(collection.getBookCount(), 0);
    
    collection.addBook(book1);
    collection.addBook(book2);
    
    EXPECT_FALSE(collection.isEmpty());
    EXPECT_EQ(collection.getBookCount(), 2);
    EXPECT_TRUE(collection.containsBook(book1));
    EXPECT_TRUE(collection.containsBook(book2));
    
    collection.removeBook(book1);
    EXPECT_EQ(collection.getBookCount(), 1);
    EXPECT_FALSE(collection.containsBook(book1));
    EXPECT_TRUE(collection.containsBook(book2));
    
    // Test getInfo
    std::string info = collection.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("My Books"), std::string::npos);
    EXPECT_NE(info.find("Science"), std::string::npos);
}

TEST(BookCollectionTest, InvalidCollection) {
    // Invalid name
    EXPECT_THROW(BookCollection collection("", "Desc", "Category"), DataValidationException);
    EXPECT_THROW(BookCollection collection("   ", "Desc", "Category"), DataValidationException);
    
    // Invalid category
    EXPECT_THROW(BookCollection collection("Valid", "Desc", ""), DataValidationException);
    EXPECT_THROW(BookCollection collection("Valid", "Desc", "   "), DataValidationException);
    
    // Long description
    std::string longDesc(501, 'a');
    EXPECT_THROW(BookCollection collection("Valid", longDesc, "Category"), DataValidationException);
    
    // Long name/category
    std::string longName(101, 'a');
    EXPECT_THROW(BookCollection collection(longName, "Desc", "Category"), DataValidationException);
    EXPECT_THROW(BookCollection collection("Valid", "Desc", longName), DataValidationException);
}

TEST(BookCollectionTest, DuplicateAndNullBook) {
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
    
    // Duplicate book
    EXPECT_THROW(collection.addBook(book), DuplicateBookException);
    
    // Null book
    EXPECT_THROW(collection.addBook(nullptr), DataValidationException);
}

TEST(BookCollectionTest, RemoveNonExistentBook) {
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
    
    // Remove book that doesn't exist (should not throw)
    EXPECT_NO_THROW(collection.removeBook(book));
    
    // Add and then remove
    collection.addBook(book);
    EXPECT_EQ(collection.getBookCount(), 1);
    collection.removeBook(book);
    EXPECT_EQ(collection.getBookCount(), 0);
    
    // Remove again (should not throw)
    EXPECT_NO_THROW(collection.removeBook(book));
}

TEST(BookCollectionTest, EqualityAndInequality) {
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
    
    BookCollection coll1("Same", "Desc", "Category");
    BookCollection coll2("Same", "Desc", "Category");
    BookCollection coll3("Different", "Desc", "Category");
    BookCollection coll4("Same", "Different", "Category");
    BookCollection coll5("Same", "Desc", "Different");
    
    // Add same book to both collections
    coll1.addBook(book1);
    coll2.addBook(book1);
    
    EXPECT_EQ(coll1, coll2);
    EXPECT_NE(coll1, coll3);
    EXPECT_NE(coll1, coll4);
    EXPECT_NE(coll1, coll5);
    
    // Test with different books
    BookCollection coll6("Same", "Desc", "Category");
    EXPECT_NE(coll1, coll6); // Different books
    
    // Self-equality
    EXPECT_EQ(coll1, coll1);
    EXPECT_EQ(coll2, coll2);
}

// ==================== Integration Test (Extended) ====================
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
    
    // Test full info
    std::string fullInfo = book->getFullInfo();
    EXPECT_NE(fullInfo.find("Dragon Quest"), std::string::npos);
    EXPECT_NE(fullInfo.find("Fantasy"), std::string::npos);
    
    // Test collection info
    std::string collInfo = collection.getInfo();
    EXPECT_NE(collInfo.find("Bestsellers"), std::string::npos);
    EXPECT_NE(collInfo.find("Fantasy"), std::string::npos);
}

// ==================== Edge Cases and Boundary Tests ====================
TEST(EdgeCasesTest, BoundaryValues) {
    // Test minimum and maximum allowed values
    
    // BookTitle boundaries
    std::string minTitle(1, 'a');
    std::string maxTitle(128, 'a');
    EXPECT_NO_THROW(BookTitle title(minTitle, "", "EN"));
    EXPECT_NO_THROW(BookTitle title(maxTitle, "", "EN"));
    
    // BookMetadata boundaries
    EXPECT_NO_THROW(BookMetadata metadata(1400, "EN", 1, ""));
    EXPECT_NO_THROW(BookMetadata metadata(2025, "EN", 1, ""));
    
    // PhysicalProperties boundaries
    EXPECT_NO_THROW(PhysicalProperties props(1, 1, 1, 1, 1, 
                                           PhysicalProperties::CoverType::PAPERBACK, "Paper"));
    EXPECT_NO_THROW(PhysicalProperties props(5000, 500, 500, 500, 5000, 
                                           PhysicalProperties::CoverType::HARDCOVER, "Hardcover"));
    
    // BookReview boundaries
    EXPECT_NO_THROW(BookReview review("A", "T", "Text", 1, "2024-01-01"));
    EXPECT_NO_THROW(BookReview review("A", "T", "Text", 5, "2024-01-01"));
}

TEST(EdgeCasesTest, ZeroAndNegativeCases) {
    // Test that appropriate exceptions are thrown for invalid values
    
    // ISBN with empty string
    EXPECT_THROW(ISBN isbn(""), InvalidISBNException);
    
    // BookTitle with only spaces
    EXPECT_THROW(BookTitle title("   ", "", "EN"), DataValidationException);
    
    // BookMetadata with invalid years
    EXPECT_THROW(BookMetadata metadata(1399, "EN", 1, ""), DataValidationException);
    EXPECT_THROW(BookMetadata metadata(2026, "EN", 1, ""), DataValidationException);
    
    // PhysicalProperties with zeros and negatives
    EXPECT_THROW(PhysicalProperties props(0, 200, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    EXPECT_THROW(PhysicalProperties props(300, 0, 130, 20, 250, 
                                        PhysicalProperties::CoverType::PAPERBACK, "Paper"), 
                 DataValidationException);
    
    // BookReview with invalid ratings
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 0, "2024-01-15"), DataValidationException);
    EXPECT_THROW(BookReview review("Author", "Title", "Text", 6, "2024-01-15"), DataValidationException);
}

// ==================== Performance and Stress Tests ====================
TEST(PerformanceTest, LargeNumberOfReviews) {
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
    
    // Add many reviews
    for (int i = 0; i < 100; i++) {
        auto review = std::make_shared<BookReview>(
            "Reader " + std::to_string(i), 
            "Review " + std::to_string(i), 
            "Text " + std::to_string(i), 
            3 + (i % 3), // Ratings between 3-5
            "2024-01-15"
        );
        book->addReview(review);
    }
    
    EXPECT_EQ(book->getReviewCount(), 100);
    EXPECT_GE(book->getAverageRating(), 3.0);
    EXPECT_LE(book->getAverageRating(), 5.0);
}

TEST(PerformanceTest, LargeCollection) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    BookCollection collection("Large Collection", "Many books", "Various");
    
    // Add many books to collection
    for (int i = 0; i < 50; i++) {
        auto book = std::make_shared<Book>(
            ISBN("9783161484100"),
            BookTitle("Book " + std::to_string(i), "", "EN"),
            BookMetadata(2024, "EN", 1, ""),
            PhysicalProperties(300, 200, 130, 20, 250, 
                             PhysicalProperties::CoverType::PAPERBACK, "Paper"),
            Genre(Genre::Type::SCIENCE_FICTION),
            publisher,
            BookCondition(BookCondition::Condition::NEW),
            19.99 + i
        );
        collection.addBook(book);
    }
    
    EXPECT_EQ(collection.getBookCount(), 50);
    EXPECT_FALSE(collection.isEmpty());
}