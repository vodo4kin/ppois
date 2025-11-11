#pragma once
#include <string>
#include <memory>
#include "Transport.hpp"

class TransportSchedule {
private:
    std::shared_ptr<Transport> transport;
    std::string departureDate;
    std::string origin;
    std::string destination;
    int availableSeats;

public:
    TransportSchedule(std::shared_ptr<Transport> transport,
                      const std::string& departureDate,
                      const std::string& origin,
                      const std::string& destination,
                      int availableSeats);
    std::shared_ptr<Transport> getTransport() const;
    std::string getDepartureDate() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    int getAvailableSeats() const;
    void reserveSeats(int count);
    std::string getScheduleInfo() const;
};
