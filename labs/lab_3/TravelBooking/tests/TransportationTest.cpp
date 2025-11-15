#include <gtest/gtest.h>
#include "Transport.hpp"
#include "TransportManager.hpp"
#include "TransportReview.hpp"
#include "TransportSchedule.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "utils/Utils.hpp"
#include "configs/TransportConfig.hpp"

TEST(TransportTest, ConstructorValidData) {
    EXPECT_NO_THROW({
        Transport transport("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-01", 100.0, Transport::Type::FLIGHT);
    });
}

TEST(TransportTest, ConstructorEmptyCompany) {
    EXPECT_THROW({
        Transport transport("", "Moscow", "London", "2024-01-01", "2024-01-01", 100.0, Transport::Type::FLIGHT);
    }, InvalidDataException);
}

TEST(TransportTest, ConstructorLongCompanyName) {
    std::string longName(TransportConfig::Transport::MAX_COMPANY_NAME_LENGTH + 1, 'A');
    EXPECT_THROW({
        Transport transport(longName, "Moscow", "London", "2024-01-01", "2024-01-01", 100.0, Transport::Type::FLIGHT);
    }, InvalidDataException);
}

TEST(TransportTest, ConstructorEmptyDeparture) {
    EXPECT_THROW({
        Transport transport("Aeroflot", "", "London", "2024-01-01", "2024-01-01", 100.0, Transport::Type::FLIGHT);
    }, InvalidDataException);
}

TEST(TransportTest, ConstructorEmptyArrival) {
    EXPECT_THROW({
        Transport transport("Aeroflot", "Moscow", "", "2024-01-01", "2024-01-01", 100.0, Transport::Type::FLIGHT);
    }, InvalidDataException);
}

TEST(TransportTest, ConstructorInvalidDepartureTime) {
    EXPECT_THROW({
        Transport transport("Aeroflot", "Moscow", "London", "invalid-date", "2024-01-01", 100.0, Transport::Type::FLIGHT);
    }, InvalidDateException);
}

TEST(TransportTest, ConstructorInvalidArrivalTime) {
    EXPECT_THROW({
        Transport transport("Aeroflot", "Moscow", "London", "2024-01-01", "invalid-date", 100.0, Transport::Type::FLIGHT);
    }, InvalidDateException);
}

TEST(TransportTest, ConstructorPriceBelowMin) {
    EXPECT_THROW({
        Transport transport("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-01", TransportConfig::Transport::MIN_TRANSPORT_PRICE - 1, Transport::Type::FLIGHT);
    }, InvalidDataException);
}

TEST(TransportTest, ConstructorPriceAboveMax) {
    EXPECT_THROW({
        Transport transport("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-01", TransportConfig::Transport::MAX_TRANSPORT_PRICE + 1, Transport::Type::FLIGHT);
    }, InvalidDataException);
}

TEST(TransportTest, Getters) {
    Transport transport("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_EQ(transport.getCompany(), "Aeroflot");
    EXPECT_EQ(transport.getDeparture(), "Moscow");
    EXPECT_EQ(transport.getArrival(), "London");
    EXPECT_EQ(transport.getDepartureTime(), "2024-01-01");
    EXPECT_EQ(transport.getArrivalTime(), "2024-01-02");
    EXPECT_EQ(transport.getPrice(), 100.0);
    EXPECT_EQ(transport.getTransportType(), Transport::Type::FLIGHT);
    EXPECT_EQ(transport.getTransportTypeStr(), "Flight");
}

TEST(TransportTest, TransportIdIncrement) {
    int firstId = Transport("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-01", 100.0, Transport::Type::FLIGHT).getTransportId();
    int secondId = Transport("Lufthansa", "Berlin", "Paris", "2024-01-02", "2024-01-02", 200.0, Transport::Type::FLIGHT).getTransportId();
    EXPECT_EQ(secondId, firstId + 1);
}

TEST(TransportTest, GetTransportInfo) {
    Transport transport("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    std::string info = transport.getTransportInfo();
    EXPECT_TRUE(info.find("Aeroflot") != std::string::npos);
    EXPECT_TRUE(info.find("Flight") != std::string::npos);
    EXPECT_TRUE(info.find("Moscow") != std::string::npos);
    EXPECT_TRUE(info.find("London") != std::string::npos);
    EXPECT_TRUE(info.find("100") != std::string::npos);
}

TEST(TransportScheduleTest, ConstructorValidData) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_NO_THROW({
        TransportSchedule schedule(transport, "2024-01-01", "Moscow", "London", 100);
    });
}

TEST(TransportScheduleTest, ConstructorNullTransport) {
    EXPECT_THROW({
        TransportSchedule schedule(nullptr, "2024-01-01", "Moscow", "London", 100);
    }, TransportationSchedulingException);
}

TEST(TransportScheduleTest, ConstructorInvalidDate) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportSchedule schedule(transport, "invalid-date", "Moscow", "London", 100);
    }, InvalidDateException);
}

TEST(TransportScheduleTest, ConstructorEmptyOrigin) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportSchedule schedule(transport, "2024-01-01", "", "London", 100);
    }, InvalidDataException);
}

TEST(TransportScheduleTest, ConstructorEmptyDestination) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportSchedule schedule(transport, "2024-01-01", "Moscow", "", 100);
    }, InvalidDataException);
}

TEST(TransportScheduleTest, ConstructorNegativeSeats) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportSchedule schedule(transport, "2024-01-01", "Moscow", "London", -1);
    }, InvalidDataException);
}

TEST(TransportScheduleTest, Getters) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    TransportSchedule schedule(transport, "2024-01-01", "Moscow", "London", 100);
    EXPECT_EQ(schedule.getTransport(), transport);
    EXPECT_EQ(schedule.getDepartureDate(), "2024-01-01");
    EXPECT_EQ(schedule.getOrigin(), "Moscow");
    EXPECT_EQ(schedule.getDestination(), "London");
    EXPECT_EQ(schedule.getAvailableSeats(), 100);
}

TEST(TransportScheduleTest, ReserveSeatsValid) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    TransportSchedule schedule(transport, "2024-01-01", "Moscow", "London", 100);
    EXPECT_NO_THROW({
        schedule.reserveSeats(50);
    });
    EXPECT_EQ(schedule.getAvailableSeats(), 50);
}

TEST(TransportScheduleTest, ReserveSeatsExceeding) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    TransportSchedule schedule(transport, "2024-01-01", "Moscow", "London", 100);
    EXPECT_THROW({
        schedule.reserveSeats(150);
    }, TransportationSchedulingException);
    EXPECT_EQ(schedule.getAvailableSeats(), 100);
}

TEST(TransportScheduleTest, GetScheduleInfo) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    TransportSchedule schedule(transport, "2024-01-01", "Moscow", "London", 100);
    std::string info = schedule.getScheduleInfo();
    EXPECT_TRUE(info.find("Flight") != std::string::npos);
    EXPECT_TRUE(info.find("Moscow") != std::string::npos);
    EXPECT_TRUE(info.find("London") != std::string::npos);
    EXPECT_TRUE(info.find("2024-01-01") != std::string::npos);
    EXPECT_TRUE(info.find("100") != std::string::npos);
}

TEST(TransportReviewTest, ConstructorValidData) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_NO_THROW({
        TransportReview review(transport, "John Doe", "Great flight!", 5);
    });
}

TEST(TransportReviewTest, ConstructorNullTransport) {
    EXPECT_THROW({
        TransportReview review(nullptr, "John Doe", "Great flight!", 5);
    }, InvalidDataException);
}

TEST(TransportReviewTest, ConstructorInvalidReviewerName) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportReview review(transport, "", "Great flight!", 5);
    }, InvalidDataException);
}

TEST(TransportReviewTest, ConstructorEmptyComment) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportReview review(transport, "John Doe", "", 5);
    }, InvalidDataException);
}

TEST(TransportReviewTest, ConstructorRatingBelowMin) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportReview review(transport, "John Doe", "Great flight!", TransportConfig::TransportReview::MIN_RATING - 1);
    }, InvalidDataException);
}

TEST(TransportReviewTest, ConstructorRatingAboveMax) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    EXPECT_THROW({
        TransportReview review(transport, "John Doe", "Great flight!", TransportConfig::TransportReview::MAX_RATING + 1);
    }, InvalidDataException);
}

TEST(TransportReviewTest, Getters) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    TransportReview review(transport, "John Doe", "Great flight!", 5);
    EXPECT_EQ(review.getTransport(), transport);
    EXPECT_EQ(review.getReviewerName(), "John Doe");
    EXPECT_EQ(review.getComment(), "Great flight!");
    EXPECT_EQ(review.getRating(), 5);
}

TEST(TransportReviewTest, GetReviewSummary) {
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    TransportReview review(transport, "John Doe", "Great flight!", 5);
    std::string summary = review.getReviewSummary();
    EXPECT_TRUE(summary.find("John Doe") != std::string::npos);
    EXPECT_TRUE(summary.find("5") != std::string::npos);
    EXPECT_TRUE(summary.find("Great flight!") != std::string::npos);
}

TEST(TransportManagerTest, AddScheduleValid) {
    TransportManager manager;
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto schedule = std::make_shared<TransportSchedule>(transport, "2024-01-01", "Moscow", "London", 100);
    EXPECT_NO_THROW({
        manager.addSchedule(schedule);
    });
}

TEST(TransportManagerTest, AddScheduleNull) {
    TransportManager manager;
    EXPECT_THROW({
        manager.addSchedule(nullptr);
    }, InvalidDataException);
}

TEST(TransportManagerTest, AddReviewValid) {
    TransportManager manager;
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto review = std::make_shared<TransportReview>(transport, "John Doe", "Great flight!", 5);
    EXPECT_NO_THROW({
        manager.addReview(review);
    });
}

TEST(TransportManagerTest, AddReviewNull) {
    TransportManager manager;
    EXPECT_THROW({
        manager.addReview(nullptr);
    }, InvalidDataException);
}

TEST(TransportManagerTest, FindScheduleByRouteExists) {
    TransportManager manager;
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto schedule = std::make_shared<TransportSchedule>(transport, "2024-01-01", "Moscow", "London", 100);
    manager.addSchedule(schedule);
    auto found = manager.findScheduleByRoute("Moscow", "London", "2024-01-01");
    EXPECT_EQ(found, schedule);
}

TEST(TransportManagerTest, FindScheduleByRouteNotFound) {
    TransportManager manager;
    EXPECT_THROW({
        manager.findScheduleByRoute("Moscow", "London", "2024-01-01");
    }, ResourceNotFoundException);
}

TEST(TransportManagerTest, ReserveSeatsValid) {
    TransportManager manager;
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto schedule = std::make_shared<TransportSchedule>(transport, "2024-01-01", "Moscow", "London", 100);
    manager.addSchedule(schedule);
    EXPECT_NO_THROW({
        manager.reserveSeats(Transport::Type::FLIGHT, "Moscow", "London", "2024-01-01", 50);
    });
    EXPECT_EQ(schedule->getAvailableSeats(), 50);
}

TEST(TransportManagerTest, ReserveSeatsInvalidDate) {
    TransportManager manager;
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto schedule = std::make_shared<TransportSchedule>(transport, "2024-01-01", "Moscow", "London", 100);
    manager.addSchedule(schedule);
    EXPECT_THROW({
        manager.reserveSeats(Transport::Type::FLIGHT, "Moscow", "London", "invalid-date", 50);
    }, InvalidDateException);
}

TEST(TransportManagerTest, ReserveSeatsInvalidCount) {
    TransportManager manager;
    auto transport = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto schedule = std::make_shared<TransportSchedule>(transport, "2024-01-01", "Moscow", "London", 100);
    manager.addSchedule(schedule);
    EXPECT_THROW({
        manager.reserveSeats(Transport::Type::FLIGHT, "Moscow", "London", "2024-01-01", 0);
    }, InvalidDataException);
}

TEST(TransportManagerTest, GetReviewsForTransport) {
    TransportManager manager;
    auto transport1 = std::make_shared<Transport>("Aeroflot", "Moscow", "London", "2024-01-01", "2024-01-02", 100.0, Transport::Type::FLIGHT);
    auto transport2 = std::make_shared<Transport>("Russian Railways", "Moscow", "SPb", "2024-01-01", "2024-01-02", 50.0, Transport::Type::TRAIN);
    auto review1 = std::make_shared<TransportReview>(transport1, "John", "Good flight", 4);
    auto review2 = std::make_shared<TransportReview>(transport1, "Jane", "Excellent flight", 5);
    auto review3 = std::make_shared<TransportReview>(transport2, "Bob", "Comfortable train", 4);
    manager.addReview(review1);
    manager.addReview(review2);
    manager.addReview(review3);
    auto flightReviews = manager.getReviewsForTransport("Flight");
    EXPECT_EQ(flightReviews.size(), 2);
    auto trainReviews = manager.getReviewsForTransport("Train");
    EXPECT_EQ(trainReviews.size(), 1);
    auto busReviews = manager.getReviewsForTransport("Bus");
    EXPECT_EQ(busReviews.size(), 0);
}

TEST(StringValidationTest, IsValidName) {
    EXPECT_TRUE(StringValidation::isValidName("John Doe"));
    EXPECT_FALSE(StringValidation::isValidName(""));
    EXPECT_FALSE(StringValidation::isValidName("   "));
    EXPECT_FALSE(StringValidation::isValidName("John\tDoe"));
    EXPECT_FALSE(StringValidation::isValidName("John\nDoe"));
}

TEST(StringValidationTest, IsValidNameWithMaxLength) {
    EXPECT_TRUE(StringValidation::isValidName("John", 10));
    EXPECT_FALSE(StringValidation::isValidName("Very Long Name Indeed", 10));
}

TEST(StringValidationTest, IsValidDate) {
    EXPECT_TRUE(StringValidation::isValidDate("2024-01-01"));
    EXPECT_FALSE(StringValidation::isValidDate("2024-01-1"));
    EXPECT_FALSE(StringValidation::isValidDate("2024/01/01"));
    EXPECT_FALSE(StringValidation::isValidDate("invalid"));
    EXPECT_FALSE(StringValidation::isValidDate("2024-01"));
    EXPECT_FALSE(StringValidation::isValidDate("2024-00"));
}