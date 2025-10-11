/**
 * @file PurchaseOrder.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the PurchaseOrder class for working with purchase orders
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "orders/Order.hpp"

/**
 * @class PurchaseOrder
 * @brief Class for working with purchase orders from suppliers
 * 
 * Extends Order class with supplier-specific functionality including
 * supplier information, delivery tracking, and inventory integration.
 */
class PurchaseOrder : public Order {
private:
    std::string supplierName;                   ///< Name of the supplier
    std::string supplierContact;                ///< Supplier contact information
    std::string expectedDeliveryDate;          ///< Expected delivery date from supplier
    std::string actualDeliveryDate;            ///< Actual delivery date
    double shippingCost;                       ///< Shipping cost from supplier
    bool isReceived;                           ///< Whether order has been received

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
     * @brief Private method to validate supplier contact
     * 
     * @param contact constant reference to the string containing contact to validate
     * 
     * @return true if contact is valid
     * @return false if contact is invalid
     */
    bool isValidSupplierContact(const std::string& contact) const;

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
     * @brief Construct a new PurchaseOrder object
     * 
     * @param orderId constant reference to the string containing order identifier
     * @param orderDate constant reference to the string containing order date
     * @param supplierName constant reference to the string containing supplier name
     * @param supplierContact constant reference to the string containing supplier contact
     * @param expectedDeliveryDate constant reference to the string containing expected delivery date
     * @param shippingCost double value containing shipping cost
     * @param notes constant reference to the string containing additional notes
     */
    PurchaseOrder(const std::string& orderId, const std::string& orderDate,
                  const std::string& supplierName, const std::string& supplierContact,
                  const std::string& expectedDeliveryDate, double shippingCost = 0.0,
                  const std::string& notes = "");

    /**
     * @brief Get the supplier name
     * 
     * @return std::string containing supplier name
     */
    std::string getSupplierName() const noexcept;

    /**
     * @brief Get the supplier contact
     * 
     * @return std::string containing supplier contact
     */
    std::string getSupplierContact() const noexcept;

    /**
     * @brief Get the expected delivery date
     * 
     * @return std::string containing expected delivery date
     */
    std::string getExpectedDeliveryDate() const noexcept;

    /**
     * @brief Get the actual delivery date
     * 
     * @return std::string containing actual delivery date
     */
    std::string getActualDeliveryDate() const noexcept;

    /**
     * @brief Get the shipping cost
     * 
     * @return double containing shipping cost
     */
    double getShippingCost() const noexcept;

    /**
     * @brief Check if order is received
     * 
     * @return true if order is received
     * @return false if order is not received
     */
    bool isOrReceived() const noexcept;

    /**
     * @brief Set the supplier contact
     * 
     * @param contact constant reference to the string containing new supplier contact
     */
    void setSupplierContact(const std::string& contact);

    /**
     * @brief Set the expected delivery date
     * 
     * @param deliveryDate constant reference to the string containing new expected delivery date
     */
    void setExpectedDeliveryDate(const std::string& deliveryDate);

    /**
     * @brief Set the shipping cost
     * 
     * @param cost double value containing new shipping cost
     */
    void setShippingCost(double cost);

    /**
     * @brief Calculate total order cost including shipping
     * 
     * @return double containing total cost
     */
    double getTotalCost() const noexcept;

    /**
     * @brief Check if order is overdue
     * 
     * @return true if order is overdue
     * @return false if order is not overdue
     */
    bool isOverdue() const;

    /**
     * @brief Receive the order from supplier
     * 
     * @param deliveryDate constant reference to the string containing actual delivery date
     */
    void receiveOrder(const std::string& deliveryDate);

    /**
     * @brief Check if order can be received
     * 
     * @return true if order can be received
     * @return false if order cannot be received
     */
    bool canBeReceived() const noexcept;

    /**
     * @brief Get purchase order information
     * 
     * @return std::string containing formatted purchase order information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Equality comparison operator for purchase orders
     * 
     * @param other constant reference to the purchase order to compare with
     * 
     * @return true if purchase orders are equal
     * @return false if purchase orders are not equal
     */
    bool operator==(const PurchaseOrder& other) const noexcept;

    /**
     * @brief Inequality comparison operator for purchase orders
     * 
     * @param other constant reference to the purchase order to compare with
     * 
     * @return true if purchase orders are not equal
     * @return false if purchase orders are equal
     */
    bool operator!=(const PurchaseOrder& other) const noexcept;
};