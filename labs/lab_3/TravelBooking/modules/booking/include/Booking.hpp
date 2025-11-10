#pragma once
#include <string>
#include <memory>
#include <vector>

class Customer;

class Booking {
public:
    enum class Status {
        PENDING,
        CONFIRMED,
        CANCELLED,
        COMPLETED
    };
    enum class PaymentStatus {
        PENDING,
        PAID,
        REFUNDED,
        FAILED
    };
private:
    int bookingId;
    std::weak_ptr<Customer> customer;
    std::string destination;
    std::string travelDates; // "2024-01-01 to 2024-01-10"
    double totalPrice;
    Status status;
    PaymentStatus paymentStatus;
    std::string bookingDate;
    std::vector<std::string> services; // ["Flight", "Hotel", "Tour"]
    int travelersCount;
    std::string specialRequests;
    static std::atomic<int> nextBookingId;
public:
    Booking(std::shared_ptr<Customer> customer, 
            const std::string& destination,
            const std::string& travelDates,
            double totalPrice,
            int travelersCount = 1);
    int getBookingId() const noexcept;
    std::string getCustomerName() const noexcept;
    std::string getDestination() const noexcept;
    std::string getTravelDates() const noexcept;
    double getTotalPrice() const noexcept;
    Status getStatus() const noexcept;
    PaymentStatus getPaymentStatus() const noexcept;
    std::string getBookingDate() const noexcept;
    std::vector<std::string> getServices() const noexcept;
    int getTravelersCount() const noexcept;
    std::string getSpecialRequests() const noexcept;
    std::string getStatusString() const noexcept;
    std::string getPaymentStatusString() const noexcept;
    bool isActive() const noexcept;
    bool isConfirmed() const noexcept;
    bool isCancelled() const noexcept;
    void setStatus(Status newStatus);
    void setPaymentStatus(PaymentStatus newStatus);
    void addService(const std::string& service);
    void removeService(const std::string& service);
    void setSpecialRequests(const std::string& requests);
    void updateTravelersCount(int count);
    void applyDiscount(double discount);
    double calculateRefundAmount() const;
    bool canBeCancelled() const;
    bool canBeModified() const;
    int getBookingDuration() const; // in days
    std::string getBookingInfo() const noexcept;
    std::string getBriefInfo() const noexcept;
    ~Booking() = default;
};