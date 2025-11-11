#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Booking.hpp"

class BookingManager {
private:
    std::vector<std::shared_ptr<Booking>> bookings;
public:
    void addBooking(const std::shared_ptr<Booking>& booking);
    bool cancelBooking(int bookingId);
    std::shared_ptr<Booking> findBookingById(int bookingId) const;
    std::vector<std::shared_ptr<Booking>> getActiveBookings() const;
    double calculateTotalRevenue() const;
    int countBookingsByStatus(Booking::Status status) const;
    std::string getSummary() const;
};
