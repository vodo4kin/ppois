#pragma once
#include <cstddef>

namespace ToursConfig {
    namespace Tour {
        static constexpr size_t MIN_TITLE_LENGTH = 5;
        static constexpr size_t MAX_TITLE_LENGTH = 100;
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 500;
        static constexpr double MIN_TOUR_PRICE = 0.0;
        static constexpr double MAX_TOUR_PRICE = 100000.0;
        static constexpr int MAX_ACCOMMODATIONS_PER_TOUR = 20;
        static constexpr int MAX_MEALS_PER_TOUR = 30;
    }
    
    namespace TourReview {
        static constexpr size_t MAX_REVIEW_LENGTH = 500;
        static constexpr int MIN_RATING = 1;
        static constexpr int MAX_RATING = 5;
    }
}