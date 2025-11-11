#include "TransportSchedule.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"

TransportSchedule::TransportSchedule(std::shared_ptr<Transport> transport,
                                     const std::string& departureDate,
                                     const std::string& origin,
                                     const std::string& destination,
                                     int availableSeats)
    : transport(transport), departureDate(departureDate),
      origin(origin), destination(destination), availableSeats(availableSeats) {
    if (!transport) {
        throw TransportationSchedulingException("null", "Transport is not available");
    }
    if (!StringValidation::isValidDate(departureDate)) {
        throw InvalidDateException("departureDate");
    }
    if (origin.empty() || destination.empty()) {
        throw InvalidDataException("origin/destination", "must be non-empty");
    }
    if (availableSeats < 0) {
        throw InvalidDataException("availableSeats", "must be non-negative");
    }
}

std::shared_ptr<Transport> TransportSchedule::getTransport() const {
    return transport;
}

std::string TransportSchedule::getDepartureDate() const {
    return departureDate;
}

std::string TransportSchedule::getOrigin() const {
    return origin;
}

std::string TransportSchedule::getDestination() const {
    return destination;
}

int TransportSchedule::getAvailableSeats() const {
    return availableSeats;
}

void TransportSchedule::reserveSeats(int count) {
    if (count > availableSeats) {
        throw TransportationSchedulingException(
            transport ? transport->getTransportTypeStr() : "unknown",
            "Not enough seats available (" + std::to_string(availableSeats) + " left, requested " + std::to_string(count) + ")"
        );
    }
    availableSeats -= count;
}

std::string TransportSchedule::getScheduleInfo() const {
    return "Transport: " + transport->getTransportTypeStr() + "\n"
         + "From: " + origin + " To: " + destination + "\n"
         + "Departure: " + departureDate + "\n"
         + "Available Seats: " + std::to_string(availableSeats);
}
