#pragma once
#include <cstddef>

namespace BookingConfig {
    namespace Booking {
        static constexpr double MIN_PRICE = 50;
        static constexpr double MAX_PRICE = 50000;
    }
    namespace Payment {
        constexpr size_t MAX_PAYER_NAME = 50;
        constexpr int MAX_AMOUNT = 50000;
        constexpr int MIN_AMOUNT = 1;
    }
}