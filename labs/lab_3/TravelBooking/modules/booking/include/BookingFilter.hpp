#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Booking.hpp"

class BookingFilter {
public:
    static std::vector<std::shared_ptr<Booking>> filterByStatus(
        const std::vector<std::shared_ptr<Booking>>& bookings,
        Booking::Status status);

    static std::vector<std::shared_ptr<Booking>> filterByDate(
        const std::vector<std::shared_ptr<Booking>>& bookings,
        const std::string& targetDate);

    static std::vector<std::shared_ptr<Booking>> filterByPriceRange(
        const std::vector<std::shared_ptr<Booking>>& bookings,
        double minPrice,
        double maxPrice);
};