/**
 * @file Hostel.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Hostel class for hostel accommodations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Accommodation.hpp"

/**
 * @class Hostel
 * @brief Class representing hostel type accommodation
 * 
 * Extends Accommodation with hostel-specific properties like room privacy,
 * bed count, and shared facilities. Provides methods for dormitory classification
 * and group suitability assessment.
 */
class Hostel : public Accommodation {
private:
    bool isPrivateRoom;                                      ///< Private room availability flag
    int bedsPerRoom;                                         ///< Number of beds per room
    bool hasSharedKitchen;                                   ///< Shared kitchen availability flag
    std::string bathroomType;                                ///< Type of bathroom facilities

public:
    /**
     * @brief Construct a new Hostel object
     * 
     * @param name constant reference to the string containing hostel name
     * @param location constant reference to the string containing location
     * @param price double value containing price per night
     * @param capacity integer value containing maximum guest capacity
     * @param rating double value containing hostel rating
     * @param privateRoom boolean value indicating private room availability
     * @param beds integer value containing beds per room
     * @param sharedKitchen boolean value indicating shared kitchen availability
     * @param bathroom constant reference to the string containing bathroom type
     */
    Hostel(const std::string& name, const std::string& location,
           double price, int capacity, double rating,
           bool privateRoom, int beds, bool sharedKitchen, const std::string& bathroom);
    
    /**
     * @brief Get the hostel type
     * 
     * @return std::string containing "Hostel"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive hostel information
     * 
     * @return std::string containing formatted hostel details
     */
    std::string getAccommodationInfo() const override;
    
    /**
     * @brief Check if room is private
     * 
     * @return true if room is private
     * @return false if room is shared
     */
    bool isPrivate() const;
    
    /**
     * @brief Get the number of beds per room
     * 
     * @return int containing beds per room count
     */
    int getBedsPerRoom() const;
    
    /**
     * @brief Check if hostel has common kitchen
     * 
     * @return true if shared kitchen is available
     * @return false if shared kitchen is not available
     */
    bool hasCommonKitchen() const;
    
    /**
     * @brief Get the bathroom type
     * 
     * @return std::string containing bathroom type description
     */
    std::string getBathroomType() const;
    
    /**
     * @brief Check if accommodation is dormitory type
     * 
     * @return true if accommodation is dormitory
     * @return false if accommodation is not dormitory
     */
    bool isDormitory() const;
    
    /**
     * @brief Calculate price per bed
     * 
     * @return double containing price per bed per night
     */
    double calculatePricePerBed() const;
    
    /**
     * @brief Check if room has private bathroom
     * 
     * @return true if private bathroom is available
     * @return false if private bathroom is not available
     */
    bool hasPrivateBathroom() const;
    
    /**
     * @brief Get hostel category
     * 
     * @return std::string containing hostel category
     */
    std::string getHostelCategory() const;
    
    /**
     * @brief Check if hostel is suitable for group
     * 
     * @param groupSize integer value containing group size to check
     * 
     * @return true if suitable for specified group size
     * @return false if not suitable for specified group size
     */
    bool isSuitableForGroup(int groupSize) const;
};