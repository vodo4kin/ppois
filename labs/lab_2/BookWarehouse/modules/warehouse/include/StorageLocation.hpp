/**
 * @file StorageLocation.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the StorageLocation class for working with storage locations in warehouse
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class StorageLocation
 * @brief Class for working with storage locations in warehouse
 * 
 * Represents a specific storage location in the warehouse with unique identifier,
 * capacity tracking, and status management. Used as building block for shelf and section organization.
 */
class StorageLocation {
public:
    /**
     * @enum LocationStatus
     * @brief Enumeration of storage location statuses
     */
    enum class LocationStatus {
        FREE,       ///< Location is free and available for use
        OCCUPIED,   ///< Location is occupied with books
        BLOCKED     ///< Location is blocked (maintenance or other reasons)
    };

private:
    std::string locationId;  ///< Unique identifier for storage location (format: "A-01-B-05")
    int capacity;            ///< Maximum number of books that can be stored
    int currentLoad;         ///< Current number of books stored
    LocationStatus status;   ///< Current status of the location

    /**
     * @brief Private method to validate location ID format
     * 
     * @param locationId constant reference to the string containing location ID to validate
     * 
     * @return true if location ID is valid
     * @return false if location ID is invalid
     */
    bool isValidLocationId(const std::string& locationId) const;

    /**
     * @brief Private method to validate capacity value
     * 
     * @param capacity integer value containing capacity to validate
     * 
     * @return true if capacity is valid
     * @return false if capacity is invalid
     */
    bool isValidCapacity(int capacity) const;

    /**
     * @brief Private method to validate current load value
     * 
     * @param load integer value containing current load to validate
     * @param capacity integer value containing capacity for validation
     * 
     * @return true if current load is valid
     * @return false if current load is invalid
     */
    bool isValidLoad(int load, int capacity) const;

public:
    /**
     * @brief Construct a new StorageLocation object
     * 
     * @param locationId constant reference to the string containing location identifier
     * @param capacity integer value containing maximum capacity
     * @param currentLoad integer value containing current load
     * @param status LocationStatus value containing location status
     */
    StorageLocation(const std::string& locationId, int capacity, 
                    int currentLoad = 0, LocationStatus status = LocationStatus::FREE);

    /**
     * @brief Get the location identifier
     * 
     * @return std::string containing location identifier
     */
    std::string getLocationId() const noexcept;

    /**
     * @brief Get the capacity
     * 
     * @return int containing maximum capacity
     */
    int getCapacity() const noexcept;

    /**
     * @brief Get the current load
     * 
     * @return int containing current number of books stored
     */
    int getCurrentLoad() const noexcept;

    /**
     * @brief Get the available space
     * 
     * @return int containing available space (capacity - current load)
     */
    int getAvailableSpace() const noexcept;

    /**
     * @brief Get the location status
     * 
     * @return LocationStatus containing current status
     */
    LocationStatus getStatus() const noexcept;

    /**
     * @brief Check if location can accommodate specified number of books
     * 
     * @param books integer value containing number of books to check
     * 
     * @return true if location can accommodate the books
     * @return false if location cannot accommodate the books
     */
    bool canAccommodate(int books) const noexcept;

    /**
     * @brief Add books to location
     * 
     * @param count integer value containing number of books to add
     */
    void addBooks(int count);

    /**
     * @brief Remove books from location
     * 
     * @param count integer value containing number of books to remove
     */
    void removeBooks(int count);

    /**
     * @brief Set the location status
     * 
     * @param newStatus LocationStatus value containing new status
     */
    void setStatus(LocationStatus newStatus) noexcept;

    /**
     * @brief Check if location is empty
     * 
     * @return true if location is empty
     * @return false if location is not empty
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Check if location is full
     * 
     * @return true if location is full
     * @return false if location is not full
     */
    bool isFull() const noexcept;

    /**
     * @brief Get location information
     * 
     * @return std::string containing formatted location information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for storage locations
     * 
     * @param other constant reference to the storage location to compare with
     * 
     * @return true if storage locations are equal
     * @return false if storage locations are not equal
     */
    bool operator==(const StorageLocation& other) const noexcept;

    /**
     * @brief Inequality comparison operator for storage locations
     * 
     * @param other constant reference to the storage location to compare with
     * 
     * @return true if storage locations are not equal
     * @return false if storage locations are equal
     */
    bool operator!=(const StorageLocation& other) const noexcept;
};