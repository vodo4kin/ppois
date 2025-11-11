#pragma once
#include <cstddef>

namespace TransportConfig {
    namespace Transport {
        static constexpr size_t MAX_COMPANY_NAME_LENGTH = 40;
        static constexpr double MIN_TRANSPORT_PRICE = 5.0;
        static constexpr double MAX_TRANSPORT_PRICE = 5000.0;
    }
    namespace TransportReview {
        static constexpr int MIN_RATING = 1;
        static constexpr int MAX_RATING = 5;
    }
}
