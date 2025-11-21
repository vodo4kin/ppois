/**
 * @file TourSchedule.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the TourSchedule class for tour scheduling
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Tour.hpp"

/**
 * @class TourSchedule
 * @brief Class representing tour schedule information
 * 
 * Manages tour schedules with dates and available slots.
 * Provides functionality for slot management and schedule information retrieval.
 */
class TourSchedule {
private:
    std::shared_ptr<Tour> tour;                             ///< Shared pointer to tour object
    std::string scheduledDate;                              ///< Date of scheduled tour
    int availableSlots;                                     ///< Number of available slots

public:
    /**
     * @brief Construct a new TourSchedule object
     * 
     * @param tour shared pointer to the Tour object
     * @param scheduledDate constant reference to the string containing scheduled date
     * @param availableSlots integer value containing available slot count
     */
    TourSchedule(std::shared_ptr<Tour> tour,
                 const std::string& scheduledDate,
                 int availableSlots);

    /**
     * @brief Get the tour object
     * 
     * @return std::shared_ptr<Tour> containing tour object
     */
    std::shared_ptr<Tour> getTour() const;
    
    /**
     * @brief Get the scheduled date
     * 
     * @return std::string containing scheduled date
     */
    std::string getScheduledDate() const;
    
    /**
     * @brief Get the available slots count
     * 
     * @return int containing number of available slots
     */
    int getAvailableSlots() const;
    
    /**
     * @brief Reduce available slots by specified count
     * 
     * @param count integer value containing number of slots to reduce
     */
    void reduceSlots(int count);
    
    /**
     * @brief Get comprehensive schedule information
     * 
     * @return std::string containing formatted schedule details
     */
    std::string getScheduleInfo() const;
};