/**
 * @file WarehouseManager.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the WarehouseManager class for managing warehouse operations
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Warehouse.hpp"
#include "StockReceipt.hpp"
#include "StockWriteOff.hpp"
#include "StockTransfer.hpp"
#include "Delivery.hpp"
#include "Book.hpp"
#include "StorageLocation.hpp"

/**
 * @class WarehouseManager
 * @brief Facade class for managing all warehouse operations
 * 
 * Provides high-level interface for common warehouse operations,
 * coordinating between different components and simplifying complex workflows.
 */
class WarehouseManager {
private:
    std::shared_ptr<Warehouse> warehouse;  ///< Managed warehouse instance

    /**
     * @brief Private method to validate warehouse exists
     * 
     * @throws WarehouseException if warehouse is not set
     */
    void validateWarehouse() const;

    /**
     * @brief Private method to generate unique movement ID
     * 
     * @param prefix constant reference to the string containing ID prefix
     * 
     * @return std::string containing generated movement ID
     */
    std::string generateMovementId(const std::string& prefix) const;

public:
    /**
     * @brief Construct a new WarehouseManager object
     * 
     * @param warehouse shared pointer to the Warehouse object to manage
     */
    explicit WarehouseManager(std::shared_ptr<Warehouse> warehouse);

    /**
     * @brief Get the managed warehouse
     * 
     * @return std::shared_ptr<Warehouse> containing managed warehouse
     */
    std::shared_ptr<Warehouse> getWarehouse() const noexcept;

    /**
     * @brief Set the managed warehouse
     * 
     * @param warehouse shared pointer to the Warehouse object
     */
    void setWarehouse(std::shared_ptr<Warehouse> warehouse);

    // Stock Receipt Operations
    /**
     * @brief Process stock receipt from supplier
     * 
     * @param supplierName constant reference to the string containing supplier name
     * @param purchaseOrderNumber constant reference to the string containing purchase order number
     * @param invoiceNumber constant reference to the string containing invoice number
     * @param totalCost double value containing total cost
     * @param items vector of pairs containing book and quantity
     * @param employeeId constant reference to the string containing employee identifier
     * @param notes constant reference to the string containing additional notes
     * 
     * @return std::shared_ptr<StockReceipt> containing created stock receipt
     */
    std::shared_ptr<StockReceipt> processStockReceipt(
        const std::string& supplierName,
        const std::string& purchaseOrderNumber,
        const std::string& invoiceNumber,
        double totalCost,
        const std::vector<std::pair<std::shared_ptr<Book>, int>>& items,
        const std::string& employeeId,
        const std::string& notes = ""
    );

    // Stock Write-off Operations
    /**
     * @brief Process stock write-off
     * 
     * @param reason StockWriteOff::WriteOffReason value containing write-off reason
     * @param detailedReason constant reference to the string containing detailed reason
     * @param items vector of pairs containing book, location and quantity
     * @param employeeId constant reference to the string containing employee identifier
     * @param notes constant reference to the string containing additional notes
     * 
     * @return std::shared_ptr<StockWriteOff> containing created stock write-off
     */
    std::shared_ptr<StockWriteOff> processStockWriteOff(
        StockWriteOff::WriteOffReason reason,
        const std::string& detailedReason,
        const std::vector<std::tuple<std::shared_ptr<Book>, std::shared_ptr<StorageLocation>, int>>& items,
        const std::string& employeeId,
        const std::string& notes = ""
    );

    // Stock Transfer Operations
    /**
     * @brief Process stock transfer between locations
     * 
     * @param sourceLocation shared pointer to the source StorageLocation
     * @param destinationLocation shared pointer to the destination StorageLocation
     * @param transferReason constant reference to the string containing transfer reason
     * @param items vector of pairs containing book and quantity
     * @param employeeId constant reference to the string containing employee identifier
     * @param notes constant reference to the string containing additional notes
     * 
     * @return std::shared_ptr<StockTransfer> containing created stock transfer
     */
    std::shared_ptr<StockTransfer> processStockTransfer(
        std::shared_ptr<StorageLocation> sourceLocation,
        std::shared_ptr<StorageLocation> destinationLocation,
        const std::string& transferReason,
        const std::vector<std::pair<std::shared_ptr<Book>, int>>& items,
        const std::string& employeeId,
        const std::string& notes = ""
    );

    // Delivery Operations
    /**
     * @brief Create new delivery from supplier
     * 
     * @param supplierName constant reference to the string containing supplier name
     * @param scheduledDate constant reference to the string containing scheduled date
     * @param trackingNumber constant reference to the string containing tracking number
     * @param carrier constant reference to the string containing carrier company
     * @param shippingCost double value containing shipping cost
     * @param books vector of shared pointers to Book objects in delivery
     * 
     * @return std::shared_ptr<Delivery> containing created delivery
     */
    std::shared_ptr<Delivery> createDelivery(
        const std::string& supplierName,
        const std::string& scheduledDate,
        const std::string& trackingNumber,
        const std::string& carrier,
        double shippingCost,
        const std::vector<std::shared_ptr<Book>>& books
    );

    /**
     * @brief Process delivery arrival and create stock receipt
     * 
     * @param delivery shared pointer to the Delivery object
     * @param employeeId constant reference to the string containing employee identifier
     * 
     * @return std::shared_ptr<StockReceipt> containing created stock receipt
     */
    std::shared_ptr<StockReceipt> processDeliveryArrival(
        std::shared_ptr<Delivery> delivery,
        const std::string& employeeId
    );

    // Inventory Management
    /**
     * @brief Find optimal location for book storage
     * 
     * @param book shared pointer to the Book object
     * @param quantity integer value containing quantity to store
     * @param preferredSectionType WarehouseSection::SectionType value containing preferred section type
     * 
     * @return std::shared_ptr<StorageLocation> containing optimal location or nullptr
     */
    std::shared_ptr<StorageLocation> findOptimalBookLocation(
        std::shared_ptr<Book> book,
        int quantity,
        WarehouseSection::SectionType preferredSectionType = WarehouseSection::SectionType::GENERAL
    ) const;

    /**
     * @brief Get book stock information
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * 
     * @return std::string containing formatted stock information
     */
    std::string getBookStockInfo(const std::string& bookIsbn) const;

    /**
     * @brief Check if book is available in required quantity
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * @param requiredQuantity integer value containing required quantity
     * 
     * @return true if book is available in required quantity
     * @return false if book is not available in required quantity
     */
    bool isBookAvailable(const std::string& bookIsbn, int requiredQuantity) const;

    // Warehouse Analytics
    /**
     * @brief Get warehouse utilization report
     * 
     * @return std::string containing utilization report
     */
    std::string getWarehouseUtilizationReport() const;

    /**
     * @brief Get inventory summary
     * 
     * @return std::string containing inventory summary
     */
    std::string getInventorySummary() const;

    /**
     * @brief Get low stock alerts
     * 
     * @param threshold integer value containing low stock threshold
     * 
     * @return std::vector<std::string> containing low stock alerts
     */
    std::vector<std::string> getLowStockAlerts(int threshold = 10) const;

    /**
     * @brief Equality comparison operator for warehouse managers
     * 
     * @param other constant reference to the warehouse manager to compare with
     * 
     * @return true if warehouse managers are equal
     * @return false if warehouse managers are not equal
     */
    bool operator==(const WarehouseManager& other) const noexcept;

    /**
     * @brief Inequality comparison operator for warehouse managers
     * 
     * @param other constant reference to the warehouse manager to compare with
     * 
     * @return true if warehouse managers are not equal
     * @return false if warehouse managers are equal
     */
    bool operator!=(const WarehouseManager& other) const noexcept;
};