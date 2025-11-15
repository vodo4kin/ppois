#include <gtest/gtest.h>
#include "Admin.hpp"
#include "Customer.hpp"
#include "VipCustomer.hpp"
#include "User.hpp"
#include "Booking.hpp"
#include "Tour.hpp"
#include "Transport.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include "configs/PersonsConfig.hpp"

TEST(UserTest, ConstructorValidData) {
    EXPECT_NO_THROW({
        User* user = new Customer("John Doe", "john@example.com", "Password123", "1990-01-01");
        delete user;
    });
}

TEST(UserTest, ConstructorInvalidName) {
    EXPECT_THROW({
        Customer customer("", "john@example.com", "Password123", "1990-01-01");
    }, InvalidDataException);
}

TEST(UserTest, ConstructorInvalidEmail) {
    EXPECT_THROW({
        Customer customer("John Doe", "invalid-email", "Password123", "1990-01-01");
    }, InvalidDataException);
}

TEST(UserTest, ConstructorInvalidPassword) {
    EXPECT_THROW({
        Customer customer("John Doe", "john@example.com", "short", "1990-01-01");
    }, InvalidDataException);
}

TEST(UserTest, ConstructorInvalidBirthDate) {
    EXPECT_THROW({
        Customer customer("John Doe", "john@example.com", "Password123", "invalid-date");
    }, InvalidDataException);
}

TEST(UserTest, ConstructorUnderage) {
    EXPECT_THROW({
        Customer customer("John Doe", "john@example.com", "Password123", "2020-01-01");
    }, UnderageException);
}

TEST(UserTest, Getters) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_FALSE(customer.getName().empty());
    EXPECT_FALSE(customer.getEmail().empty());
    EXPECT_FALSE(customer.getDateOfBirth().empty());
    EXPECT_TRUE(customer.getIsActive());
    EXPECT_GT(customer.getUserId(), 0);
    EXPECT_GT(customer.getAge(), 0);
}

TEST(UserTest, SetNameValid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_NO_THROW({
        customer.setName("Jane Smith");
    });
    EXPECT_EQ(customer.getName(), "Jane Smith");
}

TEST(UserTest, SetNameInvalid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.setName("");
    }, InvalidDataException);
}

TEST(UserTest, SetEmailValid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_NO_THROW({
        customer.setEmail("jane@example.com");
    });
    EXPECT_EQ(customer.getEmail(), "jane@example.com");
}

TEST(UserTest, SetEmailInvalid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.setEmail("invalid-email");
    }, InvalidDataException);
}

TEST(UserTest, SetPhoneNumberValid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_NO_THROW({
        customer.setPhoneNumber("+1234567890");
    });
    EXPECT_EQ(customer.getPhoneNumber(), "+1234567890");
}

TEST(UserTest, SetPhoneNumberInvalid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.setPhoneNumber("1234567890");
    }, InvalidDataException);
}

TEST(UserTest, SetAddressValid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_NO_THROW({
        customer.setAddress("123 Main St");
    });
    EXPECT_EQ(customer.getAddress(), "123 Main St");
}

TEST(UserTest, SetAddressEmpty) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_NO_THROW({
        customer.setAddress("");
    });
    EXPECT_EQ(customer.getAddress(), "not specified");
}

TEST(UserTest, VerifyPasswordCorrect) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_TRUE(customer.verifyPassword("Password123"));
}

TEST(UserTest, VerifyPasswordIncorrect) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_FALSE(customer.verifyPassword("WrongPassword"));
}

TEST(UserTest, ChangePasswordValid) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_NO_THROW({
        customer.changePassword("Password123", "NewPassword123");
    });
    EXPECT_TRUE(customer.verifyPassword("NewPassword123"));
}

TEST(UserTest, ChangePasswordWrongOld) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.changePassword("WrongPassword", "NewPassword123");
    }, InvalidDataException);
}

TEST(UserTest, ChangePasswordSameAsOld) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.changePassword("Password123", "Password123");
    }, InvalidDataException);
}

TEST(UserTest, ChangePasswordInvalidNew) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.changePassword("Password123", "short");
    }, InvalidDataException);
}

TEST(UserTest, ActivateDeactivate) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    customer.deactivate();
    EXPECT_FALSE(customer.getIsActive());
    customer.activate();
    EXPECT_TRUE(customer.getIsActive());
}

TEST(UserTest, GetInfo) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    std::string info = customer.getInfo();
    EXPECT_TRUE(info.find("John Doe") != std::string::npos);
    EXPECT_TRUE(info.find("john@example.com") != std::string::npos);
}

TEST(CustomerTest, Constructor) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_EQ(customer.getUserRole(), "Customer");
    EXPECT_EQ(customer.getBookingsCount(), 0);
    EXPECT_EQ(customer.getTotalSpent(), 0.0);
}

TEST(CustomerTest, AddBookingValid) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 100.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 50.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_NO_THROW({
        customer->addBooking(booking);
    });
    EXPECT_EQ(customer->getBookingsCount(), 1);
}

TEST(CustomerTest, AddBookingNull) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.addBooking(std::weak_ptr<Booking>());
    }, InvalidDataException);
}

TEST(CustomerTest, CancelBookingExists) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 100.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 50.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    customer->addBooking(booking);
    EXPECT_NO_THROW({
        customer->cancelBooking(booking->getBookingId());
    });
}

TEST(CustomerTest, CancelBookingNotFound) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_THROW({
        customer.cancelBooking(999);
    }, InvalidDataException);
}

TEST(CustomerTest, GetCustomerInfo) {
    Customer customer("John Doe", "john@example.com", "Password123", "1990-01-01");
    std::string info = customer.getCustomerInfo();
    EXPECT_TRUE(info.find("Customer") != std::string::npos);
    EXPECT_TRUE(info.find("Total bookings") != std::string::npos);
}

TEST(CustomerTest, HasActiveBookings) {
    auto customer = std::make_shared<Customer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 100.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 50.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    booking->confirm();
    customer->addBooking(booking);
    EXPECT_TRUE(customer->hasActiveBookings());
}

TEST(VipCustomerTest, Constructor) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_EQ(vipCustomer.getUserRole(), "VIP Customer");
    EXPECT_EQ(vipCustomer.getLoyaltyPoints(), 0.0);
    EXPECT_EQ(vipCustomer.getVIPTierStr(), "SILVER");
}

TEST(VipCustomerTest, AddLoyaltyPoints) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    vipCustomer.addLoyaltyPoints(100.0);
    EXPECT_EQ(vipCustomer.getLoyaltyPoints(), 100.0);
}

TEST(VipCustomerTest, UseLoyaltyPointsValid) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    vipCustomer.addLoyaltyPoints(100.0);
    EXPECT_TRUE(vipCustomer.useLoyaltyPoints(50.0));
    EXPECT_EQ(vipCustomer.getLoyaltyPoints(), 50.0);
}

TEST(VipCustomerTest, UseLoyaltyPointsInvalid) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_FALSE(vipCustomer.useLoyaltyPoints(50.0));
    EXPECT_FALSE(vipCustomer.useLoyaltyPoints(-10.0));
}

TEST(VipCustomerTest, TierUpgrade) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    vipCustomer.addLoyaltyPoints(PersonsConfig::VipCustomer::GOLD_THRESHOLD);
    EXPECT_EQ(vipCustomer.getVIPTierStr(), "GOLD");
    vipCustomer.addLoyaltyPoints(PersonsConfig::VipCustomer::PLATINUM_THRESHOLD);
    EXPECT_EQ(vipCustomer.getVIPTierStr(), "PLATINUM");
}

TEST(VipCustomerTest, CalculateDiscount) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_EQ(vipCustomer.calculateDiscount(), PersonsConfig::VipCustomer::SILVER_DISCOUNT);
    vipCustomer.addLoyaltyPoints(PersonsConfig::VipCustomer::GOLD_THRESHOLD);
    EXPECT_EQ(vipCustomer.calculateDiscount(), PersonsConfig::VipCustomer::GOLD_DISCOUNT);
}

TEST(VipCustomerTest, PremiumSupportEligibility) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_FALSE(vipCustomer.isEligibleForPremiumSupport());
    vipCustomer.addLoyaltyPoints(PersonsConfig::VipCustomer::GOLD_THRESHOLD);
    EXPECT_TRUE(vipCustomer.isEligibleForPremiumSupport());
}

TEST(VipCustomerTest, FreeCancellation) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    EXPECT_FALSE(vipCustomer.hasFreeCancellation());
    vipCustomer.addLoyaltyPoints(PersonsConfig::VipCustomer::PLATINUM_THRESHOLD);
    EXPECT_TRUE(vipCustomer.hasFreeCancellation());
}

TEST(VipCustomerTest, AddBookingEarnsPoints) {
    auto vipCustomer = std::make_shared<VipCustomer>("John Doe", "john@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 100.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 50.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(vipCustomer, tour, transport);
    vipCustomer->addBooking(booking);
    EXPECT_GT(vipCustomer->getLoyaltyPoints(), 0.0);
}

TEST(VipCustomerTest, GetCustomerInfoVIP) {
    VipCustomer vipCustomer("John Doe", "john@example.com", "Password123", "1990-01-01");
    std::string info = vipCustomer.getCustomerInfo();
    EXPECT_TRUE(info.find("VIP Customer") != std::string::npos);
    EXPECT_TRUE(info.find("VIP Tier") != std::string::npos);
}

TEST(AdminTest, ConstructorValid) {
    EXPECT_NO_THROW({
        Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    });
}

TEST(AdminTest, ConstructorInvalidDepartment) {
    EXPECT_THROW({
        Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01", Admin::AdminLevel::MODERATOR, "");
    }, InvalidDataException);
}

TEST(AdminTest, GetUserRole) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_EQ(admin.getUserRole(), "Administrator");
}

TEST(AdminTest, AdminLevelGetters) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_EQ(admin.getAdminLevel(), Admin::AdminLevel::MODERATOR);
    EXPECT_EQ(admin.getAdminLevelStr(), "Moderator");
}

TEST(AdminTest, SetAdminLevel) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    admin.setAdminLevel(Admin::AdminLevel::SUPER_ADMIN);
    EXPECT_EQ(admin.getAdminLevel(), Admin::AdminLevel::SUPER_ADMIN);
}

TEST(AdminTest, SetDepartmentValid) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_NO_THROW({
        admin.setDepartment("IT Department");
    });
    EXPECT_EQ(admin.getDepartment(), "IT Department");
}

TEST(AdminTest, SetDepartmentInvalid) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_THROW({
        admin.setDepartment("");
    }, InvalidDataException);
}

TEST(AdminTest, PermissionManagement) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_TRUE(admin.hasPermission(Admin::Permission::MANAGE_USERS));
    EXPECT_TRUE(admin.hasPermission(Admin::Permission::VIEW_REPORTS));
    EXPECT_FALSE(admin.hasPermission(Admin::Permission::MANAGE_BOOKINGS));
    admin.grantPermission(Admin::Permission::MANAGE_BOOKINGS);
    EXPECT_TRUE(admin.hasPermission(Admin::Permission::MANAGE_BOOKINGS));
    admin.revokePermission(Admin::Permission::MANAGE_BOOKINGS);
    EXPECT_FALSE(admin.hasPermission(Admin::Permission::MANAGE_BOOKINGS));
}

TEST(AdminTest, ConveniencePermissionMethods) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_TRUE(admin.canManageUsers());
    EXPECT_TRUE(admin.canViewReports());
    EXPECT_FALSE(admin.canManageBookings());
    EXPECT_FALSE(admin.canConfigureSystem());
    EXPECT_FALSE(admin.hasFullAccess());
}

TEST(AdminTest, SuperAdminPermissions) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01", Admin::AdminLevel::SUPER_ADMIN);
    EXPECT_TRUE(admin.canManageUsers());
    EXPECT_TRUE(admin.canManageBookings());
    EXPECT_TRUE(admin.canViewReports());
    EXPECT_TRUE(admin.canConfigureSystem());
    EXPECT_TRUE(admin.hasFullAccess());
}

TEST(AdminTest, PromoteDemote) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    admin.promoteToSuperAdmin();
    EXPECT_EQ(admin.getAdminLevel(), Admin::AdminLevel::SUPER_ADMIN);
    EXPECT_TRUE(admin.hasFullAccess());
    admin.demoteToModerator();
    EXPECT_EQ(admin.getAdminLevel(), Admin::AdminLevel::MODERATOR);
    EXPECT_FALSE(admin.hasFullAccess());
}

TEST(AdminTest, UserManagement) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    auto user = std::make_shared<Customer>("Test User", "test@example.com", "Password123", "1990-01-01");
    EXPECT_TRUE(admin.deactivateUser(user));
    EXPECT_FALSE(user->getIsActive());
    EXPECT_TRUE(admin.activateUser(user));
    EXPECT_TRUE(user->getIsActive());
}

TEST(AdminTest, UserManagementNoPermission) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    auto user = std::make_shared<Customer>("Test User", "test@example.com", "Password123", "1990-01-01");
    admin.revokePermission(Admin::Permission::MANAGE_USERS);
    EXPECT_FALSE(admin.deactivateUser(user));
    EXPECT_FALSE(admin.activateUser(nullptr));
}

TEST(AdminTest, CalculateTotalRevenue) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    std::vector<std::shared_ptr<Customer>> customers;
    auto customer1 = std::make_shared<Customer>("User1", "user1@example.com", "Password123", "1990-01-01");
    auto customer2 = std::make_shared<Customer>("User2", "user2@example.com", "Password123", "1990-01-01");
    customers.push_back(customer1);
    customers.push_back(customer2);
    double revenue = admin.calculateTotalRevenue(customers);
    EXPECT_EQ(revenue, 0.0);
}

TEST(AdminTest, GetActiveUsersCount) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    std::vector<std::shared_ptr<User>> users;
    auto user1 = std::make_shared<Customer>("User1", "user1@example.com", "Password123", "1990-01-01");
    auto user2 = std::make_shared<Customer>("User2", "user2@example.com", "Password123", "1990-01-01");
    user2->deactivate();
    users.push_back(user1);
    users.push_back(user2);
    int activeCount = admin.getActiveUsersCount(users);
    EXPECT_EQ(activeCount, 1);
}

TEST(AdminTest, CanPerformAction) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_TRUE(admin.canPerformAction("deactivate_user"));
    EXPECT_TRUE(admin.canPerformAction("view_reports"));
    EXPECT_FALSE(admin.canPerformAction("system_config"));
}

TEST(AdminTest, CheckSystemLoadValid) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_NO_THROW({
        admin.checkSystemLoad(3);
    });
}

TEST(AdminTest, CheckSystemLoadInvalid) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    EXPECT_THROW({
        admin.checkSystemLoad(10);
    }, SystemOverloadException);
}

TEST(AdminTest, GetAdminInfo) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    std::string info = admin.getAdminInfo();
    EXPECT_TRUE(info.find("Administrator") != std::string::npos);
    EXPECT_TRUE(info.find("Moderator") != std::string::npos);
}

TEST(AdminTest, GetAdminCapabilities) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    std::string capabilities = admin.getAdminCapabilities();
    EXPECT_TRUE(capabilities.find("manage users") != std::string::npos);
    EXPECT_TRUE(capabilities.find("view reports") != std::string::npos);
}

TEST(AdminTest, CancelAnyBooking) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01", Admin::AdminLevel::SUPER_ADMIN);
    auto customer = std::make_shared<Customer>("Test User", "test@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 100.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 50.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_TRUE(admin.cancelAnyBooking(booking));
    EXPECT_EQ(booking->getStatus(), Booking::Status::CANCELLED);
}

TEST(AdminTest, CancelAnyBookingNoPermission) {
    Admin admin("Admin User", "admin@example.com", "Password123", "1980-01-01");
    auto customer = std::make_shared<Customer>("Test User", "test@example.com", "Password123", "1990-01-01");
    auto tour = std::make_shared<Tour>("Test Tour", "Description", "2024-01-01", "2024-01-05", 100.0, Tour::Type::ADVENTURE);
    auto transport = std::make_shared<Transport>("Test Company", "A", "B", "2024-01-01", "2024-01-02", 50.0, Transport::Type::BUS);
    auto booking = std::make_shared<Booking>(customer, tour, transport);
    EXPECT_FALSE(admin.cancelAnyBooking(booking));
}