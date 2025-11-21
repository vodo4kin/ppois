/**
 * @file Apartment.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Apartment class for apartment accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class Apartment
 * @brief Class representing apartment type accommodation
 * 
 * Extends Accommodation with apartment-specific properties like room count,
 * kitchen availability, and area. Provides methods for apartment categorization
 * and family suitability assessment.
 */
class Apartment : public Accommodation {
private:
    int numberOfRooms;                                      ///< Number of rooms in apartment
    bool hasKitchen;                                        ///< Kitchen availability flag
    bool hasWashingMachine;                                 ///< Washing machine availability flag
    double area;                                            ///< Apartment area in square meters

public:
    /**
     * @brief Construct a new Apartment object
     * 
     * @param name constant reference to the string containing apartment name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing apartment rating
     * @param rooms integer value containing number of rooms
     * @param kitchen boolean value indicating kitchen availability
     * @param washingMachine boolean value indicating washing machine availability
     * @param area double value containing apartment area
     */
    Apartment(const std::string& name, const std::string& location,
              double price, int capacity, double rating,
              int rooms, bool kitchen, bool washingMachine, double area);
    
    /**
     * @brief Get the apartment type
     * 
     * @return std::string containing "Apartment"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive apartment information
     * 
     * @return std::string containing formatted apartment details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Get the number of rooms
     * 
     * @return int containing room count
     */
    int getNumberOfRooms() const;
    
    /**
     * @brief Check if apartment has full kitchen
     * 
     * @return true if apartment has kitchen
     * @return false if apartment does not have kitchen
     */
    bool hasFullKitchen() const;
    
    /**
     * @brief Check if apartment has laundry facilities
     * 
     * @return true if apartment has washing machine
     * @return false if apartment does not have washing machine
     */
    bool hasLaundry() const;
    
    /**
     * @brief Get the apartment area
     * 
     * @return double containing area in square meters
     */
    double getArea() const;
    
    /**
     * @brief Check if apartment is suitable for families
     * 
     * @return true if apartment is family-friendly
     * @return false if apartment is not family-friendly
     */
    bool isSuitableForFamily() const;
    
    /**
     * @brief Check if apartment is studio type
     * 
     * @return true if apartment is studio
     * @return false if apartment is not studio
     */
    bool isStudio() const;
    
    /**
     * @brief Calculate price per person
     * 
     * @return double containing price per person per night
     */
    double calculatePricePerPerson() const;
    
    /**
     * @brief Get apartment category based on features
     * 
     * @return std::string containing apartment category
     */
    std::string getApartmentCategory() const;
    
    /**
     * @brief Check if apartment has full amenities
     * 
     * @return true if apartment has all essential amenities
     * @return false if apartment lacks some amenities
     */
    bool hasFullAmenities() const;
};