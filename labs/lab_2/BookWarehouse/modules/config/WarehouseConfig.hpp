/**
 * @file WarehouseConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Warehouse module
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once

#include <cstddef>

/**
 * @namespace WarehouseConfig
 * @brief Namespace containing all configuration constants for the Warehouse module
 * 
 * Provides centralized configuration for all warehouse-related limits and constraints.
 */
namespace WarehouseConfig {
    /**
     * @namespace StorageLocation
     * @brief Configuration constants for StorageLocation class
     */
    namespace StorageLocation {
        static constexpr int MAX_CAPACITY = 1000;              ///< Maximum capacity for a storage location
        static constexpr int MIN_CAPACITY = 1;                 ///< Minimum capacity for a storage location
    }

    /**
     * @namespace Shelf
     * @brief Configuration constants for Shelf class
     */
    namespace Shelf {
        static constexpr int MAX_LOCATIONS = 50;               ///< Maximum number of locations per shelf
        static constexpr int MIN_LOCATIONS = 1;                ///< Minimum number of locations per shelf
    }

    /**
     * @namespace WarehouseSection
     * @brief Configuration constants for WarehouseSection class
     */
    namespace WarehouseSection {
        static constexpr double MIN_TEMPERATURE = -50.0;       ///< Minimum allowed temperature
        static constexpr double MAX_TEMPERATURE = 50.0;        ///< Maximum allowed temperature
        static constexpr double MIN_HUMIDITY = 0.0;            ///< Minimum allowed humidity
        static constexpr double MAX_HUMIDITY = 100.0;          ///< Maximum allowed humidity
        static constexpr size_t MAX_NAME_LENGTH = 50;          ///< Maximum section name length
        static constexpr double DEFAULT_TEMPERATURE = 20.0;    ///< Default section temperature
        static constexpr double DEFAULT_HUMIDITY = 50.0;       ///< Default section humidity
    }

    /**
     * @namespace InventoryItem
     * @brief Configuration constants for InventoryItem class
     */
    namespace InventoryItem {
        static constexpr int MAX_QUANTITY = 10000;             ///< Maximum quantity per inventory item
        static constexpr int MIN_QUANTITY = 0;                 ///< Minimum quantity per inventory item
    }

    /**
     * @namespace Warehouse
     * @brief Configuration constants for Warehouse class
     */
    namespace Warehouse {
        static constexpr int MAX_SECTIONS = 26;                ///< Maximum number of sections (A-Z)
        static constexpr size_t MAX_NAME_LENGTH = 100;         ///< Maximum warehouse name length
        static constexpr size_t MAX_ADDRESS_LENGTH = 200;      ///< Maximum warehouse address length
    }

    /**
     * @namespace StockMovement
     * @brief Configuration constants for StockMovement classes
     */
    namespace StockMovement {
        static constexpr size_t MAX_NOTES_LENGTH = 500;        ///< Maximum notes length
        static constexpr size_t MAX_DETAILED_REASON_LENGTH = 500; ///< Maximum detailed reason length
        static constexpr size_t MAX_TRANSFER_REASON_LENGTH = 200; ///< Maximum transfer reason length
    }

    /**
     * @namespace StockReceipt
     * @brief Configuration constants for StockReceipt class
     */
    namespace StockReceipt {
        static constexpr size_t MAX_SUPPLIER_NAME_LENGTH = 100; ///< Maximum supplier name length
        static constexpr double MAX_TOTAL_COST = 1000000.0;     ///< Maximum total cost
        static constexpr double MIN_TOTAL_COST = 0.0;           ///< Minimum total cost
    }

    /**
     * @namespace StringValidation
     * @brief Configuration constants for StringValidation utilities
     */
    namespace StringValidation {
        static constexpr size_t MAX_DATE_LENGTH = 10;          ///< Maximum date string length (YYYY-MM-DD)
    }
    
    /**
     * @namespace DeliveryConfig
     * @brief Configuration constants for Delivery class
     */
    namespace DeliveryConfig {
        static constexpr double MAX_SHIPPING_COST = 10000.0;  ///< Maximum allowed shipping cost in currency units
        static constexpr size_t MAX_TRACKING_LENGTH = 50;     ///< Maximum allowed length for tracking numbers
        static constexpr size_t MAX_CARRIER_LENGTH = 50;      ///< Maximum allowed length for carrier company names
    }
}