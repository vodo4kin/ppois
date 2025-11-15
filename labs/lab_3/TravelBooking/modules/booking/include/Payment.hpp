/**
 * @file Payment.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Payment class for payment management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class Payment
 * @brief Class representing payment transactions
 * 
 * Manages payment information including payment method, amount, and status.
 * Provides functionality for payment processing and information retrieval.
 */
class Payment {
public:
    /**
     * @enum Method
     * @brief Enumeration of payment methods
     */
    enum class Method {
        CARD,                                               ///< Credit/debit card payment
        PAYPAL,                                             ///< PayPal payment
        BANK_TRANSFER,                                      ///< Bank transfer payment
        CASH                                                ///< Cash payment
    };

private:
    std::string payerName;                                  ///< Name of the payer
    std::string paymentDate;                                ///< Date of payment
    double amount;                                          ///< Payment amount
    Method method;                                          ///< Payment method used
    bool success;                                           ///< Payment success status

public:
    /**
     * @brief Construct a new Payment object
     * 
     * @param payerName constant reference to the string containing payer name
     * @param paymentDate constant reference to the string containing payment date
     * @param amount double value containing payment amount
     * @param method Method value containing payment method
     */
    Payment(const std::string& payerName,
            const std::string& paymentDate,
            double amount,
            Method method);
    
    /**
     * @brief Get the payment identifier
     * 
     * @return int containing unique payment identifier
     */
    int getPaymentId() const;
    
    /**
     * @brief Get the payer name
     * 
     * @return std::string containing payer name
     */
    std::string getPayerName() const;
    
    /**
     * @brief Get the payment date
     * 
     * @return std::string containing payment date
     */
    std::string getPaymentDate() const;
    
    /**
     * @brief Get the payment amount
     * 
     * @return double containing payment amount
     */
    double getAmount() const;
    
    /**
     * @brief Get the payment method
     * 
     * @return Method containing payment method enum value
     */
    Method getMethod() const;
    
    /**
     * @brief Get the payment method as string
     * 
     * @return std::string containing payment method description
     */
    std::string getMethodStr() const;
    
    /**
     * @brief Check if payment was successful
     * 
     * @return true if payment successful
     * @return false if payment failed
     */
    bool isSuccessful() const;
    
    /**
     * @brief Mark payment as successful
     */
    void markSuccess();
    
    /**
     * @brief Mark payment as failed
     */
    void markFailed();
    
    /**
     * @brief Get comprehensive payment information
     * 
     * @return std::string containing formatted payment details
     */
    std::string getPaymentInfo() const;
};