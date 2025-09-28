#include <string>

class WarehouseException : public std::exception {
protected:
    std::string message;
public:
    explicit WarehouseException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// 12 персональных исключений
class InsufficientStockException : public WarehouseException {
public:
    explicit InsufficientStockException(const std::string& msg) 
        : WarehouseException("Insufficient Stock: " + msg) {}
};

class BookNotFoundException : public WarehouseException {
public:
    explicit BookNotFoundException(const std::string& msg) 
        : WarehouseException("Book Not Found: " + msg) {}
};

class InvalidISBNException : public WarehouseException {
public:
    explicit InvalidISBNException(const std::string& msg) 
        : WarehouseException("Invalid ISBN: " + msg) {}
};

class OrderProcessingException : public WarehouseException {
public:
    explicit OrderProcessingException(const std::string& msg) 
        : WarehouseException("Order Processing Error: " + msg) {}
};

class PaymentProcessingException : public WarehouseException {
public:
    explicit PaymentProcessingException(const std::string& msg) 
        : WarehouseException("Payment Processing Error: " + msg) {}
};

class AuthenticationException : public WarehouseException {
public:
    explicit AuthenticationException(const std::string& msg) 
        : WarehouseException("Authentication Failed: " + msg) {}
};

class AuthorizationException : public WarehouseException {
public:
    explicit AuthorizationException(const std::string& msg) 
        : WarehouseException("Authorization Denied: " + msg) {}
};

class DuplicateBookException : public WarehouseException {
public:
    explicit DuplicateBookException(const std::string& msg) 
        : WarehouseException("Duplicate Book: " + msg) {}
};

class InvalidOrderStateException : public WarehouseException {
public:
    explicit InvalidOrderStateException(const std::string& msg) 
        : WarehouseException("Invalid Order State: " + msg) {}
};

class ShippingException : public WarehouseException {
public:
    explicit ShippingException(const std::string& msg) 
        : WarehouseException("Shipping Error: " + msg) {}
};

class ReportGenerationException : public WarehouseException {
public:
    explicit ReportGenerationException(const std::string& msg) 
        : WarehouseException("Report Generation Failed: " + msg) {}
};

class DataValidationException : public WarehouseException {
public:
    explicit DataValidationException(const std::string& msg) 
        : WarehouseException("Data Validation Error: " + msg) {}
};