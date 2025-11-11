#include "BookingNotification.hpp"
#include "utils/Utils.hpp"

void BookingNotification::notifyStatusChange(const std::shared_ptr<Booking>& booking) {
    if (!booking) return;
    Logger::logInfo("Booking #" + std::to_string(booking->getBookingId()) +
                    " status changed to: " + booking->getStatusStr());
}

void BookingNotification::notifyCancellation(const std::shared_ptr<Booking>& booking) {
    if (!booking) return;
    Logger::logWarning("Booking #" + std::to_string(booking->getBookingId()) +
                       " has been cancelled.");
}

void BookingNotification::notifyConfirmation(const std::shared_ptr<Booking>& booking) {
    if (!booking) return;
    Logger::logInfo("Booking #" + std::to_string(booking->getBookingId()) +
                    " confirmed successfully.");
}
