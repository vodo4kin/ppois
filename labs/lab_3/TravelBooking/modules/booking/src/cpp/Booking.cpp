#include "Booking.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include <atomic>
#include "configs/BookingConfig.hpp"

static std::atomic<int> nextBookingId{1};

void Booking::updateTotalPrice() {
    totalPrice = tour->calculateTotalTourCost() + transport->getPrice();
}

Booking::Booking(std::shared_ptr<Customer> customer,
                 std::shared_ptr<Tour> tour,
                 std::shared_ptr<Transport> transport)
    : customer(customer), tour(tour), transport(transport), status(Status::PENDING) {
    try {
        if (!customer || !tour || !transport) {
            throw InvalidBookingException("Booking must have valid customer, tour, and transport");
        }
        updateTotalPrice();
        bookingDate = DateUtils::getCurrentDate();
        nextBookingId++;
    } catch (const TravelBookingException& e) {
        throw InvalidBookingException("Failed to create booking object: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw InvalidBookingException("Unexpected error during booking creation: " + std::string(e.what()));
    } catch (...) {
        throw InvalidBookingException("Unknown error during booking creation");
    }
}

int Booking::getBookingId() const {
    return nextBookingId - 1;
}

std::string Booking::getBookingDate() const {
    return bookingDate;
}

Booking::Status Booking::getStatus() const {
    return status;
}

std::string Booking::getStatusStr() const {
    if (status == Status::PENDING) return "Pending";
    if (status == Status::CONFIRMED) return "Confirmed";
    if (status == Status::CANCELLED) return "Cancelled";
    return "Unknown";
}

double Booking::getTotalPrice() {
    updateTotalPrice();
    return totalPrice;
}

bool Booking::isActive() const {
    return status == Status::CONFIRMED;
}

void Booking::confirm() {
    updateTotalPrice();
    status = Status::CONFIRMED;
}

void Booking::cancel() {
    updateTotalPrice();
    status = Status::CANCELLED;
}

void Booking::setStatus(Status newStatus) {
    updateTotalPrice();
    status = newStatus;
}

std::string Booking::getBookingInfo() {
    updateTotalPrice();
    return "Booking ID: " + std::to_string(nextBookingId - 1) + "\n"
         + "Customer: " + (customer ? customer->getName() : "Unknown") + "\n"
         + "Tour: " + (tour ? tour->getTitle() : "Unknown") + "\n"
         + "Transport: " + (transport ? transport->getTransportTypeStr() : "Unknown") + "\n"
         + "Date: " + bookingDate + "\n"
         + "Status: " + getStatusStr() + "\n"
         + "Total Price: $" + std::to_string(static_cast<int>(totalPrice));
}
