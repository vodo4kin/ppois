/**
 * @file OrderManager.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the OrderManager class for managing all order operations
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "orders/CustomerOrder.hpp"
#include "orders/PurchaseOrder.hpp"
#include "warehouse/WarehouseManager.hpp"

/**
 * @class OrderManager
 * @brief Facade class for managing all order operations in the system
 * 
 * Provides high-level interface for order management including creation,
 * processing, tracking, and integration with warehouse operations.
 */
class OrderManager {
private:
    std::vector<std::shared_ptr<CustomerOrder>> customerOrders;    ///< All customer orders
    std::vector<std::shared_ptr<PurchaseOrder>> purchaseOrders;    ///< All purchase orders
    std::shared_ptr<WarehouseManager> warehouseManager;           ///< Warehouse manager for inventory operations
    int nextCustomerOrderId;                                      ///< Next customer order ID counter
    int nextPurchaseOrderId;                                      ///< Next purchase order ID counter

    /**
     * @brief Generate unique customer order ID
     * 
     * @return std::string containing generated order ID
     */
    std::string generateCustomerOrderId();

    /**
     * @brief Generate unique purchase order ID
     * 
     * @return std::string containing generated order ID
     */
    std::string generatePurchaseOrderId();

    /**
     * @brief Validate order items availability in warehouse
     * 
     * @param items vector of order items to validate
     * 
     * @return true if all items are available
     * @return false if some items are not available
     */
    bool validateItemsAvailability(const std::vector<std::shared_ptr<OrderItem>>& items) const;

    /**
     * @brief Reserve items in warehouse for order
     * 
     * @param items vector of order items to reserve
     */
    void reserveItems(const std::vector<std::shared_ptr<OrderItem>>& items);

    /**
     * @brief Release reserved items from warehouse
     * 
     * @param items vector of order items to release
     */
    void releaseReservedItems(const std::vector<std::shared_ptr<OrderItem>>& items);

public:
    /**
     * @brief Construct a new OrderManager object
     * 
     * @param warehouseManager shared pointer to the WarehouseManager object
     */
    explicit OrderManager(std::shared_ptr<WarehouseManager> warehouseManager);

    /**
     * @brief Get the warehouse manager
     * 
     * @return std::shared_ptr<WarehouseManager> containing warehouse manager
     */
    std::shared_ptr<WarehouseManager> getWarehouseManager() const noexcept;

    /**
     * @brief Set the warehouse manager
     * 
     * @param warehouseManager shared pointer to the WarehouseManager object
     */
    void setWarehouseManager(std::shared_ptr<WarehouseManager> warehouseManager);

    // Customer Order Operations
    /**
     * @brief Create new customer order
     * 
     * @param customer shared pointer to the Customer object
     * @param shipping shared pointer to the ShippingInfo object
     * @param items vector of order items
     * @param notes constant reference to the string containing additional notes
     * 
     * @return std::shared_ptr<CustomerOrder> containing created customer order
     */
    std::shared_ptr<CustomerOrder> createCustomerOrder(
        std::shared_ptr<Customer> customer,
        std::shared_ptr<ShippingInfo> shipping,
        const std::vector<std::shared_ptr<OrderItem>>& items,
        const std::string& notes = ""
    );

    /**
     * @brief Process customer order payment
     * 
     * @param order shared pointer to the CustomerOrder object
     * @param paymentDate constant reference to the string containing payment date
     */
    void processCustomerOrderPayment(std::shared_ptr<CustomerOrder> order, const std::string& paymentDate);

    /**
     * @brief Fulfill customer order (prepare for shipping)
     * 
     * @param order shared pointer to the CustomerOrder object
     */
    void fulfillCustomerOrder(std::shared_ptr<CustomerOrder> order);

    /**
     * @brief Ship customer order
     * 
     * @param order shared pointer to the CustomerOrder object
     * @param shipDate constant reference to the string containing ship date
     */
    void shipCustomerOrder(std::shared_ptr<CustomerOrder> order, const std::string& shipDate);

    /**
     * @brief Cancel customer order
     * 
     * @param order shared pointer to the CustomerOrder object
     * @param cancelDate constant reference to the string containing cancellation date
     */
    void cancelCustomerOrder(std::shared_ptr<CustomerOrder> order, const std::string& cancelDate);

    // Purchase Order Operations
    /**
     * @brief Create new purchase order
     * 
     * @param supplierName constant reference to the string containing supplier name
     * @param supplierContact constant reference to the string containing supplier contact
     * @param expectedDeliveryDate constant reference to the string containing expected delivery date
     * @param items vector of order items
     * @param shippingCost double value containing shipping cost
     * @param notes constant reference to the string containing additional notes
     * 
     * @return std::shared_ptr<PurchaseOrder> containing created purchase order
     */
    std::shared_ptr<PurchaseOrder> createPurchaseOrder(
        const std::string& supplierName,
        const std::string& supplierContact,
        const std::string& expectedDeliveryDate,
        const std::vector<std::shared_ptr<OrderItem>>& items,
        double shippingCost = 0.0,
        const std::string& notes = ""
    );

    /**
     * @brief Receive purchase order from supplier
     * 
     * @param order shared pointer to the PurchaseOrder object
     * @param deliveryDate constant reference to the string containing delivery date
     */
    void receivePurchaseOrder(std::shared_ptr<PurchaseOrder> order, const std::string& deliveryDate);

    // Order Retrieval and Analysis
    /**
     * @brief Get all customer orders
     * 
     * @return std::vector<std::shared_ptr<CustomerOrder>> containing all customer orders
     */
    std::vector<std::shared_ptr<CustomerOrder>> getCustomerOrders() const noexcept;

    /**
     * @brief Get all purchase orders
     * 
     * @return std::vector<std::shared_ptr<PurchaseOrder>> containing all purchase orders
     */
    std::vector<std::shared_ptr<PurchaseOrder>> getPurchaseOrders() const noexcept;

    /**
     * @brief Find customer order by ID
     * 
     * @param orderId constant reference to the string containing order ID
     * 
     * @return std::shared_ptr<CustomerOrder> containing found order or nullptr
     */
    std::shared_ptr<CustomerOrder> findCustomerOrder(const std::string& orderId) const noexcept;

    /**
     * @brief Find purchase order by ID
     * 
     * @param orderId constant reference to the string containing order ID
     * 
     * @return std::shared_ptr<PurchaseOrder> containing found order or nullptr
     */
    std::shared_ptr<PurchaseOrder> findPurchaseOrder(const std::string& orderId) const noexcept;

    /**
     * @brief Get orders by status
     * 
     * @param status OrderStatus::Status value containing status to filter
     * 
     * @return std::vector<std::shared_ptr<CustomerOrder>> containing filtered customer orders
     */
    std::vector<std::shared_ptr<CustomerOrder>> getCustomerOrdersByStatus(OrderStatus::Status status) const noexcept;

    /**
     * @brief Get purchase orders by status
     * 
     * @param status OrderStatus::Status value containing status to filter
     * 
     * @return std::vector<std::shared_ptr<PurchaseOrder>> containing filtered purchase orders
     */
    std::vector<std::shared_ptr<PurchaseOrder>> getPurchaseOrdersByStatus(OrderStatus::Status status) const noexcept;

    /**
     * @brief Get orders for specific customer
     * 
     * @param customerId constant reference to the string containing customer ID
     * 
     * @return std::vector<std::shared_ptr<CustomerOrder>> containing customer's orders
     */
    std::vector<std::shared_ptr<CustomerOrder>> getCustomerOrdersByCustomer(const std::string& customerId) const noexcept;

    /**
     * @brief Get total revenue from completed orders
     * 
     * @return double containing total revenue
     */
    double getTotalRevenue() const noexcept;

    /**
     * @brief Get order statistics
     * 
     * @return std::string containing order statistics report
     */
    std::string getOrderStatistics() const;

    /**
     * @brief Equality comparison operator for order managers
     * 
     * @param other constant reference to the order manager to compare with
     * 
     * @return true if order managers are equal
     * @return false if order managers are not equal
     */
    bool operator==(const OrderManager& other) const noexcept;

    /**
     * @brief Inequality comparison operator for order managers
     * 
     * @param other constant reference to the order manager to compare with
     * 
     * @return true if order managers are not equal
     * @return false if order managers are equal
     */
    bool operator!=(const OrderManager& other) const noexcept;
};