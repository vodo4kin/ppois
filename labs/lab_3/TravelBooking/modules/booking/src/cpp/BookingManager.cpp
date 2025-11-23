#include "BookingManager.hpp"
#include "exceptions/TravelBookingExceptions.hpp"

void BookingManager::addBooking(const std::shared_ptr<Booking>& booking) {
    try {
        if (!booking) throw InvalidDataException("booking", "cannot be null");
        bookings.push_back(booking);
    } catch (const TravelBookingException& e) {
        throw InvalidDataException("BookingManager", "Failed to add booking: " + std::string(e.what()));
    }
}

bool BookingManager::cancelBooking(int bookingId) {
    try {
        for (auto& booking : bookings) {
            if (booking->getBookingId() == bookingId) {
                booking->cancel();
                return true;
            }
        }
        throw ResourceNotFoundException("Booking", std::to_string(bookingId));
    } catch (const TravelBookingException& e) {
        throw InvalidDataException("BookingManager", "Failed to cancel booking: " + std::string(e.what()));
    }
}

std::shared_ptr<Booking> BookingManager::findBookingById(int bookingId) const {
    for (const auto& booking : bookings) {
        if (booking->getBookingId() == bookingId) {
            return booking;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Booking>> BookingManager::getActiveBookings() const {
    std::vector<std::shared_ptr<Booking>> active;
    for (const auto& booking : bookings) {
        if (booking->isActive()) {
            active.push_back(booking);
        }
    }
    return active;
}

double BookingManager::calculateTotalRevenue() const {
    double total = 0.0;
    for (const auto& booking : bookings) {
        total += booking->getTotalPrice();
    }
    return total;
}

int BookingManager::countBookingsByStatus(Booking::Status status) const {
    int count = 0;
    for (const auto& booking : bookings) {
        if (booking->getStatus() == status) {
            count++;
        }
    }
    return count;
}

std::string BookingManager::getSummary() const {
    return "Total bookings: " + std::to_string(bookings.size()) + "\n"
         + "Confirmed: " + std::to_string(countBookingsByStatus(Booking::Status::CONFIRMED)) + "\n"
         + "Cancelled: " + std::to_string(countBookingsByStatus(Booking::Status::CANCELLED)) + "\n"
         + "Pending: " + std::to_string(countBookingsByStatus(Booking::Status::PENDING)) + "\n"
         + "Revenue: $" + std::to_string(static_cast<int>(calculateTotalRevenue()));
}
