#pragma once
#include "User.hpp"
#include "Booking.hpp"
#include <vector>
#include <memory>

class Customer : public User {
private:
    std::vector<std::weak_ptr<Booking>> bookings;
protected:
    int totalBookingsCount;
    double totalSpent;
public:
    Customer(const std::string& name, const std::string& email, 
             const std::string& password, const std::string& birthDate);
    std::string getUserRole() const override;
    virtual void addBooking(const std::weak_ptr<Booking>& booking);
    virtual void cancelBooking(int bookingId);
    const std::vector<std::weak_ptr<Booking>>& getBookings() const noexcept;
    size_t getBookingsCount() const noexcept;
    virtual double getTotalSpent() const noexcept;
    virtual std::string getCustomerInfo() const noexcept;
    int getMembershipDuration() const noexcept;
    virtual bool hasActiveBookings() const noexcept;
};