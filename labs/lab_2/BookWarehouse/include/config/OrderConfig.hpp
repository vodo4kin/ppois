/**
 * @file OrderConfig.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Configuration file with all constants for the Orders module
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once

#include <cstddef>

namespace OrderConfig {
    namespace OrderItem {
        static constexpr int MAX_QUANTITY = 1000;                 ///< Maximum quantity per order item
        static constexpr double MAX_UNIT_PRICE = 10000.0;         ///< Maximum unit price
        static constexpr double MAX_DISCOUNT_PERCENTAGE = 100.0;  ///< Maximum discount percentage
    }

    namespace ShippingInfo {
        static constexpr double MAX_SHIPPING_COST = 10000.0;     ///< Maximum shipping cost
        static constexpr double MAX_INSURANCE_COST = 5000.0;     ///< Maximum insurance cost
        static constexpr double SIGNATURE_THRESHOLD = 100.0;     ///< Insurance threshold requiring signature
    }

    namespace CustomerOrder {
        static constexpr double FREE_SHIPPING_THRESHOLD = 100.0; ///< Order amount for free shipping
        static constexpr double MAX_CUSTOMER_DISCOUNT = 50.0;    ///< Maximum customer-specific discount
        static constexpr double MAX_TAX_RATIO = 0.5;             ///< Maximum tax as ratio of order amount
    }

    namespace OrderManager {
        static constexpr int START_CUSTOMER_ORDER_ID = 1000;     ///< Starting customer order ID
        static constexpr int START_PURCHASE_ORDER_ID = 5000;     ///< Starting purchase order ID
    }

    namespace Order {
        static constexpr size_t MAX_ORDER_ID_LENGTH = 20;        ///< Maximum order ID length
        static constexpr size_t MAX_NOTES_LENGTH = 500;          ///< Maximum notes length
    }

    namespace PurchaseOrder {
        static constexpr size_t MAX_SUPPLIER_NAME_LENGTH = 100;  ///< Maximum supplier name length
        static constexpr size_t MAX_SUPPLIER_CONTACT_LENGTH = 100; ///< Maximum supplier contact length
    }
}