#include "gtest/gtest.h"
#include "AllInclusiveMeal.hpp"
#include "BarbecueMeal.hpp"
#include "BreakfastBuffet.hpp"
#include "DietarySpecificMeal.hpp"
#include "EthnicDinner.hpp"
#include "EventCatering.hpp"
#include "FixedMenuDinner.hpp"
#include "PicnicLunch.hpp"
#include "TastingMenu.hpp"
#include "exceptions/TravelBookingExceptions.hpp"

TEST(AllInclusiveMealTest, ValidConstruction) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant", "Pool Bar"};
    EXPECT_NO_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants));
}

TEST(AllInclusiveMealTest, InvalidMealsPerDayThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    EXPECT_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 0, restaurants), InvalidDataException);
}

TEST(AllInclusiveMealTest, GetType) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_EQ(meal.getType(), "All Inclusive Meal");
}

TEST(AllInclusiveMealTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(AllInclusiveMealTest, HasAlcoholicDrinks) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_TRUE(meal.hasAlcoholicDrinks());
}

TEST(AllInclusiveMealTest, HasSnacks) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_TRUE(meal.hasSnacks());
}

TEST(AllInclusiveMealTest, GetMealsPerDay) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_EQ(meal.getMealsPerDay(), 3);
}

TEST(AllInclusiveMealTest, GetAvailableRestaurants) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant", "Pool Bar"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_EQ(meal.getAvailableRestaurants().size(), 2);
}

TEST(AllInclusiveMealTest, IsPremiumAllInclusive) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 4, restaurants);
    EXPECT_TRUE(meal.isPremiumAllInclusive());
}

TEST(AllInclusiveMealTest, IsUnlimitedMeals) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 5, restaurants);
    EXPECT_TRUE(meal.isUnlimitedMeals());
}

TEST(AllInclusiveMealTest, GetAllInclusiveCategory) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 4, restaurants);
    EXPECT_FALSE(meal.getAllInclusiveCategory().empty());
}

TEST(AllInclusiveMealTest, InvalidRestaurantNameThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"", "Pool Bar"};
    EXPECT_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants), InvalidDataException);
}

TEST(BarbecueMealTest, ValidConstruction) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    EXPECT_NO_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden"));
}

TEST(BarbecueMealTest, InvalidCaloriesThrows) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    EXPECT_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 2000, tags, meats, true, true, "garden"), InvalidDataException);
}

TEST(BarbecueMealTest, GetType) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_EQ(meal.getType(), "Barbecue Meal");
}

TEST(BarbecueMealTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(BarbecueMealTest, GetMeatTypes) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_EQ(meal.getMeatTypes().size(), 2);
}

TEST(BarbecueMealTest, HasVegetarianOptions) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_TRUE(meal.hasVegetarianOptions());
}

TEST(BarbecueMealTest, IsSelfService) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_TRUE(meal.isSelfService());
}

TEST(BarbecueMealTest, GetLocationType) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_EQ(meal.getLocationType(), "garden");
}

TEST(BarbecueMealTest, IsOutdoorBarbecue) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_TRUE(meal.isOutdoorBarbecue());
}

TEST(BarbecueMealTest, HasMultipleMeatOptions) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken", "pork"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_TRUE(meal.hasMultipleMeatOptions());
}

TEST(BarbecueMealTest, GetBarbecueCategory) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken", "pork"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden");
    EXPECT_FALSE(meal.getBarbecueCategory().empty());
}

TEST(BarbecueMealTest, InvalidLocationTypeThrows) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    EXPECT_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, ""), InvalidDataException);
}

TEST(BreakfastBuffetTest, ValidConstruction) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    EXPECT_NO_THROW(BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines));
}

TEST(BreakfastBuffetTest, InvalidCaloriesThrows) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    EXPECT_THROW(BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 200, tags, true, true, cuisines), InvalidDataException);
}

TEST(BreakfastBuffetTest, GetType) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_EQ(meal.getType(), "Breakfast Buffet");
}

TEST(BreakfastBuffetTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(BreakfastBuffetTest, HasHotItems) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_TRUE(meal.hasHotItems());
}

TEST(BreakfastBuffetTest, HasBeverages) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_TRUE(meal.hasBeverages());
}

TEST(BreakfastBuffetTest, GetCuisineStyles) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_EQ(meal.getCuisineStyles().size(), 2);
}

TEST(BreakfastBuffetTest, IsInternationalBreakfast) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American", "Asian"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_TRUE(meal.isInternationalBreakfast());
}

TEST(BreakfastBuffetTest, IsContinentalBreakfast) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, false, true, cuisines);
    EXPECT_TRUE(meal.isContinentalBreakfast());
}

TEST(BreakfastBuffetTest, GetBreakfastCategory) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"Continental", "American"};
    BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines);
    EXPECT_FALSE(meal.getBreakfastCategory().empty());
}

TEST(DietarySpecificMealTest, ValidConstruction) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    EXPECT_NO_THROW(DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens));
}

TEST(DietarySpecificMealTest, InvalidDietTypeThrows) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    EXPECT_THROW(DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "", true, "controlled", allergens), InvalidDataException);
}

TEST(DietarySpecificMealTest, GetType) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_EQ(meal.getType(), "Dietary Specific Meal");
}

TEST(DietarySpecificMealTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(DietarySpecificMealTest, GetDietType) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_EQ(meal.getDietType(), "vegan");
}

TEST(DietarySpecificMealTest, IsNutritionistApproved) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_TRUE(meal.isNutritionistApproved());
}

TEST(DietarySpecificMealTest, GetPortionControl) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_EQ(meal.getPortionControl(), "controlled");
}

TEST(DietarySpecificMealTest, GetAllergensExcluded) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_EQ(meal.getAllergensExcluded().size(), 2);
}

TEST(DietarySpecificMealTest, IsStrictDiet) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_TRUE(meal.isStrictDiet());
}

TEST(DietarySpecificMealTest, IsAllergenFree) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy", "nuts"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_TRUE(meal.isAllergenFree());
}

TEST(DietarySpecificMealTest, GetDietCategory) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", "dairy"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens);
    EXPECT_FALSE(meal.getDietCategory().empty());
}

TEST(EthnicDinnerTest, ValidConstruction) {
    std::vector<std::string> tags = {"ethnic"};
    EXPECT_NO_THROW(EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style"));
}

TEST(EthnicDinnerTest, InvalidCuisineThrows) {
    std::vector<std::string> tags = {"ethnic"};
    EXPECT_THROW(EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "", true, true, "family-style"), InvalidDataException);
}

TEST(EthnicDinnerTest, GetType) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_EQ(meal.getType(), "Ethnic Dinner");
}

TEST(EthnicDinnerTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(EthnicDinnerTest, GetCuisine) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_EQ(meal.getCuisine(), "Italian");
}

TEST(EthnicDinnerTest, HasCookingDemo) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_TRUE(meal.hasCookingDemo());
}

TEST(EthnicDinnerTest, HasTraditionalDrinks) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_TRUE(meal.hasTraditionalDrinks());
}

TEST(EthnicDinnerTest, GetServingStyle) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_EQ(meal.getServingStyle(), "family-style");
}

TEST(EthnicDinnerTest, IsAuthenticExperience) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_TRUE(meal.isAuthenticExperience());
}

TEST(EthnicDinnerTest, IsFamilyStyle) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_TRUE(meal.isFamilyStyle());
}

TEST(EthnicDinnerTest, GetEthnicCategory) {
    std::vector<std::string> tags = {"ethnic"};
    EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, "family-style");
    EXPECT_FALSE(meal.getEthnicCategory().empty());
}

TEST(EventCateringTest, ValidConstruction) {
    std::vector<std::string> tags = {"catering"};
    EXPECT_NO_THROW(EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding"));
}

TEST(EventCateringTest, InvalidMinimumGuestsThrows) {
    std::vector<std::string> tags = {"catering"};
    EXPECT_THROW(EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 5, "buffet", true, "wedding"), InvalidDataException);
}

TEST(EventCateringTest, GetType) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_EQ(meal.getType(), "Event Catering");
}

TEST(EventCateringTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(EventCateringTest, GetMinimumGuests) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_EQ(meal.getMinimumGuests(), 50);
}

TEST(EventCateringTest, GetServiceType) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_EQ(meal.getServiceType(), "buffet");
}

TEST(EventCateringTest, HasServiceStaff) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_TRUE(meal.hasServiceStaff());
}

TEST(EventCateringTest, GetEventType) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_EQ(meal.getEventType(), "wedding");
}

TEST(EventCateringTest, IsLargeEvent) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 100, "buffet", true, "wedding");
    EXPECT_TRUE(meal.isLargeEvent());
}

TEST(EventCateringTest, IsFormalService) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "served", true, "wedding");
    EXPECT_TRUE(meal.isFormalService());
}

TEST(EventCateringTest, GetCateringCategory) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, "wedding");
    EXPECT_FALSE(meal.getCateringCategory().empty());
}

TEST(FixedMenuDinnerTest, ValidConstruction) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    EXPECT_NO_THROW(FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic"));
}

TEST(FixedMenuDinnerTest, InvalidMenuItemThrows) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"", "Salad", "Main Course"};
    EXPECT_THROW(FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic"), InvalidDataException);
}

TEST(FixedMenuDinnerTest, GetType) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_EQ(meal.getType(), "Fixed Menu Dinner");
}

TEST(FixedMenuDinnerTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(FixedMenuDinnerTest, GetMenuItems) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_EQ(meal.getMenuItems().size(), 4);
}

TEST(FixedMenuDinnerTest, HasWinePairing) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_TRUE(meal.hasWinePairing());
}

TEST(FixedMenuDinnerTest, GetAmbiance) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_EQ(meal.getAmbiance(), "romantic");
}

TEST(FixedMenuDinnerTest, IsFineDining) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert", "Cheese Plate"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_TRUE(meal.isFineDining());
}

TEST(FixedMenuDinnerTest, HasMultipleCourses) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_TRUE(meal.hasMultipleCourses());
}

TEST(FixedMenuDinnerTest, GetDinnerCategory) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad", "Main Course", "Dessert"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic");
    EXPECT_FALSE(meal.getDinnerCategory().empty());
}

TEST(PicnicLunchTest, ValidConstruction) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    EXPECT_NO_THROW(PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers));
}

TEST(PicnicLunchTest, InvalidContainerThrows) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {""};
    EXPECT_THROW(PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers), InvalidDataException);
}

TEST(PicnicLunchTest, GetType) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_EQ(meal.getType(), "Picnic Lunch");
}

TEST(PicnicLunchTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(PicnicLunchTest, IsPrePackagedMeal) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_TRUE(meal.isPrePackagedMeal());
}

TEST(PicnicLunchTest, NeedsHeating) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, true, containers);
    EXPECT_TRUE(meal.needsHeatings());
}

TEST(PicnicLunchTest, GetContainerTypes) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_EQ(meal.getContainerTypes().size(), 2);
}

TEST(PicnicLunchTest, IsReadyToEat) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_TRUE(meal.isReadyToEat());
}

TEST(PicnicLunchTest, IsOutdoorFriendly) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_TRUE(meal.isOutdoorFriendly());
}

TEST(PicnicLunchTest, GetPicnicCategory) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box", "bottle"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers);
    EXPECT_FALSE(meal.getPicnicCategory().empty());
}

TEST(TastingMenuTest, ValidConstruction) {
    std::vector<std::string> tags = {"tasting"};
    EXPECT_NO_THROW(TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing"));
}

TEST(TastingMenuTest, InvalidNumberOfDishesThrows) {
    std::vector<std::string> tags = {"tasting"};
    EXPECT_THROW(TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 2, "Seafood", true, "White wine pairing"), InvalidDataException);
}

TEST(TastingMenuTest, GetType) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_EQ(meal.getType(), "Tasting Menu");
}

TEST(TastingMenuTest, GetMealInfoNotEmpty) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_FALSE(meal.getMealInfo().empty());
}

TEST(TastingMenuTest, GetNumberOfDishes) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_EQ(meal.getNumberOfDishes(), 5);
}

TEST(TastingMenuTest, GetChefSpecialty) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_EQ(meal.getChefSpecialty(), "Seafood");
}

TEST(TastingMenuTest, HasWineTasting) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_TRUE(meal.hasWineTasting());
}

TEST(TastingMenuTest, GetPairingNotes) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_EQ(meal.getPairingNotes(), "White wine pairing");
}

TEST(TastingMenuTest, IsPremiumTasting) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 6, "Seafood", true, "White wine pairing");
    EXPECT_TRUE(meal.isPremiumTasting());
}

TEST(TastingMenuTest, IsWinePaired) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_TRUE(meal.isWinePaired());
}

TEST(TastingMenuTest, GetTastingCategory) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, "White wine pairing");
    EXPECT_FALSE(meal.getTastingCategory().empty());
}

TEST(AllInclusiveMealTest, TooManyRestaurantsThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants(16, "Restaurant");
    EXPECT_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants), InvalidDataException);
}

TEST(AllInclusiveMealTest, InvalidRestaurantCountThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants(20, "Restaurant");
    EXPECT_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants), InvalidDataException);
}

TEST(BarbecueMealTest, TooManyMeatTypesThrows) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats(9, "meat");
    EXPECT_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden"), InvalidDataException);
}

TEST(BarbecueMealTest, InvalidMeatTypeThrows) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", ""};
    EXPECT_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, "garden"), InvalidDataException);
}

TEST(BarbecueMealTest, LocationTypeTooLongThrows) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef", "chicken"};
    std::string longLocation(25, 'a');
    EXPECT_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, true, true, longLocation), InvalidDataException);
}

TEST(BreakfastBuffetTest, TooManyCuisineStylesThrows) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines(11, "Cuisine");
    EXPECT_THROW(BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines), InvalidDataException);
}

TEST(BreakfastBuffetTest, InvalidCuisineNameThrows) {
    std::vector<std::string> tags = {"breakfast"};
    std::vector<std::string> cuisines = {"", "American"};
    EXPECT_THROW(BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines), InvalidDataException);
}

TEST(BreakfastBuffetTest, CuisineNameTooLongThrows) {
    std::vector<std::string> tags = {"breakfast"};
    std::string longCuisine(25, 'a');
    std::vector<std::string> cuisines = {longCuisine};
    EXPECT_THROW(BreakfastBuffet meal("Breakfast Buffet", "Description", 20.0, 600, tags, true, true, cuisines), InvalidDataException);
}

TEST(DietarySpecificMealTest, DietTypeTooLongThrows) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten"};
    std::string longDietType(25, 'a');
    EXPECT_THROW(DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, longDietType, true, "controlled", allergens), InvalidDataException);
}

TEST(DietarySpecificMealTest, PortionControlTooLongThrows) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten"};
    std::string longPortion(20, 'a');
    EXPECT_THROW(DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, longPortion, allergens), InvalidDataException);
}

TEST(DietarySpecificMealTest, TooManyAllergensThrows) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens(11, "allergen");
    EXPECT_THROW(DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens), InvalidDataException);
}

TEST(DietarySpecificMealTest, InvalidAllergenNameThrows) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten", ""};
    EXPECT_THROW(DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", true, "controlled", allergens), InvalidDataException);
}

TEST(EthnicDinnerTest, CuisineTooLongThrows) {
    std::vector<std::string> tags = {"ethnic"};
    std::string longCuisine(30, 'a');
    EXPECT_THROW(EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, longCuisine, true, true, "family-style"), InvalidDataException);
}

TEST(EthnicDinnerTest, ServingStyleTooLongThrows) {
    std::vector<std::string> tags = {"ethnic"};
    std::string longServingStyle(25, 'a');
    EXPECT_THROW(EthnicDinner meal("Ethnic Dinner", "Description", 40.0, 700, tags, "Italian", true, true, longServingStyle), InvalidDataException);
}

TEST(EventCateringTest, ServiceTypeTooLongThrows) {
    std::vector<std::string> tags = {"catering"};
    std::string longServiceType(25, 'a');
    EXPECT_THROW(EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, longServiceType, true, "wedding"), InvalidDataException);
}

TEST(EventCateringTest, EventTypeTooLongThrows) {
    std::vector<std::string> tags = {"catering"};
    std::string longEventType(30, 'a');
    EXPECT_THROW(EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, longEventType), InvalidDataException);
}

TEST(EventCateringTest, InvalidServiceTypeThrows) {
    std::vector<std::string> tags = {"catering"};
    EXPECT_THROW(EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "", true, "wedding"), InvalidDataException);
}

TEST(EventCateringTest, InvalidEventTypeThrows) {
    std::vector<std::string> tags = {"catering"};
    EXPECT_THROW(EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", true, ""), InvalidDataException);
}

TEST(FixedMenuDinnerTest, TooManyMenuItemsThrows) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items(11, "Menu Item");
    EXPECT_THROW(FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic"), InvalidDataException);
}

TEST(FixedMenuDinnerTest, MenuItemTooLongThrows) {
    std::vector<std::string> tags = {"dinner"};
    std::string longMenuItem(60, 'a');
    std::vector<std::string> items = {longMenuItem};
    EXPECT_THROW(FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, "romantic"), InvalidDataException);
}

TEST(FixedMenuDinnerTest, AmbianceTooLongThrows) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Salad"};
    std::string longAmbiance(25, 'a');
    EXPECT_THROW(FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, true, longAmbiance), InvalidDataException);
}

TEST(PicnicLunchTest, TooManyContainerTypesThrows) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers(6, "container");
    EXPECT_THROW(PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, false, containers), InvalidDataException);
}

TEST(TastingMenuTest, TooManyDishesThrows) {
    std::vector<std::string> tags = {"tasting"};
    EXPECT_THROW(TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 13, "Seafood", true, "Pairing notes"), InvalidDataException);
}

TEST(TastingMenuTest, ChefSpecialtyTooLongThrows) {
    std::vector<std::string> tags = {"tasting"};
    std::string longSpecialty(35, 'a');
    EXPECT_THROW(TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, longSpecialty, true, "Pairing notes"), InvalidDataException);
}

TEST(TastingMenuTest, PairingNotesTooLongThrows) {
    std::vector<std::string> tags = {"tasting"};
    std::string longNotes(110, 'a');
    EXPECT_THROW(TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", true, longNotes), InvalidDataException);
}

TEST(AllInclusiveMealTest, SetValidPrice) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_NO_THROW(meal.setPrice(100.0));
}

TEST(AllInclusiveMealTest, SetInvalidPriceThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_THROW(meal.setPrice(-1.0), InvalidDataException);
}

TEST(AllInclusiveMealTest, SetValidCalories) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_NO_THROW(meal.setCalories(700));
}

TEST(AllInclusiveMealTest, SetInvalidCaloriesThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_THROW(meal.setCalories(4000), InvalidDataException);
}

TEST(AllInclusiveMealTest, AddValidDietaryTag) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_NO_THROW(meal.addDietaryTag("vegetarian"));
}

TEST(AllInclusiveMealTest, AddInvalidDietaryTagThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_THROW(meal.addDietaryTag(""), InvalidDataException);
}

TEST(AllInclusiveMealTest, AddTooLongDietaryTagThrows) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    std::string longTag(35, 'a');
    EXPECT_THROW(meal.addDietaryTag(longTag), InvalidDataException);
}

TEST(AllInclusiveMealTest, AddDuplicateDietaryTagNoThrow) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    meal.addDietaryTag("vegetarian");
    EXPECT_NO_THROW(meal.addDietaryTag("vegetarian"));
}

TEST(AllInclusiveMealTest, AddTooManyDietaryTagsThrows) {
    std::vector<std::string> tags = {};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    for (int i = 0; i < 8; ++i) {
        meal.addDietaryTag("tag" + std::to_string(i));
    }
    EXPECT_THROW(meal.addDietaryTag("excess-tag"), InvalidDataException);
}

TEST(AllInclusiveMealTest, IsSuitableForDiet) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    meal.addDietaryTag("vegetarian");
    EXPECT_TRUE(meal.isSuitableForDiet("vegetarian"));
}

TEST(AllInclusiveMealTest, IsNotSuitableForDiet) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_FALSE(meal.isSuitableForDiet("vegan"));
}

TEST(AllInclusiveMealTest, IsWithinCalorieRange) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_TRUE(meal.isWithinCalorieRange(700, 900));
}

TEST(AllInclusiveMealTest, IsNotWithinCalorieRange) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 3, restaurants);
    EXPECT_FALSE(meal.isWithinCalorieRange(900, 1000));
}

TEST(AllInclusiveMealEdgeCases, MinimumValidMealsPerDay) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    EXPECT_NO_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 1, restaurants));
}

TEST(AllInclusiveMealEdgeCases, MaximumValidMealsPerDay) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    EXPECT_NO_THROW(AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, true, true, 6, restaurants));
}

TEST(BarbecueMealEdgeCases, MinimumValidCalories) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef"};
    EXPECT_NO_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 600, tags, meats, true, true, "garden"));
}

TEST(BarbecueMealEdgeCases, MaximumValidCalories) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef"};
    EXPECT_NO_THROW(BarbecueMeal meal("Barbecue", "Description", 35.0, 1500, tags, meats, true, true, "garden"));
}

TEST(MealConfigurationTests, MealNameTooLongThrows) {
    std::vector<std::string> tags = {"test"};
    std::string longName(150, 'a');
    EXPECT_THROW(BreakfastBuffet meal(longName, "Description", 20.0, 600, tags, true, true, {"Continental"}), InvalidDataException);
}

TEST(MealConfigurationTests, MealDescriptionTooLongThrows) {
    std::vector<std::string> tags = {"test"};
    std::string longDescription(350, 'a');
    EXPECT_THROW(BreakfastBuffet meal("Breakfast", longDescription, 20.0, 600, tags, true, true, {"Continental"}), InvalidDataException);
}

TEST(MealConfigurationTests, MealPriceTooHighThrows) {
    std::vector<std::string> tags = {"test"};
    EXPECT_THROW(BreakfastBuffet meal("Breakfast", "Description", 600.0, 600, tags, true, true, {"Continental"}), InvalidDataException);
}

TEST(MealConfigurationTests, MealInitialTagsTooManyThrows) {
    std::vector<std::string> tags(12, "tag");
    EXPECT_THROW(BreakfastBuffet meal("Breakfast", "Description", 20.0, 600, tags, true, true, {"Continental"}), InvalidDataException);
}

TEST(MealConfigurationTests, MealInitialTagTooLongThrows) {
    std::vector<std::string> tags = {std::string(35, 'a')};
    EXPECT_THROW(BreakfastBuffet meal("Breakfast", "Description", 20.0, 600, tags, true, true, {"Continental"}), InvalidDataException);
}

TEST(AllInclusiveMealPremiumCases, StandardAllInclusiveCategory) {
    std::vector<std::string> tags = {"all-inclusive"};
    std::vector<std::string> restaurants = {"Main Restaurant"};
    AllInclusiveMeal meal("All Inclusive", "Description", 50.0, 800, tags, false, false, 3, restaurants);
    EXPECT_EQ(meal.getAllInclusiveCategory(), "Standard All Inclusive");
}

TEST(BarbecueMealCategoryCases, StandardBarbecueCategory) {
    std::vector<std::string> tags = {"bbq"};
    std::vector<std::string> meats = {"beef"};
    BarbecueMeal meal("Barbecue", "Description", 35.0, 900, tags, meats, false, false, "indoor");
    EXPECT_EQ(meal.getBarbecueCategory(), "Standard Barbecue");
}

TEST(DietarySpecificMealCategoryCases, StandardDietaryCategory) {
    std::vector<std::string> tags = {"healthy"};
    std::vector<std::string> allergens = {"gluten"};
    DietarySpecificMeal meal("Diet Meal", "Description", 30.0, 400, tags, "vegan", false, "standard", allergens);
    EXPECT_EQ(meal.getDietCategory(), "Standard Dietary Meal");
}

TEST(EventCateringCategoryCases, StandardCateringCategory) {
    std::vector<std::string> tags = {"catering"};
    EventCatering meal("Event Catering", "Description", 45.0, 600, tags, 50, "buffet", false, "corporate");
    EXPECT_EQ(meal.getCateringCategory(), "Standard Event Catering");
}

TEST(FixedMenuDinnerCategoryCases, StandardDinnerCategory) {
    std::vector<std::string> tags = {"dinner"};
    std::vector<std::string> items = {"Soup", "Main Course"};
    FixedMenuDinner meal("Fixed Menu", "Description", 60.0, 800, tags, items, false, "casual");
    EXPECT_EQ(meal.getDinnerCategory(), "Multi-Course Dinner");
}

TEST(PicnicLunchCategoryCases, PackagedLunchCategory) {
    std::vector<std::string> tags = {"picnic"};
    std::vector<std::string> containers = {"box"};
    PicnicLunch meal("Picnic Lunch", "Description", 15.0, 500, tags, true, true, containers);
    EXPECT_EQ(meal.getPicnicCategory(), "Packaged Lunch");
}

TEST(TastingMenuCategoryCases, StandardTastingCategory) {
    std::vector<std::string> tags = {"tasting"};
    TastingMenu meal("Tasting Menu", "Description", 80.0, 700, tags, 5, "Seafood", false, "1");
    EXPECT_EQ(meal.getTastingCategory(), "Standard Tasting Menu");
}