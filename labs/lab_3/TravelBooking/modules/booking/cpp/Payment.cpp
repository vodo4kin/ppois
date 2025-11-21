#include "Payment.hpp"
#include "utils/Utils.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/BookingConfig.hpp"
#include <atomic>

static std::atomic<int> nextPaymentId{1};

Payment::Payment(const std::string& payerName,
                 const std::string& paymentDate,
                 double amount,
                 Method method)
    : payerName(payerName), paymentDate(paymentDate),
      amount(amount), method(method), success(false) {
    if (payerName.empty() || payerName.length() > BookingConfig::Payment::MAX_PAYER_NAME) 
    throw InvalidDataException("payerName", "cannot be empty or longer than " 
        + std::to_string(BookingConfig::Payment::MAX_PAYER_NAME));
    if (!StringValidation::isValidDate(paymentDate)) throw InvalidDateException("paymentDate");
    if (amount < BookingConfig::Payment::MIN_AMOUNT || amount > BookingConfig::Payment::MAX_AMOUNT) throw PaymentProcessingException("Amount must be in range \"" + std::to_string(BookingConfig::Payment::MIN_AMOUNT) 
        + " - " + std::to_string(BookingConfig::Payment::MAX_AMOUNT) + "\".");
    nextPaymentId++;
}

int Payment::getPaymentId() const {
    return nextPaymentId;
}

std::string Payment::getPayerName() const {
    return payerName;
}

std::string Payment::getPaymentDate() const {
    return paymentDate;
}

double Payment::getAmount() const {
    return amount;
}

Payment::Method Payment::getMethod() const {
    return method;
}

std::string Payment::getMethodStr() const {
    switch (method) {
        case Method::CARD: return "Card";
        case Method::PAYPAL: return "PayPal";
        case Method::BANK_TRANSFER: return "Bank Transfer";
        case Method::CASH: return "Cash";
        default: return "Unknown";
    }
}

bool Payment::isSuccessful() const {
    return success;
}

void Payment::markSuccess() {
    success = true;
}

void Payment::markFailed() {
    success = false;
}

std::string Payment::getPaymentInfo() const {
    return "Payment ID: " + std::to_string(nextPaymentId - 1) + "\n"
         + "Payer: " + payerName + "\n"
         + "Date: " + paymentDate + "\n"
         + "Amount: $" + std::to_string(static_cast<int>(amount)) + "\n"
         + "Method: " + getMethodStr() + "\n"
         + "Status: " + (success ? "Success" : "Failed");
}
