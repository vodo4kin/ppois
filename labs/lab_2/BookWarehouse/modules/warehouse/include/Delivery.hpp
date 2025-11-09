/**
 * @file Delivery.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Delivery class for managing book deliveries
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "StockReceipt.hpp"
#include "Book.hpp"

/**
 * @class Delivery
 * @brief Class for managing book deliveries from suppliers
 * 
 * Handles complete delivery process including scheduling, tracking,
 * and integration with warehouse stock receipt operations.
 */
class Delivery {
public:
    /**
     * @enum DeliveryStatus
     * @brief Enumeration of delivery statuses
     */
    enum class DeliveryStatus {
        SCHEDULED,      ///< Delivery is scheduled
        IN_TRANSIT,     ///< Delivery is in transit
        ARRIVED,        ///< Delivery has arrived at warehouse
        UNLOADING,      ///< Delivery is being unloaded
        COMPLETED,      ///< Delivery is completed
        CANCELLED,      ///< Delivery is cancelled
        DELAYED         ///< Delivery is delayed
    };

private:
    std::string deliveryId;                         ///< Unique delivery identifier
    std::string supplierName;                       ///< Name of supplier
    std::vector<std::shared_ptr<Book>> books;       ///< Books in delivery
    std::string scheduledDate;                      ///< Scheduled delivery date
    std::string actualDate;                         ///< Actual delivery date
    DeliveryStatus status;                          ///< Current delivery status
    std::shared_ptr<StockReceipt> stockReceipt;     ///< Associated stock receipt
    std::string trackingNumber;                     ///< Delivery tracking number
    std::string carrier;                            ///< Delivery carrier company
    double shippingCost;                            ///< Shipping cost

    /**
     * @brief Private method to validate delivery ID
     * 
     * @param deliveryId constant reference to the string containing delivery ID to validate
     * 
     * @return true if delivery ID is valid
     * @return false if delivery ID is invalid
     */
    bool isValidDeliveryId(const std::string& deliveryId) const;

    /**
     * @brief Private method to validate tracking number
     * 
     * @param trackingNumber constant reference to the string containing tracking number to validate
     * 
     * @return true if tracking number is valid
     * @return false if tracking number is invalid
     */
    bool isValidTrackingNumber(const std::string& trackingNumber) const;

    /**
     * @brief Private method to validate shipping cost
     * 
     * @param cost double value containing shipping cost to validate
     * 
     * @return true if shipping cost is valid
     * @return false if shipping cost is invalid
     */
    bool isValidShippingCost(double cost) const;

public:
    /**
     * @brief Construct a new Delivery object
     * 
     * @param deliveryId constant reference to the string containing delivery identifier
     * @param supplierName constant reference to the string containing supplier name
     * @param scheduledDate constant reference to the string containing scheduled date
     * @param trackingNumber constant reference to the string containing tracking number
     * @param carrier constant reference to the string containing carrier company
     * @param shippingCost double value containing shipping cost
     */
    Delivery(const std::string& deliveryId, const std::string& supplierName,
             const std::string& scheduledDate, const std::string& trackingNumber,
             const std::string& carrier, double shippingCost);

    /**
     * @brief Get the delivery identifier
     * 
     * @return std::string containing delivery identifier
     */
    std::string getDeliveryId() const noexcept;

    /**
     * @brief Get the supplier name
     * 
     * @return std::string containing supplier name
     */
    std::string getSupplierName() const noexcept;

    /**
     * @brief Get the scheduled date
     * 
     * @return std::string containing scheduled date
     */
    std::string getScheduledDate() const noexcept;

    /**
     * @brief Get the actual date
     * 
     * @return std::string containing actual delivery date
     */
    std::string getActualDate() const noexcept;

    /**
     * @brief Get the delivery status
     * 
     * @return DeliveryStatus containing delivery status
     */
    DeliveryStatus getStatus() const noexcept;

    /**
     * @brief Get the tracking number
     * 
     * @return std::string containing tracking number
     */
    std::string getTrackingNumber() const noexcept;

    /**
     * @brief Get the carrier company
     * 
     * @return std::string containing carrier company
     */
    std::string getCarrier() const noexcept;

    /**
     * @brief Get the shipping cost
     * 
     * @return double containing shipping cost
     */
    double getShippingCost() const noexcept;

    /**
     * @brief Get all books in delivery
     * 
     * @return std::vector<std::shared_ptr<Book>> containing all books
     */
    std::vector<std::shared_ptr<Book>> getBooks() const noexcept;

    /**
     * @brief Get the associated stock receipt
     * 
     * @return std::shared_ptr<StockReceipt> containing stock receipt
     */
    std::shared_ptr<StockReceipt> getStockReceipt() const noexcept;

    /**
     * @brief Add book to delivery
     * 
     * @param book shared pointer to the Book object to add
     */
    void addBook(std::shared_ptr<Book> book);

    /**
     * @brief Remove book from delivery
     * 
     * @param book shared pointer to the Book object to remove
     */
    void removeBook(std::shared_ptr<Book> book);

    /**
     * @brief Set the delivery status
     * 
     * @param status DeliveryStatus value containing new status
     */
    void setStatus(DeliveryStatus status) noexcept;

    /**
     * @brief Set the actual delivery date
     * 
     * @param date constant reference to the string containing actual date
     */
    void setActualDate(const std::string& date);

    /**
     * @brief Set the associated stock receipt
     * 
     * @param receipt shared pointer to the StockReceipt object
     */
    void setStockReceipt(std::shared_ptr<StockReceipt> receipt);

    /**
     * @brief Check if delivery contains specific book
     * 
     * @param book shared pointer to the Book object to check
     * 
     * @return true if delivery contains book
     * @return false if delivery does not contain book
     */
    bool containsBook(std::shared_ptr<Book> book) const noexcept;

    /**
     * @brief Get the number of books in delivery
     * 
     * @return size_t containing number of books
     */
    size_t getBookCount() const noexcept;

    /**
     * @brief Check if delivery is completed
     * 
     * @return true if delivery is completed
     * @return false if delivery is not completed
     */
    bool isCompleted() const noexcept;

    /**
     * @brief Check if delivery is in transit
     * 
     * @return true if delivery is in transit
     * @return false if delivery is not in transit
     */
    bool isInTransit() const noexcept;

    /**
     * @brief Check if delivery is delayed
     * 
     * @return true if delivery is delayed
     * @return false if delivery is not delayed
     */
    bool isDelayed() const noexcept;

    /**
     * @brief Process delivery arrival
     * 
     * Marks delivery as arrived and sets actual date
     */
    void processArrival();

    /**
     * @brief Complete delivery processing
     * 
     * Marks delivery as completed and creates stock receipt
     */
    void completeDelivery();

    /**
     * @brief Get delivery information
     * 
     * @return std::string containing formatted delivery information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Get delivery status as string
     * 
     * @return std::string containing delivery status description
     */
    std::string getStatusString() const noexcept;

    /**
     * @brief Equality comparison operator for deliveries
     * 
     * @param other constant reference to the delivery to compare with
     * 
     * @return true if deliveries are equal
     * @return false if deliveries are not equal
     */
    bool operator==(const Delivery& other) const noexcept;

    /**
     * @brief Inequality comparison operator for deliveries
     * 
     * @param other constant reference to the delivery to compare with
     * 
     * @return true if deliveries are not equal
     * @return false if deliveries are equal
     */
    bool operator!=(const Delivery& other) const noexcept;
};