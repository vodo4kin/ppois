/**
 * @file OrderItem.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the OrderItem class for working with order line items
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "books/Book.hpp"

/**
 * @class OrderItem
 * @brief Class for working with order line items
 * 
 * Represents a single line item in an order with book, quantity,
 * pricing, and discount information. Provides cost calculations.
 */
class OrderItem {
private:
    std::shared_ptr<Book> book;      ///< Book associated with this order item
    int quantity;                    ///< Quantity of books ordered
    double unitPrice;                ///< Price per unit at time of order
    double discountPercentage;       ///< Discount percentage applied (0-100)

    /**
     * @brief Private method to validate quantity
     * 
     * @param quantity integer value containing quantity to validate
     * 
     * @return true if quantity is valid
     * @return false if quantity is invalid
     */
    bool isValidQuantity(int quantity) const;

    /**
     * @brief Private method to validate unit price
     * 
     * @param price double value containing unit price to validate
     * 
     * @return true if unit price is valid
     * @return false if unit price is invalid
     */
    bool isValidUnitPrice(double price) const;

    /**
     * @brief Private method to validate discount percentage
     * 
     * @param discount double value containing discount to validate
     * 
     * @return true if discount is valid
     * @return false if discount is invalid
     */
    bool isValidDiscount(double discount) const;

public:
    /**
     * @brief Construct a new OrderItem object
     * 
     * @param book shared pointer to the Book object
     * @param quantity integer value containing quantity
     * @param unitPrice double value containing unit price
     * @param discountPercentage double value containing discount percentage
     */
    OrderItem(std::shared_ptr<Book> book, int quantity, double unitPrice, double discountPercentage = 0.0);

    /**
     * @brief Get the book
     * 
     * @return std::shared_ptr<Book> containing book information
     */
    std::shared_ptr<Book> getBook() const noexcept;

    /**
     * @brief Get the quantity
     * 
     * @return int containing quantity
     */
    int getQuantity() const noexcept;

    /**
     * @brief Get the unit price
     * 
     * @return double containing unit price
     */
    double getUnitPrice() const noexcept;

    /**
     * @brief Get the discount percentage
     * 
     * @return double containing discount percentage
     */
    double getDiscountPercentage() const noexcept;

    /**
     * @brief Set the quantity
     * 
     * @param quantity integer value containing new quantity
     */
    void setQuantity(int quantity);

    /**
     * @brief Set the discount percentage
     * 
     * @param discount double value containing new discount percentage
     */
    void setDiscountPercentage(double discount);

    /**
     * @brief Calculate discounted unit price
     * 
     * @return double containing discounted unit price
     */
    double getDiscountedUnitPrice() const noexcept;

    /**
     * @brief Calculate total price for this line item
     * 
     * @return double containing total price (quantity * discounted unit price)
     */
    double getTotalPrice() const noexcept;

    /**
     * @brief Calculate discount amount for this line item
     * 
     * @return double containing total discount amount
     */
    double getTotalDiscount() const noexcept;

    /**
     * @brief Check if item has discount
     * 
     * @return true if item has discount
     * @return false if item has no discount
     */
    bool hasDiscount() const noexcept;

    /**
     * @brief Increase quantity
     * 
     * @param amount integer value containing amount to increase
     */
    void increaseQuantity(int amount);

    /**
     * @brief Decrease quantity
     * 
     * @param amount integer value containing amount to decrease
     */
    void decreaseQuantity(int amount);

    /**
     * @brief Get order item information
     * 
     * @return std::string containing formatted order item information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for order items
     * 
     * @param other constant reference to the order item to compare with
     * 
     * @return true if order items are equal
     * @return false if order items are not equal
     */
    bool operator==(const OrderItem& other) const noexcept;

    /**
     * @brief Inequality comparison operator for order items
     * 
     * @param other constant reference to the order item to compare with
     * 
     * @return true if order items are not equal
     * @return false if order items are equal
     */
    bool operator!=(const OrderItem& other) const noexcept;
};