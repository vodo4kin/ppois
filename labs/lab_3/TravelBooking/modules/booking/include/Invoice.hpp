#pragma once
#include <string>
#include <memory>
#include "Booking.hpp"
#include "Payment.hpp"

class Invoice {
private:
    std::shared_ptr<Booking> booking;
    std::shared_ptr<Payment> payment;
    std::string issueDate;
    bool isPaid;
public:
    Invoice(std::shared_ptr<Booking> booking,
            std::shared_ptr<Payment> payment,
            const std::string& issueDate);

    int getInvoiceId() const;
    std::string getIssueDate() const;
    bool getIsPaid() const;
    void markPaid();
    void markUnpaid();
    std::string getInvoiceInfo() const;
};
