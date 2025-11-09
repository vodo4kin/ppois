/**
 * @file ShippingInfo.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the ShippingInfo class for working with shipping information
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "Address.hpp"

/**
 * @class ShippingInfo
 * @brief Class for working with shipping information
 * 
 * Manages shipping details including addresses, carrier information,
 * tracking numbers, and shipping costs.
 */
class ShippingInfo {
public:
    /**
     * @enum ShippingMethod
     * @brief Enumeration of shipping methods
     */
    enum class ShippingMethod {
        STANDARD,       ///< Standard ground shipping
        EXPEDITED,      ///< Expedited shipping (2-3 days)
        EXPRESS,        ///< Express shipping (1-2 days)
        OVERNIGHT,      ///< Overnight shipping
        INTERNATIONAL   ///< International shipping
    };

    /**
     * @enum ShippingStatus
     * @brief Enumeration of shipping statuses
     */
    enum class ShippingStatus {
        PENDING,        ///< Shipping not yet processed
        LABEL_CREATED,  ///< Shipping label created
        PICKED_UP,      ///< Package picked up by carrier
        IN_TRANSIT,     ///< Package in transit
        OUT_FOR_DELIVERY, ///< Package out for delivery
        DELIVERED,      ///< Package delivered
        FAILED,         ///< Delivery failed
        RETURNED        ///< Package returned to sender
    };

private:
    std::shared_ptr<Address> shippingAddress;  ///< Destination shipping address
    std::shared_ptr<Address> returnAddress;    ///< Return address
    ShippingMethod method;                     ///< Shipping method
    ShippingStatus status;                     ///< Current shipping status
    std::string trackingNumber;               ///< Carrier tracking number
    std::string carrier;                      ///< Shipping carrier company
    double shippingCost;                      ///< Shipping cost
    double insuranceCost;                     ///< Insurance cost
    std::string estimatedDelivery;            ///< Estimated delivery date
    std::string actualDelivery;               ///< Actual delivery date

    /**
     * @brief Private method to validate tracking number
     * 
     * @param trackingNumber constant reference to the string containing tracking number to validate
     * 
     * @return true if tracking number is valid
     * @return false if tracking number is invalid
     */
    bool isValidTrackingNumber(const std::string& trackingNumber) const;

    /**
     * @brief Private method to validate carrier name
     * 
     * @param carrier constant reference to the string containing carrier to validate
     * 
     * @return true if carrier is valid
     * @return false if carrier is invalid
     */
    bool isValidCarrier(const std::string& carrier) const;

    /**
     * @brief Private method to validate shipping cost
     * 
     * @param cost double value containing shipping cost to validate
     * 
     * @return true if shipping cost is valid
     * @return false if shipping cost is invalid
     */
    bool isValidShippingCost(double cost) const;

    /**
     * @brief Private method to validate insurance cost
     * 
     * @param cost double value containing insurance cost to validate
     * 
     * @return true if insurance cost is valid
     * @return false if insurance cost is invalid
     */
    bool isValidInsuranceCost(double cost) const;

public:
    /**
     * @brief Construct a new ShippingInfo object
     * 
     * @param shippingAddress shared pointer to the shipping Address object
     * @param returnAddress shared pointer to the return Address object
     * @param method ShippingMethod value containing shipping method
     * @param trackingNumber constant reference to the string containing tracking number
     * @param carrier constant reference to the string containing carrier company
     * @param shippingCost double value containing shipping cost
     * @param insuranceCost double value containing insurance cost
     * @param estimatedDelivery constant reference to the string containing estimated delivery date
     */
    ShippingInfo(std::shared_ptr<Address> shippingAddress, std::shared_ptr<Address> returnAddress,
                 ShippingMethod method, const std::string& trackingNumber, const std::string& carrier,
                 double shippingCost, double insuranceCost = 0.0, const std::string& estimatedDelivery = "");

    /**
     * @brief Get the shipping address
     * 
     * @return std::shared_ptr<Address> containing shipping address
     */
    std::shared_ptr<Address> getShippingAddress() const noexcept;

    /**
     * @brief Get the return address
     * 
     * @return std::shared_ptr<Address> containing return address
     */
    std::shared_ptr<Address> getReturnAddress() const noexcept;

    /**
     * @brief Get the shipping method
     * 
     * @return ShippingMethod containing shipping method
     */
    ShippingMethod getMethod() const noexcept;

    /**
     * @brief Get the shipping status
     * 
     * @return ShippingStatus containing shipping status
     */
    ShippingStatus getStatus() const noexcept;

    /**
     * @brief Get the tracking number
     * 
     * @return std::string containing tracking number
     */
    std::string getTrackingNumber() const noexcept;

    /**
     * @brief Get the carrier company
     * 
     * @return std::string containing carrier company
     */
    std::string getCarrier() const noexcept;

    /**
     * @brief Get the shipping cost
     * 
     * @return double containing shipping cost
     */
    double getShippingCost() const noexcept;

    /**
     * @brief Get the insurance cost
     * 
     * @return double containing insurance cost
     */
    double getInsuranceCost() const noexcept;

    /**
     * @brief Get the estimated delivery date
     * 
     * @return std::string containing estimated delivery date
     */
    std::string getEstimatedDelivery() const noexcept;

    /**
     * @brief Get the actual delivery date
     * 
     * @return std::string containing actual delivery date
     */
    std::string getActualDelivery() const noexcept;

    /**
     * @brief Set the shipping status
     * 
     * @param status ShippingStatus value containing new status
     */
    void setStatus(ShippingStatus status) noexcept;

    /**
     * @brief Set the tracking number
     * 
     * @param trackingNumber constant reference to the string containing new tracking number
     */
    void setTrackingNumber(const std::string& trackingNumber);

    /**
     * @brief Set the actual delivery date
     * 
     * @param deliveryDate constant reference to the string containing actual delivery date
     */
    void setActualDelivery(const std::string& deliveryDate);

    /**
     * @brief Calculate total shipping cost (shipping + insurance)
     * 
     * @return double containing total shipping cost
     */
    double getTotalShippingCost() const noexcept;

    /**
     * @brief Check if package is delivered
     * 
     * @return true if package is delivered
     * @return false if package is not delivered
     */
    bool isDelivered() const noexcept;

    /**
     * @brief Check if package is in transit
     * 
     * @return true if package is in transit
     * @return false if package is not in transit
     */
    bool isInTransit() const noexcept;

    /**
     * @brief Check if shipping requires signature
     * 
     * @return true if shipping requires signature
     * @return false if shipping does not require signature
     */
    bool requiresSignature() const noexcept;

    /**
     * @brief Get shipping method as string
     * 
     * @return std::string containing shipping method description
     */
    std::string getMethodString() const noexcept;

    /**
     * @brief Get shipping status as string
     * 
     * @return std::string containing shipping status description
     */
    std::string getStatusString() const noexcept;

    /**
     * @brief Get shipping information
     * 
     * @return std::string containing formatted shipping information
     */
    std::string getInfo() const noexcept;

    /**
     * @brief Equality comparison operator for shipping info
     * 
     * @param other constant reference to the shipping info to compare with
     * 
     * @return true if shipping info are equal
     * @return false if shipping info are not equal
     */
    bool operator==(const ShippingInfo& other) const noexcept;

    /**
     * @brief Inequality comparison operator for shipping info
     * 
     * @param other constant reference to the shipping info to compare with
     * 
     * @return true if shipping info are not equal
     * @return false if shipping info are equal
     */
    bool operator!=(const ShippingInfo& other) const noexcept;
};