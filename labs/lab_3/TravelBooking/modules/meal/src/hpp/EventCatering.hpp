/**
 * @file EventCatering.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the EventCatering class for event catering meals
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Meal.hpp"

/**
 * @class EventCatering
 * @brief Class representing event catering type meal
 * 
 * Extends Meal with event catering-specific properties like guest minimums,
 * service types, and event categories. Provides methods for large event
 * classification and service formality assessment.
 */
class EventCatering : public Meal {
private:
    int minimumGuests;                                      ///< Minimum number of guests required
    std::string serviceType;                                ///< Type of catering service
    bool includesServiceStaff;                              ///< Service staff inclusion flag
    std::string eventType;                                  ///< Type of event catered

public:
    /**
     * @brief Construct a new EventCatering object
     * 
     * @param name constant reference to the string containing meal name
     * @param description constant reference to the string containing description
     * @param price double value containing meal price
     * @param calories integer value containing calorie count
     * @param tags constant reference to the vector containing dietary tags
     * @param minGuests integer value containing minimum guest count
     * @param serviceType constant reference to the string containing service type
     * @param staff boolean value indicating service staff inclusion
     * @param eventType constant reference to the string containing event type
     */
    EventCatering(const std::string& name, const std::string& description,
                  double price, int calories, const std::vector<std::string>& tags,
                  int minGuests, const std::string& serviceType, bool staff, 
                  const std::string& eventType);
    
    /**
     * @brief Get the event catering type
     * 
     * @return std::string containing "EventCatering"
     */
    std::string getType() const override;
    
    /**
     * @brief Get comprehensive event catering information
     * 
     * @return std::string containing formatted event catering details
     */
    std::string getMealInfo() const override;
    
    /**
     * @brief Get the minimum guest count
     * 
     * @return int containing minimum number of guests
     */
    int getMinimumGuests() const;
    
    /**
     * @brief Get the service type
     * 
     * @return std::string containing service type description
     */
    std::string getServiceType() const;
    
    /**
     * @brief Check if catering includes service staff
     * 
     * @return true if service staff are included
     * @return false if service staff are not included
     */
    bool hasServiceStaff() const;
    
    /**
     * @brief Get the event type
     * 
     * @return std::string containing event type description
     */
    std::string getEventType() const;
    
    /**
     * @brief Check if catering is for large event
     * 
     * @return true if large event category
     * @return false if small event category
     */
    bool isLargeEvent() const;
    
    /**
     * @brief Check if catering offers formal service
     * 
     * @return true if formal service style
     * @return false if casual service style
     */
    bool isFormalService() const;
    
    /**
     * @brief Get event catering category
     * 
     * @return std::string containing event catering category
     */
    std::string getCateringCategory() const;
};