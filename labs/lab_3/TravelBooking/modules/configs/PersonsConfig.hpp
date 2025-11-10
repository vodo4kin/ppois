#pragma once
#include <cstddef>

namespace PersonsConfig {
    namespace User {
        static constexpr size_t MAX_NAME_LENGTH = 20;
        static constexpr size_t MIN_PASSWORD_LENGTH = 8;
        static constexpr size_t MIN_PHONE_NUMBER_LENGTH = 7;
        static constexpr size_t MAX_PHONE_NUMBER_LENGTH = 15;
        static constexpr size_t MAX_ADDRESS_LENGTH = 100;
    }
    namespace VipCustomer {
        constexpr double SILVER_THRESHOLD = 0;
        constexpr double GOLD_THRESHOLD = 1000;
        constexpr double PLATINUM_THRESHOLD = 5000;
        constexpr double SILVER_DISCOUNT = 0.05;
        constexpr double GOLD_DISCOUNT = 0.10;
        constexpr double PLATINUM_DISCOUNT = 0.15;
        constexpr double POINTS_EARN_RATE = 0.10;
    }
    namespace Admin {
        constexpr int MAX_DEPARTMENT_LENGTH = 50;
        constexpr int MAX_PERMISSIONS = 10;
    }
}