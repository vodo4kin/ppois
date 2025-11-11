#pragma once
#include <string>

class Transport {
public:
    enum class Type {
        FLIGHT,
        TRAIN,
        BUS,
        SHIP,
        TAXI
    };
private:
    std::string company;
    std::string departure;
    std::string arrival;
    std::string departureTime;
    std::string arrivalTime;
    double price;
    Type transportType;
public:
    Transport(const std::string& company,
              const std::string& departure,
              const std::string& arrival,
              const std::string& departureTime,
              const std::string& arrivalTime,
              double price,
              Type type);
    int getTransportId() const;
    std::string getCompany() const;
    std::string getDeparture() const;
    std::string getArrival() const;
    std::string getDepartureTime() const;
    std::string getArrivalTime() const;
    double getPrice() const;
    Type getTransportType() const;
    std::string getTransportTypeStr() const;
    std::string getTransportInfo() const;
};
