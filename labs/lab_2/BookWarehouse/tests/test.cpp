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

#include "warehouse/Delivery.hpp"
#include "warehouse/InventoryItem.hpp"
#include "warehouse/InventoryReport.hpp"
#include "warehouse/Shelf.hpp"
#include "warehouse/StockMovement.hpp"
#include "warehouse/StockReceipt.hpp"
#include "warehouse/StockTransfer.hpp"
#include "warehouse/StockWriteOff.hpp"
#include "warehouse/StorageLocation.hpp"
#include "warehouse/Warehouse.hpp"
#include "warehouse/WarehouseManager.hpp"
#include "warehouse/WarehouseSection.hpp"

// ==================== WAREHOUSE MODULE TESTS ====================
// ==================== StorageLocation Tests ====================
TEST(StorageLocationTest, ValidLocation) {
    EXPECT_NO_THROW(StorageLocation location("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE));
    StorageLocation location("B-02-C-10", 50, 10, StorageLocation::LocationStatus::OCCUPIED);
    EXPECT_EQ(location.getLocationId(), "B-02-C-10");
    EXPECT_EQ(location.getCapacity(), 50);
    EXPECT_EQ(location.getCurrentLoad(), 10);
    EXPECT_EQ(location.getAvailableSpace(), 40);
    EXPECT_FALSE(location.isEmpty());
    EXPECT_FALSE(location.isFull());
    EXPECT_TRUE(location.canAccommodate(30));
}

TEST(StorageLocationTest, InvalidLocation) {
    EXPECT_THROW(StorageLocation location("", 100, 0, StorageLocation::LocationStatus::FREE), DataValidationException);
    EXPECT_THROW(StorageLocation location("A-01", 100, 0, StorageLocation::LocationStatus::FREE), DataValidationException);
    EXPECT_THROW(StorageLocation location("A-01-B-05", 0, 0, StorageLocation::LocationStatus::FREE), DataValidationException);
    EXPECT_THROW(StorageLocation location("A-01-B-05", 100, -5, StorageLocation::LocationStatus::FREE), DataValidationException);
}

TEST(StorageLocationTest, BookOperations) {
    StorageLocation location("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
    location.addBooks(30);
    EXPECT_EQ(location.getCurrentLoad(), 30);
    EXPECT_EQ(location.getAvailableSpace(), 70);
    EXPECT_EQ(location.getStatus(), StorageLocation::LocationStatus::OCCUPIED);
    location.removeBooks(10);
    EXPECT_EQ(location.getCurrentLoad(), 20);
    EXPECT_EQ(location.getAvailableSpace(), 80);
    EXPECT_THROW(location.addBooks(90), WarehouseException);
    EXPECT_THROW(location.removeBooks(30), WarehouseException);
}

TEST(StorageLocationTest, StatusManagement) {
    StorageLocation location("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
    location.setStatus(StorageLocation::LocationStatus::BLOCKED);
    EXPECT_EQ(location.getStatus(), StorageLocation::LocationStatus::BLOCKED);
    EXPECT_THROW(location.addBooks(10), WarehouseException);
    EXPECT_THROW(location.removeBooks(10), WarehouseException);
}

// ==================== Shelf Tests ====================
TEST(ShelfTest, ValidShelf) {
    EXPECT_NO_THROW(Shelf shelf("A-01", 10));
    Shelf shelf("B-05", 5);
    EXPECT_EQ(shelf.getShelfId(), "B-05");
    EXPECT_EQ(shelf.getMaxLocations(), 5);
    EXPECT_EQ(shelf.getCurrentLocationsCount(), 0);
    EXPECT_TRUE(shelf.hasAvailableSpace());
    EXPECT_TRUE(shelf.isEmpty());
}

TEST(ShelfTest, LocationManagement) {
    Shelf shelf("A-01", 3);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 50, 0, StorageLocation::LocationStatus::FREE);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 50, 0, StorageLocation::LocationStatus::FREE);
    shelf.addLocation(location1);
    shelf.addLocation(location2);
    EXPECT_EQ(shelf.getCurrentLocationsCount(), 2);
    EXPECT_TRUE(shelf.containsLocation("A-01-B-01"));
    EXPECT_EQ(shelf.findLocation("A-01-B-01"), location1);
    shelf.removeLocation("A-01-B-01");
    EXPECT_EQ(shelf.getCurrentLocationsCount(), 1);
    EXPECT_FALSE(shelf.containsLocation("A-01-B-01"));
}

TEST(ShelfTest, CapacityTracking) {
    Shelf shelf("A-01", 2);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 100, 30, StorageLocation::LocationStatus::OCCUPIED);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 100, 20, StorageLocation::LocationStatus::OCCUPIED);
    shelf.addLocation(location1);
    shelf.addLocation(location2);
    EXPECT_EQ(shelf.getTotalCapacity(), 200);
    EXPECT_EQ(shelf.getCurrentLoad(), 50);
    EXPECT_EQ(shelf.getAvailableSpace(), 150);
}

// ==================== WarehouseSection Tests ====================
TEST(WarehouseSectionTest, ValidSection) {
    EXPECT_NO_THROW(WarehouseSection section("A", "General Storage", "Main storage area", 
                                           WarehouseSection::SectionType::GENERAL, 20.0, 50.0));
    WarehouseSection section("B", "Refrigerated", "Cold storage", 
                           WarehouseSection::SectionType::REFRIGERATED, 5.0, 40.0);
    EXPECT_EQ(section.getSectionId(), "B");
    EXPECT_EQ(section.getName(), "Refrigerated");
    EXPECT_EQ(section.getSectionType(), WarehouseSection::SectionType::REFRIGERATED);
    EXPECT_DOUBLE_EQ(section.getTemperature(), 5.0);
    EXPECT_DOUBLE_EQ(section.getHumidity(), 40.0);
}

TEST(WarehouseSectionTest, ShelfManagement) {
    WarehouseSection section("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf1 = std::make_shared<Shelf>("A-01", 5);
    auto shelf2 = std::make_shared<Shelf>("A-02", 5);
    section.addShelf(shelf1);
    section.addShelf(shelf2);
    EXPECT_EQ(section.getShelvesCount(), 2);
    EXPECT_TRUE(section.containsShelf("A-01"));
    EXPECT_EQ(section.findShelf("A-01"), shelf1);
}

// ==================== Warehouse Tests ====================
TEST(WarehouseTest, ValidWarehouse) {
    EXPECT_NO_THROW(Warehouse warehouse("Main Warehouse", "123 Main St, City"));
    Warehouse warehouse("Distribution Center", "456 Oak Ave, Town");
    EXPECT_EQ(warehouse.getName(), "Distribution Center");
    EXPECT_EQ(warehouse.getAddress(), "456 Oak Ave, Town");
    EXPECT_EQ(warehouse.getSectionsCount(), 0);
    EXPECT_TRUE(warehouse.isEmpty());
}

TEST(WarehouseTest, SectionManagement) {
    Warehouse warehouse("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "Section A", "", WarehouseSection::SectionType::GENERAL);
    warehouse.addSection(section);
    EXPECT_EQ(warehouse.getSectionsCount(), 1);
    EXPECT_TRUE(warehouse.containsSection("A"));
    EXPECT_EQ(warehouse.findSection("A"), section);
    warehouse.removeSection("A");
    EXPECT_EQ(warehouse.getSectionsCount(), 0);
}

// ==================== InventoryItem Tests ====================
TEST(InventoryItemTest, ValidInventoryItem) {
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
    auto location = std::make_shared<StorageLocation>("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
    EXPECT_NO_THROW(InventoryItem item(book, 50, location, "2024-01-15"));
    InventoryItem item(book, 25, location, "2024-01-20");
    EXPECT_EQ(item.getBook(), book);
    EXPECT_EQ(item.getQuantity(), 25);
    EXPECT_EQ(item.getLocation(), location);
    EXPECT_TRUE(item.isInStock());
}

TEST(InventoryItemTest, QuantityOperations) {
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
    auto location = std::make_shared<StorageLocation>("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
    InventoryItem item(book, 10, location, "2024-01-15");
    item.increaseQuantity(5);
    EXPECT_EQ(item.getQuantity(), 15);
    item.decreaseQuantity(3);
    EXPECT_EQ(item.getQuantity(), 12);
    EXPECT_THROW(item.decreaseQuantity(20), WarehouseException);
}

// ==================== StockMovement Tests ====================
TEST(StockReceiptTest, ValidReceipt) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto location = std::make_shared<StorageLocation>("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
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
    auto receipt = std::make_shared<StockReceipt>(
        "REC-2024-001", "2024-01-15", "EMP-001", warehouse,
        "Test Supplier", "PO-2024-001", "INV-2024-001", 1000.0, "Test receipt"
    );
    auto inventoryItem = std::make_shared<InventoryItem>(book, 50, location, "2024-01-15");
    receipt->addAffectedItem(inventoryItem);
    EXPECT_EQ(receipt->getMovementId(), "REC-2024-001");
    EXPECT_EQ(receipt->getSupplierName(), "Test Supplier");
    EXPECT_DOUBLE_EQ(receipt->getTotalCost(), 1000.0);
    EXPECT_EQ(receipt->getAffectedItems().size(), 1);
}

// ==================== Delivery Tests ====================
TEST(DeliveryTest, ValidDelivery) {
    EXPECT_NO_THROW(
        Delivery delivery("DEL-2024-001", "Test Supplier", "2024-01-20", 
                         "TRK123456", "Fast Shipping", 150.0)
    );
    Delivery delivery("DEL-2024-002", "Book Distributor", "2024-01-25", 
                     "TRK789012", "Express Mail", 200.0);
    EXPECT_EQ(delivery.getDeliveryId(), "DEL-2024-002");
    EXPECT_EQ(delivery.getSupplierName(), "Book Distributor");
    EXPECT_EQ(delivery.getCarrier(), "Express Mail");
    EXPECT_DOUBLE_EQ(delivery.getShippingCost(), 200.0);
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::SCHEDULED);
}

TEST(DeliveryTest, BookManagement) {
    Delivery delivery("DEL-2024-001", "Supplier", "2024-01-20", "TRK123", "Carrier", 100.0);
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
        ISBN("0306406152"),
        BookTitle("Book 2", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        24.99
    );
    delivery.addBook(book1);
    delivery.addBook(book2);
    EXPECT_EQ(delivery.getBookCount(), 2);
    EXPECT_TRUE(delivery.containsBook(book1));
    delivery.removeBook(book1);
    EXPECT_EQ(delivery.getBookCount(), 1);
}

// ==================== WarehouseManager Tests ====================
TEST(WarehouseManagerTest, BasicOperations) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    WarehouseManager manager(warehouse);
    EXPECT_EQ(manager.getWarehouse(), warehouse);
    auto newWarehouse = std::make_shared<Warehouse>("New Warehouse", "New Address");
    manager.setWarehouse(newWarehouse);
    EXPECT_EQ(manager.getWarehouse(), newWarehouse);
}

// ==================== InventoryReport Tests ====================
TEST(InventoryReportTest, ReportGeneration) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    InventoryReport report(warehouse);
    EXPECT_EQ(report.getWarehouse(), warehouse);
    auto fullReport = report.generateFullReport();
    EXPECT_FALSE(fullReport.empty());
    auto capacityReport = report.generateCapacityReport();
    EXPECT_FALSE(capacityReport.empty());
}

// ==================== Integration Test ====================
TEST(WarehouseIntegrationTest, CompleteWarehouseFlow) {
    auto warehouse = std::make_shared<Warehouse>("Main Distribution", "123 Warehouse Rd");
    auto section = std::make_shared<WarehouseSection>("A", "General Storage", "", WarehouseSection::SectionType::GENERAL);
    warehouse->addSection(section);
    auto shelf = std::make_shared<Shelf>("A-01", 5);
    section->addShelf(shelf);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location1);
    shelf->addLocation(location2);
    auto publisher = std::make_shared<Publisher>("Book House", "contact@bookhouse.com", 1995);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Advanced C++", "Modern Programming", "EN"),
        BookMetadata(2024, "EN", 1, "C++ programming guide"),
        PhysicalProperties(500, 230, 160, 35, 400, 
                         PhysicalProperties::CoverType::HARDCOVER, "Hardcover"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        49.99
    );
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"),
        BookTitle("Algorithms", "Data Structures", "EN"),
        BookMetadata(2023, "EN", 2, "Algorithm reference"),
        PhysicalProperties(450, 220, 150, 30, 350, 
                         PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        publisher,
        BookCondition(BookCondition::Condition::NEW),
        39.99
    );
    auto item1 = std::make_shared<InventoryItem>(book1, 50, location1, "2024-01-15");
    auto item2 = std::make_shared<InventoryItem>(book2, 30, location2, "2024-01-15");
    warehouse->addInventoryItem(item1);
    warehouse->addInventoryItem(item2);
    EXPECT_FALSE(warehouse->isEmpty());
    EXPECT_EQ(warehouse->getCurrentLoad(), 80);
    EXPECT_TRUE(warehouse->isBookInStock("9783161484100"));
    EXPECT_EQ(warehouse->getBookTotalQuantity("9783161484100"), 50);
    WarehouseManager manager(warehouse);
    InventoryReport reporter(warehouse); 
    auto stockInfo = manager.getBookStockInfo("9783161484100");
    auto utilizationReport = manager.getWarehouseUtilizationReport();
    EXPECT_FALSE(stockInfo.empty());
    EXPECT_FALSE(utilizationReport.empty());
    EXPECT_TRUE(manager.isBookAvailable("9783161484100", 25));
    EXPECT_FALSE(manager.isBookAvailable("9783161484100", 60));
}

#include "persons/Person.hpp"
#include "persons/Address.hpp"
#include "persons/ContactInfo.hpp"
#include "persons/CustomerCategory.hpp"
#include "persons/EmployeeRole.hpp"
#include "persons/Customer.hpp"
#include "persons/Employee.hpp"
#include "persons/UserAccount.hpp"

// ==================== PERSONS MODULE TESTS ====================
// ==================== Address Tests ====================
TEST(AddressTest, ValidAddress) {
    EXPECT_NO_THROW(Address addr("123 Main St", "Springfield", "12345", "USA"));
    Address addr("456 Oak Ave", "Shelbyville", "67890", "Canada");
    EXPECT_EQ(addr.getStreet(), "456 Oak Ave");
    EXPECT_EQ(addr.getCity(), "Shelbyville");
    EXPECT_EQ(addr.getPostalCode(), "67890");
    EXPECT_EQ(addr.getCountry(), "Canada");
    EXPECT_TRUE(addr.isComplete());
    EXPECT_EQ(addr.getFullAddress(), "456 Oak Ave, Shelbyville, 67890, Canada");
}

TEST(AddressTest, InvalidAddress) {
    EXPECT_THROW(Address addr("", "City", "12345", "USA"), DataValidationException);
    EXPECT_THROW(Address addr("Valid", "", "12345", "USA"), DataValidationException);
    EXPECT_THROW(Address addr("Valid", "City", "", "USA"), DataValidationException);
    EXPECT_THROW(Address addr("Valid", "City", "12345", ""), DataValidationException);
}

TEST(AddressTest, AddressOperations) {
    Address addr("123 Main St", "Springfield", "12345", "USA");
    addr.setStreet("456 Oak Ave");
    addr.setCity("Shelbyville");
    addr.setPostalCode("67890");
    addr.setCountry("Canada");
    EXPECT_EQ(addr.getStreet(), "456 Oak Ave");
    EXPECT_EQ(addr.getCity(), "Shelbyville");
    EXPECT_EQ(addr.getFullAddress(), "456 Oak Ave, Shelbyville, 67890, Canada");
}

// ==================== ContactInfo Tests ====================
TEST(ContactInfoTest, ValidContactInfo) {
    EXPECT_NO_THROW(ContactInfo info("john@test.com", "+1234567890", "john2@test.com", "+0987654321"));
    ContactInfo info("jane@test.com", "+1112223333");
    EXPECT_EQ(info.getEmail(), "jane@test.com");
    EXPECT_EQ(info.getPhoneNumber(), "+1112223333");
    EXPECT_TRUE(info.hasValidContact());
    EXPECT_TRUE(info.hasEmail());
    EXPECT_TRUE(info.hasPhoneNumber());
    EXPECT_EQ(info.getPrimaryContact(), "jane@test.com");
}

TEST(ContactInfoTest, InvalidContactInfo) {
    EXPECT_THROW(ContactInfo info("invalid-email", "+1234567890"), DataValidationException);
    EXPECT_THROW(ContactInfo info("valid@test.com", "short"), DataValidationException);
    EXPECT_THROW(ContactInfo info("valid@test.com", "+1234567890", "invalid", "+0987654321"), DataValidationException);
}

TEST(ContactInfoTest, ContactOperations) {
    ContactInfo info("initial@test.com", "+1111111111");
    info.setEmail("new@test.com");
    info.setPhoneNumber("+2222222222");
    info.setSecondaryEmail("secondary@test.com");
    info.setSecondaryPhone("+3333333333");
    EXPECT_EQ(info.getEmail(), "new@test.com");
    EXPECT_EQ(info.getSecondaryEmail(), "secondary@test.com");
    EXPECT_EQ(info.getInfo(), "Primary: new@test.com, Secondary Email: secondary@test.com, Secondary Phone: +3333333333");
}

// ==================== CustomerCategory Tests ====================
TEST(CustomerCategoryTest, CategoryTypes) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    CustomerCategory student(CustomerCategory::Category::STUDENT);
    EXPECT_EQ(regular.toString(), "Regular");
    EXPECT_EQ(gold.toString(), "Gold");
    EXPECT_EQ(student.toString(), "Student");
    EXPECT_DOUBLE_EQ(regular.getDiscountPercentage(), 0.0);
    EXPECT_DOUBLE_EQ(gold.getDiscountPercentage(), 10.0);
    EXPECT_DOUBLE_EQ(student.getDiscountPercentage(), 10.0);
    EXPECT_FALSE(regular.hasFreeShipping());
    EXPECT_TRUE(gold.hasFreeShipping());
    EXPECT_FALSE(student.hasFreeShipping());
    EXPECT_FALSE(regular.isEligibleForLoyaltyProgram());
    EXPECT_TRUE(gold.isEligibleForLoyaltyProgram());
}

TEST(CustomerCategoryTest, UpgradeLogic) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory silver(CustomerCategory::Category::SILVER);
    EXPECT_TRUE(regular.canUpgrade(1500.0));
    EXPECT_FALSE(regular.canUpgrade(500.0));
    EXPECT_TRUE(silver.canUpgrade(6000.0));
    EXPECT_FALSE(silver.canUpgrade(4000.0));
    EXPECT_EQ(regular.getNextCategory(), CustomerCategory::Category::SILVER);
    EXPECT_EQ(silver.getNextCategory(), CustomerCategory::Category::GOLD);
}

// ==================== EmployeeRole Tests ====================
TEST(EmployeeRoleTest, RolePermissions) {
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    EXPECT_EQ(worker.toString(), "Warehouse Worker");
    EXPECT_EQ(manager.toString(), "Inventory Manager");
    EXPECT_FALSE(worker.canManageInventory());
    EXPECT_TRUE(manager.canManageInventory());
    EXPECT_TRUE(admin.canManageInventory());
    EXPECT_FALSE(worker.canManageUsers());
    EXPECT_FALSE(manager.canManageUsers());
    EXPECT_TRUE(admin.canManageUsers());
    EXPECT_DOUBLE_EQ(worker.getSalaryMultiplier(), 1.0);
    EXPECT_DOUBLE_EQ(manager.getSalaryMultiplier(), 1.5);
    EXPECT_DOUBLE_EQ(admin.getSalaryMultiplier(), 2.0);
}

TEST(EmployeeRoleTest, AccessLevels) {
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    EmployeeRole supervisor(EmployeeRole::Role::SUPERVISOR);
    EmployeeRole hr(EmployeeRole::Role::HR_MANAGER);
    EXPECT_EQ(cashier.getAccessLevel(), 2);
    EXPECT_EQ(supervisor.getAccessLevel(), 6);
    EXPECT_EQ(hr.getAccessLevel(), 7);
    EXPECT_TRUE(cashier.canProcessSales());
    EXPECT_TRUE(supervisor.canProcessSales());
    EXPECT_FALSE(hr.canProcessSales());
}

// ==================== Person Tests ====================
TEST(PersonTest, ValidPerson) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("john@test.com", "+1234567890");
    EXPECT_NO_THROW(Person person("P001", "John", "Doe", "1990-05-15", address, contact));
    Person person("P002", "Jane", "Smith", "1985-08-20", address, contact);
    EXPECT_EQ(person.getId(), "P002");
    EXPECT_EQ(person.getFullName(), "Jane Smith");
    EXPECT_EQ(person.getDateOfBirth(), "1985-08-20");
    EXPECT_TRUE(person.isAdult());
    EXPECT_GT(person.calculateAge(), 25);
}

TEST(PersonTest, PersonOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person person("P003", "Bob", "Johnson", "2000-01-01", address, contact);
    person.setFirstName("Robert");
    person.setLastName("Johnsonson");
    auto newAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "Canada");
    person.setAddress(newAddress);
    EXPECT_EQ(person.getFirstName(), "Robert");
    EXPECT_EQ(person.getFullName(), "Robert Johnsonson");
    EXPECT_EQ(person.getAddress()->getCity(), "Shelbyville");
}

// ==================== Customer Tests ====================
TEST(CustomerTest, ValidCustomer) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    CustomerCategory category(CustomerCategory::Category::SILVER);
    EXPECT_NO_THROW(
        Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                         "CUST001", category, "2024-01-15")
    );
    Customer customer("P002", "Jane", "Smith", "1985-08-20", address, contact,
                     "CUST002", category, "2024-01-16");
    EXPECT_EQ(customer.getCustomerId(), "CUST002");
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
    EXPECT_DOUBLE_EQ(customer.getTotalPurchases(), 0.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 0);
    EXPECT_TRUE(customer.isCustActive());
}

TEST(CustomerTest, CustomerOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                     "CUST001", regular, "2024-01-15");
    customer.addPurchase(100.0);
    customer.addLoyaltyPoints(50);
    EXPECT_DOUBLE_EQ(customer.getTotalPurchases(), 100.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 150); // 100 from purchase + 50 bonus
    customer.redeemLoyaltyPoints(30);
    EXPECT_EQ(customer.getLoyaltyPoints(), 120);
    EXPECT_THROW(customer.redeemLoyaltyPoints(200), InsufficientStockException);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    customer.setCategory(gold);
    EXPECT_DOUBLE_EQ(customer.calculateDiscount(), 10.0);
}

TEST(CustomerTest, CategoryUpgrade) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                     "CUST001", regular, "2024-01-15");
    customer.addPurchase(1500.0); // Above regular threshold (1000)
    EXPECT_TRUE(customer.isEligibleForUpgrade());
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
}

// ==================== Employee Tests ====================
TEST(EmployeeTest, ValidEmployee) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("employee@test.com", "+1234567890");
    EmployeeRole role(EmployeeRole::Role::WAREHOUSE_WORKER);
    EXPECT_NO_THROW(
        Employee employee("P001", "John", "Doe", "1990-05-15", address, contact,
                         "EMP001", role, "2024-01-15", 30000.0, "Warehouse")
    );
    Employee employee("P002", "Jane", "Smith", "1985-08-20", address, contact,
                     "EMP002", role, "2024-01-16", 35000.0, "Operations");
    EXPECT_EQ(employee.getEmployeeId(), "EMP002");
    EXPECT_EQ(employee.getRole().toString(), "Warehouse Worker");
    EXPECT_DOUBLE_EQ(employee.getBaseSalary(), 35000.0);
    EXPECT_EQ(employee.getDepartment(), "Operations");
    EXPECT_TRUE(employee.isEmplActive());
}

TEST(EmployeeTest, EmployeeOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    Employee employee("P001", "John", "Doe", "1990-05-15", address, contact,
                     "EMP001", worker, "2020-01-15", 30000.0, "Warehouse");
    EXPECT_GE(employee.calculateYearsOfService(), 4);
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 30000.0); // 30000 * 1.0    
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    employee.promote(manager, 45000.0);
    EXPECT_EQ(employee.getRole().toString(), "Inventory Manager");
    EXPECT_DOUBLE_EQ(employee.getBaseSalary(), 45000.0);
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 67500.0); // 45000 * 1.5
    EXPECT_TRUE(employee.canManageInventory());
    EXPECT_FALSE(employee.canManageUsers());
}

TEST(EmployeeTest, PermissionChecks) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    Employee cashierEmp("P001", "Cash", "Ier", "1995-01-01", address, contact,
                       "EMP001", cashier, "2024-01-15", 25000.0, "Sales");
    EXPECT_TRUE(cashierEmp.canProcessSales());
    EXPECT_FALSE(cashierEmp.canManageInventory());
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    Employee adminEmp("P002", "Admin", "User", "1980-01-01", address, contact,
                     "EMP002", admin, "2024-01-15", 60000.0, "IT");
    EXPECT_TRUE(adminEmp.canManageUsers());
    EXPECT_TRUE(adminEmp.canManageInventory());
}

// ==================== UserAccount Tests ====================
TEST(UserAccountTest, ValidUserAccount) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    EXPECT_NO_THROW(UserAccount account("johndoe", "SecurePass123", person));
    UserAccount account("janedoe", "StrongPass456", person);
    EXPECT_EQ(account.getUsername(), "janedoe");
    EXPECT_EQ(account.getPerson(), person);
    EXPECT_FALSE(account.isAccountLocked());
    EXPECT_EQ(account.getFailedLoginAttempts(), 0);
}

TEST(UserAccountTest, Authentication) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    UserAccount account("testuser", "MyPassword123", person);
    EXPECT_TRUE(account.authenticate("MyPassword123"));
    EXPECT_THROW(account.authenticate("wrongpassword"), AuthenticationException);
    for (int i = 0; i < 4; i++) {
        EXPECT_THROW(account.authenticate("wrong"), AuthenticationException);
    }
    EXPECT_THROW(account.authenticate("wrong"), AuthenticationException); // 5th attempt
    EXPECT_TRUE(account.isAccountLocked());
    EXPECT_THROW(account.authenticate("MyPassword123"), AuthenticationException);
    account.unlockAccount();
    EXPECT_FALSE(account.isAccountLocked());
    EXPECT_TRUE(account.authenticate("MyPassword123")); // Should work after unlock
}

TEST(UserAccountTest, PasswordManagement) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    UserAccount account("testuser", "OldPassword123", person);
    account.changePassword("OldPassword123", "NewPassword456");
    EXPECT_TRUE(account.authenticate("NewPassword456"));
    EXPECT_THROW(account.authenticate("OldPassword123"), AuthenticationException);
    EXPECT_THROW(account.changePassword("wrongold", "NewPass"), AuthenticationException);
    EXPECT_THROW(account.changePassword("NewPassword456", "short"), DataValidationException);
    account.resetPassword("ResetPass123");
    EXPECT_TRUE(account.authenticate("ResetPass123"));
}

TEST(UserAccountTest, PasswordExpiry) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    UserAccount account("olduser", "Password123", person);
    EXPECT_FALSE(account.isPasswordExpired()); //false for new account
}

// ==================== Integration Tests ====================
TEST(PersonsIntegrationTest, CompletePersonSystem) {
    // Create address and contact
    auto address = std::make_shared<Address>("789 Business Blvd", "Metropolis", "54321", "USA");
    auto contact = std::make_shared<ContactInfo>("biz@company.com", "+1987654321");
    // Create person
    auto person = std::make_shared<Person>("P100", "Alice", "Wonderland", "1988-03-25", address, contact);
    // Create customer from person
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    Customer customer("P100", "Alice", "Wonderland", "1988-03-25", address, contact,
                     "CUST100", gold, "2024-01-01");
    // Create employee from same person
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    Employee employee("P100", "Alice", "Wonderland", "1988-03-25", address, contact,
                     "EMP100", manager, "2023-06-15", 50000.0, "Operations");
    // Create user account
    UserAccount account("alicew", "SecureAlice123", person);
    // Test customer operations
    customer.addPurchase(2000.0);
    customer.addLoyaltyPoints(100);
    EXPECT_DOUBLE_EQ(customer.calculateDiscount(), 10.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 2100);
    // Test employee operations
    EXPECT_TRUE(employee.canManageInventory());
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 75000.0); // 50000 * 1.5
    // Test authentication
    EXPECT_TRUE(account.authenticate("SecureAlice123"));
    EXPECT_EQ(account.getPerson()->getFullName(), "Alice Wonderland");
    // Verify all objects are properly linked
    EXPECT_EQ(customer.getFullName(), "Alice Wonderland");
    EXPECT_EQ(employee.getFullName(), "Alice Wonderland");
    EXPECT_EQ(account.getPerson()->getFullName(), "Alice Wonderland");
}

TEST(PersonsIntegrationTest, BusinessRules) {
    auto address = std::make_shared<Address>("123 Test St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person minor("PMIN", "Child", "Minor", "2010-01-01", address, contact);
    EXPECT_FALSE(minor.isAdult());
    Person adult("PADT", "Adult", "Person", "2000-01-01", address, contact);
    EXPECT_TRUE(adult.isAdult());
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("PCUST", "Test", "Customer", "1990-01-01", address, contact,
                     "CUST999", regular, "2024-01-01");
    customer.addPurchase(500.0);
    EXPECT_FALSE(customer.isEligibleForUpgrade());
    customer.addPurchase(600.0);
    EXPECT_TRUE(customer.isEligibleForUpgrade());
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
}

// ==================== Edge Case Tests ====================
TEST(PersonsEdgeCasesTest, BoundaryConditions) {
    auto address = std::make_shared<Address>("A", "B", "1", "C");
    auto contact = std::make_shared<ContactInfo>("a@b.c", "+1234567");
    EXPECT_NO_THROW(
        Person person("P1", "A", "B", "2000-01-01", address, contact)
    );
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P1", "A", "B", "2000-01-01", address, contact,
                     "C1", regular, "2024-01-01");
    customer.addPurchase(999999.99);
    EXPECT_DOUBLE_EQ(customer.getTotalPurchases(), 999999.99);
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EXPECT_NO_THROW(
        Employee employee("P1", "A", "B", "2000-01-01", address, contact,
                         "E1", worker, "2024-01-01", 0.0, "Dept")
    );
}

TEST(PersonsEdgeCasesTest, ErrorConditions) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EXPECT_THROW(
        Person person("", "John", "Doe", "1990-01-01", address, contact),
        DataValidationException
    );
    CustomerCategory platinum(CustomerCategory::Category::PLATINUM);
    Customer customer("P1", "John", "Doe", "1990-01-01", address, contact,
                     "C1", platinum, "2024-01-01");
    customer.addPurchase(100000.0);
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Platinum");
    auto person = std::make_shared<Person>("P1", "John", "Doe", "1990-01-01", address, contact);
    EXPECT_THROW(
        UserAccount account("user", "weak", person),
        DataValidationException
    );
}

// ==================== Performance Tests ====================
TEST(PersonsPerformanceTest, MultipleObjectCreation) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    for (int i = 0; i < 100; i++) {
        std::string id = "P" + std::to_string(i);
        EXPECT_NO_THROW(
            Person person(id, "First" + std::to_string(i), "Last" + std::to_string(i), 
                         "1990-01-01", address, contact)
        );
    }
}

#include "orders/OrderStatus.hpp"
#include "orders/OrderItem.hpp"
#include "orders/ShippingInfo.hpp"
#include "orders/Order.hpp"
#include "orders/CustomerOrder.hpp"
#include "orders/PurchaseOrder.hpp"
#include "orders/OrderManager.hpp"

// ==================== ORDERS MODULE TESTS ====================
// ==================== OrderStatus Tests ====================
TEST(OrderStatusTest, ValidStatusTransitions) {
    OrderStatus status(OrderStatus::Status::PENDING, "2024-01-15");
    EXPECT_TRUE(status.isValidTransition(OrderStatus::Status::CONFIRMED));
    EXPECT_TRUE(status.isValidTransition(OrderStatus::Status::CANCELLED));
    EXPECT_FALSE(status.isValidTransition(OrderStatus::Status::DELIVERED));
    EXPECT_TRUE(status.isActive());
    EXPECT_TRUE(status.isCancellable());
    EXPECT_TRUE(status.requiresAction());
}

TEST(OrderStatusTest, StatusUpdate) {
    OrderStatus status(OrderStatus::Status::PENDING, "2024-01-15");
    status.updateStatus(OrderStatus::Status::CONFIRMED, "2024-01-16");
    EXPECT_EQ(status.getStatus(), OrderStatus::Status::CONFIRMED);
    EXPECT_EQ(status.getStatusChangedDate(), "2024-01-16");
    EXPECT_THROW(status.updateStatus(OrderStatus::Status::DELIVERED, "2024-01-17"), InvalidOrderStateException);
}

TEST(OrderStatusTest, CompletedStatus) {
    OrderStatus delivered(OrderStatus::Status::DELIVERED, "2024-01-20");
    OrderStatus cancelled(OrderStatus::Status::CANCELLED, "2024-01-18");
    OrderStatus refunded(OrderStatus::Status::REFUNDED, "2024-01-25");
    EXPECT_TRUE(delivered.isCompleted());
    EXPECT_TRUE(cancelled.isCompleted());
    EXPECT_TRUE(refunded.isCompleted());
    EXPECT_FALSE(delivered.isActive());
}

// ==================== OrderItem Tests ====================
TEST(OrderItemTest, ValidOrderItem) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    
    EXPECT_NO_THROW(OrderItem item(book, 5, 25.0, 10.0));
    OrderItem item(book, 3, 20.0, 15.0);
    EXPECT_EQ(item.getBook(), book);
    EXPECT_EQ(item.getQuantity(), 3);
    EXPECT_DOUBLE_EQ(item.getUnitPrice(), 20.0);
    EXPECT_DOUBLE_EQ(item.getDiscountPercentage(), 15.0);
    EXPECT_DOUBLE_EQ(item.getDiscountedUnitPrice(), 17.0);
    EXPECT_DOUBLE_EQ(item.getTotalPrice(), 51.0);
    EXPECT_DOUBLE_EQ(item.getTotalDiscount(), 9.0);
    EXPECT_TRUE(item.hasDiscount());
}

TEST(OrderItemTest, InvalidOrderItem) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    
    EXPECT_THROW(OrderItem item(nullptr, 5, 25.0, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 0, 25.0, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 5, -10.0, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 5, 25.0, 150.0), DataValidationException);
}

// ==================== ShippingInfo Tests ====================
TEST(ShippingInfoTest, ValidShippingInfo) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    
    EXPECT_NO_THROW(ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::EXPRESS,
                                     "TRK123456", "Fast Delivery", 25.0, 5.0, "2024-01-20"));
    ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK789012", "Standard Mail", 10.0, 2.0);
    
    EXPECT_EQ(info.getCarrier(), "Standard Mail");
    EXPECT_DOUBLE_EQ(info.getTotalShippingCost(), 12.0);
    EXPECT_FALSE(info.isDelivered());
    EXPECT_FALSE(info.isInTransit());
    EXPECT_FALSE(info.requiresSignature());
}

TEST(ShippingInfoTest, ShippingStatusFlow) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::EXPRESS,
                     "TRK123456", "Fast Delivery", 50.0, 10.0);
    
    info.setStatus(ShippingInfo::ShippingStatus::IN_TRANSIT);
    EXPECT_TRUE(info.isInTransit());
    info.setActualDelivery("2024-01-18");
    EXPECT_TRUE(info.isDelivered());
    EXPECT_EQ(info.getActualDelivery(), "2024-01-18");
    EXPECT_EQ(info.getStatus(), ShippingInfo::ShippingStatus::DELIVERED);
}

// ==================== Order Tests ====================
TEST(OrderTest, BasicOrderOperations) {
    Order order("ORD-001", "2024-01-15", "Test order");
    EXPECT_EQ(order.getOrderId(), "ORD-001");
    EXPECT_EQ(order.getOrderDate(), "2024-01-15");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::PENDING);
    EXPECT_TRUE(order.isEmpty());
    EXPECT_TRUE(order.isCancellable());
    EXPECT_FALSE(order.isCompleted());
}

TEST(OrderTest, OrderItemManagement) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Book 1", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 20.0);
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"), BookTitle("Book 2", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 30.0);
    
    Order order("ORD-002", "2024-01-15");
    auto item1 = std::make_shared<OrderItem>(book1, 2, 20.0);
    auto item2 = std::make_shared<OrderItem>(book2, 1, 30.0, 10.0);
    
    order.addItem(item1);
    order.addItem(item2);
    EXPECT_EQ(order.getItemCount(), 2);
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 67.0);
    EXPECT_TRUE(order.containsBook("9783161484100"));
    EXPECT_EQ(order.getBookQuantity("9783161484100"), 2);
    
    order.removeItem(item1);
    EXPECT_EQ(order.getItemCount(), 1);
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 27.0);
}

TEST(OrderTest, OrderCancellation) {
    Order order("ORD-003", "2024-01-15");
    order.cancelOrder("2024-01-16");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::CANCELLED);
    EXPECT_TRUE(order.isCompleted());
    EXPECT_FALSE(order.isCancellable());
}

// ==================== CustomerOrder Tests ====================
TEST(CustomerOrderTest, CustomerOrderCreation) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::SILVER), "2024-01-01");
    
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    
    CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping);
    EXPECT_EQ(order.getCustomer(), customer);
    EXPECT_EQ(order.getShippingInfo(), shipping);
    EXPECT_DOUBLE_EQ(order.getCustomerDiscount(), 5.0);
}

TEST(CustomerOrderTest, OrderProcessingFlow) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01");
    
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    
    CustomerOrder order("CUST-ORD-002", "2024-01-15", customer, shipping);
    
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 50.0);
    auto item = std::make_shared<OrderItem>(book, 2, 50.0);
    order.addItem(item);
    
    order.processPayment("2024-01-16");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::CONFIRMED);
    EXPECT_DOUBLE_EQ(customer->getTotalPurchases(), 0.0);
    
    order.setStatus(OrderStatus::Status::PROCESSING, "2024-01-17");
    order.setStatus(OrderStatus::Status::READY_FOR_SHIPPING, "2024-01-17");
    order.shipOrder("2024-01-18");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::SHIPPED);
    
    order.deliverOrder("2024-01-20");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::DELIVERED);
    EXPECT_TRUE(order.isCompleted());
}

// ==================== PurchaseOrder Tests ====================
TEST(PurchaseOrderTest, PurchaseOrderCreation) {
    PurchaseOrder order("PURCH-001", "2024-01-15", "Book Supplier", "supplier@test.com", 
                       "2024-01-25", 25.0, "Test purchase");
    EXPECT_EQ(order.getSupplierName(), "Book Supplier");
    EXPECT_EQ(order.getSupplierContact(), "supplier@test.com");
    EXPECT_EQ(order.getExpectedDeliveryDate(), "2024-01-25");
    EXPECT_DOUBLE_EQ(order.getShippingCost(), 25.0);
    EXPECT_FALSE(order.isOrReceived());
}

TEST(PurchaseOrderTest, OverdueCheck) {
    PurchaseOrder order("PURCH-003", "2024-01-15", "Supplier", "contact@test.com", "2024-01-01");
    bool isOverdue = order.isOverdue();
    SUCCEED();
}

// ==================== OrderManager Tests ====================
TEST(OrderManagerTest, OrderManagerOperations) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    EXPECT_EQ(orderManager.getWarehouseManager(), warehouseManager);
    auto customerOrders = orderManager.getCustomerOrders();
    auto purchaseOrders = orderManager.getPurchaseOrders();
    EXPECT_TRUE(customerOrders.empty());
    EXPECT_TRUE(purchaseOrders.empty());
}

TEST(OrderManagerTest, CustomerOrderCreation) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01");
    
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    std::vector<std::shared_ptr<OrderItem>> items = {std::make_shared<OrderItem>(book, 2, 25.0)};
    
    try {
        auto order = orderManager.createCustomerOrder(customer, shipping, items, "Test order");
        EXPECT_EQ(order->getCustomer(), customer);
        EXPECT_EQ(order->getItemCount(), 1);
        auto foundOrder = orderManager.findCustomerOrder(order->getOrderId());
        EXPECT_EQ(foundOrder, order);
    } catch (const InsufficientStockException&) {
        SUCCEED();
    }
}

TEST(OrderManagerTest, PurchaseOrderCreation) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 15.0);
    std::vector<std::shared_ptr<OrderItem>> items = {std::make_shared<OrderItem>(book, 10, 15.0)};
    
    auto order = orderManager.createPurchaseOrder("Book Supplier", "supplier@test.com", 
                                                 "2024-01-25", items, 20.0, "Stock replenishment");
    EXPECT_EQ(order->getSupplierName(), "Book Supplier");
    EXPECT_DOUBLE_EQ(order->getTotalCost(), 170.0);
    auto foundOrder = orderManager.findPurchaseOrder(order->getOrderId());
    EXPECT_EQ(foundOrder, order);
}

// ==================== Integration Tests ====================
TEST(OrdersIntegrationTest, CompleteOrderWorkflow) {
    auto warehouse = std::make_shared<Warehouse>("Main Warehouse", "123 Warehouse St");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    
    auto address = std::make_shared<Address>("789 Customer Rd", "Customerville", "54321", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1987654321");
    auto customer = std::make_shared<Customer>("P100", "Alice", "Johnson", "1985-03-20", address, contact, "CUST100", 
                                              CustomerCategory(CustomerCategory::Category::GOLD), "2024-01-01");
    
    auto shippingAddr = std::make_shared<Address>("789 Customer Rd", "Customerville", "54321", "USA");
    auto returnAddr = std::make_shared<Address>("456 Business Ave", "Business City", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::EXPRESS,
                                                  "TRK987654", "Express Delivery", 25.0, 5.0);
    
    auto publisher = std::make_shared<Publisher>("Book House", "contact@bookhouse.com", 1995);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Advanced Programming", "", "EN"), BookMetadata(2024, "EN", 1, "Programming guide"),
        PhysicalProperties(500, 230, 160, 35, 400, PhysicalProperties::CoverType::HARDCOVER, "Hardcover"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 45.0);
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"), BookTitle("Data Structures", "", "EN"), BookMetadata(2023, "EN", 2, "Algorithm reference"),
        PhysicalProperties(450, 220, 150, 30, 350, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 35.0);
    
    std::vector<std::shared_ptr<OrderItem>> items = {
        std::make_shared<OrderItem>(book1, 1, 45.0, 10.0),
        std::make_shared<OrderItem>(book2, 2, 35.0)
    };
    
    try {
        auto order = orderManager.createCustomerOrder(customer, shipping, items, "Priority order");
        EXPECT_EQ(order->getItemCount(), 2);
        EXPECT_TRUE(order->qualifiesForFreeShipping());
        
        orderManager.processCustomerOrderPayment(order, "2024-01-16");
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::CONFIRMED);
        
        orderManager.fulfillCustomerOrder(order);
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::PROCESSING);
        
        order->setStatus(OrderStatus::Status::READY_FOR_SHIPPING, "2024-01-17");
        orderManager.shipCustomerOrder(order, "2024-01-18");
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::SHIPPED);
        
        EXPECT_GT(customer->getLoyaltyPoints(), 0);
        
        auto customerOrders = orderManager.getCustomerOrdersByCustomer("CUST100");
        EXPECT_FALSE(customerOrders.empty());
        
        auto shippedOrders = orderManager.getCustomerOrdersByStatus(OrderStatus::Status::SHIPPED);
        EXPECT_FALSE(shippedOrders.empty());
        
        auto stats = orderManager.getOrderStatistics();
        EXPECT_FALSE(stats.empty());
    } catch (const InsufficientStockException&) {
        SUCCEED();
    }
}

// ==================== Edge Case Tests ====================
TEST(OrdersEdgeCasesTest, BoundaryConditions) {
    Order emptyOrder("EMPTY-001", "2024-01-15");
    EXPECT_TRUE(emptyOrder.isEmpty());
    EXPECT_NO_THROW(emptyOrder.cancelOrder("2024-01-16"));
    
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 9999.0);
    
    EXPECT_NO_THROW(OrderItem maxItem(book, 1000, 9999.0, 100.0));
    
    Order order("DUP-001", "2024-01-15");
    auto item1 = std::make_shared<OrderItem>(book, 1, 50.0);
    auto item2 = std::make_shared<OrderItem>(book, 2, 45.0);
    
    order.addItem(item1);
    EXPECT_THROW(order.addItem(item2), DuplicateBookException);
}

// ==================== Error Condition Tests ====================
TEST(OrdersErrorConditionsTest, InvalidOperations) {
    OrderStatus completed(OrderStatus::Status::DELIVERED, "2024-01-20");
    EXPECT_THROW(completed.updateStatus(OrderStatus::Status::PROCESSING, "2024-01-21"), InvalidOrderStateException);
    
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    
    EXPECT_THROW(orderManager.createCustomerOrder(nullptr, nullptr, {}, ""), DataValidationException);
    
    PurchaseOrder po("PO-001", "2024-01-15", "Supplier", "contact@test.com", "2024-01-20");
    EXPECT_FALSE(po.canBeReceived());
    EXPECT_THROW(po.receiveOrder("2024-01-18"), InvalidOrderStateException);
}