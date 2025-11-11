#pragma once
#include <string>

class Payment {
public:
    enum class Method {
        CARD,
        PAYPAL,
        BANK_TRANSFER,
        CASH
    };
private:
    std::string payerName;
    std::string paymentDate;
    double amount;
    Method method;
    bool success;
public:
    Payment(const std::string& payerName,
            const std::string& paymentDate,
            double amount,
            Method method);
    int getPaymentId() const;
    std::string getPayerName() const;
    std::string getPaymentDate() const;
    double getAmount() const;
    Method getMethod() const;
    std::string getMethodStr() const;
    bool isSuccessful() const;
    void markSuccess();
    void markFailed();
    std::string getPaymentInfo() const;
};
