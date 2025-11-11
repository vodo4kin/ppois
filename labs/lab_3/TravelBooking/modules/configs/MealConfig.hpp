#pragma once
#include <cstddef>

namespace MealConfig {
    namespace Meal {
        static constexpr size_t MAX_NAME_LENGTH = 100;
        static constexpr size_t MAX_DESCRIPTION_LENGTH = 300;
        static constexpr double MIN_PRICE = 0.0;
        static constexpr double MAX_PRICE = 500.0;
        static constexpr int MIN_CALORIES = 0;
        static constexpr int MAX_CALORIES = 3000;
        static constexpr size_t MAX_TAG_LENGTH = 30;
        static constexpr size_t MAX_TAGS_COUNT = 10;
        static constexpr double MAX_PRICE_PER_CALORIE = 0.1;
    }
    namespace Breakfast {
        static constexpr int MIN_CALORIES = 300;
        static constexpr int MAX_CALORIES = 800;
        static constexpr size_t MAX_CUISINE_STYLES = 10;
        static constexpr size_t MAX_CUISINE_NAME_LENGTH = 20;
        static constexpr int INTERNATIONAL_CUISINE_THRESHOLD = 3;
    }
    namespace Lunch {
        static constexpr int MIN_CALORIES = 400;
        static constexpr int MAX_CALORIES = 1000;
        static constexpr int MIN_COURSES = 1;
        static constexpr int MAX_COURSES = 5;
        static constexpr size_t MAX_RESTAURANT_TYPE_LENGTH = 30;
        static constexpr int FULL_COURSE_THRESHOLD = 3;
        static constexpr int BUSINESS_COURSE_COUNT = 2;
    }
    namespace Dinner {
        static constexpr int MIN_CALORIES = 500;
        static constexpr int MAX_CALORIES = 1200;
        static constexpr size_t MAX_MENU_ITEMS = 10;
        static constexpr size_t MAX_MENU_ITEM_LENGTH = 50;
        static constexpr size_t MAX_AMBIANCE_LENGTH = 20;
        static constexpr int FINE_DINING_COURSE_THRESHOLD = 4;
        static constexpr int MULTI_COURSE_THRESHOLD = 2;
    }
    namespace AllInclusive {
        static constexpr int MIN_MEALS_PER_DAY = 1;
        static constexpr int MAX_MEALS_PER_DAY = 6;
        static constexpr size_t MAX_RESTAURANTS = 15;
        static constexpr int PREMIUM_MEAL_THRESHOLD = 4;
        static constexpr int UNLIMITED_MEAL_THRESHOLD = 5;
    }
    namespace Picnic {
        static constexpr int MIN_CALORIES = 300;
        static constexpr int MAX_CALORIES = 800;
        static constexpr size_t MAX_CONTAINER_TYPES = 5;
        static constexpr int MULTIPLE_CONTAINER_THRESHOLD = 2;
        static constexpr int OUTDOOR_CONTAINER_THRESHOLD = 3;
    }
    namespace Ethnic {
        static constexpr int MIN_CALORIES = 500;
        static constexpr int MAX_CALORIES = 1200;
        static constexpr size_t MAX_CUISINE_LENGTH = 25;
        static constexpr size_t MAX_SERVING_STYLE_LENGTH = 20;
    }
    namespace Barbecue {
        static constexpr int MIN_CALORIES = 600;
        static constexpr int MAX_CALORIES = 1500;
        static constexpr size_t MAX_MEAT_TYPES = 8;
        static constexpr size_t MAX_LOCATION_TYPE_LENGTH = 20;
        static constexpr int MULTIPLE_MEAT_THRESHOLD = 3;
    }
    namespace Tasting {
        static constexpr int MIN_CALORIES = 400;
        static constexpr int MAX_CALORIES = 1000;
        static constexpr int MIN_DISHES = 3;
        static constexpr int MAX_DISHES = 12;
        static constexpr size_t MAX_CHEF_SPECIALTY_LENGTH = 30;
        static constexpr size_t MAX_PAIRING_NOTES_LENGTH = 100;
        static constexpr int PREMIUM_DISH_THRESHOLD = 6;
    }
    namespace EventCatering {
        static constexpr int MIN_CALORIES = 400;
        static constexpr int MAX_CALORIES = 1200;
        static constexpr int MIN_GUESTS = 10;
        static constexpr int MAX_GUESTS = 500;
        static constexpr size_t MAX_SERVICE_TYPE_LENGTH = 20;
        static constexpr size_t MAX_EVENT_TYPE_LENGTH = 25;
        static constexpr int LARGE_EVENT_THRESHOLD = 100;
    }
    namespace Dietary {
        static constexpr int MIN_CALORIES = 200;
        static constexpr int MAX_CALORIES = 800;
        static constexpr size_t MAX_DIET_TYPE_LENGTH = 20;
        static constexpr size_t MAX_PORTION_LENGTH = 15;
        static constexpr size_t MAX_ALLERGENS = 10;
        static constexpr int MULTIPLE_ALLERGEN_THRESHOLD = 3;
    }
}
