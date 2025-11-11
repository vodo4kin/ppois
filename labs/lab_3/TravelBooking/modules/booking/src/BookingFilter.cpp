#include "BookingFilter.hpp"
#include "utils/Utils.hpp"

std::vector<std::shared_ptr<Booking>> BookingFilter::filterByStatus(
    const std::vector<std::shared_ptr<Booking>>& bookings,
    Booking::Status status) {
    std::vector<std::shared_ptr<Booking>> result;
    for (const auto& booking : bookings) {
        if (booking->getStatus() == status) {
            result.push_back(booking);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Booking>> BookingFilter::filterByDate(
    const std::vector<std::shared_ptr<Booking>>& bookings,
    const std::string& targetDate) {
    std::vector<std::shared_ptr<Booking>> result;
    for (const auto& booking : bookings) {
        if (booking->getBookingDate() == targetDate) {
            result.push_back(booking);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Booking>> BookingFilter::filterByPriceRange(
    const std::vector<std::shared_ptr<Booking>>& bookings,
    double minPrice,
    double maxPrice) {
    std::vector<std::shared_ptr<Booking>> result;
    for (const auto& booking : bookings) {
        double price = booking->getTotalPrice();
        if (price >= minPrice && price <= maxPrice) {
            result.push_back(booking);
        }
    }
    return result;
}
