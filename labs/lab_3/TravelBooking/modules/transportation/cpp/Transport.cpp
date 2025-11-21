#include "Transport.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/TransportConfig.hpp"
#include <atomic>

static std::atomic<int> nextTransportId{1};

Transport::Transport(const std::string& company,
                     const std::string& departure,
                     const std::string& arrival,
                     const std::string& departureTime,
                     const std::string& arrivalTime,
                     double price,
                     Type type)
    : company(company), departure(departure), arrival(arrival),
      departureTime(departureTime), arrivalTime(arrivalTime),
      price(price), transportType(type) {
    if (company.empty()) throw InvalidDataException("company", "cannot be empty");
    if (company.length() > TransportConfig::Transport::MAX_COMPANY_NAME_LENGTH) throw InvalidDataException("length company", " cannnot be longer than" 
        + std::to_string(TransportConfig::Transport::MAX_COMPANY_NAME_LENGTH));
    if (departure.empty() || arrival.empty()) throw InvalidDataException("location", "departure and arrival must be specified");
    if (!StringValidation::isValidDate(departureTime)) throw InvalidDateException("departureTime");
    if (!StringValidation::isValidDate(arrivalTime)) throw InvalidDateException("arrivalTime");
    if (price < TransportConfig::Transport::MIN_TRANSPORT_PRICE  || price > TransportConfig::Transport::MAX_TRANSPORT_PRICE) throw InvalidDataException("price", "must be in the range \"" 
        + std::to_string(TransportConfig::Transport::MIN_TRANSPORT_PRICE) + " - " + std::to_string(TransportConfig::Transport::MAX_TRANSPORT_PRICE) + "\".");
    nextTransportId++;
}

int Transport::getTransportId() const {
    return nextTransportId - 1;
}

std::string Transport::getCompany() const {
    return company;
}

std::string Transport::getDeparture() const {
    return departure;
}

std::string Transport::getArrival() const {
    return arrival;
}

std::string Transport::getDepartureTime() const {
    return departureTime;
}

std::string Transport::getArrivalTime() const {
    return arrivalTime;
}

double Transport::getPrice() const {
    return price;
}

Transport::Type Transport::getTransportType() const {
    return transportType;
}

std::string Transport::getTransportTypeStr() const {
    switch (transportType) {
        case Type::FLIGHT: return "Flight";
        case Type::TRAIN: return "Train";
        case Type::BUS: return "Bus";
        case Type::SHIP: return "Ship";
        case Type::TAXI: return "Taxi";
        default: return "Unknown";
    }
}

std::string Transport::getTransportInfo() const {
    return "Transport ID: " + std::to_string(nextTransportId - 1) + "\n"
         + "Company: " + company + "\n"
         + "Type: " + getTransportTypeStr() + "\n"
         + "From: " + departure + " at " + departureTime + "\n"
         + "To: " + arrival + " at " + arrivalTime + "\n"
         + "Price: $" + std::to_string(static_cast<int>(price));
}
