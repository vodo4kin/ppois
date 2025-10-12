#include <gtest/gtest.h>
#include <memory>
#include "exceptions/WarehouseExceptions.hpp"
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