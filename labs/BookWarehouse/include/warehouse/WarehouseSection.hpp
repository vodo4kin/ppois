/**
 * @file WarehouseSection.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the WarehouseSection class for working with warehouse sections
 * @version 0.1
 * @date 2025-10-04
 * 
 * 
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "warehouse/Shelf.hpp"

/**
 * @class WarehouseSection
 * @brief Class for working with warehouse sections
 * 
 * Represents a section of the warehouse containing multiple shelves.
 * Manages section organization, provides operations for finding available
 * storage space and managing section-wide inventory metrics.
 */
class WarehouseSection {
public:
    /**
     * @enum SectionType
     * @brief Enumeration of warehouse section types
     */
    enum class SectionType {
        GENERAL,        ///< General storage section
        REFRIGERATED,   ///< Refrigerated section for sensitive materials
        SECURE,         ///< Secure section for valuable items
        BULK,           ///< Bulk storage section for large quantities
        PICKING         ///< Picking section for fast order fulfillment
    };

private:
    std::string sectionId;                          ///< Unique identifier for the section (A, B, C...)
    std::string name;                               ///< Name of the section
    std::string description;                        ///< Description of the section
    SectionType sectionType;                        ///< Type of the section
    std::vector<std::shared_ptr<Shelf>> shelves;    ///< Shelves in this section
    double temperature;                             ///< Current temperature in section (optional)
    double humidity;                                ///< Current humidity in section (optional)

    /**
     * @brief Private method to validate section ID
     * 
     * @param sectionId constant reference to the string containing section ID to validate
     * 
     * @return true if section ID is valid
     * @return false if section ID is invalid
     */
    bool isValidSectionId(const std::string& sectionId) const;

    /**
     * @brief Private method to validate section name
     * 
     * @param name constant reference to the string containing section name to validate
     * 
     * @return true if section name is valid
     * @return false if section name is invalid
     */
    bool isValidName(const std::string& name) const;

    /**
     * @brief Private method to validate temperature value
     * 
     * @param temperature double value containing temperature to validate
     * 
     * @return true if temperature is valid
     * @return false if temperature is invalid
     */
    bool isValidTemperature(double temperature) const;

    /**
     * @brief Private method to validate humidity value
     * 
     * @param humidity double value containing humidity to validate
     * 
     * @return true if humidity is valid
     * @return false if humidity is invalid
     */
    bool isValidHumidity(double humidity) const;

public:
    /**
     * @brief Construct a new WarehouseSection object
     * 
     * @param sectionId constant reference to the string containing section identifier
     * @param name constant reference to the string containing section name
     * @param description constant reference to the string containing section description
     * @param sectionType SectionType value containing section type
     * @param temperature double value containing section temperature
     * @param humidity double value containing section humidity
     */
    WarehouseSection(const std::string& sectionId, const std::string& name, 
                     const std::string& description = "", SectionType sectionType = SectionType::GENERAL,
                     double temperature = 20.0, double humidity = 50.0);

    /**
     * @brief Get the section identifier
     * 
     * @return std::string containing section identifier
     */
    std::string getSectionId() const noexcept;

    /**
     * @brief Get the section name
     * 
     * @return std::string containing section name
     */
    std::string getName() const noexcept;

    /**
     * @brief Get the section description
     * 
     * @return std::string containing section description
     */
    std::string getDescription() const noexcept;

    /**
     * @brief Get the section type
     * 
     * @return SectionType containing section type
     */
    SectionType getSectionType() const noexcept;

    /**
     * @brief Get the section temperature
     * 
     * @return double containing section temperature
     */
    double getTemperature() const noexcept;

    /**
     * @brief Get the section humidity
     * 
     * @return double containing section humidity
     */
    double getHumidity() const noexcept;

    /**
     * @brief Get all shelves in section
     * 
     * @return std::vector<std::shared_ptr<Shelf>> containing all shelves
     */
    std::vector<std::shared_ptr<Shelf>> getShelves() const noexcept;

    /**
     * @brief Get the number of shelves in section
     * 
     * @return int containing number of shelves
     */
    int getShelvesCount() const noexcept;

    /**
     * @brief Add shelf to section
     * 
     * @param shelf shared pointer to the Shelf object to add
     */
    void addShelf(std::shared_ptr<Shelf> shelf);

    /**
     * @brief Remove shelf from section
     * 
     * @param shelfId constant reference to the string containing shelf ID to remove
     */
    void removeShelf(const std::string& shelfId);

    /**
     * @brief Find shelf by ID
     * 
     * @param shelfId constant reference to the string containing shelf ID to find
     * 
     * @return std::shared_ptr<Shelf> containing found shelf or nullptr
     */
    std::shared_ptr<Shelf> findShelf(const std::string& shelfId) const noexcept;

    /**
     * @brief Check if section contains shelf with specified ID
     * 
     * @param shelfId constant reference to the string containing shelf ID to check
     * 
     * @return true if section contains shelf
     * @return false if section does not contain shelf
     */
    bool containsShelf(const std::string& shelfId) const noexcept;

    /**
     * @brief Find available storage locations in entire section
     * 
     * @return std::vector<std::shared_ptr<StorageLocation>> containing all available locations
     */
    std::vector<std::shared_ptr<StorageLocation>> findAvailableLocations() const noexcept;

    /**
     * @brief Find specific storage location by full ID
     * 
     * @param locationId constant reference to the string containing full location ID (A-01-B-05)
     * 
     * @return std::shared_ptr<StorageLocation> containing found location or nullptr
     */
    std::shared_ptr<StorageLocation> findLocation(const std::string& locationId) const noexcept;

    /**
     * @brief Get total capacity of entire section
     * 
     * @return int containing total capacity
     */
    int getTotalCapacity() const noexcept;

    /**
     * @brief Get current load of entire section
     * 
     * @return int containing current total load
     */
    int getCurrentLoad() const noexcept;

    /**
     * @brief Get available space in entire section
     * 
     * @return int containing total available space
     */
    int getAvailableSpace() const noexcept;

    /**
     * @brief Check if section is empty
     * 
     * @return true if section is empty
     * @return false if section is not empty
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Check if section is full
     * 
     * @return true if section is full
     * @return false if section is not full
     */
    bool isFull() const noexcept;

    /**
     * @brief Set the section temperature
     * 
     * @param temperature double value containing new temperature
     */
    void setTemperature(double temperature);

    /**
     * @brief Set the section humidity
     * 
     * @param humidity double value containing new humidity
     */
    void setHumidity(double humidity);

    /**
     * @brief Get section information
     * 
     * @return std::string containing formatted section information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Get section type as string
     * 
     * @return std::string containing section type description
     */
    std::string getSectionTypeString() const noexcept;

    /**
     * @brief Equality comparison operator for warehouse sections
     * 
     * @param other constant reference to the warehouse section to compare with
     * 
     * @return true if warehouse sections are equal
     * @return false if warehouse sections are not equal
     */
    bool operator==(const WarehouseSection& other) const noexcept;

    /**
     * @brief Inequality comparison operator for warehouse sections
     * 
     * @param other constant reference to the warehouse section to compare with
     * 
     * @return true if warehouse sections are not equal
     * @return false if warehouse sections are equal
     */
    bool operator!=(const WarehouseSection& other) const noexcept;
};