/**
 * @file Invoice.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Invoice class for invoice management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Booking.hpp"
#include "Payment.hpp"

/**
 * @class Invoice
 * @brief Class representing invoice documents
 * 
 * Manages invoice information linking bookings with payments.
 * Provides functionality for invoice status management and information retrieval.
 */
class Invoice {
private:
    std::shared_ptr<Booking> booking;                       ///< Shared pointer to booking object
    std::shared_ptr<Payment> payment;                       ///< Shared pointer to payment object
    std::string issueDate;                                  ///< Invoice issue date
    bool isPaid;                                            ///< Invoice payment status

public:
    /**
     * @brief Construct a new Invoice object
     * 
     * @param booking shared pointer to the Booking object
     * @param payment shared pointer to the Payment object
     * @param issueDate constant reference to the string containing issue date
     */
    Invoice(std::shared_ptr<Booking> booking,
            std::shared_ptr<Payment> payment,
            const std::string& issueDate);

    /**
     * @brief Get the invoice identifier
     * 
     * @return int containing unique invoice identifier
     */
    int getInvoiceId() const;
    
    /**
     * @brief Get the issue date
     * 
     * @return std::string containing invoice issue date
     */
    std::string getIssueDate() const;
    
    /**
     * @brief Get the payment status
     * 
     * @return true if invoice is paid
     * @return false if invoice is unpaid
     */
    bool getIsPaid() const;
    
    /**
     * @brief Mark invoice as paid
     */
    void markPaid();
    
    /**
     * @brief Mark invoice as unpaid
     */
    void markUnpaid();
    
    /**
     * @brief Get comprehensive invoice information
     * 
     * @return std::string containing formatted invoice details
     */
    std::string getInvoiceInfo() const;
};