/**
 * @file StockTransfer.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the StockTransfer class for managing stock transfer operations
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "warehouse/StockMovement.hpp"

// Forward declaration
class StorageLocation;

/**
 * @class StockTransfer
 * @brief Class for managing stock transfer operations between warehouse locations
 * 
 * Handles movement of stock between different storage locations within the warehouse.
 * Tracks source and destination locations, ensures quantity availability,
 * and maintains inventory consistency during transfers.
 */
class StockTransfer : public StockMovement {
private:
    std::shared_ptr<StorageLocation> sourceLocation;      ///< Source location for transfer
    std::shared_ptr<StorageLocation> destinationLocation; ///< Destination location for transfer
    std::string transferReason;                           ///< Reason for the transfer

    /**
     * @brief Private method to validate transfer reason
     * 
     * @param reason constant reference to the string containing transfer reason to validate
     * 
     * @return true if transfer reason is valid
     * @return false if transfer reason is invalid
     */
    bool isValidTransferReason(const std::string& reason) const;

    /**
     * @brief Private method to validate locations are different
     * 
     * @param source shared pointer to the source StorageLocation
     * @param destination shared pointer to the destination StorageLocation
     * 
     * @return true if locations are different and valid
     * @return false if locations are same or invalid
     */
    bool areLocationsValid(std::shared_ptr<StorageLocation> source, 
                          std::shared_ptr<StorageLocation> destination) const;

public:
    /**
     * @brief Construct a new StockTransfer object
     * 
     * @param movementId constant reference to the string containing movement identifier
     * @param movementDate constant reference to the string containing movement date
     * @param employeeId constant reference to the string containing employee identifier
     * @param warehouse shared pointer to the Warehouse object
     * @param sourceLocation shared pointer to the source StorageLocation
     * @param destinationLocation shared pointer to the destination StorageLocation
     * @param transferReason constant reference to the string containing transfer reason
     * @param notes constant reference to the string containing additional notes
     */
    StockTransfer(const std::string& movementId, const std::string& movementDate,
                  const std::string& employeeId, std::shared_ptr<class Warehouse> warehouse,
                  std::shared_ptr<StorageLocation> sourceLocation,
                  std::shared_ptr<StorageLocation> destinationLocation, 
                  const std::string& transferReason, const std::string& notes = "");

    /**
     * @brief Get the source location
     * 
     * @return std::shared_ptr<StorageLocation> containing source location
     */
    std::shared_ptr<StorageLocation> getSourceLocation() const noexcept;

    /**
     * @brief Get the destination location
     * 
     * @return std::shared_ptr<StorageLocation> containing destination location
     */
    std::shared_ptr<StorageLocation> getDestinationLocation() const noexcept;

    /**
     * @brief Get the transfer reason
     * 
     * @return std::string containing transfer reason
     */
    std::string getTransferReason() const noexcept;

    /**
     * @brief Execute the transfer operation
     * 
     * Processes the transfer by moving inventory items between source and destination locations
     */
    void execute() override;

    /**
     * @brief Cancel the transfer operation
     * 
     * Reverts the transfer by moving items back to source location
     */
    void cancel() override;

    /**
     * @brief Get transfer information
     * 
     * @return std::string containing formatted transfer information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Get total quantity being transferred
     * 
     * @return int containing total quantity of transferred items
     */
    int getTotalTransferQuantity() const noexcept;

    /**
     * @brief Check if transfer is between different sections
     * 
     * @return true if transfer is between different sections
     * @return false if transfer is within same section
     */
    bool isCrossSectionTransfer() const noexcept;

    /**
     * @brief Check if destination has sufficient capacity for transfer
     * 
     * @return true if destination has sufficient capacity
     * @return false if destination does not have sufficient capacity
     */
    bool canDestinationAccommodate() const noexcept;

    /**
     * @brief Check if source has sufficient stock for transfer
     * 
     * @return true if source has sufficient stock
     * @return false if source does not have sufficient stock
     */
    bool doesSourceHaveSufficientStock() const noexcept;

    /**
     * @brief Equality comparison operator for stock transfers
     * 
     * @param other constant reference to the stock transfer to compare with
     * 
     * @return true if stock transfers are equal
     * @return false if stock transfers are not equal
     */
    bool operator==(const StockTransfer& other) const noexcept;

    /**
     * @brief Inequality comparison operator for stock transfers
     * 
     * @param other constant reference to the stock transfer to compare with
     * 
     * @return true if stock transfers are not equal
     * @return false if stock transfers are equal
     */
    bool operator!=(const StockTransfer& other) const noexcept;
};