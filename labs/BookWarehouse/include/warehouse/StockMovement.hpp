/**
 * @file StockMovement.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the StockMovement class for managing stock movement operations
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include <vector>

// Forward declaration to avoid circular dependency
class Warehouse;

/**
 * @class StockMovement
 * @brief Base class for all stock movement operations in warehouse
 * 
 * Provides common functionality for receipt, write-off, and transfer operations.
 * Tracks movement date, type, status, and related inventory items.
 */
class StockMovement {
public:
    /**
     * @enum MovementType
     * @brief Enumeration of stock movement types
     */
    enum class MovementType {
        RECEIPT,        ///< Receipt of new stock
        WRITE_OFF,      ///< Write-off of stock
        TRANSFER        ///< Transfer between locations
    };

    /**
     * @enum MovementStatus
     * @brief Enumeration of stock movement statuses
     */
    enum class MovementStatus {
        PENDING,        ///< Movement is pending processing
        IN_PROGRESS,    ///< Movement is in progress
        COMPLETED,      ///< Movement is completed
        CANCELLED       ///< Movement is cancelled
    };

private:
    std::string movementId;                         ///< Unique identifier for the movement
    MovementType movementType;                      ///< Type of movement
    MovementStatus status;                          ///< Current status of movement
    std::string movementDate;                       ///< Date when movement occurred
    std::string employeeId;                         ///< ID of employee who performed movement
    std::vector<std::shared_ptr<class InventoryItem>> affectedItems; ///< Inventory items affected by movement
    std::string notes;                              ///< Additional notes or comments
    std::weak_ptr<Warehouse> warehouse;             ///< Weak pointer to warehouse

    /**
     * @brief Private method to validate movement ID
     * 
     * @param movementId constant reference to the string containing movement ID to validate
     * 
     * @return true if movement ID is valid
     * @return false if movement ID is invalid
     */
    bool isValidMovementId(const std::string& movementId) const;

    /**
     * @brief Private method to validate movement date
     * 
     * @param date constant reference to the string containing movement date to validate
     * 
     * @return true if movement date is valid
     * @return false if movement date is invalid
     */
    bool isValidDate(const std::string& date) const;

    /**
     * @brief Private method to validate employee ID
     * 
     * @param employeeId constant reference to the string containing employee ID to validate
     * 
     * @return true if employee ID is valid
     * @return false if employee ID is invalid
     */
    bool isValidEmployeeId(const std::string& employeeId) const;

public:
    /**
     * @brief Construct a new StockMovement object
     * 
     * @param movementId constant reference to the string containing movement identifier
     * @param movementType MovementType value containing movement type
     * @param movementDate constant reference to the string containing movement date
     * @param employeeId constant reference to the string containing employee identifier
     * @param warehouse shared pointer to the Warehouse object
     * @param notes constant reference to the string containing additional notes
     */
    StockMovement(const std::string& movementId, MovementType movementType,
                  const std::string& movementDate, const std::string& employeeId,
                  std::shared_ptr<Warehouse> warehouse, const std::string& notes = "");

    /**
     * @brief Destroy the StockMovement object
     */
    virtual ~StockMovement() = default;

    /**
     * @brief Get the movement identifier
     * 
     * @return std::string containing movement identifier
     */
    std::string getMovementId() const noexcept;

    /**
     * @brief Get the movement type
     * 
     * @return MovementType containing movement type
     */
    MovementType getMovementType() const noexcept;

    /**
     * @brief Get the movement status
     * 
     * @return MovementStatus containing movement status
     */
    MovementStatus getStatus() const noexcept;

    /**
     * @brief Get the movement date
     * 
     * @return std::string containing movement date
     */
    std::string getMovementDate() const noexcept;

    /**
     * @brief Get the employee identifier
     * 
     * @return std::string containing employee identifier
     */
    std::string getEmployeeId() const noexcept;

    /**
     * @brief Get the affected inventory items
     * 
     * @return std::vector<std::shared_ptr<InventoryItem>> containing affected items
     */
    std::vector<std::shared_ptr<class InventoryItem>> getAffectedItems() const noexcept;

    /**
     * @brief Get the notes
     * 
     * @return std::string containing additional notes
     */
    std::string getNotes() const noexcept;

    /**
     * @brief Get the warehouse
     * 
     * @return std::shared_ptr<Warehouse> containing warehouse pointer
     */
    std::shared_ptr<Warehouse> getWarehouse() const noexcept;

    /**
     * @brief Set the movement status
     * 
     * @param status MovementStatus value containing new status
     */
    void setStatus(MovementStatus status) noexcept;

    /**
     * @brief Set the notes
     * 
     * @param notes constant reference to the string containing new notes
     */
    void setNotes(const std::string& notes) noexcept;

    /**
     * @brief Add affected inventory item
     * 
     * @param item shared pointer to the InventoryItem object to add
     */
    void addAffectedItem(std::shared_ptr<class InventoryItem> item);

    /**
     * @brief Remove affected inventory item
     * 
     * @param item shared pointer to the InventoryItem object to remove
     */
    void removeAffectedItem(std::shared_ptr<class InventoryItem> item);

    /**
     * @brief Check if movement is completed
     * 
     * @return true if movement is completed
     * @return false if movement is not completed
     */
    bool isCompleted() const noexcept;

    /**
     * @brief Check if movement is pending
     * 
     * @return true if movement is pending
     * @return false if movement is not pending
     */
    bool isPending() const noexcept;

    /**
     * @brief Check if movement is cancellable
     * 
     * @return true if movement can be cancelled
     * @return false if movement cannot be cancelled
     */
    bool isCancellable() const noexcept;

    /**
     * @brief Execute the movement operation
     * 
     * Pure virtual method to be implemented by derived classes
     */
    virtual void execute() = 0;

    /**
     * @brief Cancel the movement operation
     * 
     * Pure virtual method to be implemented by derived classes
     */
    virtual void cancel() = 0;

    /**
     * @brief Get movement information
     * 
     * @return std::string containing formatted movement information
     */
    virtual std::string getInfo() const noexcept;

    /**
     * @brief Get movement type as string
     * 
     * @return std::string containing movement type description
     */
    std::string getMovementTypeString() const noexcept;

    /**
     * @brief Get movement status as string
     * 
     * @return std::string containing movement status description
     */
    std::string getMovementStatusString() const noexcept;

    /**
     * @brief Equality comparison operator for stock movements
     * 
     * @param other constant reference to the stock movement to compare with
     * 
     * @return true if stock movements are equal
     * @return false if stock movements are not equal
     */
    bool operator==(const StockMovement& other) const noexcept;

    /**
     * @brief Inequality comparison operator for stock movements
     * 
     * @param other constant reference to the stock movement to compare with
     * 
     * @return true if stock movements are not equal
     * @return false if stock movements are equal
     */
    bool operator!=(const StockMovement& other) const noexcept;
};