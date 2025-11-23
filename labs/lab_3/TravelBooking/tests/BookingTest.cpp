#include <gtest/gtest.h>
#include "Booking.hpp"
#include "BookingFilter.hpp"
#include "BookingManager.hpp"
#include "BookingNotification.hpp"
#include "Invoice.hpp"
#include "Payment.hpp"
#include "Customer.hpp"
#include "Tour.hpp"
#include "Transport.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/BookingConfig.hpp"

TEST(BookingTest, ConstructorValidData) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    EXPECT_NO_THROW({
        Booking booking(customer, tour, transport);
    });
}

TEST(BookingTest, ConstructorNullCustomer) {
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    EXPECT_THROW({
        Booking booking(nullptr, tour, transport);
    }, InvalidBookingException);
}

TEST(BookingTest, ConstructorNullTour) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    EXPECT_THROW({
        Booking booking(customer, nullptr, transport);
    }, InvalidBookingException);
}

TEST(BookingTest, ConstructorNullTransport) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    EXPECT_THROW({
        Booking booking(customer, tour, nullptr);
    }, InvalidBookingException);
}

TEST(BookingTest, Getters) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    EXPECT_GT(booking.getBookingId(), 0);
    EXPECT_FALSE(booking.getBookingDate().empty());
    EXPECT_EQ(booking.getStatus(), Booking::Status::PENDING);
    EXPECT_EQ(booking.getStatusStr(), "Pending");
    EXPECT_FALSE(booking.isActive());
    EXPECT_GT(booking.getTotalPrice(), 0);
}

TEST(BookingTest, Confirm) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    booking.confirm();
    EXPECT_EQ(booking.getStatus(), Booking::Status::CONFIRMED);
    EXPECT_EQ(booking.getStatusStr(), "Confirmed");
    EXPECT_TRUE(booking.isActive());
}

TEST(BookingTest, Cancel) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    booking.cancel();
    EXPECT_EQ(booking.getStatus(), Booking::Status::CANCELLED);
    EXPECT_EQ(booking.getStatusStr(), "Cancelled");
    EXPECT_FALSE(booking.isActive());
}

TEST(BookingTest, SetStatus) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    booking.setStatus(Booking::Status::CONFIRMED);
    EXPECT_EQ(booking.getStatus(), Booking::Status::CONFIRMED);
    booking.setStatus(Booking::Status::PENDING);
    EXPECT_EQ(booking.getStatus(), Booking::Status::PENDING);
}

TEST(BookingTest, GetBookingInfo) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    std::string info = booking.getBookingInfo();
    EXPECT_TRUE(info.find("Booking ID") != std::string::npos);
    EXPECT_TRUE(info.find("John Doe") != std::string::npos);
    EXPECT_TRUE(info.find("Test Tour") != std::string::npos);
    EXPECT_TRUE(info.find("Bus") != std::string::npos);
}

TEST(BookingTest, TotalPriceCalculation) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    EXPECT_EQ(booking.getTotalPrice(), 600.0);
}

TEST(BookingTest, PriceUpdateOnStatusChange) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    Booking booking(customer, tour, transport);
    double initialPrice = booking.getTotalPrice();
    booking.confirm();
    double priceAfterConfirm = booking.getTotalPrice();
    EXPECT_EQ(initialPrice, priceAfterConfirm);
}

TEST(BookingFilterTest, FilterByStatus) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    std::vector<std::shared_ptr<Booking>> bookings;
    auto booking1 = std::make_shared<Booking>(customer, tour, transport);
    auto booking2 = std::make_shared<Booking>(customer, tour, transport);
    booking2->confirm();
    auto booking3 = std::make_shared<Booking>(customer, tour, transport);
    booking3->cancel();
    bookings.push_back(booking1);
    bookings.push_back(booking2);
    bookings.push_back(booking3);
    auto pending = BookingFilter::filterByStatus(bookings, Booking::Status::PENDING);
    EXPECT_EQ(pending.size(), 1);
    auto confirmed = BookingFilter::filterByStatus(bookings, Booking::Status::CONFIRMED);
    EXPECT_EQ(confirmed.size(), 1);
    auto cancelled = BookingFilter::filterByStatus(bookings, Booking::Status::CANCELLED);
    EXPECT_EQ(cancelled.size(), 1);
}

TEST(BookingFilterTest, FilterByDate) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    std::vector<std::shared_ptr<Booking>> bookings;
    auto booking1 = std::make_shared<Booking>(customer, tour, transport);
    auto booking2 = std::make_shared<Booking>(customer, tour, transport);
    bookings.push_back(booking1);
    bookings.push_back(booking2);
    std::string currentDate = booking1->getBookingDate();
    auto filtered = BookingFilter::filterByDate(bookings, currentDate);
    EXPECT_EQ(filtered.size(), 2);
    auto emptyResult = BookingFilter::filterByDate(bookings, "2023-01-01");
    EXPECT_EQ(emptyResult.size(), 0);
}

TEST(BookingFilterTest, FilterByPriceRange) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour1 = std::make_shared<Tour>("Cheap Tour", "Description", "2024-01-01", "2024-01-05", 200.0, Tour::Type::ADVENTURE);
    auto tour2 = std::make_shared<Tour>("Expensive Tour", "Description", "2024-01-01", "2024-01-05", 1000.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    std::vector<std::shared_ptr<Booking>> bookings;
    auto booking1 = std::make_shared<Booking>(customer, tour1, transport);
    auto booking2 = std::make_shared<Booking>(customer, tour2, transport);
    bookings.push_back(booking1);
    bookings.push_back(booking2);
    auto cheapBookings = BookingFilter::filterByPriceRange(bookings, 0, 400);
    EXPECT_EQ(cheapBookings.size(), 1);
    auto expensiveBookings = BookingFilter::filterByPriceRange(bookings, 800, 1200);
    EXPECT_EQ(expensiveBookings.size(), 1);
    auto allBookings = BookingFilter::filterByPriceRange(bookings, 0, 2000);
    EXPECT_EQ(allBookings.size(), 2);
}

TEST(BookingManagerTest, AddBookingValid) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_NO_THROW({
        manager.addBooking(booking);
    });
}

TEST(BookingManagerTest, AddBookingNull) {
    BookingManager manager;
    EXPECT_THROW({
        manager.addBooking(nullptr);
    }, InvalidDataException);
}

TEST(BookingManagerTest, CancelBookingExists) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    manager.addBooking(booking);
    EXPECT_TRUE(manager.cancelBooking(booking->getBookingId()));
    EXPECT_EQ(booking->getStatus(), Booking::Status::CANCELLED);
}

TEST(BookingManagerTest, CancelBookingNotFound) {
    BookingManager manager;
    EXPECT_THROW({
        manager.cancelBooking(999);
    }, InvalidDataException);
}

TEST(BookingManagerTest, FindBookingByIdExists) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    manager.addBooking(booking);
    auto found = manager.findBookingById(booking->getBookingId());
    EXPECT_EQ(found, booking);
}

TEST(BookingManagerTest, FindBookingByIdNotFound) {
    BookingManager manager;
    auto found = manager.findBookingById(999);
    EXPECT_EQ(found, nullptr);
}

TEST(BookingManagerTest, GetActiveBookings) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking1 = std::make_shared<Booking>(customer, tour, transport);
    auto booking2 = std::make_shared<Booking>(customer, tour, transport);
    booking2->confirm();
    auto booking3 = std::make_shared<Booking>(customer, tour, transport);
    booking3->cancel();
    manager.addBooking(booking1);
    manager.addBooking(booking2);
    manager.addBooking(booking3);
    auto active = manager.getActiveBookings();
    EXPECT_EQ(active.size(), 1);
}

TEST(BookingManagerTest, CalculateTotalRevenue) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking1 = std::make_shared<Booking>(customer, tour, transport);
    auto booking2 = std::make_shared<Booking>(customer, tour, transport);
    manager.addBooking(booking1);
    manager.addBooking(booking2);
    double revenue = manager.calculateTotalRevenue();
    EXPECT_EQ(revenue, 1200.0);
}

TEST(BookingManagerTest, CountBookingsByStatus) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking1 = std::make_shared<Booking>(customer, tour, transport);
    auto booking2 = std::make_shared<Booking>(customer, tour, transport);
    booking2->confirm();
    auto booking3 = std::make_shared<Booking>(customer, tour, transport);
    booking3->cancel();
    manager.addBooking(booking1);
    manager.addBooking(booking2);
    manager.addBooking(booking3);
    EXPECT_EQ(manager.countBookingsByStatus(Booking::Status::PENDING), 1);
    EXPECT_EQ(manager.countBookingsByStatus(Booking::Status::CONFIRMED), 1);
    EXPECT_EQ(manager.countBookingsByStatus(Booking::Status::CANCELLED), 1);
}

TEST(BookingManagerTest, GetSummary) {
    BookingManager manager;
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    manager.addBooking(booking);
    std::string summary = manager.getSummary();
    EXPECT_TRUE(summary.find("Total bookings") != std::string::npos);
    EXPECT_TRUE(summary.find("Confirmed") != std::string::npos);
    EXPECT_TRUE(summary.find("Revenue") != std::string::npos);
}

TEST(BookingNotificationTest, NotifyStatusChange) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_NO_THROW({
        BookingNotification::notifyStatusChange(booking);
    });
}

TEST(BookingNotificationTest, NotifyCancellation) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_NO_THROW({
        BookingNotification::notifyCancellation(booking);
    });
}

TEST(BookingNotificationTest, NotifyConfirmation) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_NO_THROW({
        BookingNotification::notifyConfirmation(booking);
    });
}

TEST(BookingNotificationTest, NotifyWithNull) {
    EXPECT_NO_THROW({
        BookingNotification::notifyStatusChange(nullptr);
        BookingNotification::notifyCancellation(nullptr);
        BookingNotification::notifyConfirmation(nullptr);
    });
}

TEST(PaymentTest, ConstructorValidData) {
    EXPECT_NO_THROW({
        Payment payment("John Doe", "2024-01-01", 100.0, Payment::Method::CARD);
    });
}

TEST(PaymentTest, ConstructorInvalidPayerName) {
    EXPECT_THROW({
        Payment payment("", "2024-01-01", 100.0, Payment::Method::CARD);
    }, InvalidDataException);
}

TEST(PaymentTest, ConstructorPayerNameTooLong) {
    std::string longName(BookingConfig::Payment::MAX_PAYER_NAME + 1, 'A');
    EXPECT_THROW({
        Payment payment(longName, "2024-01-01", 100.0, Payment::Method::CARD);
    }, InvalidDataException);
}

TEST(PaymentTest, ConstructorInvalidDate) {
    EXPECT_THROW({
        Payment payment("John Doe", "invalid-date", 100.0, Payment::Method::CARD);
    }, InvalidDateException);
}

TEST(PaymentTest, ConstructorAmountTooLow) {
    EXPECT_THROW({
        Payment payment("John Doe", "2024-01-01", BookingConfig::Payment::MIN_AMOUNT - 1, Payment::Method::CARD);
    }, PaymentProcessingException);
}

TEST(PaymentTest, ConstructorAmountTooHigh) {
    EXPECT_THROW({
        Payment payment("John Doe", "2024-01-01", BookingConfig::Payment::MAX_AMOUNT + 1, Payment::Method::CARD);
    }, PaymentProcessingException);
}

TEST(PaymentTest, Getters) {
    Payment payment("John Doe", "2024-01-01", 100.0, Payment::Method::CARD);
    EXPECT_GT(payment.getPaymentId(), 0);
    EXPECT_EQ(payment.getPayerName(), "John Doe");
    EXPECT_EQ(payment.getPaymentDate(), "2024-01-01");
    EXPECT_EQ(payment.getAmount(), 100.0);
    EXPECT_EQ(payment.getMethod(), Payment::Method::CARD);
    EXPECT_EQ(payment.getMethodStr(), "Card");
    EXPECT_FALSE(payment.isSuccessful());
}

TEST(PaymentTest, MarkSuccess) {
    Payment payment("John Doe", "2024-01-01", 100.0, Payment::Method::CARD);
    payment.markSuccess();
    EXPECT_TRUE(payment.isSuccessful());
}

TEST(PaymentTest, MarkFailed) {
    Payment payment("John Doe", "2024-01-01", 100.0, Payment::Method::CARD);
    payment.markFailed();
    EXPECT_FALSE(payment.isSuccessful());
}

TEST(PaymentTest, GetPaymentInfo) {
    Payment payment("John Doe", "2024-01-01", 100.0, Payment::Method::CARD);
    std::string info = payment.getPaymentInfo();
    EXPECT_TRUE(info.find("Payment ID") != std::string::npos);
    EXPECT_TRUE(info.find("John Doe") != std::string::npos);
    EXPECT_TRUE(info.find("100") != std::string::npos);
    EXPECT_TRUE(info.find("Card") != std::string::npos);
}

TEST(InvoiceTest, ConstructorValidData) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    EXPECT_NO_THROW({
        Invoice invoice(booking, payment, "2024-01-01");
    });
}

TEST(InvoiceTest, ConstructorNullBooking) {
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    EXPECT_THROW({
        Invoice invoice(nullptr, payment, "2024-01-01");
    }, InvalidDataException);
}

TEST(InvoiceTest, ConstructorNullPayment) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_THROW({
        Invoice invoice(booking, nullptr, "2024-01-01");
    }, InvalidDataException);
}

TEST(InvoiceTest, ConstructorInvalidDate) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    EXPECT_THROW({
        Invoice invoice(booking, payment, "invalid-date");
    }, InvalidDateException);
}

TEST(InvoiceTest, Getters) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    Invoice invoice(booking, payment, "2024-01-01");
    EXPECT_GT(invoice.getInvoiceId(), 0);
    EXPECT_EQ(invoice.getIssueDate(), "2024-01-01");
    EXPECT_FALSE(invoice.getIsPaid());
}

TEST(InvoiceTest, MarkPaid) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    Invoice invoice(booking, payment, "2024-01-01");
    invoice.markPaid();
    EXPECT_TRUE(invoice.getIsPaid());
    EXPECT_TRUE(payment->isSuccessful());
}

TEST(InvoiceTest, MarkUnpaid) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    Invoice invoice(booking, payment, "2024-01-01");
    invoice.markUnpaid();
    EXPECT_FALSE(invoice.getIsPaid());
    EXPECT_FALSE(payment->isSuccessful());
}

TEST(InvoiceTest, GetInvoiceInfo) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", 600.0, Payment::Method::CARD);
    Invoice invoice(booking, payment, "2024-01-01");
    std::string info = invoice.getInvoiceInfo();
    EXPECT_TRUE(info.find("Invoice ID") != std::string::npos);
    EXPECT_TRUE(info.find("Booking ID") != std::string::npos);
    EXPECT_TRUE(info.find("Payment ID") != std::string::npos);
    EXPECT_TRUE(info.find("2024-01-01") != std::string::npos);
}

TEST(BookingIntegrationTest, CompleteBookingFlow) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 500.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 100.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_EQ(booking->getStatus(), Booking::Status::PENDING);
    booking->confirm();
    EXPECT_EQ(booking->getStatus(), Booking::Status::CONFIRMED);
    EXPECT_TRUE(booking->isActive());
    auto payment = std::make_shared<Payment>("John Doe", "2024-01-01", booking->getTotalPrice(), Payment::Method::CARD);
    auto invoice = std::make_shared<Invoice>(booking, payment, "2024-01-01");
    invoice->markPaid();
    EXPECT_TRUE(invoice->getIsPaid());
    EXPECT_TRUE(payment->isSuccessful());
    BookingManager manager;
    manager.addBooking(booking);
    EXPECT_EQ(manager.countBookingsByStatus(Booking::Status::CONFIRMED), 1);
    EXPECT_GT(manager.calculateTotalRevenue(), 0);
}

TEST(BookingBoundaryTest, PaymentAmountBoundaries) {
    EXPECT_NO_THROW({
        Payment payment1("John Doe", "2024-01-01", BookingConfig::Payment::MIN_AMOUNT, Payment::Method::CARD);
        Payment payment2("John Doe", "2024-01-01", BookingConfig::Payment::MAX_AMOUNT, Payment::Method::CARD);
    });
}

TEST(BookingBoundaryTest, PayerNameLengthBoundary) {
    std::string maxName(BookingConfig::Payment::MAX_PAYER_NAME, 'A');
    EXPECT_NO_THROW({
        Payment payment(maxName, "2024-01-01", 100.0, Payment::Method::CARD);
    });
}

TEST(BookingBoundaryTest, PaymentMethodCoverage) {
    EXPECT_NO_THROW({
        Payment payment1("John Doe", "2024-01-01", 100.0, Payment::Method::CARD);
        Payment payment2("John Doe", "2024-01-01", 100.0, Payment::Method::PAYPAL);
        Payment payment3("John Doe", "2024-01-01", 100.0, Payment::Method::BANK_TRANSFER);
        Payment payment4("John Doe", "2024-01-01", 100.0, Payment::Method::CASH);
    });
}