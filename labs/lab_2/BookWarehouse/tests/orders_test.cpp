#include <gtest/gtest.h>
#include "Order.hpp"
#include "CustomerOrder.hpp"
#include "PurchaseOrder.hpp"
#include "OrderItem.hpp"
#include "OrderStatus.hpp"
#include "ShippingInfo.hpp"
#include "OrderManager.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"

TEST(OrderStatusTest, ConstructorValidData) {
    EXPECT_NO_THROW(OrderStatus status(OrderStatus::Status::PENDING, "2024-01-15"));
    OrderStatus status(OrderStatus::Status::CONFIRMED, "2024-01-16");
    EXPECT_EQ(status.getStatus(), OrderStatus::Status::CONFIRMED);
    EXPECT_EQ(status.getStatusChangedDate(), "2024-01-16");
}

TEST(OrderStatusTest, ConstructorInvalidDate) {
    EXPECT_THROW(OrderStatus status(OrderStatus::Status::PENDING, "invalid-date"), DataValidationException);
}

TEST(OrderStatusTest, StatusToString) {
    OrderStatus pending(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus confirmed(OrderStatus::Status::CONFIRMED, "2024-01-15");
    OrderStatus processing(OrderStatus::Status::PROCESSING, "2024-01-15");
    OrderStatus shipped(OrderStatus::Status::SHIPPED, "2024-01-15");
    OrderStatus delivered(OrderStatus::Status::DELIVERED, "2024-01-15");
    OrderStatus cancelled(OrderStatus::Status::CANCELLED, "2024-01-15");
    EXPECT_EQ(pending.toString(), "Pending");
    EXPECT_EQ(confirmed.toString(), "Confirmed");
    EXPECT_EQ(processing.toString(), "Processing");
    EXPECT_EQ(shipped.toString(), "Shipped");
    EXPECT_EQ(delivered.toString(), "Delivered");
    EXPECT_EQ(cancelled.toString(), "Cancelled");
}

TEST(OrderStatusTest, StatusTransitions) {
    OrderStatus pending(OrderStatus::Status::PENDING, "2024-01-15");
    EXPECT_TRUE(pending.isValidTransition(OrderStatus::Status::CONFIRMED));
    EXPECT_TRUE(pending.isValidTransition(OrderStatus::Status::CANCELLED));
    EXPECT_FALSE(pending.isValidTransition(OrderStatus::Status::SHIPPED));
    
    OrderStatus confirmed(OrderStatus::Status::CONFIRMED, "2024-01-15");
    EXPECT_TRUE(confirmed.isValidTransition(OrderStatus::Status::PROCESSING));
    EXPECT_FALSE(confirmed.isValidTransition(OrderStatus::Status::DELIVERED));
}

TEST(OrderStatusTest, UpdateStatusValid) {
    OrderStatus status(OrderStatus::Status::PENDING, "2024-01-15");
    status.updateStatus(OrderStatus::Status::CONFIRMED, "2024-01-16");
    EXPECT_EQ(status.getStatus(), OrderStatus::Status::CONFIRMED);
    EXPECT_EQ(status.getStatusChangedDate(), "2024-01-16");
}

TEST(OrderStatusTest, UpdateStatusInvalid) {
    OrderStatus status(OrderStatus::Status::PENDING, "2024-01-15");
    EXPECT_THROW(status.updateStatus(OrderStatus::Status::SHIPPED, "2024-01-16"), OrderProcessingException);
}

TEST(OrderStatusTest, StatusChecks) {
    OrderStatus pending(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus delivered(OrderStatus::Status::DELIVERED, "2024-01-15");
    OrderStatus cancelled(OrderStatus::Status::CANCELLED, "2024-01-15");
    EXPECT_FALSE(pending.isCompleted());
    EXPECT_TRUE(delivered.isCompleted());
    EXPECT_TRUE(cancelled.isCompleted());
    EXPECT_TRUE(pending.isActive());
    EXPECT_FALSE(delivered.isActive());
    EXPECT_TRUE(pending.isCancellable());
    EXPECT_FALSE(delivered.isCancellable());
    EXPECT_TRUE(pending.requiresAction());
    EXPECT_FALSE(delivered.requiresAction());
}

TEST(OrderStatusTest, NextPossibleStatuses) {
    OrderStatus pending(OrderStatus::Status::PENDING, "2024-01-15");
    auto nextStatuses = pending.getNextPossibleStatuses();
    EXPECT_GT(nextStatuses.size(), 0);
}

TEST(OrderStatusTest, EqualityOperators) {
    OrderStatus status1(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus status2(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus status3(OrderStatus::Status::CONFIRMED, "2024-01-15");
    EXPECT_TRUE(status1 == status2);
    EXPECT_FALSE(status1 == status3);
    EXPECT_TRUE(status1 != status3);
}

TEST(OrderItemTest, ConstructorValidData) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    EXPECT_NO_THROW(OrderItem item(book, 5, 19.99, 10.0));
    OrderItem item(book, 10, 24.99, 5.0);
    EXPECT_EQ(item.getBook(), book);
    EXPECT_EQ(item.getQuantity(), 10);
    EXPECT_DOUBLE_EQ(item.getUnitPrice(), 24.99);
    EXPECT_DOUBLE_EQ(item.getDiscountPercentage(), 5.0);
}

TEST(OrderItemTest, ConstructorInvalidData) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    EXPECT_THROW(OrderItem item(nullptr, 5, 19.99, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 0, 19.99, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 1001, 19.99, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 5, -1.0, 10.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 5, 19.99, -1.0), DataValidationException);
    EXPECT_THROW(OrderItem item(book, 5, 19.99, 101.0), DataValidationException);
}

TEST(OrderItemTest, PriceCalculations) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    OrderItem item(book, 10, 20.0, 10.0);
    EXPECT_DOUBLE_EQ(item.getDiscountedUnitPrice(), 18.0);
    EXPECT_DOUBLE_EQ(item.getTotalPrice(), 180.0);
    EXPECT_DOUBLE_EQ(item.getTotalDiscount(), 20.0);
    EXPECT_TRUE(item.hasDiscount());
    OrderItem noDiscount(book, 5, 20.0, 0.0);
    EXPECT_FALSE(noDiscount.hasDiscount());
}

TEST(OrderItemTest, QuantityOperations) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    OrderItem item(book, 10, 20.0, 10.0);
    item.setQuantity(15);
    EXPECT_EQ(item.getQuantity(), 15);
    item.increaseQuantity(5);
    EXPECT_EQ(item.getQuantity(), 20);
    item.decreaseQuantity(10);
    EXPECT_EQ(item.getQuantity(), 10);
    EXPECT_THROW(item.setQuantity(0), DataValidationException);
    EXPECT_THROW(item.increaseQuantity(-1), DataValidationException);
    EXPECT_THROW(item.decreaseQuantity(-1), DataValidationException);
    EXPECT_THROW(item.decreaseQuantity(20), DataValidationException);
}

TEST(OrderItemTest, DiscountOperations) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    OrderItem item(book, 10, 20.0, 10.0);
    item.setDiscountPercentage(15.0);
    EXPECT_DOUBLE_EQ(item.getDiscountPercentage(), 15.0);
    EXPECT_DOUBLE_EQ(item.getDiscountedUnitPrice(), 17.0);
    EXPECT_THROW(item.setDiscountPercentage(-1.0), DataValidationException);
    EXPECT_THROW(item.setDiscountPercentage(101.0), DataValidationException);
}

TEST(OrderItemTest, GetInfo) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    OrderItem item(book, 10, 20.0, 10.0);
    std::string info = item.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("Test Book"), std::string::npos);
}

TEST(OrderItemTest, EqualityOperators) {
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    OrderItem item1(book, 10, 20.0, 10.0);
    OrderItem item2(book, 10, 20.0, 10.0);
    OrderItem item3(book, 5, 20.0, 10.0);
    EXPECT_TRUE(item1 == item2);
    EXPECT_FALSE(item1 == item3);
    EXPECT_TRUE(item1 != item3);
}

TEST(OrderTest, ConstructorValidData) {
    EXPECT_NO_THROW(Order order("ORD-001", "2024-01-15", "Test notes"));
    Order order("ORD-002", "2024-01-16", "");
    EXPECT_EQ(order.getOrderId(), "ORD-002");
    EXPECT_EQ(order.getOrderDate(), "2024-01-16");
    EXPECT_EQ(order.getNotes(), "");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::PENDING);
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 0.0);
    EXPECT_TRUE(order.isEmpty());
}

TEST(OrderTest, ConstructorInvalidData) {
    EXPECT_THROW(Order order("", "2024-01-15", ""), DataValidationException);
    EXPECT_THROW(Order order("INVALID-ID-THAT-IS-TOO-LONG", "2024-01-15", ""), DataValidationException);
    EXPECT_THROW(Order order("ORD-001", "invalid-date", ""), DataValidationException);
    std::string longNotes(501, 'a');
    EXPECT_THROW(Order order("ORD-001", "2024-01-15", longNotes), DataValidationException);
}

TEST(OrderTest, ItemManagement) {
    Order order("ORD-001", "2024-01-15", "");
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book 1", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"),
        BookTitle("Test Book 2", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        24.99
    );
    auto item1 = std::make_shared<OrderItem>(book1, 5, 19.99, 10.0);
    auto item2 = std::make_shared<OrderItem>(book2, 3, 24.99, 5.0);
    order.addItem(item1);
    order.addItem(item2);
    EXPECT_EQ(order.getItemCount(), 2);
    EXPECT_FALSE(order.isEmpty());
    EXPECT_TRUE(order.containsBook("9783161484100"));
    EXPECT_EQ(order.getBookQuantity("9783161484100"), 5);
    EXPECT_GT(order.getTotalAmount(), 0);
    order.removeItem(item1);
    EXPECT_EQ(order.getItemCount(), 1);
    EXPECT_TRUE(order.containsBook("0306406152"));
}

TEST(OrderTest, InvalidItemOperations) {
    Order order("ORD-001", "2024-01-15", "");
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    EXPECT_THROW(order.addItem(nullptr), DataValidationException);
    auto item = std::make_shared<OrderItem>(book, 5, 19.99, 10.0);
    order.addItem(item);
    EXPECT_THROW(order.addItem(item), DuplicateBookException);
    auto nonExistentItem = std::make_shared<OrderItem>(book, 3, 15.0, 0.0);
    EXPECT_THROW(order.removeItem(nonExistentItem), BookNotFoundException);
}

TEST(OrderTest, StatusOperations) {
    Order order("ORD-001", "2024-01-15", "");
    order.setStatus(OrderStatus::Status::CONFIRMED, "2024-01-16");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::CONFIRMED);
    EXPECT_TRUE(order.isCancellable());
    order.cancelOrder("2024-01-17");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::CANCELLED);
    EXPECT_FALSE(order.isCancellable());
    EXPECT_TRUE(order.isCompleted());
}

TEST(OrderTest, InvalidStatusOperations) {
    Order order("ORD-001", "2024-01-15", "");
    EXPECT_THROW(order.setStatus(OrderStatus::Status::DELIVERED, "2024-01-16"), OrderProcessingException);
}

TEST(OrderTest, NotesOperations) {
    Order order("ORD-001", "2024-01-15", "Initial notes");
    order.setNotes("Updated notes");
    EXPECT_EQ(order.getNotes(), "Updated notes");
    std::string longNotes(500, 'a');
    EXPECT_NO_THROW(order.setNotes(longNotes));
    std::string tooLongNotes(501, 'a');
    EXPECT_THROW(order.setNotes(tooLongNotes), DataValidationException);
}

TEST(OrderTest, DiscountCalculation) {
    Order order("ORD-001", "2024-01-15", "");
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book 1", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"),
        BookTitle("Test Book 2", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        24.99
    );
    auto item1 = std::make_shared<OrderItem>(book1, 5, 20.0, 10.0);
    auto item2 = std::make_shared<OrderItem>(book2, 3, 15.0, 5.0);
    order.addItem(item1);
    order.addItem(item2);
    EXPECT_GT(order.getTotalDiscount(), 0);
}

TEST(OrderTest, GetInfo) {
    Order order("ORD-001", "2024-01-15", "Test order");
    std::string info = order.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("ORD-001"), std::string::npos);
    EXPECT_NE(info.find("2024-01-15"), std::string::npos);
}

TEST(OrderTest, EqualityOperators) {
    Order order1("ORD-001", "2024-01-15", "");
    Order order2("ORD-001", "2024-01-16", "Different notes");
    Order order3("ORD-002", "2024-01-15", "");
    EXPECT_TRUE(order1 == order2);
    EXPECT_FALSE(order1 == order3);
    EXPECT_TRUE(order1 != order3);
}

TEST(ShippingInfoTest, ConstructorValidData) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    EXPECT_NO_THROW(ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                    "TRK123456", "Test Carrier", 15.0, 5.0, "2024-01-20"));
    ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::EXPRESS,
                     "TRK789012", "Fast Carrier", 25.0, 0.0, "");
    EXPECT_EQ(info.getShippingAddress(), shippingAddress);
    EXPECT_EQ(info.getReturnAddress(), returnAddress);
    EXPECT_EQ(info.getMethod(), ShippingInfo::ShippingMethod::EXPRESS);
    EXPECT_EQ(info.getTrackingNumber(), "TRK789012");
    EXPECT_EQ(info.getCarrier(), "Fast Carrier");
    EXPECT_DOUBLE_EQ(info.getShippingCost(), 25.0);
    EXPECT_DOUBLE_EQ(info.getInsuranceCost(), 0.0);
}

TEST(ShippingInfoTest, ConstructorInvalidData) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    EXPECT_THROW(ShippingInfo info(nullptr, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                 "TRK123", "Carrier", 10.0, 0.0, ""), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddress, nullptr, ShippingInfo::ShippingMethod::STANDARD,
                                 "TRK123", "Carrier", 10.0, 0.0, ""), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                 "", "Carrier", 10.0, 0.0, ""), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                 "TRK123", "", 10.0, 0.0, ""), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                 "TRK123", "Carrier", -10.0, 0.0, ""), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                 "TRK123", "Carrier", 10.0, -5.0, ""), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                                 "TRK123", "Carrier", 10.0, 0.0, "invalid-date"), DataValidationException);
}

TEST(ShippingInfoTest, StatusOperations) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK123456", "Carrier", 15.0, 5.0, "2024-01-20");
    EXPECT_FALSE(info.isDelivered());
    EXPECT_FALSE(info.isInTransit());
    info.setStatus(ShippingInfo::ShippingStatus::IN_TRANSIT);
    EXPECT_TRUE(info.isInTransit());
    info.setActualDelivery("2024-01-25");
    EXPECT_TRUE(info.isDelivered());
    EXPECT_EQ(info.getStatus(), ShippingInfo::ShippingStatus::DELIVERED);
}

TEST(ShippingInfoTest, CostCalculations) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK123456", "Carrier", 15.0, 5.0, "2024-01-20");
    EXPECT_DOUBLE_EQ(info.getTotalShippingCost(), 20.0);
}

TEST(ShippingInfoTest, MethodAndStatusStrings) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo standard(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                         "TRK123", "Carrier", 10.0, 0.0, "");
    ShippingInfo express(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::EXPRESS,
                        "TRK456", "Carrier", 25.0, 0.0, "");
    EXPECT_EQ(standard.getMethodString(), "Standard");
    EXPECT_EQ(express.getMethodString(), "Express");
    EXPECT_EQ(standard.getStatusString(), "Pending");
    standard.setStatus(ShippingInfo::ShippingStatus::IN_TRANSIT);
    EXPECT_EQ(standard.getStatusString(), "In Transit");
}

TEST(ShippingInfoTest, SignatureRequirements) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo standard(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                         "TRK123", "Carrier", 10.0, 0.0, "");
    ShippingInfo express(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::EXPRESS,
                        "TRK456", "Carrier", 25.0, 0.0, "");
    ShippingInfo highInsurance(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                              "TRK789", "Carrier", 10.0, 150.0, "");
    EXPECT_FALSE(standard.requiresSignature());
    EXPECT_TRUE(express.requiresSignature());
    EXPECT_TRUE(highInsurance.requiresSignature());
}

TEST(ShippingInfoTest, TrackingOperations) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK123456", "Carrier", 15.0, 5.0, "2024-01-20");
    info.setTrackingNumber("TRK-NEW-123");
    EXPECT_EQ(info.getTrackingNumber(), "TRK-NEW-123");
    EXPECT_THROW(info.setTrackingNumber(""), DataValidationException);
}

TEST(ShippingInfoTest, GetInfo) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK123456", "Test Carrier", 15.0, 5.0, "2024-01-20");
    std::string infoStr = info.getInfo();
    EXPECT_FALSE(infoStr.empty());
    EXPECT_NE(infoStr.find("Standard"), std::string::npos);
    EXPECT_NE(infoStr.find("Test Carrier"), std::string::npos);
}

TEST(ShippingInfoTest, EqualityOperators) {
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info1(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                      "TRK123456", "Carrier", 15.0, 5.0, "2024-01-20");
    ShippingInfo info2(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::STANDARD,
                      "TRK123456", "Carrier", 15.0, 5.0, "2024-01-20");
    ShippingInfo info3(shippingAddress, returnAddress, ShippingInfo::ShippingMethod::EXPRESS,
                      "TRK123456", "Carrier", 15.0, 5.0, "2024-01-20");
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 == info3);
    EXPECT_TRUE(info1 != info3);
}

TEST(CustomerOrderTest, ConstructorValidData) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    EXPECT_NO_THROW(CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping, "Test notes"));
    CustomerOrder order("CUST-ORD-002", "2024-01-16", customer, shipping);
    EXPECT_EQ(order.getCustomer(), customer);
    EXPECT_EQ(order.getShippingInfo(), shipping);
    EXPECT_DOUBLE_EQ(order.getCustomerDiscount(), 0.0);
    EXPECT_DOUBLE_EQ(order.getTaxAmount(), 0.0);
}

TEST(CustomerOrderTest, ConstructorInvalidData) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    EXPECT_THROW(CustomerOrder order("CUST-ORD-001", "2024-01-15", nullptr, shipping), DataValidationException);
    EXPECT_THROW(CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, nullptr), ShippingException);
    EXPECT_NO_THROW(CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping));
    CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping);
    EXPECT_NO_THROW(order.processPayment("2025-10-10"));
    EXPECT_ANY_THROW(order.shipOrder("2025-10-10"));
    EXPECT_ANY_THROW(order.shipOrder("2025-10-120"));
    CustomerOrder orderTwo("CUST-ORD-002", "2024-01-15", customer, shipping);
    EXPECT_THROW(orderTwo.shipOrder("2025-10-12"), InvalidOrderStateException);
}

TEST(CustomerOrderTest, DiscountAndTaxOperations) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::GOLD), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto item = std::make_shared<OrderItem>(book, 5, 20.0, 0.0);
    order.addItem(item);
    order.setCustomerDiscount(15.0);
    order.setTaxAmount(10.0);
    EXPECT_DOUBLE_EQ(order.getCustomerDiscount(), 15.0);
    EXPECT_DOUBLE_EQ(order.getTaxAmount(), 10.0);
    EXPECT_GT(order.getFinalAmount(), 0);
    EXPECT_THROW(order.setCustomerDiscount(-1.0), DataValidationException);
    EXPECT_THROW(order.setCustomerDiscount(51.0), DataValidationException);
    EXPECT_THROW(order.setTaxAmount(-1.0), DataValidationException);
}

TEST(CustomerOrderTest, ShippingOperations) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::GOLD), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        100.0
    );
    auto item = std::make_shared<OrderItem>(book, 2, 100.0, 0.0);
    order.addItem(item);
    EXPECT_TRUE(order.qualifiesForFreeShipping());
    auto newShipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                    ShippingInfo::ShippingMethod::EXPRESS,
                                                    "TRK789012", "Fast Carrier", 25.0, 0.0, "");
    order.setShippingInfo(newShipping);
    EXPECT_EQ(order.getShippingInfo(), newShipping);
    EXPECT_THROW(order.setShippingInfo(nullptr), DataValidationException);
}

TEST(CustomerOrderTest, CategoryDiscountApplication) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::GOLD), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping);
    order.applyCustomerCategoryDiscount();
    EXPECT_DOUBLE_EQ(order.getCustomerDiscount(), 10.0);
}

TEST(CustomerOrderTest, GetInfo) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::GOLD), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Test Carrier", 15.0, 0.0, "");
    CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, shipping);
    std::string info = order.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("CUST-ORD-001"), std::string::npos);
    EXPECT_NE(info.find("John Doe"), std::string::npos);
}

TEST(CustomerOrderTest, EqualityOperators) {
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    CustomerOrder order1("CUST-ORD-001", "2024-01-15", customer, shipping);
    CustomerOrder order2("CUST-ORD-001", "2024-01-16", customer, shipping);
    CustomerOrder order3("CUST-ORD-002", "2024-01-15", customer, shipping);
    EXPECT_TRUE(order1 == order2);
    EXPECT_FALSE(order1 == order3);
    EXPECT_TRUE(order1 != order3);
}

TEST(PurchaseOrderTest, ConstructorValidData) {
    EXPECT_NO_THROW(PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                                      "supplier@test.com", "2024-01-25", 50.0, "Test notes"));
    PurchaseOrder order("PURCH-ORD-002", "2024-01-16", "Another Supplier", 
                       "contact@supplier.com", "2024-01-30", 75.0);
    EXPECT_EQ(order.getSupplierName(), "Another Supplier");
    EXPECT_EQ(order.getSupplierContact(), "contact@supplier.com");
    EXPECT_EQ(order.getExpectedDeliveryDate(), "2024-01-30");
    EXPECT_DOUBLE_EQ(order.getShippingCost(), 75.0);
    EXPECT_FALSE(order.isOrReceived());
    EXPECT_EQ(order.getActualDeliveryDate(), "");
}

TEST(PurchaseOrderTest, ConstructorInvalidData) {
    EXPECT_THROW(PurchaseOrder order("", "2024-01-15", "Supplier", "contact@test.com", 
                                   "2024-01-25", 50.0), DataValidationException);
    EXPECT_THROW(PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "", "contact@test.com", 
                                   "2024-01-25", 50.0), DataValidationException);
    EXPECT_THROW(PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Supplier", "", 
                                   "2024-01-25", 50.0), DataValidationException);
    EXPECT_THROW(PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Supplier", "contact@test.com", 
                                   "invalid-date", 50.0), DataValidationException);
    EXPECT_THROW(PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Supplier", "contact@test.com", 
                                   "2024-01-25", -10.0), ShippingException);
}

TEST(PurchaseOrderTest, SupplierOperations) {
    PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                       "old@test.com", "2024-01-25", 50.0);
    order.setSupplierContact("new@test.com");
    EXPECT_EQ(order.getSupplierContact(), "new@test.com");
    order.setExpectedDeliveryDate("2024-02-01");
    EXPECT_EQ(order.getExpectedDeliveryDate(), "2024-02-01");
    order.setShippingCost(60.0);
    EXPECT_DOUBLE_EQ(order.getShippingCost(), 60.0);
    EXPECT_THROW(order.setSupplierContact(""), DataValidationException);
    EXPECT_THROW(order.setExpectedDeliveryDate("invalid-date"), DataValidationException);
    EXPECT_THROW(order.setShippingCost(-10.0), DataValidationException);
}

TEST(PurchaseOrderTest, CostCalculations) {
    PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                       "contact@test.com", "2024-01-25", 50.0);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto item = std::make_shared<OrderItem>(book, 10, 15.0, 0.0);
    order.addItem(item);
    EXPECT_GT(order.getTotalCost(), 0);
}

TEST(PurchaseOrderTest, InvalidReceiveOrder) {
    PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                       "contact@test.com", "2024-01-25", 50.0);
    EXPECT_THROW(order.receiveOrder("2024-01-24"), InvalidOrderStateException);
    order.setStatus(OrderStatus::Status::CONFIRMED, "2024-01-16");
    EXPECT_THROW(order.receiveOrder("invalid-date"), DataValidationException);
}

TEST(PurchaseOrderTest, OverdueCheck) {
    PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                       "contact@test.com", "2024-12-31", 50.0);
    EXPECT_TRUE(order.isOverdue());
}

TEST(PurchaseOrderTest, GetInfo) {
    PurchaseOrder order("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                       "contact@test.com", "2024-01-25", 50.0, "Test purchase");
    std::string info = order.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("PURCH-ORD-001"), std::string::npos);
    EXPECT_NE(info.find("Test Supplier"), std::string::npos);
}

TEST(PurchaseOrderTest, EqualityOperators) {
    PurchaseOrder order1("PURCH-ORD-001", "2024-01-15", "Test Supplier", 
                        "contact@test.com", "2024-01-25", 50.0);
    PurchaseOrder order2("PURCH-ORD-001", "2024-01-16", "Different Supplier", 
                        "different@test.com", "2024-01-30", 75.0);
    PurchaseOrder order3("PURCH-ORD-002", "2024-01-15", "Test Supplier", 
                        "contact@test.com", "2024-01-25", 50.0);
    EXPECT_TRUE(order1 != order2);
    EXPECT_FALSE(order1 == order3);
    EXPECT_TRUE(order1 != order3);
}

TEST(OrderManagerTest, ConstructorValidData) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    EXPECT_NO_THROW(OrderManager manager(warehouseManager));
    OrderManager manager(warehouseManager);
    EXPECT_EQ(manager.getWarehouseManager(), warehouseManager);
}

TEST(OrderManagerTest, ConstructorInvalidData) {
    EXPECT_THROW(OrderManager manager(nullptr), DataValidationException);
}

TEST(OrderManagerTest, WarehouseManagerOperations) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    OrderManager manager(warehouseManager);
    auto newWarehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("New Warehouse", "New Address")
    );
    manager.setWarehouseManager(newWarehouseManager);
    EXPECT_EQ(manager.getWarehouseManager(), newWarehouseManager);
    EXPECT_THROW(manager.setWarehouseManager(nullptr), DataValidationException);
}

TEST(OrderManagerTest, CreateCustomerOrder) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto section = std::make_shared<WarehouseSection>("A", "General", "", WarehouseSection::SectionType::GENERAL);
    auto shelf = std::make_shared<Shelf>("A-01", 2);
    auto location = std::make_shared<StorageLocation>("A-01-B-01", 100, 0, StorageLocation::LocationStatus::FREE);
    shelf->addLocation(location);
    section->addShelf(shelf);
    warehouse->addSection(section);
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager manager(warehouseManager);
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto inventoryItem = std::make_shared<InventoryItem>(book, 10, location, "2024-01-15");
    warehouse->addInventoryItem(inventoryItem);
    auto item = std::make_shared<OrderItem>(book, 5, 19.99, 10.0);
    std::vector<std::shared_ptr<OrderItem>> items = {item};
    auto order = manager.createCustomerOrder(customer, shipping, items, "Test order");
    EXPECT_NE(order, nullptr);
    EXPECT_EQ(order->getCustomer(), customer);
    EXPECT_EQ(order->getShippingInfo(), shipping);
    EXPECT_EQ(manager.getCustomerOrders().size(), 1);
}

TEST(OrderManagerTest, CreateCustomerOrderInvalidData) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    OrderManager manager(warehouseManager);
    auto customer = std::make_shared<Customer>(
        "P001", "John", "Doe", "1990-01-01",
        std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA"),
        std::make_shared<ContactInfo>("john@test.com", "+1234567890"),
        "CUST001", CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01"
    );
    auto shippingAddress = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddress, returnAddress, 
                                                 ShippingInfo::ShippingMethod::STANDARD,
                                                 "TRK123456", "Carrier", 15.0, 0.0, "");
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto item = std::make_shared<OrderItem>(book, 5, 19.99, 10.0);
    std::vector<std::shared_ptr<OrderItem>> items = {item};
    EXPECT_THROW(manager.createCustomerOrder(nullptr, shipping, items), DataValidationException);
    EXPECT_THROW(manager.createCustomerOrder(customer, nullptr, items), DataValidationException);
    EXPECT_THROW(manager.createCustomerOrder(customer, shipping, std::vector<std::shared_ptr<OrderItem>>()), DataValidationException);
}

TEST(OrderManagerTest, CreatePurchaseOrder) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    OrderManager manager(warehouseManager);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"),
        BookTitle("Test Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        19.99
    );
    auto item = std::make_shared<OrderItem>(book, 50, 15.0, 0.0);
    std::vector<std::shared_ptr<OrderItem>> items = {item};
    auto order = manager.createPurchaseOrder("Test Supplier", "contact@test.com", 
                                           "2024-01-25", items, 75.0, "Test purchase");
    EXPECT_NE(order, nullptr);
    EXPECT_EQ(order->getSupplierName(), "Test Supplier");
    EXPECT_EQ(manager.getPurchaseOrders().size(), 1);
}

TEST(OrderManagerTest, OrderRetrieval) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    OrderManager manager(warehouseManager);
    auto purchaseBook = std::make_shared<Book>(
        ISBN("0306406152"),
        BookTitle("Purchase Book", "", "EN"),
        BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION),
        std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000),
        BookCondition(BookCondition::Condition::NEW),
        24.99
    );
    auto purchaseItem = std::make_shared<OrderItem>(purchaseBook, 50, 20.0, 0.0);
    std::vector<std::shared_ptr<OrderItem>> purchaseItems = {purchaseItem};
    auto purchaseOrder = manager.createPurchaseOrder("Supplier", "contact@test.com", 
                                                   "2024-01-25", purchaseItems, 75.0);
    EXPECT_EQ(manager.findPurchaseOrder(purchaseOrder->getOrderId()), purchaseOrder);
    EXPECT_EQ(manager.findCustomerOrder("NONEXISTENT"), nullptr);
    EXPECT_EQ(manager.findPurchaseOrder("NONEXISTENT"), nullptr);
    auto purchaseOrders = manager.getPurchaseOrdersByStatus(OrderStatus::Status::CONFIRMED);
    EXPECT_EQ(purchaseOrders.size(), 1);
}

TEST(OrderManagerTest, RevenueAndStatistics) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    OrderManager manager(warehouseManager);
    std::string stats = manager.getOrderStatistics();
    EXPECT_FALSE(stats.empty());
}

TEST(OrderManagerTest, EqualityOperators) {
    auto warehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Test Warehouse", "Test Address")
    );
    OrderManager manager1(warehouseManager);
    OrderManager manager2(warehouseManager);
    auto differentWarehouseManager = std::make_shared<WarehouseManager>(
        std::make_shared<Warehouse>("Different Warehouse", "Different Address")
    );
    OrderManager manager3(differentWarehouseManager);
    EXPECT_TRUE(manager1 == manager2);
    EXPECT_FALSE(manager1 == manager3);
    EXPECT_TRUE(manager1 != manager3);
}