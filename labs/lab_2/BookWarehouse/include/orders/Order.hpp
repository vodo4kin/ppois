/**
 * @file Order.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Order base class for working with orders
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "orders/OrderStatus.hpp"
#include "orders/OrderItem.hpp"
#include "orders/ShippingInfo.hpp"

/**
 * @class Order
 * @brief Base class for all order types in the system
 * 
 * Provides common functionality for customer orders and purchase orders
 * including order items, status tracking, and basic order operations.
 */
class Order {
protected:
    std::string orderId;                        ///< Unique order identifier
    std::string orderDate;                      ///< Date when order was created
    OrderStatus status;                         ///< Current order status
    std::vector<std::shared_ptr<OrderItem>> items; ///< Order line items
    double totalAmount;                         ///< Total order amount
    std::string notes;                          ///< Additional order notes

    /**
     * @brief Private method to validate order ID
     * 
     * @param orderId constant reference to the string containing order ID to validate
     * 
     * @return true if order ID is valid
     * @return false if order ID is invalid
     */
    bool isValidOrderId(const std::string& orderId) const;

    /**
     * @brief Private method to validate order date
     * 
     * @param orderDate constant reference to the string containing order date to validate
     * 
     * @return true if order date is valid
     * @return false if order date is invalid
     */
    bool isValidOrderDate(const std::string& orderDate) const;

    /**
     * @brief Private method to validate notes
     * 
     * @param notes constant reference to the string containing notes to validate
     * 
     * @return true if notes are valid
     * @return false if notes are invalid
     */
    bool isValidNotes(const std::string& notes) const;

    /**
     * @brief Recalculate total order amount
     */
    void recalculateTotalAmount();

public:
    /**
     * @brief Construct a new Order object
     * 
     * @param orderId constant reference to the string containing order identifier
     * @param orderDate constant reference to the string containing order date
     * @param notes constant reference to the string containing additional notes
     */
    Order(const std::string& orderId, const std::string& orderDate, const std::string& notes = "");

    /**
     * @brief Destroy the Order object
     */
    virtual ~Order() = default;

    /**
     * @brief Get the order identifier
     * 
     * @return std::string containing order identifier
     */
    std::string getOrderId() const noexcept;

    /**
     * @brief Get the order date
     * 
     * @return std::string containing order date
     */
    std::string getOrderDate() const noexcept;

    /**
     * @brief Get the order status
     * 
     * @return OrderStatus containing order status
     */
    OrderStatus getStatus() const noexcept;

    /**
     * @brief Get the total amount
     * 
     * @return double containing total order amount
     */
    double getTotalAmount() const noexcept;

    /**
     * @brief Get the notes
     * 
     * @return std::string containing additional notes
     */
    std::string getNotes() const noexcept;

    /**
     * @brief Get all order items
     * 
     * @return std::vector<std::shared_ptr<OrderItem>> containing all order items
     */
    std::vector<std::shared_ptr<OrderItem>> getItems() const noexcept;

    /**
     * @brief Set the order status
     * 
     * @param newStatus OrderStatus::Status value containing new status
     * @param changeDate constant reference to the string containing status change date
     */
    void setStatus(OrderStatus::Status newStatus, const std::string& changeDate);

    /**
     * @brief Set the notes
     * 
     * @param notes constant reference to the string containing new notes
     */
    void setNotes(const std::string& notes);

    /**
     * @brief Add item to order
     * 
     * @param item shared pointer to the OrderItem object to add
     */
    void addItem(std::shared_ptr<OrderItem> item);

    /**
     * @brief Remove item from order
     * 
     * @param item shared pointer to the OrderItem object to remove
     */
    void removeItem(std::shared_ptr<OrderItem> item);

    /**
     * @brief Get the number of items in order
     * 
     * @return size_t containing number of items
     */
    size_t getItemCount() const noexcept;

    /**
     * @brief Check if order contains specific book
     * 
     * @param bookIsbn constant reference to the string containing book ISBN to check
     * 
     * @return true if order contains book
     * @return false if order does not contain book
     */
    bool containsBook(const std::string& bookIsbn) const noexcept;

    /**
     * @brief Get total quantity of specific book in order
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * 
     * @return int containing total quantity of the book
     */
    int getBookQuantity(const std::string& bookIsbn) const noexcept;

    /**
     * @brief Check if order is empty
     * 
     * @return true if order has no items
     * @return false if order has items
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Check if order is completed
     * 
     * @return true if order is completed
     * @return false if order is not completed
     */
    bool isCompleted() const noexcept;

    /**
     * @brief Check if order is cancellable
     * 
     * @return true if order can be cancelled
     * @return false if order cannot be cancelled
     */
    bool isCancellable() const noexcept;

    /**
     * @brief Cancel the order
     * 
     * @param cancelDate constant reference to the string containing cancellation date
     */
    void cancelOrder(const std::string& cancelDate);

    /**
     * @brief Calculate total discount amount for order
     * 
     * @return double containing total discount amount
     */
    double getTotalDiscount() const noexcept;

    /**
     * @brief Get order information
     * 
     * @return std::string containing formatted order information
     */
    virtual std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for orders
     * 
     * @param other constant reference to the order to compare with
     * 
     * @return true if orders are equal
     * @return false if orders are not equal
     */
    bool operator==(const Order& other) const noexcept;

    /**
     * @brief Inequality comparison operator for orders
     * 
     * @param other constant reference to the order to compare with
     * 
     * @return true if orders are not equal
     * @return false if orders are equal
     */
    bool operator!=(const Order& other) const noexcept;
};