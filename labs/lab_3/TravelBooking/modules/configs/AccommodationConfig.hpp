#pragma once
#include <vector>
#include <string>

namespace AccommodationConfig {
    namespace Accommodation {
        static constexpr size_t MAX_NAME_LENGTH = 150;
        static constexpr size_t MAX_LOCATION_LENGTH = 150;
        static constexpr double MIN_PRICE_PER_NIGHT = 0;
        static constexpr double MAX_PRICE_PER_NIGHT = 500;
        static constexpr size_t MIN_CAPACITY = 1;
        static constexpr size_t MAX_CAPACITY = 300;
        static constexpr int MIN_RATING = 1;
        static constexpr int MAX_RATING = 5;
        static constexpr size_t MAX_AMENITY_LENGTH = 30;
        static constexpr size_t MAX_AMENITIES_COUNT = 30;
    }
    namespace Hotel {
        static constexpr int MIN_STARS = 1;
        static constexpr int MAX_STARS = 5;
        static constexpr size_t MAX_ROOMTYPE_LENGTH = 150;
    }
    namespace Apartment {
        static constexpr int MIN_ROOMS = 1;
        static constexpr int MAX_ROOMS = 10;
        static constexpr double MIN_AREA = 20.0;
        static constexpr double MAX_AREA = 500.0;
        static constexpr int SPACIOUS_ROOM_THRESHOLD = 3;
        static constexpr double LARGE_AREA_THRESHOLD = 80.0;
        static constexpr int FAMILY_ROOM_THRESHOLD = 2;
        static constexpr double FAMILY_AREA_THRESHOLD = 60.0;
        static constexpr int STUDIO_ROOM_COUNT = 1;
        static constexpr double STUDIO_AREA_THRESHOLD = 40.0;
        static constexpr double LUXURY_AREA_THRESHOLD = 100.0;
        static constexpr int LUXURY_ROOM_THRESHOLD = 3;
        static constexpr double COMFORT_AREA_THRESHOLD = 60.0;
        static constexpr int COMFORT_ROOM_THRESHOLD = 2;
    }
    namespace Hostel {
        static constexpr int MIN_BEDS = 1;
        static constexpr int MAX_BEDS = 12;
        static constexpr size_t MAX_BATHROOM_TYPE_LENGTH = 20;
        static constexpr int SMALL_DORM_THRESHOLD = 4;
        static constexpr int LARGE_DORM_THRESHOLD = 8;
        static constexpr int MAX_GROUP_MULTIPLIER = 2;
    }
    namespace Villa {
        static constexpr int MIN_FLOORS = 1;
        static constexpr int MAX_FLOORS = 4;
        static constexpr double MIN_VILLA_AREA = 100.0;
        static constexpr double MAX_VILLA_AREA = 2000.0;
        static constexpr int MULTISTORY_THRESHOLD = 2;
        static constexpr int LUXURY_FLOOR_THRESHOLD = 2;
        static constexpr double POOL_SURCHARGE = 50.0;
        static constexpr double GARDEN_SURCHARGE = 30.0;
        static constexpr double FLOOR_SURCHARGE = 20.0;
        static constexpr int MIN_EVENT_CAPACITY = 10;
    }
    namespace GuestHouse {
        static constexpr int MIN_TOTAL_ROOMS = 1;
        static constexpr int MAX_TOTAL_ROOMS = 20;
        static constexpr size_t MAX_HOST_LANGUAGE_LENGTH = 20;
        static constexpr int SMALL_HOUSE_THRESHOLD = 5;
        static constexpr int MEDIUM_HOUSE_THRESHOLD = 10;
        static constexpr int COMMUNITY_MIN_ROOMS = 3;
    }
    namespace Resort {
        static constexpr int MIN_RESTAURANTS = 1;
        static constexpr int MAX_RESTAURANTS = 20;
        static constexpr int MAX_ACTIVITIES_COUNT = 50;
        static constexpr size_t MAX_ACTIVITY_NAME_LENGTH = 30;
        static constexpr int MULTIPLE_RESTAURANTS_THRESHOLD = 3;
        static constexpr int LUXURY_RESTAURANT_THRESHOLD = 5;
        static constexpr int COMPREHENSIVE_RESTAURANT_THRESHOLD = 2;
    }
    namespace MountainLodge {
        static constexpr int MIN_ALTITUDE = 500;
        static constexpr int MAX_ALTITUDE = 5000;
        static constexpr size_t MAX_ACCESSIBILITY_LENGTH = 20;
        static constexpr int HIGH_ALTITUDE_THRESHOLD = 2000;
        static constexpr int COMFORT_ALTITUDE_THRESHOLD = 1000;
    }
    namespace Camping {
        static constexpr size_t MAX_CAMPING_TYPE_LENGTH = 20;
    }
    namespace BoutiqueHotel {
        static constexpr int MIN_YEAR_BUILT = 1800;
        static constexpr size_t MAX_THEME_LENGTH = 50;
        static constexpr size_t MAX_ARCH_STYLE_LENGTH = 30;
        static constexpr int HISTORIC_AGE_THRESHOLD = 50;
        static constexpr int MODERN_YEAR_THRESHOLD = 2000;
    }
    namespace CruiseCabin {
        static constexpr int MIN_DECK_NUMBER = 1;
        static constexpr int MAX_DECK_NUMBER = 20;
        static constexpr size_t MAX_SHIP_NAME_LENGTH = 50;
        static constexpr size_t MAX_CABIN_TYPE_LENGTH = 20;
        static constexpr int UPPER_DECK_THRESHOLD = 10;
    }
}