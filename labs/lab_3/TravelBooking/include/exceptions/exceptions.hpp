#pragma once

#include <stdexcept>
#include <string>

class InvalidInputFormatException : public std::runtime_error {
public:
    explicit InvalidInputFormatException(const std::string& message = "Invalid input format provided.")
        : std::runtime_error(message) {}
};

class NotFoundException : public std::runtime_error {
public:
    explicit NotFoundException(const std::string& message = "Entity not found.")
        : std::runtime_error(message) {}
};

class PermissionDeniedException : public std::runtime_error {
public:
    explicit PermissionDeniedException(const std::string& message = "Permission denied for this operation.")
        : std::runtime_error(message) {}
};

class ResourceUnavailableException : public std::runtime_error {
public:
    explicit ResourceUnavailableException(const std::string& message = "Requested resource is unavailable.")
        : std::runtime_error(message) {}
};

class InvalidCredentialsException : public std::runtime_error {
public:
    explicit InvalidCredentialsException(const std::string& message = "Invalid username or password.")
        : std::runtime_error(message) {}
};

class AlreadyExistsException : public std::runtime_error {
public:
    explicit AlreadyExistsException(const std::string& message = "Entity with this identifier already exists.")
        : std::runtime_error(message) {}
};

class PaymentFailedException : public std::runtime_error {
public:
    explicit PaymentFailedException(const std::string& message = "Payment processing failed.")
        : std::runtime_error(message) {}
};

class InvalidStateException : public std::runtime_error {
public:
    explicit InvalidStateException(const std::string& message = "Operation cannot be performed in the current state.")
        : std::runtime_error(message) {}
};

class LimitExceededException : public std::runtime_error {
public:
    explicit LimitExceededException(const std::string& message = "Operation limit exceeded.")
        : std::runtime_error(message) {}
};

class ExternalServiceException : public std::runtime_error {
public:
    explicit ExternalServiceException(const std::string& message = "Failed to connect to external service.")
        : std::runtime_error(message) {}
};

class InvalidDateRangeException : public std::runtime_error {
public:
    explicit InvalidDateRangeException(const std::string& message = "Invalid date or date range provided.")
        : std::runtime_error(message) {}
};

class InternalLogicError : public std::logic_error {
public:
    explicit InternalLogicError(const std::string& message = "An internal logic error occurred.")
        : std::logic_error(message) {}
};