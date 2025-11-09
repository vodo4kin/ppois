/**
 * @file OrderStatus.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with order status enumeration and utilities
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>

/**
 * @class OrderStatus
 * @brief Class for working with order statuses and transitions
 * 
 * Defines order status lifecycle with validation for status transitions
 * and provides status tracking functionality.
 */
class OrderStatus {
public:
    /**
     * @enum Status
     * @brief Enumeration of order statuses
     */
    enum class Status {
        PENDING,        ///< Order created but not processed
        CONFIRMED,      ///< Order confirmed by staff
        PROCESSING,     ///< Order being prepared for shipment
        READY_FOR_SHIPPING, ///< Order ready for shipping
        SHIPPED,        ///< Order shipped to customer
        DELIVERED,      ///< Order delivered to customer
        CANCELLED,      ///< Order cancelled
        REFUNDED,       ///< Order refunded
        ON_HOLD,        ///< Order placed on hold
        BACKORDERED     ///< Order backordered due to stock issues
    };

private:
    Status status;      ///< Current order status
    std::string statusChangedDate; ///< Date when status was last changed

public:
    /**
     * @brief Construct a new OrderStatus object
     * 
     * @param status Status value containing initial status
     * @param statusChangedDate constant reference to the string containing status change date
     */
    OrderStatus(Status status, const std::string& statusChangedDate);

    /**
     * @brief Get the current status
     * 
     * @return Status containing current order status
     */
    Status getStatus() const noexcept;

    /**
     * @brief Get the status change date
     * 
     * @return std::string containing status change date
     */
    std::string getStatusChangedDate() const noexcept;

    /**
     * @brief Convert status to string representation
     * 
     * @return std::string containing status description
     */
    std::string toString() const noexcept;

    /**
     * @brief Check if status transition is valid
     * 
     * @param newStatus Status value containing target status
     * 
     * @return true if transition is valid
     * @return false if transition is invalid
     */
    bool isValidTransition(Status newStatus) const noexcept;

    /**
     * @brief Update order status with validation
     * 
     * @param newStatus Status value containing new status
     * @param changeDate constant reference to the string containing change date
     */
    void updateStatus(Status newStatus, const std::string& changeDate);

    /**
     * @brief Check if order is completed
     * 
     * @return true if order is completed
     * @return false if order is not completed
     */
    bool isCompleted() const noexcept;

    /**
     * @brief Check if order is active
     * 
     * @return true if order is active
     * @return false if order is not active
     */
    bool isActive() const noexcept;

    /**
     * @brief Check if order is cancellable
     * 
     * @return true if order can be cancelled
     * @return false if order cannot be cancelled
     */
    bool isCancellable() const noexcept;

    /**
     * @brief Check if order requires action
     * 
     * @return true if order requires staff action
     * @return false if order does not require action
     */
    bool requiresAction() const noexcept;

    /**
     * @brief Get next possible statuses
     * 
     * @return std::vector<Status> containing possible next statuses
     */
    std::vector<Status> getNextPossibleStatuses() const noexcept;

    /**
     * @brief Equality comparison operator for order statuses
     * 
     * @param other constant reference to the order status to compare with
     * 
     * @return true if order statuses are equal
     * @return false if order statuses are not equal
     */
    bool operator==(const OrderStatus& other) const noexcept;

    /**
     * @brief Inequality comparison operator for order statuses
     * 
     * @param other constant reference to the order status to compare with
     * 
     * @return true if order statuses are not equal
     * @return false if order statuses are equal
     */
    bool operator!=(const OrderStatus& other) const noexcept;
};