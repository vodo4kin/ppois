#include "Customer.hpp"
#include "Booking.hpp"
#include "utils/Utils.hpp"
#include "configs/PersonsConfig.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include <algorithm>

Customer::Customer(const std::string& name, const std::string& email, 
                   const std::string& password, const std::string& birthDate)
    : User(name, email, password, birthDate), totalBookingsCount(0), totalSpent(0.0) {}

std::string Customer::getUserRole() const {
    return "Customer";
}

void Customer::addBooking(const std::weak_ptr<Booking>& booking) {
    auto sharedBooking = booking.lock();
    if (!sharedBooking) {
        throw InvalidDataException("booking", "cannot be null or expired");
    }
    bookings.push_back(booking);
    totalBookingsCount++;
    totalSpent += sharedBooking->getTotalPrice();
}

void Customer::cancelBooking(int bookingId) {
    auto it = std::find_if(bookings.begin(), bookings.end(), 
        [bookingId](const std::weak_ptr<Booking>& booking) {
            if (auto b = booking.lock()) {
                return b->getBookingId() == bookingId;
            }
            return false;
        });
    if (it != bookings.end()) {
        if (auto booking = it->lock()) {
            totalSpent -= booking->getTotalPrice();
        }
        bookings.erase(it);
    } 
    else {
        throw InvalidDataException("booking", "with ID " + std::to_string(bookingId) + " not found");
    }
}

const std::vector<std::weak_ptr<Booking>>& Customer::getBookings() const noexcept {
    return bookings;
}

size_t Customer::getBookingsCount() const noexcept {
    return bookings.size();
}

double Customer::getTotalSpent() const noexcept {
    return totalSpent;
}

std::string Customer::getCustomerInfo() const noexcept {
    std::string info = User::getInfo();
    info += "\n--- Customer Information ---\n";
    info += "Role: " + getUserRole() + "\n";
    info += "Total bookings: " + std::to_string(getBookingsCount()) + "\n";
    info += "Total spent: $" + std::to_string(totalSpent) + "\n";
    info += "Member since: " + getRegistrationDate() + "\n";
    info += "Membership duration: " + std::to_string(getMembershipDuration()) + " years\n";
    info += "Active bookings: " + std::string(hasActiveBookings() ? "Yes" : "No");
    return info;
}

int Customer::getMembershipDuration() const noexcept {
    return DateUtils::calculateAge(getRegistrationDate());
}

bool Customer::hasActiveBookings() const noexcept {
    return std::any_of(bookings.begin(), bookings.end(), 
        [](const std::weak_ptr<Booking>& booking) {
            if (auto b = booking.lock()) {
                return b->isActive();
            }
            return false;
        });
}