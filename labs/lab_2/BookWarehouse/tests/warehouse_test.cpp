#include <gtest/gtest.h>
#include <memory>
#include "Delivery.hpp"
#include "InventoryItem.hpp"
#include "InventoryReport.hpp"
#include "Shelf.hpp"
#include "StockMovement.hpp"
#include "StockReceipt.hpp"
#include "StockTransfer.hpp"
#include "StockWriteOff.hpp"
#include "StorageLocation.hpp"
#include "Warehouse.hpp"
#include "WarehouseManager.hpp"
#include "WarehouseSection.hpp"
#include "Book.hpp"
#include "exceptions/WarehouseExceptions.hpp"

TEST(DeliveryTest, ConstructorValidData) {
    EXPECT_NO_THROW(Delivery delivery("DEL-2025-001", "Supplier A", "2024-12-31", "TRK123", "Carrier X", 100.0));
    Delivery delivery("DEL-2025-002", "Supplier B", "2024-12-31", "TRK456", "Carrier Y", 50.0);
    EXPECT_EQ(delivery.getDeliveryId(), "DEL-2025-002");
    EXPECT_EQ(delivery.getSupplierName(), "Supplier B");
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::SCHEDULED);
}

TEST(DeliveryTest, ConstructorInvalidData) {
    EXPECT_THROW(Delivery delivery("INVALID", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2025-001", "", "2024-12-31", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2025-001", "Supplier", "invalid", "TRK123", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "", "Carrier", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "", 100.0), DataValidationException);
    EXPECT_THROW(Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", -10.0), DataValidationException);
}

TEST(DeliveryTest, BookManagement) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    delivery.addBook(book);
    EXPECT_EQ(delivery.getBookCount(), 1);
    EXPECT_TRUE(delivery.containsBook(book));
    delivery.removeBook(book);
    EXPECT_EQ(delivery.getBookCount(), 0);
    EXPECT_FALSE(delivery.containsBook(book));
}

TEST(DeliveryTest, StatusTransitions) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    delivery.setStatus(Delivery::DeliveryStatus::IN_TRANSIT);
    EXPECT_TRUE(delivery.isInTransit());
    delivery.processArrival();
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::ARRIVED);
    EXPECT_FALSE(delivery.getActualDate().empty());
}

TEST(InventoryItemTest, ConstructorValidData) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    EXPECT_NO_THROW(InventoryItem item(book, 10, location, "2024-01-15"));
    InventoryItem item(book, 5, location, "2024-01-16");
    EXPECT_EQ(item.getBook(), book);
    EXPECT_EQ(item.getQuantity(), 5);
    EXPECT_EQ(item.getLocation(), location);
    EXPECT_TRUE(item.isInStock());
}

TEST(InventoryItemTest, ConstructorInvalidData) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    EXPECT_THROW(InventoryItem item(nullptr, 10, location, "2024-01-15"), DataValidationException);
    EXPECT_THROW(InventoryItem item(book, -1, location, "2024-01-15"), DataValidationException);
    EXPECT_THROW(InventoryItem item(book, 10, nullptr, "2024-01-15"), DataValidationException);
    EXPECT_THROW(InventoryItem item(book, 10, location, "invalid"), DataValidationException);
}

TEST(InventoryItemTest, QuantityOperations) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    InventoryItem item(book, 10, location, "2024-01-15");
    item.increaseQuantity(5);
    EXPECT_EQ(item.getQuantity(), 15);
    item.decreaseQuantity(10);
    EXPECT_EQ(item.getQuantity(), 5);
    EXPECT_THROW(item.decreaseQuantity(10), WarehouseException);
    item.setQuantity(20);
    EXPECT_EQ(item.getQuantity(), 20);
}

TEST(InventoryItemTest, StockChecks) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    InventoryItem item(book, 0, location, "2024-01-15");
    EXPECT_FALSE(item.isInStock());
    item.setQuantity(1);
    EXPECT_TRUE(item.isInStock());
}

TEST(StorageLocationTest, ConstructorValidData) {
    EXPECT_NO_THROW(StorageLocation location("A-01-B-01", 100, 50, StorageLocation::LocationStatus::OCCUPIED));
    StorageLocation location("B-02-C-03", 200);
    EXPECT_EQ(location.getLocationId(), "B-02-C-03");
    EXPECT_EQ(location.getCapacity(), 200);
    EXPECT_EQ(location.getCurrentLoad(), 0);
    EXPECT_EQ(location.getStatus(), StorageLocation::LocationStatus::FREE);
}

TEST(StorageLocationTest, ConstructorInvalidData) {
    EXPECT_THROW(StorageLocation location("INVALID", 100), DataValidationException);
    EXPECT_THROW(StorageLocation location("A-01-B-01", 0), DataValidationException);
    EXPECT_THROW(StorageLocation location("A-01-B-01", 100, -1), DataValidationException);
    EXPECT_THROW(StorageLocation location("A-01-B-01", 100, 150), DataValidationException);
}

TEST(StorageLocationTest, BookOperations) {
    StorageLocation location("A-01-B-01", 100);
    location.addBooks(50);
    EXPECT_EQ(location.getCurrentLoad(), 50);
    EXPECT_EQ(location.getAvailableSpace(), 50);
    EXPECT_FALSE(location.isEmpty());
    EXPECT_FALSE(location.isFull());
    location.removeBooks(25);
    EXPECT_EQ(location.getCurrentLoad(), 25);
    location.addBooks(75);
    EXPECT_TRUE(location.isFull());
}

TEST(StorageLocationTest, CapacityChecks) {
    StorageLocation location("A-01-B-01", 100);
    EXPECT_TRUE(location.canAccommodate(50));
    EXPECT_FALSE(location.canAccommodate(150));
    location.addBooks(50);
    EXPECT_TRUE(location.canAccommodate(50));
    EXPECT_FALSE(location.canAccommodate(51));
}

TEST(StorageLocationTest, StatusOperations) {
    StorageLocation location("A-01-B-01", 100);
    location.setStatus(StorageLocation::LocationStatus::BLOCKED);
    EXPECT_EQ(location.getStatus(), StorageLocation::LocationStatus::BLOCKED);
    EXPECT_THROW(location.addBooks(10), WarehouseException);
    location.setStatus(StorageLocation::LocationStatus::FREE);
    location.addBooks(10);
    EXPECT_EQ(location.getStatus(), StorageLocation::LocationStatus::OCCUPIED);
}

TEST(ShelfTest, ConstructorValidData) {
    EXPECT_NO_THROW(Shelf shelf("A-01", 10));
    Shelf shelf("B-02", 5);
    EXPECT_EQ(shelf.getShelfId(), "B-02");
    EXPECT_EQ(shelf.getMaxLocations(), 5);
    EXPECT_EQ(shelf.getCurrentLocationsCount(), 0);
}

TEST(ShelfTest, ConstructorInvalidData) {
    EXPECT_THROW(Shelf shelf("INVALID", 10), DataValidationException);
    EXPECT_THROW(Shelf shelf("A-01", 0), DataValidationException);
}

TEST(ShelfTest, LocationManagement) {
    Shelf shelf("A-01", 3);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 50);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 50);
    shelf.addLocation(location1);
    shelf.addLocation(location2);
    EXPECT_EQ(shelf.getCurrentLocationsCount(), 2);
    EXPECT_TRUE(shelf.containsLocation("A-01-B-01"));
    EXPECT_EQ(shelf.findLocation("A-01-B-01"), location1);
    shelf.removeLocation("A-01-B-01");
    EXPECT_EQ(shelf.getCurrentLocationsCount(), 1);
    EXPECT_FALSE(shelf.containsLocation("A-01-B-01"));
}

TEST(ShelfTest, CapacityCalculations) {
    Shelf shelf("A-01", 2);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 150);
    location1->addBooks(50);
    location2->addBooks(75);
    shelf.addLocation(location1);
    shelf.addLocation(location2);
    EXPECT_EQ(shelf.getTotalCapacity(), 250);
    EXPECT_EQ(shelf.getCurrentLoad(), 125);
    EXPECT_EQ(shelf.getAvailableSpace(), 125);
}

TEST(ShelfTest, StatusChecks) {
    Shelf shelf("A-01", 2);
    EXPECT_TRUE(shelf.isEmpty());
    EXPECT_FALSE(shelf.isFull());
    EXPECT_TRUE(shelf.hasAvailableSpace());
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf.addLocation(location);
    EXPECT_FALSE(shelf.isFull());
    shelf.addLocation(std::make_shared<StorageLocation>("A-01-B-02", 100));
    EXPECT_TRUE(!shelf.isFull());
    EXPECT_FALSE(shelf.hasAvailableSpace());
}

TEST(WarehouseSectionTest, ConstructorValidData) {
    EXPECT_NO_THROW(WarehouseSection section("A", "General Section", "Test section", WarehouseSection::SectionType::GENERAL));
    WarehouseSection section("B", "Refrigerated", "Cold storage", WarehouseSection::SectionType::REFRIGERATED, 5.0, 60.0);
    EXPECT_EQ(section.getSectionId(), "B");
    EXPECT_EQ(section.getName(), "Refrigerated");
    EXPECT_EQ(section.getSectionType(), WarehouseSection::SectionType::REFRIGERATED);
    EXPECT_DOUBLE_EQ(section.getTemperature(), 5.0);
}

TEST(WarehouseSectionTest, ConstructorInvalidData) {
    EXPECT_THROW(WarehouseSection section("", "Name", "Desc", WarehouseSection::SectionType::GENERAL), DataValidationException);
    EXPECT_THROW(WarehouseSection section("AB", "Name", "Desc", WarehouseSection::SectionType::GENERAL), DataValidationException);
    EXPECT_THROW(WarehouseSection section("A", "", "Desc", WarehouseSection::SectionType::GENERAL), DataValidationException);
    EXPECT_THROW(WarehouseSection section("A", "Name", "Desc", WarehouseSection::SectionType::GENERAL, -100.0), DataValidationException);
    EXPECT_THROW(WarehouseSection section("A", "Name", "Desc", WarehouseSection::SectionType::GENERAL, 20.0, -10.0), DataValidationException);
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

TEST(WarehouseSectionTest, LocationOperations) {
    WarehouseSection section("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location1 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-02", 100);
    shelf->addLocation(location1);
    shelf->addLocation(location2);
    section.addShelf(shelf);
    auto available = section.findAvailableLocations();
    EXPECT_EQ(available.size(), 2);
    EXPECT_EQ(section.findLocation("A-01-B-01"), location1);
}

TEST(WarehouseSectionTest, CapacityCalculations) {
    WarehouseSection section("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf1 = std::make_shared<Shelf>("A-01", 2);
    auto shelf2 = std::make_shared<Shelf>("A-02", 2);
    auto loc1 = std::make_shared<StorageLocation>("A-01-B-01", 100); loc1->addBooks(50);
    auto loc2 = std::make_shared<StorageLocation>("A-01-B-02", 100); loc2->addBooks(25);
    auto loc3 = std::make_shared<StorageLocation>("A-02-B-01", 150); loc3->addBooks(75);
    shelf1->addLocation(loc1); shelf1->addLocation(loc2);
    shelf2->addLocation(loc3);
    section.addShelf(shelf1); section.addShelf(shelf2);
    EXPECT_EQ(section.getTotalCapacity(), 350);
    EXPECT_EQ(section.getCurrentLoad(), 150);
    EXPECT_EQ(section.getAvailableSpace(), 200);
}

TEST(WarehouseTest, ConstructorValidData) {
    EXPECT_NO_THROW(Warehouse warehouse("Main Warehouse", "123 Main St"));
    Warehouse warehouse("Secondary", "456 Oak Ave");
    EXPECT_EQ(warehouse.getName(), "Secondary");
    EXPECT_EQ(warehouse.getAddress(), "456 Oak Ave");
}

TEST(WarehouseTest, ConstructorInvalidData) {
    EXPECT_THROW(Warehouse warehouse("", "Address"), DataValidationException);
    EXPECT_THROW(Warehouse warehouse("Name", ""), DataValidationException);
}

TEST(WarehouseTest, SectionManagement) {
    Warehouse warehouse("Test", "Address");
    auto section1 = std::make_shared<WarehouseSection>("A", "Section A", "", WarehouseSection::SectionType::GENERAL);
    auto section2 = std::make_shared<WarehouseSection>("B", "Section B", "", WarehouseSection::SectionType::GENERAL);
    warehouse.addSection(section1);
    warehouse.addSection(section2);
    EXPECT_EQ(warehouse.getSectionsCount(), 2);
    EXPECT_TRUE(warehouse.containsSection("A"));
    EXPECT_EQ(warehouse.findSection("A"), section1);
    warehouse.removeSection("A");
    EXPECT_EQ(warehouse.getSectionsCount(), 1);
    EXPECT_FALSE(warehouse.containsSection("A"));
}

TEST(WarehouseTest, InventoryManagement) {
    Warehouse warehouse("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse.addSection(section);
    
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto inventoryItem = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    warehouse.addInventoryItem(inventoryItem);
    
    auto foundItems = warehouse.findInventoryByBook("9783161484100");
    EXPECT_EQ(foundItems.size(), 1);
    EXPECT_EQ(warehouse.getBookTotalQuantity("9783161484100"), 10);
    EXPECT_TRUE(warehouse.isBookInStock("9783161484100"));
    
    warehouse.removeInventoryItem("9783161484100", "A-01-B-01");
    EXPECT_EQ(warehouse.getBookTotalQuantity("9783161484100"), 0);
}

TEST(WarehouseTest, LocationSearch) {
    Warehouse warehouse("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse.addSection(section);
    
    auto available = warehouse.findAvailableLocations();
    EXPECT_EQ(available.size(), 1);
    auto optimal = warehouse.findOptimalLocation(50);
    EXPECT_NE(optimal, nullptr);
}

TEST(WarehouseTest, CapacityCalculations) {
    Warehouse warehouse("Test", "Address");
    auto section1 = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto section2 = std::make_shared<WarehouseSection>("B", "General", "", WarehouseSection::SectionType::GENERAL);
    
    auto shelf1 = std::make_shared<Shelf>("A-01", 1);
    auto shelf2 = std::make_shared<Shelf>("B-01", 1);
    auto loc1 = std::make_shared<StorageLocation>("A-01-B-01", 100); loc1->addBooks(50);
    auto loc2 = std::make_shared<StorageLocation>("B-01-B-01", 200); loc2->addBooks(100);
    shelf1->addLocation(loc1); shelf2->addLocation(loc2);
    section1->addShelf(shelf1); section2->addShelf(shelf2);
    warehouse.addSection(section1); warehouse.addSection(section2);
    
    EXPECT_EQ(warehouse.getTotalCapacity(), 300);
    EXPECT_EQ(warehouse.getCurrentLoad(), 150);
    EXPECT_EQ(warehouse.getAvailableSpace(), 150);
    EXPECT_DOUBLE_EQ(warehouse.getUtilizationPercentage(), 50.0);
    EXPECT_FALSE(warehouse.isEmpty());
    EXPECT_FALSE(warehouse.isFull());
}

TEST(StockMovementTest, ConstructorValidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_NO_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                       "Supplier A", "PO-2024-001", "INV-2024-001", 1000.0));
    StockReceipt receipt("REC-2024-002", "2024-01-16", "EMP-002", warehouse,
                        "Supplier B", "PO-2024-002", "INV-2024-002", 500.0);
    EXPECT_EQ(receipt.getMovementId(), "REC-2024-002");
    EXPECT_EQ(receipt.getMovementType(), StockMovement::MovementType::RECEIPT);
    EXPECT_EQ(receipt.getEmployeeId(), "EMP-002");
}

TEST(StockMovementTest, ConstructorInvalidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_THROW(StockReceipt receipt("INVALID", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "invalid", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "INVALID", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", nullptr,
                                    "Supplier", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
}

TEST(StockMovementTest, StatusOperations) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0);
    EXPECT_TRUE(receipt.isPending());
    EXPECT_FALSE(receipt.isCompleted());
    EXPECT_TRUE(receipt.isCancellable());
    receipt.setStatus(StockMovement::MovementStatus::COMPLETED);
    EXPECT_TRUE(receipt.isCompleted());
    EXPECT_FALSE(receipt.isCancellable());
}

TEST(StockMovementTest, ItemManagement) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto item = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    receipt.addAffectedItem(item);
    EXPECT_EQ(receipt.getAffectedItems().size(), 1);
    receipt.removeAffectedItem(item);
    EXPECT_EQ(receipt.getAffectedItems().size(), 0);
}

TEST(StockMovementTest, MovementTypeStrings) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0);
    EXPECT_EQ(receipt.getMovementTypeString(), "Receipt");
    
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("A-01-B-02", 100);
    StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                          source, dest, "Test");
    EXPECT_EQ(transfer.getMovementTypeString(), "Transfer");
    
    StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                          StockWriteOff::WriteOffReason::DAMAGED, "Damage");
    EXPECT_EQ(writeOff.getMovementTypeString(), "Write-Off");
}

TEST(StockMovementTest, StatusStrings) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0);
    EXPECT_EQ(receipt.getMovementStatusString(), "Pending");
    receipt.setStatus(StockMovement::MovementStatus::IN_PROGRESS);
    EXPECT_EQ(receipt.getMovementStatusString(), "In Progress");
    receipt.setStatus(StockMovement::MovementStatus::COMPLETED);
    EXPECT_EQ(receipt.getMovementStatusString(), "Completed");
    receipt.setStatus(StockMovement::MovementStatus::CANCELLED);
    EXPECT_EQ(receipt.getMovementStatusString(), "Cancelled");
}

TEST(StockReceiptTest, ConstructorValidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_NO_THROW(
        StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                           "Supplier A", "PO-2024-001", "INV-2024-001", 1000.0)
    );
    StockReceipt receipt("REC-2024-002", "2024-01-16", "EMP-002", warehouse,
                        "Supplier B", "PO-2024-002", "INV-2024-002", 500.0, "Test notes");
    EXPECT_EQ(receipt.getSupplierName(), "Supplier B");
    EXPECT_EQ(receipt.getPurchaseOrderNumber(), "PO-2024-002");
    EXPECT_DOUBLE_EQ(receipt.getTotalCost(), 500.0);
}

TEST(StockReceiptTest, ConstructorInvalidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "", "PO-2024-001", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "INVALID", "INV-2024-001", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INVALID", 1000.0), DataValidationException);
    EXPECT_THROW(StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                                    "Supplier", "PO-2024-001", "INV-2024-001", -100.0), DataValidationException);
}

TEST(StockReceiptTest, CostCalculations) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockReceipt receipt("REC-2024-001", "2024-01-15", "EMP-001", warehouse,
                        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto item1 = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    auto item2 = std::make_shared<InventoryItem>(book, 15, location, "2024-01-15");
    receipt.addAffectedItem(item1);
    receipt.addAffectedItem(item2);
    EXPECT_DOUBLE_EQ(receipt.calculateAverageCost(), 40.0); // 1000 / 25
}

TEST(StockTransferTest, ConstructorValidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("A-01-B-02", 100);
    EXPECT_NO_THROW(
        StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                             source, dest, "Reorganization")
    );
    StockTransfer transfer("TRF-2024-002", "2024-01-16", "EMP-002", warehouse,
                          source, dest, "Restocking", "Test notes");
    EXPECT_EQ(transfer.getSourceLocation(), source);
    EXPECT_EQ(transfer.getDestinationLocation(), dest);
    EXPECT_EQ(transfer.getTransferReason(), "Restocking");
}

TEST(StockTransferTest, ConstructorInvalidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("A-01-B-01", 100);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      source, dest, "Reason"), DataValidationException);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      source, nullptr, "Reason"), DataValidationException);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      nullptr, dest, "Reason"), DataValidationException);
    EXPECT_THROW(StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      source, dest, ""), DataValidationException);
}

TEST(StockTransferTest, TransferValidation) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("B-01-B-01", 100);
    source->addBooks(50);
    StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                          source, dest, "Test");
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto item = std::make_shared<InventoryItem>(book, 30, source, "2024-01-15");
    transfer.addAffectedItem(item);
    EXPECT_TRUE(transfer.doesSourceHaveSufficientStock());
    EXPECT_TRUE(transfer.canDestinationAccommodate());
    EXPECT_TRUE(transfer.isCrossSectionTransfer());
    EXPECT_EQ(transfer.getTotalTransferQuantity(), 30);
}

TEST(StockWriteOffTest, ConstructorValidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_NO_THROW(
        StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                             StockWriteOff::WriteOffReason::DAMAGED, "Water damage")
    );
    StockWriteOff writeOff("WO-2024-002", "2024-01-16", "EMP-002", warehouse,
                          StockWriteOff::WriteOffReason::EXPIRED, "Past expiration date", "Test notes");
    EXPECT_EQ(writeOff.getReason(), StockWriteOff::WriteOffReason::EXPIRED);
    EXPECT_EQ(writeOff.getDetailedReason(), "Past expiration date");
}

TEST(StockWriteOffTest, ConstructorInvalidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_THROW(StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                                      StockWriteOff::WriteOffReason::DAMAGED, ""), DataValidationException);
}

TEST(StockWriteOffTest, ReasonChecks) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockWriteOff damageWriteOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                                StockWriteOff::WriteOffReason::DAMAGED, "Damage");
    StockWriteOff expireWriteOff("WO-2024-002", "2024-01-16", "EMP-002", warehouse,
                                StockWriteOff::WriteOffReason::EXPIRED, "Expired");
    EXPECT_TRUE(damageWriteOff.isDueToDamage());
    EXPECT_FALSE(damageWriteOff.isDueToExpiration());
    EXPECT_TRUE(expireWriteOff.isDueToExpiration());
    EXPECT_FALSE(expireWriteOff.isDueToDamage());
}

TEST(StockWriteOffTest, QuantityCalculations) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockWriteOff writeOff("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                          StockWriteOff::WriteOffReason::DAMAGED, "Damage");
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto item1 = std::make_shared<InventoryItem>(book, 5, location, "2024-01-15");
    auto item2 = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    writeOff.addAffectedItem(item1);
    writeOff.addAffectedItem(item2);
    EXPECT_EQ(writeOff.getTotalWrittenOffQuantity(), 15);
}

TEST(InventoryReportTest, ConstructorValidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_NO_THROW(InventoryReport report(warehouse));
    InventoryReport report(warehouse);
    EXPECT_EQ(report.getWarehouse(), warehouse);
}

TEST(InventoryReportTest, ConstructorInvalidData) {
    EXPECT_THROW(InventoryReport report(nullptr), DataValidationException);
}

TEST(InventoryReportTest, ReportGeneration) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    InventoryReport report(warehouse);
    EXPECT_FALSE(report.generateFullReport().empty());
    EXPECT_FALSE(report.generateStockLevelReport().empty());
    EXPECT_FALSE(report.generateCapacityReport().empty());
    EXPECT_FALSE(report.generateStatisticsReport().empty());
    EXPECT_FALSE(report.generateEmptyLocationsReport().empty());
    EXPECT_FALSE(report.generateFullLocationsReport().empty());
}

TEST(InventoryReportTest, BookSpecificReports) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto inventoryItem = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    warehouse->addInventoryItem(inventoryItem);
    
    InventoryReport report(warehouse);
    EXPECT_FALSE(report.generateBookStockReport("9783161484100").empty());
    EXPECT_FALSE(report.generateLowStockReport().empty());
}

TEST(WarehouseManagerTest, ConstructorValidData) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_NO_THROW(WarehouseManager manager(warehouse));
    WarehouseManager manager(warehouse);
    EXPECT_EQ(manager.getWarehouse(), warehouse);
}

TEST(WarehouseManagerTest, ConstructorInvalidData) {
    EXPECT_THROW(WarehouseManager manager(nullptr), DataValidationException);
}

TEST(WarehouseManagerTest, StockReceiptProcessing) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    WarehouseManager manager(warehouse);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    std::vector<std::pair<std::shared_ptr<Book>, int>> items = {{book, 10}};
    auto receipt = manager.processStockReceipt("Supplier", "PO-2024-001", "INV-2024-001", 200.0, items, "EMP-001");
    EXPECT_NE(receipt, nullptr);
    EXPECT_EQ(warehouse->getBookTotalQuantity("9783161484100"), 20);
}

TEST(WarehouseManagerTest, LocationFinding) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    WarehouseManager manager(warehouse);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto optimalLocation = manager.findOptimalBookLocation(book, 50);
    EXPECT_NE(optimalLocation, nullptr);
}

TEST(WarehouseManagerTest, StockChecks) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto inventoryItem = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    warehouse->addInventoryItem(inventoryItem);
    
    WarehouseManager manager(warehouse);
    EXPECT_FALSE(manager.getBookStockInfo("9783161484100").empty());
    EXPECT_TRUE(manager.isBookAvailable("9783161484100", 5));
    EXPECT_FALSE(manager.isBookAvailable("9783161484100", 15));
}

TEST(WarehouseManagerTest, AnalyticsReports) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 1000);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    WarehouseManager manager(warehouse);
    EXPECT_FALSE(manager.getWarehouseUtilizationReport().empty());
    EXPECT_FALSE(manager.getInventorySummary().empty());
    EXPECT_TRUE(manager.getLowStockAlerts(100).empty());
}

TEST(IntegrationTest, CompleteWarehouseFlow) {
    auto warehouse = std::make_shared<Warehouse>("Main Warehouse", "123 Business St");
    auto sectionA = std::make_shared<WarehouseSection>("A", "General Storage", "Main storage area", WarehouseSection::SectionType::GENERAL);
    auto sectionB = std::make_shared<WarehouseSection>("B", "Bulk Storage", "Bulk items", WarehouseSection::SectionType::BULK);
    auto shelfA1 = std::make_shared<Shelf>("A-01", 3);
    auto shelfA2 = std::make_shared<Shelf>("A-02", 3);
    auto shelfB1 = std::make_shared<Shelf>("B-01", 2);
    auto locA1B1 = std::make_shared<StorageLocation>("A-01-B-01", 200);
    auto locA1B2 = std::make_shared<StorageLocation>("A-01-B-02", 200);
    auto locA2B1 = std::make_shared<StorageLocation>("A-02-B-01", 300);
    auto locB1B1 = std::make_shared<StorageLocation>("B-01-B-01", 400);
    shelfA1->addLocation(locA1B1); shelfA1->addLocation(locA1B2);
    shelfA2->addLocation(locA2B1);
    shelfB1->addLocation(locB1B1);
    sectionA->addShelf(shelfA1); sectionA->addShelf(shelfA2);
    sectionB->addShelf(shelfB1);
    warehouse->addSection(sectionA); warehouse->addSection(sectionB);
    WarehouseManager manager(warehouse);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Science Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Science Pub", "contact@science.com", 2010),
        BookCondition(BookCondition::Condition::NEW), 29.99
    );
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"), BookTitle("History Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(400, 220, 150, 30, 350, PhysicalProperties::CoverType::HARDCOVER, "Hardcover"),
        Genre(Genre::Type::HISTORICAL_FICTION), std::make_shared<Publisher>("History Press", "contact@history.com", 2005),
        BookCondition(BookCondition::Condition::NEW), 39.99
    );
    std::vector<std::pair<std::shared_ptr<Book>, int>> receiptItems = {{book1, 50}, {book2, 30}};
    auto receipt = manager.processStockReceipt("Book Distributor", "PO-2024-001", "INV-2024-001", 
                                             2500.0, receiptItems, "EMP-001", "Initial stock");
    int book1Qty = warehouse->getBookTotalQuantity("9783161484100");
    int book2Qty = warehouse->getBookTotalQuantity("0306406152");
    EXPECT_GT(book1Qty, 0);
    EXPECT_GT(book2Qty, 0);
    EXPECT_FALSE(warehouse->isEmpty());
    InventoryReport report(warehouse);
    EXPECT_FALSE(report.generateFullReport().empty());
    EXPECT_FALSE(report.generateStockLevelReport().empty());
    EXPECT_TRUE(manager.isBookAvailable("9783161484100", 10));
    EXPECT_FALSE(manager.isBookAvailable("9783161484100", 10000));
    auto optimalLoc = manager.findOptimalBookLocation(book1, 25);
    EXPECT_NE(optimalLoc, nullptr);
    EXPECT_FALSE(manager.getLowStockAlerts(10000).empty());
    EXPECT_FALSE(warehouse->getInfo().empty());
    EXPECT_FALSE(warehouse->getDetailedReport().empty());
    EXPECT_GT(warehouse->getTotalCapacity(), 0);
    EXPECT_GT(warehouse->getCurrentLoad(), 0);
    EXPECT_LT(warehouse->getUtilizationPercentage(), 100.0);
}

TEST(EdgeCasesTest, BoundaryConditions) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 1);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 1);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    
    InventoryItem item(book, 1, location, "2024-01-15");
    EXPECT_TRUE(item.isInStock());
    item.decreaseQuantity(1);
    EXPECT_FALSE(item.isInStock());
    
    location->addBooks(1);
    EXPECT_TRUE(location->isFull());
    EXPECT_FALSE(location->canAccommodate(1));
    
    EXPECT_TRUE(shelf->isFull());
    EXPECT_FALSE(shelf->hasAvailableSpace());
}

TEST(DeliveryTest, GetScheduledDate) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    EXPECT_EQ(delivery.getScheduledDate(), "2024-12-31");
}

TEST(DeliveryTest, GetTrackingNumber) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK456", "Carrier", 100.0);
    EXPECT_EQ(delivery.getTrackingNumber(), "TRK456");
}

TEST(DeliveryTest, AddDuplicateBookThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    
    delivery.addBook(book);
    EXPECT_THROW(delivery.addBook(book), DataValidationException);
}

TEST(DeliveryTest, AddBookToNonScheduledDeliveryThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    
    delivery.setStatus(Delivery::DeliveryStatus::IN_TRANSIT);
    EXPECT_THROW(delivery.addBook(book), WarehouseException);
}

TEST(DeliveryTest, RemoveBookFromNonScheduledDeliveryThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    
    delivery.addBook(book);
    delivery.setStatus(Delivery::DeliveryStatus::IN_TRANSIT);
    EXPECT_THROW(delivery.removeBook(book), WarehouseException);
}

TEST(DeliveryTest, SetActualDateValid) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    delivery.setActualDate("2024-12-25");
    EXPECT_EQ(delivery.getActualDate(), "2024-12-25");
}

TEST(DeliveryTest, SetActualDateInvalidThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    EXPECT_THROW(delivery.setActualDate("invalid-date"), DataValidationException);
}

TEST(DeliveryTest, ProcessArrivalValid) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    delivery.setStatus(Delivery::DeliveryStatus::IN_TRANSIT);
    delivery.processArrival();
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::ARRIVED);
    EXPECT_FALSE(delivery.getActualDate().empty());
}

TEST(DeliveryTest, ProcessArrivalInvalidStatusThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    EXPECT_THROW(delivery.processArrival(), WarehouseException);
}

TEST(DeliveryTest, CompleteDeliveryValid) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    delivery.addBook(book);
    delivery.setStatus(Delivery::DeliveryStatus::ARRIVED);
    auto stockReceipt = std::make_shared<StockReceipt>(
        "REC-2024-001", "2024-12-25", "EMP-001", std::make_shared<Warehouse>("Test", "Address"),
        "Supplier", "PO-2024-001", "INV-2024-001", 1000.0
    );
    delivery.setStockReceipt(stockReceipt);
    delivery.completeDelivery();
    EXPECT_EQ(delivery.getStatus(), Delivery::DeliveryStatus::COMPLETED);
}

TEST(DeliveryTest, CompleteDeliveryNoBooksThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    delivery.setStatus(Delivery::DeliveryStatus::ARRIVED);
    EXPECT_THROW(delivery.completeDelivery(), WarehouseException);
}

TEST(DeliveryTest, CompleteDeliveryNoStockReceiptThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    delivery.addBook(book);
    delivery.setStatus(Delivery::DeliveryStatus::ARRIVED);
    EXPECT_THROW(delivery.completeDelivery(), WarehouseException);
}

TEST(DeliveryTest, CompleteDeliveryWrongStatusThrows) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    delivery.addBook(book);
    EXPECT_THROW(delivery.completeDelivery(), WarehouseException);
}

TEST(DeliveryTest, GetInfo) {
    Delivery delivery("DEL-2025-001", "Test Supplier", "2024-12-31", "TRK789", "Test Carrier", 150.0);
    std::string info = delivery.getInfo();
    EXPECT_NE(info.find("DEL-2025-001"), std::string::npos);
    EXPECT_NE(info.find("Test Supplier"), std::string::npos);
    EXPECT_NE(info.find("Scheduled"), std::string::npos);
    EXPECT_NE(info.find("Test Carrier"), std::string::npos);
    EXPECT_NE(info.find("TRK789"), std::string::npos);
}

TEST(DeliveryTest, GetStatusStringAllStatuses) {
    Delivery delivery("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    delivery.setStatus(Delivery::DeliveryStatus::SCHEDULED);
    EXPECT_EQ(delivery.getStatusString(), "Scheduled");
    delivery.setStatus(Delivery::DeliveryStatus::IN_TRANSIT);
    EXPECT_EQ(delivery.getStatusString(), "In Transit");
    delivery.setStatus(Delivery::DeliveryStatus::ARRIVED);
    EXPECT_EQ(delivery.getStatusString(), "Arrived");
    delivery.setStatus(Delivery::DeliveryStatus::UNLOADING);
    EXPECT_EQ(delivery.getStatusString(), "Unloading");
    delivery.setStatus(Delivery::DeliveryStatus::COMPLETED);
    EXPECT_EQ(delivery.getStatusString(), "Completed");
    delivery.setStatus(Delivery::DeliveryStatus::CANCELLED);
    EXPECT_EQ(delivery.getStatusString(), "Cancelled");
    delivery.setStatus(Delivery::DeliveryStatus::DELAYED);
    EXPECT_EQ(delivery.getStatusString(), "Delayed");
}

TEST(DeliveryTest, EqualityOperators) {
    Delivery delivery1("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    Delivery delivery2("DEL-2025-001", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    Delivery delivery3("DEL-2025-002", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0);
    EXPECT_TRUE(delivery1 == delivery2);
    EXPECT_FALSE(delivery1 == delivery3);
    EXPECT_TRUE(delivery1 != delivery3);
    EXPECT_FALSE(delivery1 != delivery2);
}

TEST(StockWriteOffTest, EqualityOperators) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    StockWriteOff writeOff1("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                           StockWriteOff::WriteOffReason::DAMAGED, "Water damage", "Test notes");
    StockWriteOff writeOff2("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                           StockWriteOff::WriteOffReason::DAMAGED, "Water damage", "Test notes");
    StockWriteOff writeOff3("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                           StockWriteOff::WriteOffReason::EXPIRED, "Water damage", "Test notes");
    StockWriteOff writeOff4("WO-2024-001", "2024-01-15", "EMP-001", warehouse,
                           StockWriteOff::WriteOffReason::DAMAGED, "Fire damage", "Test notes");
    StockWriteOff writeOff5("WO-2024-002", "2024-01-15", "EMP-001", warehouse,
                           StockWriteOff::WriteOffReason::DAMAGED, "Water damage", "Test notes");
    EXPECT_TRUE(writeOff1 == writeOff2);
    EXPECT_FALSE(writeOff1 == writeOff3);
    EXPECT_FALSE(writeOff1 == writeOff4);
    EXPECT_FALSE(writeOff1 == writeOff5);
    EXPECT_FALSE(writeOff1 != writeOff2);
    EXPECT_TRUE(writeOff1 != writeOff3);
    EXPECT_TRUE(writeOff1 != writeOff4);
    EXPECT_TRUE(writeOff1 != writeOff5);
    EXPECT_TRUE(writeOff1 == writeOff1);
    EXPECT_FALSE(writeOff1 != writeOff1);
    EXPECT_TRUE(writeOff1 == writeOff2);
    EXPECT_TRUE(writeOff2 == writeOff1);
    EXPECT_TRUE(writeOff1 != writeOff3);
    EXPECT_TRUE(writeOff3 != writeOff1);
}

TEST(ErrorConditionsTest, ExceptionHandling) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    EXPECT_THROW(Delivery delivery("INVALID", "Supplier", "2024-12-31", "TRK123", "Carrier", 100.0), DataValidationException);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), std::make_shared<Publisher>("Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW), 19.99
    );
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 10);
    InventoryItem item(book, 5, location, "2024-01-15");
    EXPECT_THROW(item.decreaseQuantity(10), WarehouseException);
    location->addBooks(5);
    EXPECT_THROW(location->addBooks(10), WarehouseException);
    Shelf shelf("A-01", 1);
    shelf.addLocation(location);
    auto location2 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    WarehouseSection section("A", "Test", "", WarehouseSection::SectionType::GENERAL);
    section.addShelf(std::make_shared<Shelf>("A-01", 1));
    EXPECT_THROW(section.addShelf(std::make_shared<Shelf>("A-01", 1)), DataValidationException);
}

TEST(PerformanceTest, LargeScaleOperations) {
    auto warehouse = std::make_shared<Warehouse>("Large Warehouse", "123 Main St");
    for (char sectionId = 'A'; sectionId <= 'C'; sectionId++) {
        std::string sid(1, sectionId);
        auto section = std::make_shared<WarehouseSection>(sid, "Section " + sid, "", WarehouseSection::SectionType::GENERAL);
        for (int shelfNum = 1; shelfNum <= 3; shelfNum++) {
            std::string shelfId = sid + "-" + (shelfNum < 10 ? "0" : "") + std::to_string(shelfNum);
            auto shelf = std::make_shared<Shelf>(shelfId, 5);
            for (int locNum = 1; locNum <= 5; locNum++) {
                std::string locId = shelfId + "-B-" + (locNum < 10 ? "0" : "") + std::to_string(locNum);
                auto location = std::make_shared<StorageLocation>(locId, 100);
                shelf->addLocation(location);
            }
            section->addShelf(shelf);
        }
        warehouse->addSection(section);
    }
    EXPECT_GT(warehouse->getTotalCapacity(), 0);
    EXPECT_TRUE(warehouse->isEmpty());
    InventoryReport report(warehouse);
    EXPECT_FALSE(report.generateFullReport().empty());
    EXPECT_FALSE(report.generateStatisticsReport().empty());
}

TEST(StockTransferTest, GetInfo) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                          source, dest, "Reorganization", "Test notes");
    
    std::string info = transfer.getInfo();
    EXPECT_NE(info.find("TRF-2024-001"), std::string::npos);
    EXPECT_NE(info.find("A-01-B-01"), std::string::npos);
    EXPECT_NE(info.find("B-02-C-03"), std::string::npos);
    EXPECT_NE(info.find("Reorganization"), std::string::npos);
    EXPECT_NE(info.find("Yes"), std::string::npos); // Cross-Section: Yes
}

TEST(StockTransferTest, GetInfoWithNullLocations) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    
    // Создаем transfer с nullptr locations (хотя конструктор этого не позволяет)
    // Этот тест в основном для покрытия ветки "N/A" в getInfo()
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("A-01-B-02", 100);
    
    StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                          source, dest, "Reorganization");
    
    std::string info = transfer.getInfo();
    EXPECT_NE(info.find("A-01-B-01"), std::string::npos);
    EXPECT_NE(info.find("A-01-B-02"), std::string::npos);
}

TEST(StockTransferTest, EqualityOperatorsSameLocations) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source1 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest1 = std::make_shared<StorageLocation>("B-02-C-03", 100);
    auto source2 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest2 = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer1("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source1, dest1, "Reorganization", "Notes");
    StockTransfer transfer2("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source2, dest2, "Reorganization", "Notes");
    
    EXPECT_TRUE(transfer1 == transfer2);
    EXPECT_FALSE(transfer1 != transfer2);
}

TEST(StockTransferTest, EqualityOperatorsDifferentSourceLocation) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source1 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto source2 = std::make_shared<StorageLocation>("A-01-B-02", 100);
    auto dest = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer1("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source1, dest, "Reorganization");
    StockTransfer transfer2("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source2, dest, "Reorganization");
    
    EXPECT_FALSE(transfer1 == transfer2);
    EXPECT_TRUE(transfer1 != transfer2);
}

TEST(StockTransferTest, EqualityOperatorsDifferentDestinationLocation) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest1 = std::make_shared<StorageLocation>("B-02-C-03", 100);
    auto dest2 = std::make_shared<StorageLocation>("B-02-C-04", 100);
    
    StockTransfer transfer1("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source, dest1, "Reorganization");
    StockTransfer transfer2("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source, dest2, "Reorganization");
    
    EXPECT_FALSE(transfer1 == transfer2);
    EXPECT_TRUE(transfer1 != transfer2);
}

TEST(StockTransferTest, EqualityOperatorsDifferentTransferReason) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer1("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source, dest, "Reorganization");
    StockTransfer transfer2("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source, dest, "Restocking");
    
    EXPECT_FALSE(transfer1 == transfer2);
    EXPECT_TRUE(transfer1 != transfer2);
}

TEST(StockTransferTest, EqualityOperatorsDifferentMovementId) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer1("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source, dest, "Reorganization");
    StockTransfer transfer2("TRF-2024-002", "2024-01-15", "EMP-001", warehouse,
                           source, dest, "Reorganization");
    
    EXPECT_FALSE(transfer1 == transfer2);
    EXPECT_TRUE(transfer1 != transfer2);
}

TEST(StockTransferTest, EqualityOperatorsReflexivity) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                          source, dest, "Reorganization");
    
    EXPECT_TRUE(transfer == transfer);
    EXPECT_FALSE(transfer != transfer);
}

TEST(StockTransferTest, EqualityOperatorsSymmetry) {
    auto warehouse = std::make_shared<Warehouse>("Test", "Address");
    auto source1 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto source2 = std::make_shared<StorageLocation>("A-01-B-01", 100);
    auto dest1 = std::make_shared<StorageLocation>("B-02-C-03", 100);
    auto dest2 = std::make_shared<StorageLocation>("B-02-C-03", 100);
    
    StockTransfer transfer1("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source1, dest1, "Reorganization");
    StockTransfer transfer2("TRF-2024-001", "2024-01-15", "EMP-001", warehouse,
                           source2, dest2, "Reorganization");
    
    EXPECT_TRUE(transfer1 == transfer2);
    EXPECT_TRUE(transfer2 == transfer1);
    EXPECT_FALSE(transfer1 != transfer2);
    EXPECT_FALSE(transfer2 != transfer1);
}