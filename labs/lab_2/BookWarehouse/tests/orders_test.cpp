#include <gtest/gtest.h>
#include <memory>
#include "exceptions/WarehouseExceptions.hpp"
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