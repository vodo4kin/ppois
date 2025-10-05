/**
 * @file InventoryItem.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the InventoryItem class for managing book inventory in warehouse
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "books/Book.hpp"
#include "warehouse/StorageLocation.hpp"

/**
 * @class InventoryItem
 * @brief Class for managing book inventory in warehouse
 * 
 * Represents the physical presence of a book in the warehouse.
 * Links books with storage locations and manages quantities.
 * Serves as the primary storage for book stock information.
 */
class InventoryItem {
private:
    std::shared_ptr<Book> book;                  ///< Pointer to the book
    int quantity;                                ///< Quantity of books in this location
    std::shared_ptr<StorageLocation> location;   ///< Storage location where books are stored
    std::string dateAdded;                       ///< Date when books were added to this location

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
     * @brief Private method to validate date format
     * 
     * @param date constant reference to the string containing date to validate
     * 
     * @return true if date is valid
     * @return false if date is invalid
     */
    bool isValidDate(const std::string& date) const;

public:
    /**
     * @brief Construct a new InventoryItem object
     * 
     * @param book shared pointer to the Book object
     * @param quantity integer value containing quantity of books
     * @param location shared pointer to the StorageLocation object
     * @param dateAdded constant reference to the string containing date added
     */
    InventoryItem(std::shared_ptr<Book> book, int quantity,
                  std::shared_ptr<StorageLocation> location, 
                  const std::string& dateAdded);

    /**
     * @brief Get the book
     * 
     * @return std::shared_ptr<Book> containing book information
     */
    std::shared_ptr<Book> getBook() const noexcept;

    /**
     * @brief Get the quantity
     * 
     * @return int containing quantity of books
     */
    int getQuantity() const noexcept;

    /**
     * @brief Get the storage location
     * 
     * @return std::shared_ptr<StorageLocation> containing storage location
     */
    std::shared_ptr<StorageLocation> getLocation() const noexcept;

    /**
     * @brief Get the date added
     * 
     * @return std::string containing date when books were added
     */
    std::string getDateAdded() const noexcept;

    /**
     * @brief Set the quantity
     * 
     * @param quantity integer value containing new quantity
     */
    void setQuantity(int quantity);

    /**
     * @brief Set the storage location
     * 
     * @param location shared pointer to the StorageLocation object
     */
    void setLocation(std::shared_ptr<StorageLocation> location);

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
     * @brief Check if item is in stock (quantity > 0)
     * 
     * @return true if item is in stock
     * @return false if item is not in stock
     */
    bool isInStock() const noexcept;

    /**
     * @brief Get inventory item information
     * 
     * @return std::string containing formatted inventory information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for inventory items
     * 
     * @param other constant reference to the inventory item to compare with
     * 
     * @return true if inventory items are equal
     * @return false if inventory items are not equal
     */
    bool operator==(const InventoryItem& other) const noexcept;

    /**
     * @brief Inequality comparison operator for inventory items
     * 
     * @param other constant reference to the inventory item to compare with
     * 
     * @return true if inventory items are not equal
     * @return false if inventory items are equal
     */
    bool operator!=(const InventoryItem& other) const noexcept;
};