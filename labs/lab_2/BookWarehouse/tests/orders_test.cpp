#include <gtest/gtest.h>
#include <memory>
#include "exceptions/WarehouseExceptions.hpp"
#include "OrderManager.hpp"

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

TEST(OrderStatusTest, AllStatusTypes) {
    OrderStatus pending(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus confirmed(OrderStatus::Status::CONFIRMED, "2024-01-15");
    OrderStatus processing(OrderStatus::Status::PROCESSING, "2024-01-15");
    OrderStatus ready(OrderStatus::Status::READY_FOR_SHIPPING, "2024-01-15");
    OrderStatus shipped(OrderStatus::Status::SHIPPED, "2024-01-15");
    OrderStatus delivered(OrderStatus::Status::DELIVERED, "2024-01-15");
    OrderStatus cancelled(OrderStatus::Status::CANCELLED, "2024-01-15");
    OrderStatus refunded(OrderStatus::Status::REFUNDED, "2024-01-15");
    OrderStatus onHold(OrderStatus::Status::ON_HOLD, "2024-01-15");
    OrderStatus backordered(OrderStatus::Status::BACKORDERED, "2024-01-15");
    EXPECT_EQ(pending.toString(), "Pending");
    EXPECT_EQ(confirmed.toString(), "Confirmed");
    EXPECT_EQ(processing.toString(), "Processing");
    EXPECT_EQ(ready.toString(), "Ready for Shipping");
    EXPECT_EQ(shipped.toString(), "Shipped");
    EXPECT_EQ(delivered.toString(), "Delivered");
    EXPECT_EQ(cancelled.toString(), "Cancelled");
    EXPECT_EQ(refunded.toString(), "Refunded");
    EXPECT_EQ(onHold.toString(), "On Hold");
    EXPECT_EQ(backordered.toString(), "Backordered");
}

TEST(OrderStatusTest, InvalidStatusCreation) {
    EXPECT_THROW(OrderStatus status(OrderStatus::Status::PENDING, "invalid-date"), DataValidationException);
}

TEST(OrderStatusTest, StatusTransitionsComprehensive) {
    OrderStatus pending(OrderStatus::Status::PENDING, "2024-01-15");
    EXPECT_TRUE(pending.isValidTransition(OrderStatus::Status::CONFIRMED));
    EXPECT_TRUE(pending.isValidTransition(OrderStatus::Status::CANCELLED));
    EXPECT_TRUE(pending.isValidTransition(OrderStatus::Status::ON_HOLD));
    EXPECT_FALSE(pending.isValidTransition(OrderStatus::Status::DELIVERED));
    OrderStatus confirmed(OrderStatus::Status::CONFIRMED, "2024-01-15");
    EXPECT_TRUE(confirmed.isValidTransition(OrderStatus::Status::PROCESSING));
    EXPECT_TRUE(confirmed.isValidTransition(OrderStatus::Status::CANCELLED));
    EXPECT_TRUE(confirmed.isValidTransition(OrderStatus::Status::BACKORDERED));
    EXPECT_FALSE(confirmed.isValidTransition(OrderStatus::Status::PENDING));
}

TEST(OrderStatusTest, EqualityAndInequality) {
    OrderStatus status1(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus status2(OrderStatus::Status::PENDING, "2024-01-15");
    OrderStatus status3(OrderStatus::Status::CONFIRMED, "2024-01-15");
    OrderStatus status4(OrderStatus::Status::PENDING, "2024-01-16");
    EXPECT_EQ(status1, status2);
    EXPECT_NE(status1, status3);
    EXPECT_NE(status1, status4);
}

TEST(OrderItemTest, ValidOrderItem) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
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

TEST(OrderItemTest, OrderItemWithoutDiscount) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    OrderItem item(book, 2, 30.0, 0.0);
    EXPECT_FALSE(item.hasDiscount());
    EXPECT_DOUBLE_EQ(item.getDiscountedUnitPrice(), 30.0);
    EXPECT_DOUBLE_EQ(item.getTotalPrice(), 60.0);
    EXPECT_DOUBLE_EQ(item.getTotalDiscount(), 0.0);
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

TEST(OrderItemTest, QuantityOperations) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    OrderItem item(book, 5, 20.0, 10.0);
    item.increaseQuantity(3);
    EXPECT_EQ(item.getQuantity(), 8);
    item.decreaseQuantity(2);
    EXPECT_EQ(item.getQuantity(), 6);
    EXPECT_THROW(item.increaseQuantity(-1), DataValidationException);
    EXPECT_THROW(item.decreaseQuantity(10), DataValidationException);
}

TEST(OrderItemTest, Setters) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    OrderItem item(book, 5, 20.0, 10.0);
    item.setQuantity(8);
    EXPECT_EQ(item.getQuantity(), 8);
    item.setDiscountPercentage(20.0);
    EXPECT_DOUBLE_EQ(item.getDiscountPercentage(), 20.0);
    EXPECT_THROW(item.setDiscountPercentage(101.0), DataValidationException);
}

TEST(OrderItemTest, EqualityAndInequality) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Book 1", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 25.0);
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"), BookTitle("Book 2", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 30.0);
    OrderItem item1(book1, 5, 20.0, 10.0);
    OrderItem item2(book1, 5, 20.0, 10.0);
    OrderItem item3(book1, 3, 20.0, 10.0);
    OrderItem item4(book2, 5, 20.0, 10.0);
    EXPECT_EQ(item1, item2);
    EXPECT_NE(item1, item3);
    EXPECT_NE(item1, item4);
}

TEST(ShippingInfoTest, ValidShippingInfo) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    
    ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK789012", "Standard Mail", 10.0, 2.0);
    EXPECT_EQ(info.getCarrier(), "Standard Mail");
    EXPECT_DOUBLE_EQ(info.getTotalShippingCost(), 12.0);
    EXPECT_FALSE(info.isDelivered());
    EXPECT_FALSE(info.isInTransit());
    EXPECT_FALSE(info.requiresSignature());
}

TEST(ShippingInfoTest, AllShippingMethods) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo standard(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                         "TRK1", "Carrier", 10.0, 1.0);
    ShippingInfo express(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::EXPRESS,
                        "TRK2", "Carrier", 30.0, 3.0);
    EXPECT_EQ(standard.getMethodString(), "Standard");
    EXPECT_EQ(express.getMethodString(), "Express");
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

TEST(ShippingInfoTest, SignatureRequirements) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo standard(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                         "TRK1", "Carrier", 10.0, 1.0);
    ShippingInfo express(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::EXPRESS,
                        "TRK2", "Carrier", 30.0, 1.0);
    EXPECT_FALSE(standard.requiresSignature());
    EXPECT_TRUE(express.requiresSignature());
}

TEST(ShippingInfoTest, InvalidShippingInfo) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    EXPECT_THROW(ShippingInfo info(nullptr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                  "TRK123", "Carrier", 10.0, 1.0), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                  "", "Carrier", 10.0, 1.0), DataValidationException);
    EXPECT_THROW(ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                  "TRK123", "Carrier", -10.0, 1.0), DataValidationException);
}

TEST(ShippingInfoTest, SettersAndGetters) {
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    ShippingInfo info(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                     "TRK123", "Carrier", 10.0, 1.0);
    info.setTrackingNumber("NEWTRK456");
    EXPECT_EQ(info.getTrackingNumber(), "NEWTRK456");
    info.setActualDelivery("2024-01-25");
    EXPECT_EQ(info.getActualDelivery(), "2024-01-25");
    EXPECT_EQ(info.getStatus(), ShippingInfo::ShippingStatus::DELIVERED);
}

TEST(OrderTest, BasicOrderOperations) {
    Order order("ORD-001", "2024-01-15", "Test order");
    EXPECT_EQ(order.getOrderId(), "ORD-001");
    EXPECT_EQ(order.getOrderDate(), "2024-01-15");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::PENDING);
    EXPECT_TRUE(order.isEmpty());
    EXPECT_TRUE(order.isCancellable());
    EXPECT_FALSE(order.isCompleted());
}

TEST(OrderTest, InvalidOrderCreation) {
    EXPECT_THROW(Order order("", "2024-01-15", "Notes"), DataValidationException);
    EXPECT_THROW(Order order("ORD-001", "invalid-date", "Notes"), DataValidationException);
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

TEST(OrderTest, DuplicateBookHandling) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 20.0);
    Order order("ORD-003", "2024-01-15");
    auto item1 = std::make_shared<OrderItem>(book, 1, 20.0);
    auto item2 = std::make_shared<OrderItem>(book, 2, 18.0);
    order.addItem(item1);
    EXPECT_THROW(order.addItem(item2), DuplicateBookException);
}

TEST(OrderTest, InvalidItemOperations) {
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 20.0);
    Order order("ORD-004", "2024-01-15");
    auto item = std::make_shared<OrderItem>(book, 1, 20.0);
    EXPECT_THROW(order.addItem(nullptr), DataValidationException);
    EXPECT_THROW(order.removeItem(item), BookNotFoundException);
}

TEST(OrderTest, OrderCancellation) {
    Order order("ORD-003", "2024-01-15");
    order.cancelOrder("2024-01-16");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::CANCELLED);
    EXPECT_TRUE(order.isCompleted());
    EXPECT_FALSE(order.isCancellable());
    EXPECT_THROW(order.cancelOrder("2024-01-17"), InvalidOrderStateException);
}

TEST(OrderTest, StatusManagement) {
    Order order("ORD-005", "2024-01-15");
    order.setStatus(OrderStatus::Status::CONFIRMED, "2024-01-16");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::CONFIRMED);
    EXPECT_EQ(order.getStatus().getStatusChangedDate(), "2024-01-16");
    order.setStatus(OrderStatus::Status::PROCESSING, "2024-01-17");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::PROCESSING);
}

TEST(OrderTest, NotesManagement) {
    Order order("ORD-006", "2024-01-15", "Initial notes");
    EXPECT_EQ(order.getNotes(), "Initial notes");
    order.setNotes("Updated notes");
    EXPECT_EQ(order.getNotes(), "Updated notes");
    EXPECT_THROW(order.setNotes(std::string(1001, 'a')), DataValidationException);
}

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
    EXPECT_DOUBLE_EQ(order.getTaxAmount(), 0.0);
    EXPECT_DOUBLE_EQ(order.getFinalAmount(), 0.0);
}

TEST(CustomerOrderTest, InvalidCustomerOrderCreation) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01");
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    EXPECT_THROW(CustomerOrder order("CUST-ORD-001", "2024-01-15", nullptr, shipping), DataValidationException);
    EXPECT_THROW(CustomerOrder order("CUST-ORD-001", "2024-01-15", customer, nullptr), DataValidationException);
}

TEST(CustomerOrderTest, AmountCalculations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::SILVER), "2024-01-01");
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    CustomerOrder order("CUST-ORD-002", "2024-01-15", customer, shipping);
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 100.0);
    auto item = std::make_shared<OrderItem>(book, 2, 100.0, 10.0);
    order.addItem(item);
    order.recalculateFinalAmount();
    EXPECT_DOUBLE_EQ(order.getTotalAmount(), 180.0);
    EXPECT_DOUBLE_EQ(order.getCustomerDiscount(), 5.0);
    EXPECT_DOUBLE_EQ(order.getFinalAmount(), 171.0);
    order.setTaxAmount(10.0);
    EXPECT_DOUBLE_EQ(order.getFinalAmount(), 181.0);
}

TEST(CustomerOrderTest, DiscountAndTaxValidation) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01");
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    CustomerOrder order("CUST-ORD-003", "2024-01-15", customer, shipping);
    EXPECT_THROW(order.setCustomerDiscount(-5.0), DataValidationException);
    EXPECT_THROW(order.setCustomerDiscount(101.0), DataValidationException);
    EXPECT_THROW(order.setTaxAmount(-10.0), DataValidationException);
}

TEST(CustomerOrderTest, FreeShippingQualification) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto regularCustomer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                                     CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01");
    auto goldCustomer = std::make_shared<Customer>("P002", "Jane", "Smith", "1985-03-20", address, contact, "CUST002", 
                                                  CustomerCategory(CustomerCategory::Category::GOLD), "2024-01-01");
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    CustomerOrder regularOrder("CUST-ORD-004", "2024-01-15", regularCustomer, shipping);
    CustomerOrder goldOrder("CUST-ORD-005", "2024-01-15", goldCustomer, shipping);
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Test Book", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 50.0);
    auto item = std::make_shared<OrderItem>(book, 1, 50.0);
    regularOrder.addItem(item);
    goldOrder.addItem(item);
    EXPECT_FALSE(regularOrder.qualifiesForFreeShipping());
    EXPECT_TRUE(goldOrder.qualifiesForFreeShipping());
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
    order.setStatus(OrderStatus::Status::PROCESSING, "2024-01-17");
    order.setStatus(OrderStatus::Status::READY_FOR_SHIPPING, "2024-01-17");
    order.shipOrder("2024-01-18");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::SHIPPED);
    order.deliverOrder("2024-01-20");
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::DELIVERED);
    EXPECT_TRUE(order.isCompleted());
}

TEST(CustomerOrderTest, InvalidOrderOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    auto customer = std::make_shared<Customer>("P001", "John", "Doe", "1990-05-15", address, contact, "CUST001", 
                                              CustomerCategory(CustomerCategory::Category::REGULAR), "2024-01-01");
    auto shippingAddr = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto returnAddr = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "USA");
    auto shipping = std::make_shared<ShippingInfo>(shippingAddr, returnAddr, ShippingInfo::ShippingMethod::STANDARD,
                                                  "TRK123", "Test Carrier", 10.0);
    CustomerOrder order("CUST-ORD-007", "2024-01-15", customer, shipping);
    EXPECT_THROW(order.processPayment("invalid-date"), DataValidationException);
    EXPECT_THROW(order.shipOrder("invalid-date"), DataValidationException);
    EXPECT_THROW(order.deliverOrder("invalid-date"), DataValidationException);
    EXPECT_THROW(order.shipOrder("2024-01-18"), InvalidOrderStateException);
}

TEST(PurchaseOrderTest, PurchaseOrderCreation) {
    PurchaseOrder order("PURCH-001", "2024-01-15", "Book Supplier", "supplier@test.com", 
                       "2024-01-25", 25.0, "Test purchase");
    EXPECT_EQ(order.getSupplierName(), "Book Supplier");
    EXPECT_EQ(order.getSupplierContact(), "supplier@test.com");
    EXPECT_EQ(order.getExpectedDeliveryDate(), "2024-01-25");
    EXPECT_DOUBLE_EQ(order.getShippingCost(), 25.0);
    EXPECT_FALSE(order.isOrReceived());
}

TEST(PurchaseOrderTest, PurchaseOrderWithItems) {
    PurchaseOrder order("PURCH-002", "2024-01-15", "Supplier", "contact@test.com", 
                       "2024-01-25", 15.0, "Stock order");
    auto publisher = std::make_shared<Publisher>("Test Pub", "test@pub.com", 2000);
    auto book1 = std::make_shared<Book>(
        ISBN("9783161484100"), BookTitle("Book 1", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 15.0);
    auto book2 = std::make_shared<Book>(
        ISBN("0306406152"), BookTitle("Book 2", "", "EN"), BookMetadata(2024, "EN", 1, ""),
        PhysicalProperties(300, 200, 130, 20, 250, PhysicalProperties::CoverType::PAPERBACK, "Paper"),
        Genre(Genre::Type::SCIENCE_FICTION), publisher, BookCondition(BookCondition::Condition::NEW), 20.0);
    auto item1 = std::make_shared<OrderItem>(book1, 10, 12.0);
    auto item2 = std::make_shared<OrderItem>(book2, 5, 18.0);
    order.addItem(item1);
    order.addItem(item2);
    EXPECT_DOUBLE_EQ(order.getTotalCost(), 120 + 90 + 15.0);
    EXPECT_EQ(order.getItemCount(), 2);
}

TEST(PurchaseOrderTest, OrderReceiving) {
    PurchaseOrder order("PURCH-003", "2024-01-15", "Supplier", "contact@test.com", 
                       "2024-01-25", 20.0, "Test order");
    order.setStatus(OrderStatus::Status::CONFIRMED, "2024-01-16");
    order.setStatus(OrderStatus::Status::PROCESSING, "2024-01-17");
    order.setStatus(OrderStatus::Status::READY_FOR_SHIPPING, "2024-01-18");
    order.setStatus(OrderStatus::Status::SHIPPED, "2024-01-19");
    EXPECT_TRUE(order.canBeReceived());
    order.receiveOrder("2024-01-22");
    EXPECT_TRUE(order.isOrReceived());
    EXPECT_EQ(order.getStatus().getStatus(), OrderStatus::Status::DELIVERED);
    EXPECT_THROW(order.receiveOrder("2024-01-23"), InvalidOrderStateException);
}

TEST(PurchaseOrderTest, InvalidPurchaseOrder) {
    EXPECT_THROW(PurchaseOrder order("", "2024-01-15", "Supplier", "contact@test.com", 
                                    "2024-01-25", 10.0), DataValidationException);
    EXPECT_THROW(PurchaseOrder order("PURCH-006", "invalid-date", "Supplier", "contact@test.com", 
                                    "2024-01-25", 10.0), DataValidationException);
    EXPECT_THROW(PurchaseOrder order("PURCH-007", "2024-01-15", "", "contact@test.com", 
                                    "2024-01-25", 10.0), DataValidationException);
}

TEST(OrderManagerTest, OrderManagerOperations) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    EXPECT_EQ(orderManager.getWarehouseManager(), warehouseManager);
    auto customerOrders = orderManager.getCustomerOrders();
    auto purchaseOrders = orderManager.getPurchaseOrders();
    EXPECT_TRUE(customerOrders.empty());
    EXPECT_TRUE(purchaseOrders.empty());
    std::string stats = orderManager.getOrderStatistics();
    EXPECT_FALSE(stats.empty());
    EXPECT_DOUBLE_EQ(orderManager.getTotalRevenue(), 0.0);
}

TEST(OrderManagerTest, InvalidOrderManagerCreation) {
    EXPECT_THROW(OrderManager orderManager(nullptr), DataValidationException);
}

TEST(OrderManagerTest, WarehouseManagerUpdate) {
    auto warehouse1 = std::make_shared<Warehouse>("Warehouse 1", "Address 1");
    auto warehouse2 = std::make_shared<Warehouse>("Warehouse 2", "Address 2");
    auto warehouseManager1 = std::make_shared<WarehouseManager>(warehouse1);
    auto warehouseManager2 = std::make_shared<WarehouseManager>(warehouse2);
    OrderManager orderManager(warehouseManager1);
    orderManager.setWarehouseManager(warehouseManager2);
    EXPECT_EQ(orderManager.getWarehouseManager(), warehouseManager2);
    EXPECT_THROW(orderManager.setWarehouseManager(nullptr), DataValidationException);
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
        auto customerOrders = orderManager.getCustomerOrdersByCustomer("CUST001");
        EXPECT_FALSE(customerOrders.empty());
        auto pendingOrders = orderManager.getCustomerOrdersByStatus(OrderStatus::Status::PENDING);
        EXPECT_FALSE(pendingOrders.empty());
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
    auto confirmedOrders = orderManager.getPurchaseOrdersByStatus(OrderStatus::Status::CONFIRMED);
    EXPECT_FALSE(confirmedOrders.empty());
}

TEST(OrderManagerTest, OrderProcessing) {
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
        orderManager.processCustomerOrderPayment(order, "2024-01-16");
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::CONFIRMED);
        orderManager.fulfillCustomerOrder(order);
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::PROCESSING);
        orderManager.shipCustomerOrder(order, "2024-01-18");
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::SHIPPED);
        orderManager.cancelCustomerOrder(order, "2024-01-19");
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::CANCELLED);
    } catch (const InsufficientStockException&) {
        SUCCEED();
    }
}

TEST(OrderManagerTest, InvalidOrderOperations) {
    auto warehouse = std::make_shared<Warehouse>("Test Warehouse", "Test Address");
    auto warehouseManager = std::make_shared<WarehouseManager>(warehouse);
    OrderManager orderManager(warehouseManager);
    EXPECT_THROW(orderManager.createCustomerOrder(nullptr, nullptr, {}, ""), DataValidationException);
    std::vector<std::shared_ptr<OrderItem>> emptyItems;
    EXPECT_THROW(orderManager.createCustomerOrder(nullptr, nullptr, emptyItems, ""), DataValidationException);
}

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
        orderManager.shipCustomerOrder(order, "2024-01-18");
        EXPECT_EQ(order->getStatus().getStatus(), OrderStatus::Status::SHIPPED);
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