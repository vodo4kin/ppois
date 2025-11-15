#include <gtest/gtest.h>
#include "Tour.hpp"
#include "TourGuide.hpp"
#include "TourReview.hpp"
#include "TourSchedule.hpp"
#include "Hotel.hpp"
#include "BreakfastBuffet.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/ToursConfig.hpp"
#include "Apartment.hpp"

TEST(TourTest, ConstructorValidData) {
    EXPECT_NO_THROW({
        Tour tour("Adventure Tour", "Exciting adventure", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    });
}

TEST(TourTest, ConstructorInvalidTitle) {
    EXPECT_THROW({
        Tour tour("", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    }, InvalidDataException);
}

TEST(TourTest, ConstructorTitleTooShort) {
    EXPECT_THROW({
        Tour tour("Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    }, InvalidDataException);
}

TEST(TourTest, ConstructorTitleTooLong) {
    std::string longTitle(ToursConfig::Tour::MAX_TITLE_LENGTH + 1, 'A');
    EXPECT_THROW({
        Tour tour(longTitle, "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    }, InvalidDataException);
}

TEST(TourTest, ConstructorDescriptionTooLong) {
    std::string longDescription(ToursConfig::Tour::MAX_DESCRIPTION_LENGTH + 1, 'A');
    EXPECT_THROW({
        Tour tour("Valid Title", longDescription, "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    }, InvalidDataException);
}

TEST(TourTest, ConstructorInvalidStartDate) {
    EXPECT_THROW({
        Tour tour("Valid Title", "Description", "invalid-date", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    }, InvalidDateException);
}

TEST(TourTest, ConstructorInvalidEndDate) {
    EXPECT_THROW({
        Tour tour("Valid Title", "Description", "2024-01-01", "invalid-date", 500.0, Tour::Type::ADVENTURE);
    }, InvalidDateException);
}

TEST(TourTest, ConstructorPriceTooLow) {
    EXPECT_THROW({
        Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", ToursConfig::Tour::MIN_TOUR_PRICE - 1, Tour::Type::ADVENTURE);
    }, InvalidDataException);
}

TEST(TourTest, ConstructorPriceTooHigh) {
    EXPECT_THROW({
        Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", ToursConfig::Tour::MAX_TOUR_PRICE + 1, Tour::Type::ADVENTURE);
    }, InvalidDataException);
}

TEST(TourTest, ConstructorPriceZero) {
    EXPECT_NO_THROW({
        Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 0.0, Tour::Type::ADVENTURE);
    });
}

TEST(TourTest, Getters) {
    Tour tour("Adventure Tour", "Exciting adventure", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_EQ(tour.getTitle(), "Adventure Tour");
    EXPECT_EQ(tour.getDescription(), "Exciting adventure");
    EXPECT_EQ(tour.getStartDate(), "2024-01-01");
    EXPECT_EQ(tour.getEndDate(), "2024-01-05");
    EXPECT_EQ(tour.getStartPrice(), 500.0);
    EXPECT_EQ(tour.getTourType(), Tour::Type::ADVENTURE);
    EXPECT_EQ(tour.getTourTypeStr(), "Adventure");
    EXPECT_GT(tour.getTourId(), 0);
}

TEST(TourTest, GetTourInfo) {
    Tour tour("Adventure Tour", "Exciting adventure", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    std::string info = tour.getTourInfo();
    EXPECT_TRUE(info.find("Adventure Tour") != std::string::npos);
    EXPECT_TRUE(info.find("Adventure") != std::string::npos);
    EXPECT_TRUE(info.find("500") != std::string::npos);
}

TEST(TourTest, AddAccommodationValid) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_NO_THROW({
        tour.addAccommodation(accommodation);
    });
    EXPECT_EQ(tour.getAccommodationCount(), 1);
}

TEST(TourTest, AddAccommodationNull) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        tour.addAccommodation(nullptr);
    }, InvalidDataException);
}

TEST(TourTest, AddAccommodationExceedsLimit) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    for (int i = 0; i < ToursConfig::Tour::MAX_ACCOMMODATIONS_PER_TOUR; i++) {
        auto accommodation = std::make_shared<Hotel>("Hotel " + std::to_string(i), "City", 100.0, 2, 4.5, 3, true, false, "standard");
        tour.addAccommodation(accommodation);
    }
    auto extraAccommodation = std::make_shared<Hotel>("Extra Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    EXPECT_THROW({
        tour.addAccommodation(extraAccommodation);
    }, InvalidDataException);
}

TEST(TourTest, RemoveAccommodationValid) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    tour.addAccommodation(accommodation);
    EXPECT_NO_THROW({
        tour.removeAccommodation(0);
    });
    EXPECT_EQ(tour.getAccommodationCount(), 0);
}

TEST(TourTest, RemoveAccommodationInvalidIndex) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        tour.removeAccommodation(0);
    }, InvalidDataException);
}

TEST(TourTest, GetAccommodationValid) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    tour.addAccommodation(accommodation);
    EXPECT_NO_THROW({
        auto retrieved = tour.getAccommodation(0);
        EXPECT_EQ(retrieved, accommodation);
    });
}

TEST(TourTest, GetAccommodationInvalidIndex) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        tour.getAccommodation(0);
    }, InvalidDataException);
}

TEST(TourTest, CalculateTotalAccommodationCost) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation1 = std::make_shared<Hotel>("Hotel 1", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    auto accommodation2 = std::make_shared<Hotel>("Hotel 2", "City", 150.0, 2, 4.5, 3, true, false, "standard");
    tour.addAccommodation(accommodation1);
    tour.addAccommodation(accommodation2);
    EXPECT_EQ(tour.calculateTotalAccommodationCost(), 250.0);
}

TEST(TourTest, GetAccommodationsByType) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto hotel = std::make_shared<Hotel>("Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    auto apartment = std::make_shared<Apartment>("Apartment", "City", 120.0, 4, 4.5, 2, true, false, 50.0);
    tour.addAccommodation(hotel);
    tour.addAccommodation(apartment);
    auto hotels = tour.getAccommodationsByType("Hotel");
    EXPECT_EQ(hotels.size(), 1);
    auto apartments = tour.getAccommodationsByType("Apartment");
    EXPECT_EQ(apartments.size(), 1);
}

TEST(TourTest, HasAccommodationForGroup) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Hotel", "City", 100.0, 4, 4.5, 3, true, false, "standard");
    tour.addAccommodation(accommodation);
    EXPECT_TRUE(tour.hasAccommodationForGroup(3));
    EXPECT_FALSE(tour.hasAccommodationForGroup(5));
}

TEST(TourTest, GetAccommodationSummary) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Test Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    tour.addAccommodation(accommodation);
    std::string summary = tour.getAccommodationSummary();
    EXPECT_TRUE(summary.find("Test Hotel") != std::string::npos);
    EXPECT_TRUE(summary.find("100") != std::string::npos);
}

TEST(TourTest, AddMealValid) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    EXPECT_NO_THROW({
        tour.addMeal(meal);
    });
    EXPECT_EQ(tour.getMealCount(), 1);
}

TEST(TourTest, AddMealNull) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        tour.addMeal(nullptr);
    }, InvalidDataException);
}

TEST(TourTest, AddMealExceedsLimit) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    for (int i = 0; i < ToursConfig::Tour::MAX_MEALS_PER_TOUR; i++) {
        auto meal = std::make_shared<BreakfastBuffet>("Meal " + std::to_string(i), "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
        tour.addMeal(meal);
    }
    auto extraMeal = std::make_shared<BreakfastBuffet>("Extra Meal", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    EXPECT_THROW({
        tour.addMeal(extraMeal);
    }, InvalidDataException);
}

TEST(TourTest, RemoveMealValid) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(meal);
    EXPECT_NO_THROW({
        tour.removeMeal(0);
    });
    EXPECT_EQ(tour.getMealCount(), 0);
}

TEST(TourTest, RemoveMealInvalidIndex) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        tour.removeMeal(0);
    }, InvalidDataException);
}

TEST(TourTest, CalculateTotalMealCost) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal1 = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    auto meal2 = std::make_shared<BreakfastBuffet>("Lunch", "Description", 30.0, 800, std::vector<std::string>{"lunch"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(meal1);
    tour.addMeal(meal2);
    EXPECT_EQ(tour.calculateTotalMealCost(), 50.0);
}

TEST(TourTest, CalculateTotalTourCost) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    tour.addAccommodation(accommodation);
    tour.addMeal(meal);
    EXPECT_EQ(tour.calculateTotalTourCost(), 620.0);
}

TEST(TourTest, GetMealsByType) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto breakfast = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    auto lunch = std::make_shared<BreakfastBuffet>("Lunch", "Description", 30.0, 800, std::vector<std::string>{"lunch"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(breakfast);
    tour.addMeal(lunch);
    auto breakfasts = tour.getMealsByType("Breakfast Buffet");
    EXPECT_EQ(breakfasts.size(), 2);
}

TEST(TourTest, GetMealsByDiet) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast", "vegetarian"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(meal);
    auto vegetarianMeals = tour.getMealsByDiet("vegetarian");
    EXPECT_EQ(vegetarianMeals.size(), 1);
}

TEST(TourTest, GetMealsInCalorieRange) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(meal);
    auto mealsInRange = tour.getMealsInCalorieRange(500, 700);
    EXPECT_EQ(mealsInRange.size(), 1);
    auto mealsOutOfRange = tour.getMealsInCalorieRange(700, 800);
    EXPECT_EQ(mealsOutOfRange.size(), 0);
}

TEST(TourTest, GetMealSummary) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(meal);
    std::string summary = tour.getMealSummary();
    EXPECT_TRUE(summary.find("Breakfast") != std::string::npos);
    EXPECT_TRUE(summary.find("20") != std::string::npos);
}

TEST(TourTest, GetFullTourSummary) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    tour.addAccommodation(accommodation);
    tour.addMeal(meal);
    std::string summary = tour.getFullTourSummary();
    EXPECT_TRUE(summary.find("Valid Title") != std::string::npos);
    EXPECT_TRUE(summary.find("Hotel") != std::string::npos);
    EXPECT_TRUE(summary.find("Breakfast") != std::string::npos);
}

TEST(TourTest, ClearAccommodations) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto accommodation = std::make_shared<Hotel>("Hotel", "City", 100.0, 2, 4.5, 3, true, false, "standard");
    tour.addAccommodation(accommodation);
    tour.clearAccommodations();
    EXPECT_EQ(tour.getAccommodationCount(), 0);
}

TEST(TourTest, ClearMeals) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto meal = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
    tour.addMeal(meal);
    tour.clearMeals();
    EXPECT_EQ(tour.getMealCount(), 0);
}

TEST(TourGuideTest, ConstructorValidData) {
    EXPECT_NO_THROW({
        TourGuide guide("John Guide", "English", 5);
    });
}

TEST(TourGuideTest, ConstructorInvalidName) {
    EXPECT_THROW({
        TourGuide guide("", "English", 5);
    }, InvalidDataException);
}

TEST(TourGuideTest, ConstructorInvalidLanguage) {
    EXPECT_THROW({
        TourGuide guide("John Guide", "", 5);
    }, InvalidDataException);
}

TEST(TourGuideTest, ConstructorInvalidExperience) {
    EXPECT_THROW({
        TourGuide guide("John Guide", "English", -1);
    }, InvalidDataException);
}

TEST(TourGuideTest, Getters) {
    TourGuide guide("John Guide", "English", 5);
    EXPECT_EQ(guide.getName(), "John Guide");
    EXPECT_EQ(guide.getLanguage(), "English");
    EXPECT_EQ(guide.getExperienceYears(), 5);
}

TEST(TourGuideTest, GetGuideInfo) {
    TourGuide guide("John Guide", "English", 5);
    std::string info = guide.getGuideInfo();
    EXPECT_TRUE(info.find("John Guide") != std::string::npos);
    EXPECT_TRUE(info.find("English") != std::string::npos);
    EXPECT_TRUE(info.find("5") != std::string::npos);
}

TEST(TourReviewTest, ConstructorValidData) {
    EXPECT_NO_THROW({
        TourReview review("John Doe", "Great tour!", 5);
    });
}

TEST(TourReviewTest, ConstructorInvalidReviewerName) {
    EXPECT_THROW({
        TourReview review("", "Great tour!", 5);
    }, InvalidDataException);
}

TEST(TourReviewTest, ConstructorEmptyComment) {
    EXPECT_THROW({
        TourReview review("John Doe", "", 5);
    }, InvalidDataException);
}

TEST(TourReviewTest, ConstructorCommentTooLong) {
    std::string longComment(ToursConfig::TourReview::MAX_REVIEW_LENGTH + 1, 'A');
    EXPECT_THROW({
        TourReview review("John Doe", longComment, 5);
    }, InvalidDataException);
}

TEST(TourReviewTest, ConstructorRatingTooLow) {
    EXPECT_THROW({
        TourReview review("John Doe", "Great tour!", ToursConfig::TourReview::MIN_RATING - 1);
    }, InvalidDataException);
}

TEST(TourReviewTest, ConstructorRatingTooHigh) {
    EXPECT_THROW({
        TourReview review("John Doe", "Great tour!", ToursConfig::TourReview::MAX_RATING + 1);
    }, InvalidDataException);
}

TEST(TourReviewTest, Getters) {
    TourReview review("John Doe", "Great tour!", 5);
    EXPECT_EQ(review.getReviewerName(), "John Doe");
    EXPECT_EQ(review.getComment(), "Great tour!");
    EXPECT_EQ(review.getRating(), 5);
}

TEST(TourReviewTest, GetReviewSummary) {
    TourReview review("John Doe", "Great tour!", 5);
    std::string summary = review.getReviewSummary();
    EXPECT_TRUE(summary.find("John Doe") != std::string::npos);
    EXPECT_TRUE(summary.find("Great tour!") != std::string::npos);
    EXPECT_TRUE(summary.find("5") != std::string::npos);
}

TEST(TourScheduleTest, ConstructorValidData) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_NO_THROW({
        TourSchedule schedule(tour, "2024-01-01", 10);
    });
}

TEST(TourScheduleTest, ConstructorNullTour) {
    EXPECT_THROW({
        TourSchedule schedule(nullptr, "2024-01-01", 10);
    }, InvalidDataException);
}

TEST(TourScheduleTest, ConstructorInvalidDate) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        TourSchedule schedule(tour, "invalid-date", 10);
    }, InvalidDateException);
}

TEST(TourScheduleTest, ConstructorNegativeSlots) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        TourSchedule schedule(tour, "2024-01-01", -1);
    }, InvalidDataException);
}

TEST(TourScheduleTest, Getters) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    TourSchedule schedule(tour, "2024-01-01", 10);
    EXPECT_EQ(schedule.getTour(), tour);
    EXPECT_EQ(schedule.getScheduledDate(), "2024-01-01");
    EXPECT_EQ(schedule.getAvailableSlots(), 10);
}

TEST(TourScheduleTest, ReduceSlotsValid) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    TourSchedule schedule(tour, "2024-01-01", 10);
    EXPECT_NO_THROW({
        schedule.reduceSlots(3);
    });
    EXPECT_EQ(schedule.getAvailableSlots(), 7);
}

TEST(TourScheduleTest, ReduceSlotsExceeding) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    TourSchedule schedule(tour, "2024-01-01", 10);
    EXPECT_THROW({
        schedule.reduceSlots(15);
    }, TourCapacityExceededException);
}

TEST(TourScheduleTest, GetScheduleInfo) {
    auto tour = std::make_shared<Tour>("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    TourSchedule schedule(tour, "2024-01-01", 10);
    std::string info = schedule.getScheduleInfo();
    EXPECT_TRUE(info.find("Valid Title") != std::string::npos);
    EXPECT_TRUE(info.find("2024-01-01") != std::string::npos);
    EXPECT_TRUE(info.find("10") != std::string::npos);
}

TEST(TourIntegrationTest, TourWithMultipleAccommodationsAndMeals) {
    Tour tour("Comprehensive Tour", "Full experience", "2024-01-01", "2024-01-07", 1000.0, Tour::Type::CULTURAL);
    auto hotel = std::make_shared<Hotel>("Luxury Hotel", "City", 200.0, 2, 4.8, 5, true, true, "suite");
    auto apartment = std::make_shared<Apartment>("Comfort Apartment", "City", 150.0, 4, 4.5, 3, true, true, 80.0);
    auto breakfast = std::make_shared<BreakfastBuffet>("Breakfast", "Description", 25.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental", "American"});
    auto lunch = std::make_shared<BreakfastBuffet>("Lunch", "Description", 35.0, 800, std::vector<std::string>{"lunch"}, true, true, std::vector<std::string>{"International"});
    tour.addAccommodation(hotel);
    tour.addAccommodation(apartment);
    tour.addMeal(breakfast);
    tour.addMeal(lunch);
    EXPECT_EQ(tour.getAccommodationCount(), 2);
    EXPECT_EQ(tour.getMealCount(), 2);
    EXPECT_EQ(tour.calculateTotalTourCost(), 1410.0);
    EXPECT_TRUE(tour.hasAccommodationForGroup(3));
}

TEST(TourIntegrationTest, EmptyTourSummary) {
    Tour tour("Simple Tour", "Basic tour", "2024-01-01", "2024-01-03", 300.0, Tour::Type::RELAXATION);
    std::string summary = tour.getFullTourSummary();
    EXPECT_TRUE(summary.find("Simple Tour") != std::string::npos);
    EXPECT_TRUE(summary.find("300") != std::string::npos);
}

TEST(TourBoundaryTest, PriceBoundaries) {
    EXPECT_NO_THROW({
        Tour tour1("Tour Min", "Description", "2024-01-01", "2024-01-05", ToursConfig::Tour::MIN_TOUR_PRICE, Tour::Type::ADVENTURE);
        Tour tour2("Tour Max", "Description", "2024-01-01", "2024-01-05", ToursConfig::Tour::MAX_TOUR_PRICE, Tour::Type::ADVENTURE);
    });
}

TEST(TourBoundaryTest, TitleLengthBoundaries) {
    std::string minTitle(std::string(ToursConfig::Tour::MIN_TITLE_LENGTH, 'A'));
    std::string maxTitle(std::string(ToursConfig::Tour::MAX_TITLE_LENGTH, 'A'));
    EXPECT_NO_THROW({
        Tour tour1(minTitle, "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
        Tour tour2(maxTitle, "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    });
}

TEST(TourBoundaryTest, DescriptionLengthBoundary) {
    std::string maxDescription(std::string(ToursConfig::Tour::MAX_DESCRIPTION_LENGTH, 'A'));
    EXPECT_NO_THROW({
        Tour tour("Valid Title", maxDescription, "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    });
}

TEST(TourReviewBoundaryTest, CommentLengthBoundary) {
    std::string maxComment(std::string(ToursConfig::TourReview::MAX_REVIEW_LENGTH, 'A'));
    EXPECT_NO_THROW({
        TourReview review("John Doe", maxComment, 5);
    });
}

TEST(TourReviewBoundaryTest, RatingBoundaries) {
    EXPECT_NO_THROW({
        TourReview review1("John Doe", "Great tour!", ToursConfig::TourReview::MIN_RATING);
        TourReview review2("John Doe", "Great tour!", ToursConfig::TourReview::MAX_RATING);
    });
}

TEST(TourAccommodationBoundaryTest, MaxAccommodations) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    for (int i = 0; i < ToursConfig::Tour::MAX_ACCOMMODATIONS_PER_TOUR; i++) {
        auto accommodation = std::make_shared<Hotel>("Hotel " + std::to_string(i), "City", 100.0, 2, 4.5, 3, true, false, "standard");
        EXPECT_NO_THROW({
            tour.addAccommodation(accommodation);
        });
    }
    EXPECT_EQ(tour.getAccommodationCount(), ToursConfig::Tour::MAX_ACCOMMODATIONS_PER_TOUR);
}

TEST(TourMealBoundaryTest, MaxMeals) {
    Tour tour("Valid Title", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    for (int i = 0; i < ToursConfig::Tour::MAX_MEALS_PER_TOUR; i++) {
        auto meal = std::make_shared<BreakfastBuffet>("Meal " + std::to_string(i), "Description", 20.0, 600, std::vector<std::string>{"breakfast"}, true, true, std::vector<std::string>{"Continental"});
        EXPECT_NO_THROW({
            tour.addMeal(meal);
        });
    }
    EXPECT_EQ(tour.getMealCount(), ToursConfig::Tour::MAX_MEALS_PER_TOUR);
}