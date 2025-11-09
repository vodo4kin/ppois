/**
 * @file StockWriteOff.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the StockWriteOff class for managing stock write-off operations
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "StockMovement.hpp"

/**
 * @class StockWriteOff
 * @brief Class for managing stock write-off operations in warehouse
 * 
 * Handles removal of stock from warehouse due to damage, expiration,
 * or other reasons. Tracks write-off reasons and ensures proper inventory adjustment.
 */
class StockWriteOff : public StockMovement {
public:
    /**
     * @enum WriteOffReason
     * @brief Enumeration of stock write-off reasons
     */
    enum class WriteOffReason {
        DAMAGED,        ///< Goods damaged during handling or storage
        EXPIRED,        ///< Goods past expiration date
        OBSOLETE,       ///< Goods no longer needed or outdated
        LOST,           ///< Goods lost or stolen
        QUALITY_ISSUE,  ///< Goods with quality defects
        OTHER           ///< Other reasons
    };

private:
    WriteOffReason reason;          ///< Reason for write-off
    std::string detailedReason;     ///< Detailed description of write-off reason

    /**
     * @brief Private method to validate detailed reason
     * 
     * @param detailedReason constant reference to the string containing detailed reason to validate
     * 
     * @return true if detailed reason is valid
     * @return false if detailed reason is invalid
     */
    bool isValidDetailedReason(const std::string& detailedReason) const;

public:
    /**
     * @brief Construct a new StockWriteOff object
     * 
     * @param movementId constant reference to the string containing movement identifier
     * @param movementDate constant reference to the string containing movement date
     * @param employeeId constant reference to the string containing employee identifier
     * @param warehouse shared pointer to the Warehouse object
     * @param reason WriteOffReason value containing write-off reason
     * @param detailedReason constant reference to the string containing detailed reason description
     * @param notes constant reference to the string containing additional notes
     */
    StockWriteOff(const std::string& movementId, const std::string& movementDate,
                  const std::string& employeeId, std::shared_ptr<class Warehouse> warehouse,
                  WriteOffReason reason, const std::string& detailedReason, const std::string& notes = "");

    /**
     * @brief Get the write-off reason
     * 
     * @return WriteOffReason containing write-off reason
     */
    WriteOffReason getReason() const noexcept;

    /**
     * @brief Get the detailed reason
     * 
     * @return std::string containing detailed reason description
     */
    std::string getDetailedReason() const noexcept;

    /**
     * @brief Execute the write-off operation
     * 
     * Processes the write-off by removing inventory items from warehouse storage
     */
    void execute() override;

    /**
     * @brief Cancel the write-off operation
     * 
     * Reverts the write-off by restoring removed inventory items
     */
    void cancel() override;

    /**
     * @brief Get write-off information
     * 
     * @return std::string containing formatted write-off information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Get write-off reason as string
     * 
     * @return std::string containing write-off reason description
     */
    std::string getReasonString() const noexcept;

    /**
     * @brief Get total quantity of written-off items
     * 
     * @return int containing total quantity of written-off items
     */
    int getTotalWrittenOffQuantity() const noexcept;

    /**
     * @brief Check if write-off is due to damage
     * 
     * @return true if write-off is due to damage
     * @return false if write-off is not due to damage
     */
    bool isDueToDamage() const noexcept;

    /**
     * @brief Check if write-off is due to expiration
     * 
     * @return true if write-off is due to expiration
     * @return false if write-off is not due to expiration
     */
    bool isDueToExpiration() const noexcept;

    /**
     * @brief Equality comparison operator for stock write-offs
     * 
     * @param other constant reference to the stock write-off to compare with
     * 
     * @return true if stock write-offs are equal
     * @return false if stock write-offs are not equal
     */
    bool operator==(const StockWriteOff& other) const noexcept;

    /**
     * @brief Inequality comparison operator for stock write-offs
     * 
     * @param other constant reference to the stock write-off to compare with
     * 
     * @return true if stock write-offs are not equal
     * @return false if stock write-offs are equal
     */
    bool operator!=(const StockWriteOff& other) const noexcept;
};