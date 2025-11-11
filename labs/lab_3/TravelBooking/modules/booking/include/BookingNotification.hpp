#pragma once
#include <string>
#include <memory>
#include "Booking.hpp"

class BookingNotification {
public:
    static void notifyStatusChange(const std::shared_ptr<Booking>& booking);
    static void notifyCancellation(const std::shared_ptr<Booking>& booking);
    static void notifyConfirmation(const std::shared_ptr<Booking>& booking);
};
