/**
 * @file BookingFilter.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the BookingFilter class for booking filtering operations
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Booking.hpp"

/**
 * @class BookingFilter
 * @brief Utility class for filtering booking collections
 * 
 * Provides static methods for filtering bookings by various criteria
 * including status, date, and price range.
 */
class BookingFilter {
public:
    /**
     * @brief Filter bookings by status
     * 
     * @param bookings constant reference to the vector containing bookings to filter
     * @param status Booking::Status value containing target status
     * 
     * @return std::vector<std::shared_ptr<Booking>> containing filtered bookings
     */
    static std::vector<std::shared_ptr<Booking>> filterByStatus(
        const std::vector<std::shared_ptr<Booking>>& bookings,
        Booking::Status status);

    /**
     * @brief Filter bookings by date
     * 
     * @param bookings constant reference to the vector containing bookings to filter
     * @param targetDate constant reference to the string containing target date
     * 
     * @return std::vector<std::shared_ptr<Booking>> containing filtered bookings
     */
    static std::vector<std::shared_ptr<Booking>> filterByDate(
        const std::vector<std::shared_ptr<Booking>>& bookings,
        const std::string& targetDate);

    /**
     * @brief Filter bookings by price range
     * 
     * @param bookings constant reference to the vector containing bookings to filter
     * @param minPrice double value containing minimum price
     * @param maxPrice double value containing maximum price
     * 
     * @return std::vector<std::shared_ptr<Booking>> containing filtered bookings
     */
    static std::vector<std::shared_ptr<Booking>> filterByPriceRange(
        const std::vector<std::shared_ptr<Booking>>& bookings,
        double minPrice,
        double maxPrice);
};