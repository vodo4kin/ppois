#include "Booking.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include <atomic>
#include "configs/BookingConfig.hpp"

static std::atomic<int> nextBookingId{1};

Booking::Booking(std::shared_ptr<Customer> customer,
                 std::shared_ptr<Tour> tour,
                 std::shared_ptr<Transport> transport,
                 const std::string& bookingDate,
                 double price)
    : customer(customer), tour(tour), transport(transport),
      bookingDate(bookingDate), status(Status::PENDING), totalPrice(price) {
    if (!customer || !tour || !transport) {
        throw InvalidBookingException("Booking must have valid customer, tour, and transport");
    }
    if (!StringValidation::isValidDate(bookingDate)) {
        throw InvalidDateException("Invalid booking date format");
    }
    if (price < BookingConfig::Booking::MIN_PRICE || price > BookingConfig::Booking::MAX_PRICE) throw InvalidDataException("price", "must be in range \"" + std::to_string(BookingConfig::Booking::MIN_PRICE) 
    + " - " + std::to_string(BookingConfig::Booking::MAX_PRICE) + "\".");
    nextBookingId++;
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

double Booking::getTotalPrice() const {
    return totalPrice;
}

bool Booking::isActive() const {
    return status == Status::CONFIRMED;
}

void Booking::confirm() {
    status = Status::CONFIRMED;
}

void Booking::cancel() {
    status = Status::CANCELLED;
}

void Booking::setStatus(Status newStatus) {
    status = newStatus;
}

std::string Booking::getBookingInfo() const {
    return "Booking ID: " + std::to_string(nextBookingId - 1) + "\n"
         + "Customer: " + (customer ? customer->getName() : "Unknown") + "\n"
         + "Tour: " + (tour ? tour->getTitle() : "Unknown") + "\n"
         + "Transport: " + (transport ? transport->getTransportTypeStr() : "Unknown") + "\n"
         + "Date: " + bookingDate + "\n"
         + "Status: " + getStatusStr() + "\n"
         + "Total Price: $" + std::to_string(static_cast<int>(totalPrice));
}
