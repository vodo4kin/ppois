/**
 * @file StockReceipt.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the StockReceipt class for managing stock receipt operations
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
 * @class StockReceipt
 * @brief Class for managing stock receipt operations in warehouse
 * 
 * Handles receipt of new stock from suppliers. Tracks supplier information,
 * purchase orders, and integrates new inventory into warehouse storage.
 */
class StockReceipt : public StockMovement {
private:
    std::string supplierName;        ///< Name of the supplier
    std::string purchaseOrderNumber; ///< Purchase order number
    std::string invoiceNumber;       ///< Invoice number from supplier
    double totalCost;                ///< Total cost of received goods

    /**
     * @brief Private method to validate supplier name
     * 
     * @param supplierName constant reference to the string containing supplier name to validate
     * 
     * @return true if supplier name is valid
     * @return false if supplier name is invalid
     */
    bool isValidSupplierName(const std::string& supplierName) const;

    /**
     * @brief Private method to validate purchase order number
     * 
     * @param poNumber constant reference to the string containing purchase order number to validate
     * 
     * @return true if purchase order number is valid
     * @return false if purchase order number is invalid
     */
    bool isValidPurchaseOrderNumber(const std::string& poNumber) const;

    /**
     * @brief Private method to validate invoice number
     * 
     * @param invoiceNumber constant reference to the string containing invoice number to validate
     * 
     * @return true if invoice number is valid
     * @return false if invoice number is invalid
     */
    bool isValidInvoiceNumber(const std::string& invoiceNumber) const;

    /**
     * @brief Private method to validate total cost
     * 
     * @param cost double value containing total cost to validate
     * 
     * @return true if total cost is valid
     * @return false if total cost is invalid
     */
    bool isValidTotalCost(double cost) const;

public:
    /**
     * @brief Construct a new StockReceipt object
     * 
     * @param movementId constant reference to the string containing movement identifier
     * @param movementDate constant reference to the string containing movement date
     * @param employeeId constant reference to the string containing employee identifier
     * @param warehouse shared pointer to the Warehouse object
     * @param supplierName constant reference to the string containing supplier name
     * @param purchaseOrderNumber constant reference to the string containing purchase order number
     * @param invoiceNumber constant reference to the string containing invoice number
     * @param totalCost double value containing total cost of goods
     * @param notes constant reference to the string containing additional notes
     */
    StockReceipt(const std::string& movementId, const std::string& movementDate,
                 const std::string& employeeId, std::shared_ptr<class Warehouse> warehouse,
                 const std::string& supplierName, const std::string& purchaseOrderNumber, 
                 const std::string& invoiceNumber, double totalCost, const std::string& notes = "");

    /**
     * @brief Get the supplier name
     * 
     * @return std::string containing supplier name
     */
    std::string getSupplierName() const noexcept;

    /**
     * @brief Get the purchase order number
     * 
     * @return std::string containing purchase order number
     */
    std::string getPurchaseOrderNumber() const noexcept;

    /**
     * @brief Get the invoice number
     * 
     * @return std::string containing invoice number
     */
    std::string getInvoiceNumber() const noexcept;

    /**
     * @brief Get the total cost
     * 
     * @return double containing total cost of goods
     */
    double getTotalCost() const noexcept;

    /**
     * @brief Execute the receipt operation
     * 
     * Processes the receipt by adding inventory items to warehouse storage
     */
    void execute() override;

    /**
     * @brief Cancel the receipt operation
     * 
     * Reverts the receipt by removing added inventory items
     */
    void cancel() override;

    /**
     * @brief Get receipt information
     * 
     * @return std::string containing formatted receipt information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Calculate average cost per item
     * 
     * @return double containing average cost per item
     */
    double calculateAverageCost() const noexcept;

    /**
     * @brief Equality comparison operator for stock receipts
     * 
     * @param other constant reference to the stock receipt to compare with
     * 
     * @return true if stock receipts are equal
     * @return false if stock receipts are not equal
     */
    bool operator==(const StockReceipt& other) const noexcept;

    /**
     * @brief Inequality comparison operator for stock receipts
     * 
     * @param other constant reference to the stock receipt to compare with
     * 
     * @return true if stock receipts are not equal
     * @return false if stock receipts are equal
     */
    bool operator!=(const StockReceipt& other) const noexcept;
};