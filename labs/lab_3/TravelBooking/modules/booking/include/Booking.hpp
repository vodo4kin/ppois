#pragma once
#include <string>
#include <memory>
#include "Customer.hpp"
#include "Tour.hpp"
#include "Transport.hpp"

class Booking {
public:
    enum class Status {
        PENDING,
        CONFIRMED,
        CANCELLED
    };
private:
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Tour> tour;
    std::shared_ptr<Transport> transport;
    std::string bookingDate;
    Status status;
    double totalPrice;
    void updateTotalPrice();
public:
    Booking(std::shared_ptr<Customer> customer,
                 std::shared_ptr<Tour> tour,
                 std::shared_ptr<Transport> transport);
    int getBookingId() const;
    std::string getBookingDate() const;
    Status getStatus() const;
    std::string getStatusStr() const;
    double getTotalPrice();
    bool isActive() const;
    void confirm();
    void cancel();
    void setStatus(Status newStatus);
    std::string getBookingInfo();
};
