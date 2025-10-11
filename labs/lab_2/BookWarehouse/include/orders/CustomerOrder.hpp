/**
 * @file CustomerOrder.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the CustomerOrder class for working with customer orders
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "orders/Order.hpp"
#include "orders/ShippingInfo.hpp"
#include "persons/Customer.hpp"

/**
 * @class CustomerOrder
 * @brief Class for working with customer orders in the book warehouse system
 * 
 * Extends Order class with customer-specific functionality including
 * customer information, shipping details, and customer-specific pricing.
 */
class CustomerOrder : public Order {
private:
    std::shared_ptr<Customer> customer;        ///< Customer who placed the order
    std::shared_ptr<ShippingInfo> shipping;    ///< Shipping information
    double customerDiscount;                   ///< Additional customer-specific discount
    double taxAmount;                          ///< Tax amount for the order
    double finalAmount;                        ///< Final amount after discounts and tax

    /**
     * @brief Private method to validate customer discount
     * 
     * @param discount double value containing discount to validate
     * 
     * @return true if discount is valid
     * @return false if discount is invalid
     */
    bool isValidCustomerDiscount(double discount) const;

    /**
     * @brief Private method to validate tax amount
     * 
     * @param tax double value containing tax to validate
     * 
     * @return true if tax is valid
     * @return false if tax is invalid
     */
    bool isValidTaxAmount(double tax) const;

    /**
     * @brief Recalculate final order amount with discounts and tax
     */
    void recalculateFinalAmount();

public:
    /**
     * @brief Construct a new CustomerOrder object
     * 
     * @param orderId constant reference to the string containing order identifier
     * @param orderDate constant reference to the string containing order date
     * @param customer shared pointer to the Customer object
     * @param shipping shared pointer to the ShippingInfo object
     * @param notes constant reference to the string containing additional notes
     */
    CustomerOrder(const std::string& orderId, const std::string& orderDate,
                  std::shared_ptr<Customer> customer, std::shared_ptr<ShippingInfo> shipping,
                  const std::string& notes = "");

    /**
     * @brief Get the customer
     * 
     * @return std::shared_ptr<Customer> containing customer information
     */
    std::shared_ptr<Customer> getCustomer() const noexcept;

    /**
     * @brief Get the shipping information
     * 
     * @return std::shared_ptr<ShippingInfo> containing shipping information
     */
    std::shared_ptr<ShippingInfo> getShippingInfo() const noexcept;

    /**
     * @brief Get the customer discount
     * 
     * @return double containing customer discount percentage
     */
    double getCustomerDiscount() const noexcept;

    /**
     * @brief Get the tax amount
     * 
     * @return double containing tax amount
     */
    double getTaxAmount() const noexcept;

    /**
     * @brief Get the final amount
     * 
     * @return double containing final order amount
     */
    double getFinalAmount() const noexcept;

    /**
     * @brief Set the shipping information
     * 
     * @param shipping shared pointer to the ShippingInfo object
     */
    void setShippingInfo(std::shared_ptr<ShippingInfo> shipping);

    /**
     * @brief Set the customer discount
     * 
     * @param discount double value containing new customer discount
     */
    void setCustomerDiscount(double discount);

    /**
     * @brief Set the tax amount
     * 
     * @param tax double value containing new tax amount
     */
    void setTaxAmount(double tax);

    /**
     * @brief Calculate total amount including shipping
     * 
     * @return double containing total amount with shipping
     */
    double getTotalWithShipping() const noexcept;

    /**
     * @brief Apply customer category discount
     */
    void applyCustomerCategoryDiscount();

    /**
     * @brief Check if order qualifies for free shipping
     * 
     * @return true if order qualifies for free shipping
     * @return false if order does not qualify for free shipping
     */
    bool qualifiesForFreeShipping() const noexcept;

    /**
     * @brief Process order payment
     * 
     * @param paymentDate constant reference to the string containing payment date
     */
    void processPayment(const std::string& paymentDate);

    /**
     * @brief Ship the order
     * 
     * @param shipDate constant reference to the string containing ship date
     */
    void shipOrder(const std::string& shipDate);

    /**
     * @brief Deliver the order
     * 
     * @param deliveryDate constant reference to the string containing delivery date
     */
    void deliverOrder(const std::string& deliveryDate);

    /**
     * @brief Get customer order information
     * 
     * @return std::string containing formatted customer order information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Equality comparison operator for customer orders
     * 
     * @param other constant reference to the customer order to compare with
     * 
     * @return true if customer orders are equal
     * @return false if customer orders are not equal
     */
    bool operator==(const CustomerOrder& other) const noexcept;

    /**
     * @brief Inequality comparison operator for customer orders
     * 
     * @param other constant reference to the customer order to compare with
     * 
     * @return true if customer orders are not equal
     * @return false if customer orders are equal
     */
    bool operator!=(const CustomerOrder& other) const noexcept;
};