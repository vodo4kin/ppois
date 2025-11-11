#include "Invoice.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include <atomic>

std::atomic<int> nextInvoiceId{1};

Invoice::Invoice(std::shared_ptr<Booking> booking,
                 std::shared_ptr<Payment> payment,
                 const std::string& issueDate)
    : booking(booking), payment(payment), issueDate(issueDate), isPaid(false) {
    if (!booking || !payment) {
        throw InvalidDataException("invoice", "booking and payment must be valid");
    }
    if (!StringValidation::isValidDate(issueDate)) {
        throw InvalidDateException("issueDate");
    }
    nextInvoiceId++;
}

int Invoice::getInvoiceId() const {
    return nextInvoiceId - 1;
}

std::string Invoice::getIssueDate() const {
    return issueDate;
}

bool Invoice::getIsPaid() const {
    return isPaid;
}

void Invoice::markPaid() {
    isPaid = true;
    payment->markSuccess();
}

void Invoice::markUnpaid() {
    isPaid = false;
    payment->markFailed();
}

std::string Invoice::getInvoiceInfo() const {
    return "Invoice ID: " + std::to_string(nextInvoiceId - 1) + "\n"
         + "Booking ID: " + std::to_string(booking->getBookingId()) + "\n"
         + "Payment ID: " + std::to_string(payment->getPaymentId()) + "\n"
         + "Issue Date: " + issueDate + "\n"
         + "Paid: " + (isPaid ? "Yes" : "No");
}
