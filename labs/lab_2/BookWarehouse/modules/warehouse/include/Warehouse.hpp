/**
 * @file Warehouse.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Warehouse class for managing the entire warehouse system
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "WarehouseSection.hpp"
#include "InventoryItem.hpp"
#include "StorageLocation.hpp"
#include "StockMovement.hpp"
#include "Book.hpp"

/**
 * @class Warehouse
 * @brief Class for managing the entire warehouse system
 * 
 * Represents the complete warehouse with all sections, shelves, and storage locations.
 * Provides comprehensive inventory management, search operations, and warehouse analytics.
 */
class Warehouse {
private:
    std::string name;                                           ///< Name of the warehouse
    std::string address;                                        ///< Physical address of the warehouse
    std::vector<std::shared_ptr<WarehouseSection>> sections;    ///< All sections in the warehouse
    std::vector<std::shared_ptr<InventoryItem>> inventory;      ///< All inventory items in the warehouse

    /**
     * @brief Private method to validate warehouse name
     * 
     * @param name constant reference to the string containing warehouse name to validate
     * 
     * @return true if warehouse name is valid
     * @return false if warehouse name is invalid
     */
    bool isValidName(const std::string& name) const;

    /**
     * @brief Private method to validate warehouse address
     * 
     * @param address constant reference to the string containing warehouse address to validate
     * 
     * @return true if warehouse address is valid
     * @return false if warehouse address is invalid
     */
    bool isValidAddress(const std::string& address) const;

public:
    /**
     * @brief Construct a new Warehouse object
     * 
     * @param name constant reference to the string containing warehouse name
     * @param address constant reference to the string containing warehouse address
     */
    Warehouse(const std::string& name, const std::string& address);

    /**
     * @brief Clean up inventory items with zero quantity
     * 
     * Removes all inventory items that have zero quantity from the warehouse inventory
     */
    void cleanupZeroQuantityItems();

    /**
     * @brief Process stock movement operation
     * 
     * @param movement shared pointer to StockMovement object to process
     */
    void processStockMovement(std::shared_ptr<StockMovement> movement);

    /**
     * @brief Get the warehouse name
     * 
     * @return std::string containing warehouse name
     */
    std::string getName() const noexcept;

    /**
     * @brief Get the warehouse address
     * 
     * @return std::string containing warehouse address
     */
    std::string getAddress() const noexcept;

    /**
     * @brief Get all sections in warehouse
     * 
     * @return std::vector<std::shared_ptr<WarehouseSection>> containing all sections
     */
    std::vector<std::shared_ptr<WarehouseSection>> getSections() const noexcept;

    /**
     * @brief Get the number of sections in warehouse
     * 
     * @return int containing number of sections
     */
    int getSectionsCount() const noexcept;

    /**
     * @brief Add section to warehouse
     * 
     * @param section shared pointer to the WarehouseSection object to add
     */
    void addSection(std::shared_ptr<WarehouseSection> section);

    /**
     * @brief Remove section from warehouse
     * 
     * @param sectionId constant reference to the string containing section ID to remove
     */
    void removeSection(const std::string& sectionId);

    /**
     * @brief Find section by ID
     * 
     * @param sectionId constant reference to the string containing section ID to find
     * 
     * @return std::shared_ptr<WarehouseSection> containing found section or nullptr
     */
    std::shared_ptr<WarehouseSection> findSection(const std::string& sectionId) const noexcept;

    /**
     * @brief Check if warehouse contains section with specified ID
     * 
     * @param sectionId constant reference to the string containing section ID to check
     * 
     * @return true if warehouse contains section
     * @return false if warehouse does not contain section
     */
    bool containsSection(const std::string& sectionId) const noexcept;

    /**
     * @brief Add inventory item to warehouse
     * 
     * @param inventoryItem shared pointer to the InventoryItem object to add
     */
    void addInventoryItem(std::shared_ptr<InventoryItem> inventoryItem);

    /**
     * @brief Remove inventory item from warehouse
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * @param locationId constant reference to the string containing location ID
     */
    void removeInventoryItem(const std::string& bookIsbn, const std::string& locationId);

    /**
     * @brief Find inventory items by book ISBN
     * 
     * @param bookIsbn constant reference to the string containing book ISBN to find
     * 
     * @return std::vector<std::shared_ptr<InventoryItem>> containing all inventory items for the book
     */
    std::vector<std::shared_ptr<InventoryItem>> findInventoryByBook(const std::string& bookIsbn) const noexcept;

    /**
     * @brief Find inventory items by book object
     * 
     * @param book shared pointer to the Book object to find
     * 
     * @return std::vector<std::shared_ptr<InventoryItem>> containing all inventory items for the book
     */
    std::vector<std::shared_ptr<InventoryItem>> findInventoryByBook(std::shared_ptr<Book> book) const noexcept;

    /**
     * @brief Find specific inventory item by book and location
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * @param locationId constant reference to the string containing location ID
     * 
     * @return std::shared_ptr<InventoryItem> containing found inventory item or nullptr
     */
    std::shared_ptr<InventoryItem> findInventoryItem(const std::string& bookIsbn, const std::string& locationId) const noexcept;

    /**
     * @brief Get total quantity of a book in warehouse
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * 
     * @return int containing total quantity of the book
     */
    int getBookTotalQuantity(const std::string& bookIsbn) const noexcept;

    /**
     * @brief Check if book is in stock in warehouse
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * 
     * @return true if book is in stock
     * @return false if book is not in stock
     */
    bool isBookInStock(const std::string& bookIsbn) const noexcept;

    /**
     * @brief Find available storage locations in entire warehouse
     * 
     * @return std::vector<std::shared_ptr<StorageLocation>> containing all available locations
     */
    std::vector<std::shared_ptr<StorageLocation>> findAvailableLocations() const noexcept;

    /**
     * @brief Find optimal location for new inventory
     * 
     * @param quantity integer value containing quantity to store
     * @param preferredSectionType WarehouseSection::SectionType value containing preferred section type
     * 
     * @return std::shared_ptr<StorageLocation> containing optimal location or nullptr
     */
    std::shared_ptr<StorageLocation> findOptimalLocation(int quantity, WarehouseSection::SectionType preferredSectionType = WarehouseSection::SectionType::GENERAL) const noexcept;

    /**
     * @brief Get total warehouse capacity
     * 
     * @return int containing total capacity
     */
    int getTotalCapacity() const noexcept;

    /**
     * @brief Get current warehouse load
     * 
     * @return int containing current total load
     */
    int getCurrentLoad() const noexcept;

    /**
     * @brief Get available warehouse space
     * 
     * @return int containing total available space
     */
    int getAvailableSpace() const noexcept;

    /**
     * @brief Get warehouse utilization percentage
     * 
     * @return double containing utilization percentage (0-100)
     */
    double getUtilizationPercentage() const noexcept;

    /**
     * @brief Check if warehouse is empty
     * 
     * @return true if warehouse is empty
     * @return false if warehouse is not empty
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Check if warehouse is full
     * 
     * @return true if warehouse is full
     * @return false if warehouse is not full
     */
    bool isFull() const noexcept;

    /**
     * @brief Get warehouse information
     * 
     * @return std::string containing formatted warehouse information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Get detailed warehouse report
     * 
     * @return std::string containing detailed warehouse report
     */
    std::string getDetailedReport() const noexcept;

    /**
     * @brief Equality comparison operator for warehouses
     * 
     * @param other constant reference to the warehouse to compare with
     * 
     * @return true if warehouses are equal
     * @return false if warehouses are not equal
     */
    bool operator==(const Warehouse& other) const noexcept;

    /**
     * @brief Inequality comparison operator for warehouses
     * 
     * @param other constant reference to the warehouse to compare with
     * 
     * @return true if warehouses are not equal
     * @return false if warehouses are equal
     */
    bool operator!=(const Warehouse& other) const noexcept;
};