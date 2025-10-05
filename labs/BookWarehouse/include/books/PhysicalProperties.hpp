/**
 * @file PhysicalProperties.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the PhysicalProperties class for working with book physical characteristics
 * @version 0.1
 * @date 2025-01-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class PhysicalProperties
 * @brief Class for working with book physical characteristics
 * 
 * Stores physical properties of books including weight, dimensions,
 * page count, cover type and material. Provides calculations for
 * volume and density.
 */
class PhysicalProperties {
public:
    /**
     * @enum CoverType
     * @brief Enumeration for book cover types
     */
    enum class CoverType {
        HARDCOVER,  ///< Hardcover book cover
        PAPERBACK   ///< Paperback book cover
    };

private:
    int weight;           ///< Weight in grams
    int height;           ///< Height in millimeters  
    int width;            ///< Width in millimeters
    int thickness;        ///< Thickness in millimeters
    int pageCount;        ///< Number of pages
    CoverType coverType;  ///< Type of book cover
    std::string material; ///< Cover material

    /**
     * @brief Private method to validate weight value
     * 
     * @param weight integer value containing weight to validate
     * 
     * @return true if weight is valid
     * @return false if weight is invalid
     */
    bool isValidWeight(int weight) const;

    /**
     * @brief Private method to validate dimension value
     * 
     * @param dimension integer value containing dimension to validate
     * 
     * @return true if dimension is valid
     * @return false if dimension is invalid
     */
    bool isValidDimension(int dimension) const;

    /**
     * @brief Private method to validate page count value
     * 
     * @param pages integer value containing page count to validate
     * 
     * @return true if page count is valid
     * @return false if page count is invalid
     */
    bool isValidPageCount(int pages) const;

public:
    /**
     * @brief Construct a new PhysicalProperties object
     * 
     * @param weight integer value containing weight in grams
     * @param height integer value containing height in millimeters
     * @param width integer value containing width in millimeters
     * @param thickness integer value containing thickness in millimeters
     * @param pageCount integer value containing number of pages
     * @param coverType CoverType value containing cover type
     * @param material constant reference to the string containing cover material
     */
    PhysicalProperties(int weight, int height, int width, int thickness, 
                      int pageCount, CoverType coverType, const std::string& material);

    /**
     * @brief Get the weight value
     * 
     * @return int containing weight in grams
     */
    int getWeight() const noexcept;

    /**
     * @brief Get the height value
     * 
     * @return int containing height in millimeters
     */
    int getHeight() const noexcept;

    /**
     * @brief Get the width value
     * 
     * @return int containing width in millimeters
     */
    int getWidth() const noexcept;

    /**
     * @brief Get the thickness value
     * 
     * @return int containing thickness in millimeters
     */
    int getThickness() const noexcept;

    /**
     * @brief Get the page count value
     * 
     * @return int containing number of pages
     */
    int getPageCount() const noexcept;

    /**
     * @brief Get the cover type
     * 
     * @return CoverType containing cover type
     */
    CoverType getCoverType() const noexcept;

    /**
     * @brief Get the cover material
     * 
     * @return std::string containing cover material
     */
    std::string getMaterial() const noexcept;

    /**
     * @brief Calculate book volume
     * 
     * @return double containing volume in cubic centimeters
     */
    double getVolume() const noexcept;

    /**
     * @brief Calculate book density
     * 
     * @return double containing density in grams per cubic centimeter
     */
    double getDensity() const noexcept;

    /**
     * @brief Get cover type as string
     * 
     * @return std::string containing cover type description
     */
    std::string getCoverTypeString() const noexcept;

    /**
     * @brief Equality comparison operator for physical properties
     * 
     * @param other constant reference to the physical properties to compare with
     * 
     * @return true if physical properties are equal
     * @return false if physical properties are not equal
     */
    bool operator==(const PhysicalProperties& other) const noexcept;

    /**
     * @brief Inequality comparison operator for physical properties
     * 
     * @param other constant reference to the physical properties to compare with
     * 
     * @return true if physical properties are not equal
     * @return false if physical properties are equal
     */
    bool operator!=(const PhysicalProperties& other) const noexcept;
};