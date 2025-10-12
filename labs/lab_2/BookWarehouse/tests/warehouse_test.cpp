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

TEST(StorageLocationTest, EdgeCases) {
    StorageLocation location("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
    EXPECT_TRUE(location.isEmpty());
    EXPECT_FALSE(location.isFull());
    
    location.addBooks(100);
    EXPECT_TRUE(location.isFull());
    EXPECT_FALSE(location.isEmpty());
    EXPECT_EQ(location.getAvailableSpace(), 0);
    
    location.removeBooks(100);
    EXPECT_TRUE(location.isEmpty());
    EXPECT_EQ(location.getStatus(), StorageLocation::LocationStatus::FREE);
}

TEST(StorageLocationTest, EqualityOperators) {
    StorageLocation loc1("A-01-B-05", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    StorageLocation loc2("A-01-B-05", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    StorageLocation loc3("B-02-C-10", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    
    EXPECT_TRUE(loc1 == loc2);
    EXPECT_FALSE(loc1 == loc3);
    EXPECT_TRUE(loc1 != loc3);
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

TEST(ShelfTest, InvalidShelf) {
    EXPECT_THROW(Shelf shelf("", 10), DataValidationException);
    EXPECT_THROW(Shelf shelf("A1", 10), DataValidationException);
    EXPECT_THROW(Shelf shelf("A-01", 0), DataValidationException);
    EXPECT_THROW(Shelf shelf("A-01", 1000), DataValidationException);
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

TEST(ShelfTest, LocationQueries) {
    Shelf shelf("A-01", 3);
    auto loc1 = std::make_shared<StorageLocation>("A-01-B-01", 50, 0, StorageLocation::LocationStatus::FREE);
    auto loc2 = std::make_shared<StorageLocation>("A-01-B-02", 50, 50, StorageLocation::LocationStatus::OCCUPIED);
    shelf.addLocation(loc1);
    shelf.addLocation(loc2);
    
    auto available = shelf.getAvailableLocations();
    auto occupied = shelf.getOccupiedLocations();
    
    EXPECT_EQ(available.size(), 1);
    EXPECT_EQ(occupied.size(), 1);
    EXPECT_EQ(available[0]->getLocationId(), "A-01-B-01");
    EXPECT_EQ(occupied[0]->getLocationId(), "A-01-B-02");
}

TEST(ShelfTest, FullAndEmptyStates) {
    Shelf shelf("A-01", 2);
    EXPECT_TRUE(shelf.isEmpty());
    EXPECT_FALSE(shelf.isFull());
    
    auto loc1 = std::make_shared<StorageLocation>("A-01-B-01", 100, 100, StorageLocation::LocationStatus::OCCUPIED);
    auto loc2 = std::make_shared<StorageLocation>("A-01-B-02", 100, 100, StorageLocation::LocationStatus::OCCUPIED);
    shelf.addLocation(loc1);
    shelf.addLocation(loc2);
    
    EXPECT_TRUE(shelf.isFull());
    EXPECT_FALSE(shelf.isEmpty());
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

TEST(WarehouseSectionTest, InvalidSection) {
    EXPECT_THROW(WarehouseSection section("", "Test", "", WarehouseSection::SectionType::GENERAL), DataValidationException);
    EXPECT_THROW(WarehouseSection section("AA", "Test", "", WarehouseSection::SectionType::GENERAL), DataValidationException);
    EXPECT_THROW(WarehouseSection section("A", "", "", WarehouseSection::SectionType::GENERAL), DataValidationException);
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
    section.removeShelf("A-01");
    EXPECT_EQ(section.getShelvesCount(), 1);
    EXPECT_FALSE(section.containsShelf("A-01"));
}

TEST(WarehouseSectionTest, LocationFinding) {
    WarehouseSection section("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location);
    section.addShelf(shelf);
    
    EXPECT_EQ(section.findLocation("A-01-B-01"), location);
    EXPECT_EQ(section.findLocation("NONEXISTENT"), nullptr);
}

TEST(WarehouseSectionTest, CapacityAndLoad) {
    WarehouseSection section("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf1 = std::make_shared<Shelf>("A-01", 2);
    auto shelf2 = std::make_shared<Shelf>("A-02", 2);
    
    auto loc1 = std::make_shared<StorageLocation>("A-01-B-01", 100, 30, StorageLocation::LocationStatus::OCCUPIED);
    auto loc2 = std::make_shared<StorageLocation>("A-02-B-01", 100, 20, StorageLocation::LocationStatus::OCCUPIED);
    
    shelf1->addLocation(loc1);
    shelf2->addLocation(loc2);
    section.addShelf(shelf1);
    section.addShelf(shelf2);
    
    EXPECT_EQ(section.getTotalCapacity(), 200);
    EXPECT_EQ(section.getCurrentLoad(), 50);
    EXPECT_EQ(section.getAvailableSpace(), 150);
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

TEST(WarehouseTest, InvalidWarehouse) {
    EXPECT_THROW(Warehouse warehouse("", "Address"), DataValidationException);
    EXPECT_THROW(Warehouse warehouse("Name", ""), DataValidationException);
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

TEST(WarehouseTest, InventoryManagement) {
    Warehouse warehouse("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "Section A", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse.addSection(section);
    
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
    
    auto item = std::make_shared<InventoryItem>(book, 50, location, "2024-01-15");
    warehouse.addInventoryItem(item);
    
    EXPECT_FALSE(warehouse.isEmpty());
    EXPECT_EQ(warehouse.getBookTotalQuantity("9783161484100"), 50);
    EXPECT_TRUE(warehouse.isBookInStock("9783161484100"));
    
    auto foundItems = warehouse.findInventoryByBook("9783161484100");
    EXPECT_EQ(foundItems.size(), 1);
    
    warehouse.removeInventoryItem("9783161484100", "A-01-B-01");
    EXPECT_EQ(warehouse.getBookTotalQuantity("9783161484100"), 0);
}

TEST(WarehouseTest, CapacityAndUtilization) {
    Warehouse warehouse("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "Section A", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse.addSection(section);
    
    EXPECT_EQ(warehouse.getTotalCapacity(), 100);
    EXPECT_EQ(warehouse.getCurrentLoad(), 0);
    EXPECT_EQ(warehouse.getAvailableSpace(), 100);
    EXPECT_DOUBLE_EQ(warehouse.getUtilizationPercentage(), 0.0);
    
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
    
    auto item = std::make_shared<InventoryItem>(book, 75, location, "2024-01-15");
    warehouse.addInventoryItem(item);
    
    EXPECT_EQ(warehouse.getCurrentLoad(), 75);
    EXPECT_EQ(warehouse.getAvailableSpace(), 25);
    EXPECT_DOUBLE_EQ(warehouse.getUtilizationPercentage(), 75.0);
}

TEST(WarehouseTest, LocationFinding) {
    Warehouse warehouse("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "Section A", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse.addSection(section);
    
    auto availableLocations = warehouse.findAvailableLocations();
    EXPECT_EQ(availableLocations.size(), 1);
    
    auto optimalLocation = warehouse.findOptimalLocation(50, WarehouseSection::SectionType::GENERAL);
    EXPECT_NE(optimalLocation, nullptr);
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

TEST(InventoryItemTest, InvalidInventoryItem) {
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
    
    EXPECT_THROW(InventoryItem item(nullptr, 50, location, "2024-01-15"), DataValidationException);
    EXPECT_THROW(InventoryItem item(book, -5, location, "2024-01-15"), DataValidationException);
    EXPECT_THROW(InventoryItem item(book, 50, nullptr, "2024-01-15"), DataValidationException);
    EXPECT_THROW(InventoryItem item(book, 50, location, "invalid-date"), DataValidationException);
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
    EXPECT_THROW(item.increaseQuantity(-5), DataValidationException);
    EXPECT_THROW(item.decreaseQuantity(-5), DataValidationException);
}

TEST(InventoryItemTest, LocationManagement) {
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
    auto location1 = std::make_shared<StorageLocation>("A-01-B-05", 100, 0, StorageLocation::LocationStatus::FREE);
    auto location2 = std::make_shared<StorageLocation>("B-02-C-10", 100, 0, StorageLocation::LocationStatus::FREE);
    
    InventoryItem item(book, 10, location1, "2024-01-15");
    EXPECT_EQ(item.getLocation(), location1);
    
    item.setLocation(location2);
    EXPECT_EQ(item.getLocation(), location2);
    
    EXPECT_THROW(item.setLocation(nullptr), DataValidationException);
}

// ==================== StockMovement Tests ====================
TEST(StockMovementTest, ValidMovement) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    
    // Используем StockReceipt вместо StockMovement
    EXPECT_NO_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                       "Test Supplier", "PO-2024-001", "INV-2024-001", 1000.0, "Test notes"));
    
    StockReceipt receipt("REC-2024-002", "2024-01-16", "EMP-002", warehouse,
                       "Supplier", "PO-2024-002", "INV-2024-002", 1500.0, "Write-off notes");
    EXPECT_EQ(receipt.getMovementId(), "REC-2024-002");
    EXPECT_EQ(receipt.getMovementType(), StockMovement::MovementType::RECEIPT);
    EXPECT_EQ(receipt.getMovementDate(), "2024-01-16");
    EXPECT_EQ(receipt.getEmployeeId(), "EMP-002");
    EXPECT_EQ(receipt.getNotes(), "Write-off notes");
    EXPECT_TRUE(receipt.isPending());
}

TEST(StockMovementTest, InvalidMovement) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    
    // Тестируем через StockReceipt
    EXPECT_THROW(StockReceipt receipt("INVALID", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "invalid-date", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "INVALID", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", nullptr,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
}

TEST(StockMovementTest, StatusManagement) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    
    // Используем StockWriteOff для тестирования статусов
    StockWriteOff movement("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                         StockWriteOff::WriteOffReason::DAMAGED, "Test damage", "Test notes");
    
    EXPECT_TRUE(movement.isPending());
    EXPECT_TRUE(movement.isCancellable());
    
    movement.setStatus(StockMovement::MovementStatus::IN_PROGRESS);
    EXPECT_TRUE(movement.isCancellable());
    
    movement.setStatus(StockMovement::MovementStatus::COMPLETED);
    EXPECT_FALSE(movement.isCancellable());
    EXPECT_TRUE(movement.isCompleted());
}

TEST(StockMovementTest, ItemManagement) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    
    // Используем StockTransfer для тестирования управления элементами
    auto sourceLocation = std::make_shared<StorageLocation>("A-01-B-01", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    auto destLocation = std::make_shared<StorageLocation>("A-01-B-02", 100, 0, StorageLocation::LocationStatus::FREE);
    
    StockTransfer movement("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                         sourceLocation, destLocation, "Test transfer", "Test notes");
    
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
    auto item = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    
    movement.addAffectedItem(item);
    EXPECT_EQ(movement.getAffectedItems().size(), 1);
    
    movement.removeAffectedItem(item);
    EXPECT_EQ(movement.getAffectedItems().size(), 0);
    
    EXPECT_THROW(movement.addAffectedItem(nullptr), DataValidationException);
}

// ==================== StockReceipt Tests ====================
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

TEST(StockReceiptTest, InvalidReceipt) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    EXPECT_THROW(StockReceipt receipt("INVALID", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "INVALID", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INVALID", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", -100.0), DataValidationException);
}

TEST(StockReceiptTest, AverageCostCalculation) {
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
    
    StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                       "Test Supplier", "PO-2024-001", "INV-2024-001", 1000.0, "Test receipt");
    
    auto item1 = std::make_shared<InventoryItem>(book, 25, location, "2024-01-15");
    auto item2 = std::make_shared<InventoryItem>(book, 25, location, "2024-01-15");
    
    receipt.addAffectedItem(item1);
    receipt.addAffectedItem(item2);
    
    EXPECT_DOUBLE_EQ(receipt.calculateAverageCost(), 20.0); // 1000 / 50
}

// ==================== StockTransfer Tests ====================
TEST(StockTransferTest, ValidTransfer) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto sourceLocation = std::make_shared<StorageLocation>("A-01-B-01", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    auto destLocation = std::make_shared<StorageLocation>("A-01-B-02", 100, 0, StorageLocation::LocationStatus::FREE);
    
    EXPECT_NO_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                         sourceLocation, destLocation, "Reorganization", "Test transfer"));
    
    StockTransfer transfer("TRF-2024-002", "2024-01-16", "EMP-002", warehouse,
                         sourceLocation, destLocation, "Restocking", "");
    EXPECT_EQ(transfer.getMovementId(), "TRF-2024-002");
    EXPECT_EQ(transfer.getTransferReason(), "Restocking");
    EXPECT_EQ(transfer.getSourceLocation(), sourceLocation);
    EXPECT_EQ(transfer.getDestinationLocation(), destLocation);
}

TEST(StockTransferTest, InvalidTransfer) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      nullptr, location, "Reason", ""), DataValidationException);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      location, nullptr, "Reason", ""), DataValidationException);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      location, location, "Reason", ""), DataValidationException);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      location, location, "", ""), DataValidationException);
}

TEST(StockTransferTest, TransferProperties) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto sourceLocation = std::make_shared<StorageLocation>("A-01-B-01", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    auto destLocation = std::make_shared<StorageLocation>("B-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    
    StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                         sourceLocation, destLocation, "Reorganization", "");
    
    EXPECT_TRUE(transfer.isCrossSectionTransfer());
    EXPECT_TRUE(transfer.doesSourceHaveSufficientStock());
    EXPECT_TRUE(transfer.canDestinationAccommodate());
    
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
    
    auto item = std::make_shared<InventoryItem>(book, 30, sourceLocation, "2024-01-15");
    transfer.addAffectedItem(item);
    
    EXPECT_EQ(transfer.getTotalTransferQuantity(), 30);
}

// ==================== StockWriteOff Tests ====================
TEST(StockWriteOffTest, ValidWriteOff) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    
    EXPECT_NO_THROW(StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                                         StockWriteOff::WriteOffReason::DAMAGED, 
                                         "Water damage during storage", "Test write-off"));
    
    StockWriteOff writeOff("WO-2024-002", "2024-01-16", "EMP-002", warehouse,
                         StockWriteOff::WriteOffReason::EXPIRED, "Past shelf life", "");
    EXPECT_EQ(writeOff.getMovementId(), "WO-2024-002");
    EXPECT_EQ(writeOff.getReason(), StockWriteOff::WriteOffReason::EXPIRED);
    EXPECT_EQ(writeOff.getDetailedReason(), "Past shelf life");
}

TEST(StockWriteOffTest, InvalidWriteOff) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    
    EXPECT_THROW(StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      StockWriteOff::WriteOffReason::DAMAGED, "", ""), DataValidationException);
}

TEST(StockWriteOffTest, WriteOffProperties) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                         StockWriteOff::WriteOffReason::DAMAGED, "Water damage", "");
    
    EXPECT_TRUE(writeOff.isDueToDamage());
    EXPECT_FALSE(writeOff.isDueToExpiration());
    
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
    auto location = std::make_shared<StorageLocation>("A-01-B-05", 100, 50, StorageLocation::LocationStatus::OCCUPIED);
    
    auto item1 = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    auto item2 = std::make_shared<InventoryItem>(book, 5, location, "2024-01-15");
    
    writeOff.addAffectedItem(item1);
    writeOff.addAffectedItem(item2);
    
    EXPECT_EQ(writeOff.getTotalWrittenOffQuantity(), 15);
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

TEST(DeliveryTest, InvalidDelivery) {
    EXPECT_THROW(Delivery delivery("", "Supplier", "2024-01-20", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("INVALID", "Supplier", "2024-01-20", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2024-001", "", "2024-01-20", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2024-001", "Supplier", "invalid-date", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2024-001", "Supplier", "2024-01-20", "", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2024-001", "Supplier", "2024-01-20", "TRK123", "", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2024-001", "Supplier", "2024-01-20", "TRK123", "Carrier", -50.0), DataValidationException);
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
    
    EXPECT_THROW(delivery.addBook(nullptr), DataValidationException);
}

TEST(DeliveryTest, StatusTransitions) {
    Delivery delivery("DEL-2024-001", "Supplier", "2024-01-20", "TRK123", "Carrier", 100.0);
    
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::SCHEDULED);
    EXPECT_FALSE(delivery.isCompleted());
    EXPECT_FALSE(delivery.isInTransit());
    EXPECT_FALSE(delivery.isDelayed());
    
    delivery.setStatus(Delivery::DeliveryStatus::IN_TRANSIT);
    EXPECT_TRUE(delivery.isInTransit());
    
    delivery.setStatus(Delivery::DeliveryStatus::DELAYED);
    EXPECT_TRUE(delivery.isDelayed());
    
    delivery.processArrival();
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::ARRIVED);
    EXPECT_FALSE(delivery.getActualDate().empty());
}

TEST(DeliveryTest, StockReceiptLinking) {
    Delivery delivery("DEL-2024-001", "Supplier", "2024-01-20", "TRK123", "Carrier", 100.0);
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto receipt = std::make_shared<StockReceipt>(
        "REC-2024-001", "2024-01-20", "EMP-001", warehouse,
        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0, "From delivery"
    );
    
    delivery.setStockReceipt(receipt);
    EXPECT_EQ(delivery.getStockReceipt(), receipt);
}

// ==================== WarehouseManager Tests ====================
TEST(WarehouseManagerTest, BasicOperations) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    WarehouseManager manager(warehouse);
    EXPECT_EQ(manager.getWarehouse(), warehouse);
    auto newWarehouse = std::make_shared<Warehouse>("New Warehouse", "New Address");
    manager.setWarehouse(newWarehouse);
    EXPECT_EQ(manager.getWarehouse(), newWarehouse);
    
    EXPECT_THROW(WarehouseManager manager(nullptr), DataValidationException);
    EXPECT_THROW(manager.setWarehouse(nullptr), DataValidationException);
}


TEST(WarehouseManagerTest, StockTransferProcessing) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto sourceLocation = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    auto destLocation = std::make_shared<StorageLocation>("A-01-B-02", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(sourceLocation);
    shelf->addLocation(destLocation);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    WarehouseManager manager(warehouse);
    
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
    
    // First add stock to source location
    auto item = std::make_shared<InventoryItem>(book, 30, sourceLocation, "2024-01-15");
    warehouse->addInventoryItem(item);
    
    // Then transfer some
    std::vector<std::pair<std::shared_ptr<Book>, int>> transferItems = {{book, 20}};
    
    auto transfer = manager.processStockTransfer(
        sourceLocation, destLocation, "Reorganization",
        transferItems, "EMP-001", ""
    );
    
    EXPECT_NE(transfer, nullptr);
    EXPECT_EQ(sourceLocation->getCurrentLoad(), 10);
    EXPECT_EQ(destLocation->getCurrentLoad(), 20);
}


TEST(WarehouseManagerTest, OptimalLocationFinding) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 50, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location1);
    shelf->addLocation(location2);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    WarehouseManager manager(warehouse);
    
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
    
    auto optimalLocation = manager.findOptimalBookLocation(book, 75, WarehouseSection::SectionType::GENERAL);
    EXPECT_EQ(optimalLocation, location1); // location1 has 100 capacity, location2 only 50
    
    optimalLocation = manager.findOptimalBookLocation(book, 25, WarehouseSection::SectionType::GENERAL);
    EXPECT_NE(optimalLocation, nullptr);
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
    
    EXPECT_THROW(InventoryReport report(nullptr), DataValidationException);
    EXPECT_THROW(report.setWarehouse(nullptr), DataValidationException);
}

TEST(InventoryReportTest, StockReports) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
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
    
    auto item = std::make_shared<InventoryItem>(book, 50, location, "2024-01-15");
    warehouse->addInventoryItem(item);
    
    InventoryReport report(warehouse);
    
    auto stockLevelReport = report.generateStockLevelReport();
    EXPECT_FALSE(stockLevelReport.empty());
    
    auto bookStockReport = report.generateBookStockReport("9783161484100");
    EXPECT_FALSE(bookStockReport.empty());
    
    auto emptyLocationsReport = report.generateEmptyLocationsReport();
    EXPECT_FALSE(emptyLocationsReport.empty());
    
    auto fullLocationsReport = report.generateFullLocationsReport();
    EXPECT_FALSE(fullLocationsReport.empty());
    
    auto lowStockReport = report.generateLowStockReport(10);
    EXPECT_FALSE(lowStockReport.empty());
    
    auto sectionUtilizationReport = report.generateSectionUtilizationReport();
    EXPECT_FALSE(sectionUtilizationReport.empty());
    
    auto statisticsReport = report.generateStatisticsReport();
    EXPECT_FALSE(statisticsReport.empty());
}

TEST(InventoryReportTest, EmptyWarehouseReports) {
    auto warehouse = std::make_shared<Warehouse>("Empty Warehouse", "Test Address");
    InventoryReport report(warehouse);
    
    auto fullReport = report.generateFullReport();
    EXPECT_FALSE(fullReport.empty());
    
    auto stockLevelReport = report.generateStockLevelReport();
    EXPECT_FALSE(stockLevelReport.empty());
    
    auto bookStockReport = report.generateBookStockReport("NONEXISTENT");
    EXPECT_FALSE(bookStockReport.empty());
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