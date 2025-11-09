/**
 * @file InventoryReport.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the InventoryReport class for generating warehouse reports
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Warehouse.hpp"
#include "Book.hpp"
#include "InventoryItem.hpp"
#include "StorageLocation.hpp"
#include "WarehouseSection.hpp"
#include "Shelf.hpp"

/**
 * @class InventoryReport
 * @brief Class for generating comprehensive inventory reports
 * 
 * Provides various report generation capabilities including stock levels,
 * warehouse utilization, movement history, and analytical insights.
 */
class InventoryReport {
private:
    std::shared_ptr<Warehouse> warehouse;  ///< Warehouse to generate reports for

    struct BookCounts {
        int uniqueBooks;
        int totalBooks;
    };

    void validateWarehouse() const;

    // Stock analysis methods
    BookCounts calculateBookCounts(const std::vector<std::shared_ptr<InventoryItem>>& inventory) const;
    bool isValidInventoryItem(std::shared_ptr<InventoryItem> item) const;
    BookCounts updateBookCounts(BookCounts counts, const std::string& currentIsbn, 
                               const std::string& lastIsbn, int quantity) const;

    // Report building methods
    std::string buildBookHeader(const std::vector<std::shared_ptr<InventoryItem>>& items, 
                               const std::string& bookIsbn) const;
    std::string buildLocationDetails(const std::vector<std::shared_ptr<InventoryItem>>& items) const;
    std::string buildLocationLine(std::shared_ptr<InventoryItem> item) const;
    
    // Capacity analysis methods
    std::string buildCapacityMetrics() const;
    std::string buildWarehouseStatus() const;
    std::string buildLowStockAlerts(int threshold) const;
    
    // Location analysis methods
    std::string buildEmptyLocationsList(const std::vector<std::shared_ptr<StorageLocation>>& locations) const;
    std::string buildEmptyLocationLine(std::shared_ptr<StorageLocation> location) const;
    std::vector<std::shared_ptr<StorageLocation>> findFullLocations() const;
    void collectFullLocationsFromSection(std::shared_ptr<WarehouseSection> section,
                                        std::vector<std::shared_ptr<StorageLocation>>& fullLocations) const;
    void collectFullLocationsFromShelf(std::shared_ptr<Shelf> shelf,
                                      std::vector<std::shared_ptr<StorageLocation>>& fullLocations) const;
    std::string buildFullLocationsList(const std::vector<std::shared_ptr<StorageLocation>>& fullLocations) const;
    std::string buildFullLocationLine(std::shared_ptr<StorageLocation> location) const;
    
    // Statistics methods
    std::string buildBasicStatistics() const;

public:
    /**
     * @brief Construct a new InventoryReport object
     * 
     * @param warehouse shared pointer to the Warehouse object
     */
    explicit InventoryReport(std::shared_ptr<Warehouse> warehouse);

    /**
     * @brief Get the warehouse
     * 
     * @return std::shared_ptr<Warehouse> containing warehouse
     */
    std::shared_ptr<Warehouse> getWarehouse() const noexcept;

    /**
     * @brief Set the warehouse
     * 
     * @param warehouse shared pointer to the Warehouse object
     */
    void setWarehouse(std::shared_ptr<Warehouse> warehouse);

    /**
     * @brief Generate comprehensive inventory report
     * 
     * @return std::string containing full inventory report
     */
    std::string generateFullReport() const;

    /**
     * @brief Generate stock level report for all books
     * 
     * @return std::string containing stock level report
     */
    std::string generateStockLevelReport() const;

    /**
     * @brief Generate stock level report for specific book
     * 
     * @param bookIsbn constant reference to the string containing book ISBN
     * 
     * @return std::string containing book stock report
     */
    std::string generateBookStockReport(const std::string& bookIsbn) const;

    /**
     * @brief Generate warehouse capacity report
     * 
     * @return std::string containing capacity report
     */
    std::string generateCapacityReport() const;

    /**
     * @brief Generate section-wise utilization report
     * 
     * @return std::string containing section utilization report
     */
    std::string generateSectionUtilizationReport() const;

    /**
     * @brief Generate low stock alert report
     * 
     * @param threshold integer value containing low stock threshold
     * 
     * @return std::string containing low stock alerts
     */
    std::string generateLowStockReport(int threshold = 10) const;

    /**
     * @brief Generate empty locations report
     * 
     * @return std::string containing empty locations report
     */
    std::string generateEmptyLocationsReport() const;

    /**
     * @brief Generate full locations report
     * 
     * @return std::string containing full locations report
     */
    std::string generateFullLocationsReport() const;

    /**
     * @brief Generate inventory summary statistics
     * 
     * @return std::string containing inventory statistics
     */
    std::string generateStatisticsReport() const;

    /**
     * @brief Equality comparison operator for inventory reports
     * 
     * @param other constant reference to the inventory report to compare with
     * 
     * @return true if inventory reports are equal
     * @return false if inventory reports are not equal
     */
    bool operator==(const InventoryReport& other) const noexcept;

    /**
     * @brief Inequality comparison operator for inventory reports
     * 
     * @param other constant reference to the inventory report to compare with
     * 
     * @return true if inventory reports are not equal
     * @return false if inventory reports are equal
     */
    bool operator!=(const InventoryReport& other) const noexcept;
};