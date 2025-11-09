/**
 * @file WarehouseExceptions.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with exception classes for warehouse management system
 * @version 0.1
 * @date 2025-10-12
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class WarehouseException
 * @brief Base exception class for warehouse management system
 * 
 * Provides common functionality for all warehouse-related exceptions
 * with formatted error messages and std::exception compatibility.
 */
class WarehouseException : public std::exception {
protected:
    std::string message;                                      ///< Formatted error message

public:
    /**
     * @brief Construct a new WarehouseException object
     * 
     * @param msg Basic error message without formatting
     */
    explicit WarehouseException(const std::string& msg) : message(msg) {}
    
    /**
     * @brief Get error message as C-style string
     * 
     * @return const char* Formatted error message
     */
    const char* what() const noexcept override { return message.c_str(); }
};

/**
 * @class InsufficientStockException
 * @brief Exception for insufficient stock situations
 * 
 * Thrown when requested quantity exceeds available stock
 */
class InsufficientStockException : public WarehouseException {
public:
    /**
     * @brief Construct a new InsufficientStockException object
     * 
     * @param msg Detailed description of stock shortage
     */
    explicit InsufficientStockException(const std::string& msg) 
        : WarehouseException("Insufficient Stock: " + msg) {}
};

/**
 * @class BookNotFoundException
 * @brief Exception for missing books in catalog
 * 
 * Thrown when searching for non-existent book in warehouse catalog
 */
class BookNotFoundException : public WarehouseException {
public:
    /**
     * @brief Construct a new BookNotFoundException object
     * 
     * @param msg ISBN or title of missing book
     */
    explicit BookNotFoundException(const std::string& msg) 
        : WarehouseException("Book Not Found: " + msg) {}
};

/**
 * @class InvalidISBNException
 * @brief Exception for invalid ISBN format
 * 
 * Thrown when ISBN validation fails due to format or checksum errors
 */
class InvalidISBNException : public WarehouseException {
public:
    /**
     * @brief Construct a new InvalidISBNException object
     * 
     * @param msg Invalid ISBN that failed validation
     */
    explicit InvalidISBNException(const std::string& msg) 
        : WarehouseException("Invalid ISBN: " + msg) {}
};

/**
 * @class OrderProcessingException
 * @brief Exception for order processing failures
 * 
 * Thrown during order processing pipeline when critical errors occur
 */
class OrderProcessingException : public WarehouseException {
public:
    /**
     * @brief Construct a new OrderProcessingException object
     * 
     * @param msg Description of order processing failure
     */
    explicit OrderProcessingException(const std::string& msg) 
        : WarehouseException("Order Processing Error: " + msg) {}
};

/**
 * @class PaymentProcessingException
 * @brief Exception for payment processing failures
 * 
 * Thrown when payment gateway errors or invalid payment data detected
 */
class PaymentProcessingException : public WarehouseException {
public:
    /**
     * @brief Construct a new PaymentProcessingException object
     * 
     * @param msg Description of payment processing failure
     */
    explicit PaymentProcessingException(const std::string& msg) 
        : WarehouseException("Payment Processing Error: " + msg) {}
};

/**
 * @class AuthenticationException
 * @brief Exception for user authentication failures
 * 
 * Thrown when user credentials are invalid or authentication service unavailable
 */
class AuthenticationException : public WarehouseException {
public:
    /**
     * @brief Construct a new AuthenticationException object
     * 
     * @param msg Description of authentication failure
     */
    explicit AuthenticationException(const std::string& msg) 
        : WarehouseException("Authentication Failed: " + msg) {}
};

/**
 * @class AuthorizationException
 * @brief Exception for authorization failures
 * 
 * Thrown when user lacks permissions for requested operation
 */
class AuthorizationException : public WarehouseException {
public:
    /**
     * @brief Construct a new AuthorizationException object
     * 
     * @param msg Description of authorization failure
     */
    explicit AuthorizationException(const std::string& msg) 
        : WarehouseException("Authorization Denied: " + msg) {}
};

/**
 * @class DuplicateBookException
 * @brief Exception for duplicate book entries
 * 
 * Thrown when attempting to add book with existing ISBN to catalog
 */
class DuplicateBookException : public WarehouseException {
public:
    /**
     * @brief Construct a new DuplicateBookException object
     * 
     * @param msg ISBN of duplicated book
     */
    explicit DuplicateBookException(const std::string& msg) 
        : WarehouseException("Duplicate Book: " + msg) {}
};

/**
 * @class InvalidOrderStateException
 * @brief Exception for invalid order state transitions
 * 
 * Thrown when order operation conflicts with current order state
 */
class InvalidOrderStateException : public WarehouseException {
public:
    /**
     * @brief Construct a new InvalidOrderStateException object
     * 
     * @param msg Description of state transition error
     */
    explicit InvalidOrderStateException(const std::string& msg) 
        : WarehouseException("Invalid Order State: " + msg) {}
};

/**
 * @class ShippingException
 * @brief Exception for shipping and delivery failures
 * 
 * Thrown when shipping service errors or delivery constraints violated
 */
class ShippingException : public WarehouseException {
public:
    /**
     * @brief Construct a new ShippingException object
     * 
     * @param msg Description of shipping failure
     */
    explicit ShippingException(const std::string& msg) 
        : WarehouseException("Shipping Error: " + msg) {}
};

/**
 * @class ReportGenerationException
 * @brief Exception for report generation failures
 * 
 * Thrown when warehouse reports cannot be generated due to data or system errors
 */
class ReportGenerationException : public WarehouseException {
public:
    /**
     * @brief Construct a new ReportGenerationException object
     * 
     * @param msg Description of report generation failure
     */
    explicit ReportGenerationException(const std::string& msg) 
        : WarehouseException("Report Generation Failed: " + msg) {}
};

/**
 * @class DataValidationException
 * @brief Exception for data validation failures
 * 
 * Thrown when business logic validation fails for warehouse data
 */
class DataValidationException : public WarehouseException {
public:
    /**
     * @brief Construct a new DataValidationException object
     * 
     * @param msg Description of validation rule violation
     */
    explicit DataValidationException(const std::string& msg) 
        : WarehouseException("Data Validation Error: " + msg) {}
};