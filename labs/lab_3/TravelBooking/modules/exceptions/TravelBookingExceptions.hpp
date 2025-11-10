#pragma once
#include <string>
#include <exception>

class TravelBookingException : public std::exception {
protected:
    std::string message;
public:
    explicit TravelBookingException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class AuthenticationFailedException : public TravelBookingException {
public:
    explicit AuthenticationFailedException(const std::string& email) 
        : TravelBookingException("Authentication Failed: " + email + " - invalid credentials or account locked") {}
};

class UnderageException : public TravelBookingException {
public:
    explicit UnderageException(int actualAge, int requiredAge) 
        : TravelBookingException("Underage Restriction: User is " + std::to_string(actualAge) + 
                               " years old, but must be at least " + std::to_string(requiredAge) + 
                               " years old to use this service") {}
};

class AccommodationUnavailableException : public TravelBookingException {
public:
    explicit AccommodationUnavailableException(const std::string& accommodation, const std::string& dates) 
        : TravelBookingException("Accommodation Unavailable: " + accommodation + " for dates: " + dates + " - please select different dates or property") {}
};

class BookingConflictException : public TravelBookingException {
public:
    explicit BookingConflictException(const std::string& user, const std::string& tour) 
        : TravelBookingException("Booking Conflict: User " + user + " already has active booking for tour '" + tour + "' - duplicate bookings not allowed") {}
};

class TourCapacityExceededException : public TravelBookingException {
public:
    explicit TourCapacityExceededException(const std::string& tourName, int requested, int available) 
        : TravelBookingException("Tour Capacity Exceeded: " + tourName + " - Requested: " + std::to_string(requested) + ", Available: " + std::to_string(available)) {}
};

class TransportationSchedulingException : public TravelBookingException {
public:
    explicit TransportationSchedulingException(const std::string& transport, const std::string& reason) 
        : TravelBookingException("Transportation Scheduling Failed: " + transport + " - " + reason + " - no available routes for selected dates") {}
};

class PaymentProcessingException : public TravelBookingException {
public:
    explicit PaymentProcessingException(const std::string& details, const std::string& code = "") 
        : TravelBookingException("Payment Processing Failed: " + details + (code.empty() ? "" : " (Error: " + code + ")") + " - please verify payment details") {}
};

class InvalidDateRangeException : public TravelBookingException {
public:
    explicit InvalidDateRangeException(const std::string& startDate, const std::string& endDate) 
        : TravelBookingException("Invalid Date Range: " + startDate + " to " + endDate + " - end date must be after start date") {}
};

class InsufficientPermissionsException : public TravelBookingException {
public:
    explicit InsufficientPermissionsException(const std::string& action, const std::string& requiredRole) 
        : TravelBookingException("Insufficient Permissions: '" + action + "' - required role: " + requiredRole) {}
};

class SystemOverloadException : public TravelBookingException {
public:
    explicit SystemOverloadException(int concurrentUsers, const std::string& module = "") 
        : TravelBookingException("System Overload: Concurrent users: " + std::to_string(concurrentUsers) + (module.empty() ? "" : " in module: " + module) + " - please try again later") {}
};

class ResourceNotFoundException : public TravelBookingException {
public:
    explicit ResourceNotFoundException(const std::string& resourceType, const std::string& identifier) 
        : TravelBookingException("Resource Not Found: " + resourceType + " with identifier: '" + identifier + "' - please verify the reference") {}
};

class OperationTimeoutException : public TravelBookingException {
public:
    explicit OperationTimeoutException(const std::string& operation, int timeoutSeconds) 
        : TravelBookingException("Operation Timeout: '" + operation + "' timed out after " + std::to_string(timeoutSeconds) + " seconds - please retry") {}
};

class InvalidDataException : public TravelBookingException {
public:
    explicit InvalidDataException(const std::string& field, const std::string& validationRule) 
        : TravelBookingException("Invalid Data: Field '" + field + "' - " + validationRule + " - please correct and resubmit") {}
};