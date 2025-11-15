/**
 * @file TransportManager.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TransportManager class for transport management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "TransportSchedule.hpp"
#include "TransportReview.hpp"

/**
 * @class TransportManager
 * @brief Main management class for transportation system
 * 
 * Provides centralized management for transport schedules and reviews.
 * Implements functionality for schedule search, seat reservation, and review management.
 */
class TransportManager {
private:
    std::vector<std::shared_ptr<TransportSchedule>> schedules;  ///< Collection of transport schedules
    std::vector<std::shared_ptr<TransportReview>> reviews;      ///< Collection of transport reviews

public:
    /**
     * @brief Add new transport schedule
     * 
     * @param schedule shared pointer to the TransportSchedule object to add
     */
    void addSchedule(const std::shared_ptr<TransportSchedule>& schedule);
    
    /**
     * @brief Add new transport review
     * 
     * @param review shared pointer to the TransportReview object to add
     */
    void addReview(const std::shared_ptr<TransportReview>& review);
    
    /**
     * @brief Find schedule by route parameters
     * 
     * @param origin constant reference to the string containing origin location
     * @param destination constant reference to the string containing destination location
     * @param date constant reference to the string containing departure date
     * 
     * @return std::shared_ptr<TransportSchedule> containing found schedule or nullptr
     */
    std::shared_ptr<TransportSchedule> findScheduleByRoute(const std::string& origin,
                                                            const std::string& destination,
                                                            const std::string& date) const;
    
    /**
     * @brief Reserve seats for specified transport
     * 
     * @param transportType constant reference to the Transport::Type value
     * @param origin constant reference to the string containing origin location
     * @param destination constant reference to the string containing destination location
     * @param date constant reference to the string containing departure date
     * @param count integer value containing number of seats to reserve
     */
    void reserveSeats(const Transport::Type& transportType,
                      const std::string& origin,
                      const std::string& destination,
                      const std::string& date,
                      int count);
    
    /**
     * @brief Get reviews for specific transport type
     * 
     * @param transportType constant reference to the string containing transport type
     * 
     * @return std::vector<std::shared_ptr<TransportReview>> containing all matching reviews
     */
    std::vector<std::shared_ptr<TransportReview>> getReviewsForTransport(const std::string& transportType) const;
};