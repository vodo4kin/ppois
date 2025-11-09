#include "OrderManager.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/OrderConfig.hpp"

std::string OrderManager::generateCustomerOrderId() {
    return "CUST-ORD-" + std::to_string(nextCustomerOrderId++);
}

std::string OrderManager::generatePurchaseOrderId() {
    return "PURCH-ORD-" + std::to_string(nextPurchaseOrderId++);
}

bool OrderManager::validateItemsAvailability(const std::vector<std::shared_ptr<OrderItem>>& items) const {
    if (!warehouseManager) {
        throw WarehouseException("Warehouse manager not set");
    }
    for (const auto& item : items) {
        std::string bookIsbn = item->getBook()->getISBN().getCode();
        int requiredQuantity = item->getQuantity();
        if (!warehouseManager->isBookAvailable(bookIsbn, requiredQuantity)) {
            return false;
        }
    }
    return true;
}

void OrderManager::reserveItems(const std::vector<std::shared_ptr<OrderItem>>& items) {
    // In a real system, this would reserve items in warehouse
    // For now, we'll just validate availability
    if (!validateItemsAvailability(items)) {
        throw InsufficientStockException("Not all items are available in required quantities");
    }
}

void OrderManager::releaseReservedItems(const std::vector<std::shared_ptr<OrderItem>>& items) {
    // In a real system, this would release reserved items
    // For now, this is a placeholder
}

OrderManager::OrderManager(std::shared_ptr<WarehouseManager> warehouseManager) {
    if (!warehouseManager) {
        throw DataValidationException("Warehouse manager cannot be null");
    }
    this->warehouseManager = warehouseManager;
    this->nextCustomerOrderId = OrderConfig::OrderManager::START_CUSTOMER_ORDER_ID;
    this->nextPurchaseOrderId = OrderConfig::OrderManager::START_PURCHASE_ORDER_ID;
}

std::shared_ptr<WarehouseManager> OrderManager::getWarehouseManager() const noexcept {
    return warehouseManager;
}

void OrderManager::setWarehouseManager(std::shared_ptr<WarehouseManager> warehouseManager) {
    if (!warehouseManager) {
        throw DataValidationException("Warehouse manager cannot be null");
    }
    this->warehouseManager = warehouseManager;
}

std::shared_ptr<CustomerOrder> OrderManager::createCustomerOrder(
    std::shared_ptr<Customer> customer,
    std::shared_ptr<ShippingInfo> shipping,
    const std::vector<std::shared_ptr<OrderItem>>& items,
    const std::string& notes) {
    if (!customer) {
        throw DataValidationException("Customer cannot be null");
    }
    if (!shipping) {
        throw DataValidationException("Shipping info cannot be null");
    }
    if (items.empty()) {
        throw DataValidationException("Order must contain at least one item");
    }
    reserveItems(items);
    std::string orderId = generateCustomerOrderId();
    std::string orderDate = DateUtils::getCurrentDate();
    auto order = std::make_shared<CustomerOrder>(orderId, orderDate, customer, shipping, notes);
    for (const auto& item : items) {
        order->addItem(item);
    }
    customerOrders.push_back(order);
    return order;
}

void OrderManager::processCustomerOrderPayment(std::shared_ptr<CustomerOrder> order, const std::string& paymentDate) {
    if (!order) {
        throw DataValidationException("Order cannot be null");
    }
    order->processPayment(paymentDate);
}

void OrderManager::fulfillCustomerOrder(std::shared_ptr<CustomerOrder> order) {
    if (!order) {
        throw DataValidationException("Order cannot be null");
    }
    
    if (order->getStatus().getStatus() != OrderStatus::Status::CONFIRMED) {
        throw InvalidOrderStateException("Order must be confirmed before fulfillment");
    }
    order->setStatus(OrderStatus::Status::PROCESSING, DateUtils::getCurrentDate());
}

void OrderManager::shipCustomerOrder(std::shared_ptr<CustomerOrder> order, const std::string& shipDate) {
    if (!order) {
        throw DataValidationException("Order cannot be null");
    }
    order->shipOrder(shipDate);
}

void OrderManager::cancelCustomerOrder(std::shared_ptr<CustomerOrder> order, const std::string& cancelDate) {
    if (!order) {
        throw DataValidationException("Order cannot be null");
    }
    if (!order->isCancellable()) {
        throw InvalidOrderStateException("Order cannot be cancelled in current state");
    }
    order->cancelOrder(cancelDate);
    releaseReservedItems(order->getItems());
}

std::shared_ptr<PurchaseOrder> OrderManager::createPurchaseOrder(
    const std::string& supplierName,
    const std::string& supplierContact,
    const std::string& expectedDeliveryDate,
    const std::vector<std::shared_ptr<OrderItem>>& items,
    double shippingCost,
    const std::string& notes) {
    if (items.empty()) {
        throw DataValidationException("Purchase order must contain at least one item");
    }
    std::string orderId = generatePurchaseOrderId();
    std::string orderDate = DateUtils::getCurrentDate();
    auto order = std::make_shared<PurchaseOrder>(orderId, orderDate, supplierName, supplierContact, 
                                                expectedDeliveryDate, shippingCost, notes);
    for (const auto& item : items) {
        order->addItem(item);
    }
    order->setStatus(OrderStatus::Status::CONFIRMED, orderDate);
    purchaseOrders.push_back(order);
    return order;
}

void OrderManager::receivePurchaseOrder(std::shared_ptr<PurchaseOrder> order, const std::string& deliveryDate) {
    if (!order) {
        throw DataValidationException("Order cannot be null");
    }
    order->receiveOrder(deliveryDate);
    // In a real system, this would add received items to warehouse inventory
    // For now, we'll just mark the order as received
}

std::vector<std::shared_ptr<CustomerOrder>> OrderManager::getCustomerOrders() const noexcept {
    return customerOrders;
}

std::vector<std::shared_ptr<PurchaseOrder>> OrderManager::getPurchaseOrders() const noexcept {
    return purchaseOrders;
}

std::shared_ptr<CustomerOrder> OrderManager::findCustomerOrder(const std::string& orderId) const noexcept {
    for (const auto& order : customerOrders) {
        if (order->getOrderId() == orderId) {
            return order;
        }
    }
    return nullptr;
}

std::shared_ptr<PurchaseOrder> OrderManager::findPurchaseOrder(const std::string& orderId) const noexcept {
    for (const auto& order : purchaseOrders) {
        if (order->getOrderId() == orderId) {
            return order;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<CustomerOrder>> OrderManager::getCustomerOrdersByStatus(OrderStatus::Status status) const noexcept {
    std::vector<std::shared_ptr<CustomerOrder>> result;
    for (const auto& order : customerOrders) {
        if (order->getStatus().getStatus() == status) {
            result.push_back(order);
        }
    }
    return result;
}

std::vector<std::shared_ptr<PurchaseOrder>> OrderManager::getPurchaseOrdersByStatus(OrderStatus::Status status) const noexcept {
    std::vector<std::shared_ptr<PurchaseOrder>> result;
    for (const auto& order : purchaseOrders) {
        if (order->getStatus().getStatus() == status) {
            result.push_back(order);
        }
    }
    return result;
}

std::vector<std::shared_ptr<CustomerOrder>> OrderManager::getCustomerOrdersByCustomer(const std::string& customerId) const noexcept {
    std::vector<std::shared_ptr<CustomerOrder>> result;
    for (const auto& order : customerOrders) {
        if (order->getCustomer()->getCustomerId() == customerId) {
            result.push_back(order);
        }
    }
    return result;
}

double OrderManager::getTotalRevenue() const noexcept {
    double revenue = 0.0;
    for (const auto& order : customerOrders) {
        if (order->getStatus().getStatus() == OrderStatus::Status::DELIVERED) {
            revenue += order->getFinalAmount();
        }
    }
    return revenue;
}

std::string OrderManager::getOrderStatistics() const {
    int totalCustomerOrders = customerOrders.size();
    int totalPurchaseOrders = purchaseOrders.size();
    int pendingCustomerOrders = getCustomerOrdersByStatus(OrderStatus::Status::PENDING).size();
    int completedCustomerOrders = getCustomerOrdersByStatus(OrderStatus::Status::DELIVERED).size();
    double totalRevenue = getTotalRevenue();
    return "Customer Orders: " + std::to_string(totalCustomerOrders) +
           ", Purchase Orders: " + std::to_string(totalPurchaseOrders) +
           ", Pending: " + std::to_string(pendingCustomerOrders) +
           ", Completed: " + std::to_string(completedCustomerOrders) +
           ", Total Revenue: " + std::to_string(totalRevenue);
}

bool OrderManager::operator==(const OrderManager& other) const noexcept {
    return warehouseManager == other.warehouseManager;
}

bool OrderManager::operator!=(const OrderManager& other) const noexcept {
    return !(*this == other);
}