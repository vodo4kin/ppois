/**
 * @file Shelf.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Shelf class for working with shelves in warehouse
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "warehouse/StorageLocation.hpp"

/**
 * @class Shelf
 * @brief Class for working with shelves in warehouse
 * 
 * Represents a shelf containing multiple storage locations.
 * Manages shelf capacity, organization, and provides operations
 * for finding available locations and managing shelf space.
 */
class Shelf {
private:
    std::string shelfId;                                     ///< Unique identifier for the shelf
    int maxLocations;                                        ///< Maximum number of storage locations on shelf
    std::vector<std::shared_ptr<StorageLocation>> locations; ///< Storage locations on this shelf

    /**
     * @brief Private method to validate shelf ID format
     * 
     * @param shelfId constant reference to the string containing shelf ID to validate
     * 
     * @return true if shelf ID is valid
     * @return false if shelf ID is invalid
     */
    bool isValidShelfId(const std::string& shelfId) const;

    /**
     * @brief Private method to validate maximum locations count
     * 
     * @param maxLocations integer value containing maximum locations to validate
     * 
     * @return true if maximum locations is valid
     * @return false if maximum locations is invalid
     */
    bool isValidMaxLocations(int maxLocations) const;

public:
    /**
     * @brief Construct a new Shelf object
     * 
     * @param shelfId constant reference to the string containing shelf identifier
     * @param maxLocations integer value containing maximum number of locations
     */
    Shelf(const std::string& shelfId, int maxLocations);

    /**
     * @brief Get the shelf identifier
     * 
     * @return std::string containing shelf identifier
     */
    std::string getShelfId() const noexcept;

    /**
     * @brief Get the maximum locations count
     * 
     * @return int containing maximum number of locations
     */
    int getMaxLocations() const noexcept;

    /**
     * @brief Get the current locations count
     * 
     * @return int containing current number of locations
     */
    int getCurrentLocationsCount() const noexcept;

    /**
     * @brief Get all storage locations
     * 
     * @return std::vector<std::shared_ptr<StorageLocation>> containing all locations on shelf
     */
    std::vector<std::shared_ptr<StorageLocation>> getLocations() const noexcept;

    /**
     * @brief Add storage location to shelf
     * 
     * @param location shared pointer to the StorageLocation object to add
     */
    void addLocation(std::shared_ptr<StorageLocation> location);

    /**
     * @brief Remove storage location from shelf
     * 
     * @param locationId constant reference to the string containing location ID to remove
     */
    void removeLocation(const std::string& locationId);

    /**
     * @brief Find storage location by ID
     * 
     * @param locationId constant reference to the string containing location ID to find
     * 
     * @return std::shared_ptr<StorageLocation> containing found location or nullptr
     */
    std::shared_ptr<StorageLocation> findLocation(const std::string& locationId) const noexcept;

    /**
     * @brief Check if shelf contains location with specified ID
     * 
     * @param locationId constant reference to the string containing location ID to check
     * 
     * @return true if shelf contains location
     * @return false if shelf does not contain location
     */
    bool containsLocation(const std::string& locationId) const noexcept;

    /**
     * @brief Get available storage locations
     * 
     * @return std::vector<std::shared_ptr<StorageLocation>> containing available (free) locations
     */
    std::vector<std::shared_ptr<StorageLocation>> getAvailableLocations() const noexcept;

    /**
     * @brief Get occupied storage locations
     * 
     * @return std::vector<std::shared_ptr<StorageLocation>> containing occupied locations
     */
    std::vector<std::shared_ptr<StorageLocation>> getOccupiedLocations() const noexcept;

    /**
     * @brief Check if shelf has available space for new locations
     * 
     * @return true if shelf has available space
     * @return false if shelf is full
     */
    bool hasAvailableSpace() const noexcept;

    /**
     * @brief Get total capacity of all locations on shelf
     * 
     * @return int containing total capacity
     */
    int getTotalCapacity() const noexcept;

    /**
     * @brief Get current load of all locations on shelf
     * 
     * @return int containing current total load
     */
    int getCurrentLoad() const noexcept;

    /**
     * @brief Get available space on shelf
     * 
     * @return int containing total available space
     */
    int getAvailableSpace() const noexcept;

    /**
     * @brief Check if shelf is empty
     * 
     * @return true if shelf is empty
     * @return false if shelf is not empty
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Check if shelf is full
     * 
     * @return true if shelf is full
     * @return false if shelf is not full
     */
    bool isFull() const noexcept;

    /**
     * @brief Get shelf information
     * 
     * @return std::string containing formatted shelf information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for shelves
     * 
     * @param other constant reference to the shelf to compare with
     * 
     * @return true if shelves are equal
     * @return false if shelves are not equal
     */
    bool operator==(const Shelf& other) const noexcept;

    /**
     * @brief Inequality comparison operator for shelves
     * 
     * @param other constant reference to the shelf to compare with
     * 
     * @return true if shelves are not equal
     * @return false if shelves are equal
     */
    bool operator!=(const Shelf& other) const noexcept;
};