#include <gtest/gtest.h>
#include <memory>
#include "exceptions/WarehouseExceptions.hpp"
#include "persons/Person.hpp"
#include "persons/Address.hpp"
#include "persons/ContactInfo.hpp"
#include "persons/CustomerCategory.hpp"
#include "persons/EmployeeRole.hpp"
#include "persons/Customer.hpp"
#include "persons/Employee.hpp"
#include "persons/UserAccount.hpp"

// ==================== PERSONS MODULE TESTS ====================
// ==================== Address Tests ====================
TEST(AddressTest, ValidAddress) {
    EXPECT_NO_THROW(Address addr("123 Main St", "Springfield", "12345", "USA"));
    Address addr("456 Oak Ave", "Shelbyville", "67890", "Canada");
    EXPECT_EQ(addr.getStreet(), "456 Oak Ave");
    EXPECT_EQ(addr.getCity(), "Shelbyville");
    EXPECT_EQ(addr.getPostalCode(), "67890");
    EXPECT_EQ(addr.getCountry(), "Canada");
    EXPECT_TRUE(addr.isComplete());
    EXPECT_EQ(addr.getFullAddress(), "456 Oak Ave, Shelbyville, 67890, Canada");
}

TEST(AddressTest, InvalidAddress) {
    EXPECT_THROW(Address addr("", "City", "12345", "USA"), DataValidationException);
    EXPECT_THROW(Address addr("Valid", "", "12345", "USA"), DataValidationException);
    EXPECT_THROW(Address addr("Valid", "City", "", "USA"), DataValidationException);
    EXPECT_THROW(Address addr("Valid", "City", "12345", ""), DataValidationException);
}

TEST(AddressTest, AddressOperations) {
    Address addr("123 Main St", "Springfield", "12345", "USA");
    addr.setStreet("456 Oak Ave");
    addr.setCity("Shelbyville");
    addr.setPostalCode("67890");
    addr.setCountry("Canada");
    EXPECT_EQ(addr.getStreet(), "456 Oak Ave");
    EXPECT_EQ(addr.getCity(), "Shelbyville");
    EXPECT_EQ(addr.getFullAddress(), "456 Oak Ave, Shelbyville, 67890, Canada");
}

// ==================== ContactInfo Tests ====================
TEST(ContactInfoTest, ValidContactInfo) {
    EXPECT_NO_THROW(ContactInfo info("john@test.com", "+1234567890", "john2@test.com", "+0987654321"));
    ContactInfo info("jane@test.com", "+1112223333");
    EXPECT_EQ(info.getEmail(), "jane@test.com");
    EXPECT_EQ(info.getPhoneNumber(), "+1112223333");
    EXPECT_TRUE(info.hasValidContact());
    EXPECT_TRUE(info.hasEmail());
    EXPECT_TRUE(info.hasPhoneNumber());
    EXPECT_EQ(info.getPrimaryContact(), "jane@test.com");
}

TEST(ContactInfoTest, InvalidContactInfo) {
    EXPECT_THROW(ContactInfo info("invalid-email", "+1234567890"), DataValidationException);
    EXPECT_THROW(ContactInfo info("valid@test.com", "short"), DataValidationException);
    EXPECT_THROW(ContactInfo info("valid@test.com", "+1234567890", "invalid", "+0987654321"), DataValidationException);
}

TEST(ContactInfoTest, ContactOperations) {
    ContactInfo info("initial@test.com", "+1111111111");
    info.setEmail("new@test.com");
    info.setPhoneNumber("+2222222222");
    info.setSecondaryEmail("secondary@test.com");
    info.setSecondaryPhone("+3333333333");
    EXPECT_EQ(info.getEmail(), "new@test.com");
    EXPECT_EQ(info.getSecondaryEmail(), "secondary@test.com");
    EXPECT_EQ(info.getInfo(), "Primary: new@test.com, Secondary Email: secondary@test.com, Secondary Phone: +3333333333");
}

// ==================== CustomerCategory Tests ====================
TEST(CustomerCategoryTest, CategoryTypes) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    CustomerCategory student(CustomerCategory::Category::STUDENT);
    EXPECT_EQ(regular.toString(), "Regular");
    EXPECT_EQ(gold.toString(), "Gold");
    EXPECT_EQ(student.toString(), "Student");
    EXPECT_DOUBLE_EQ(regular.getDiscountPercentage(), 0.0);
    EXPECT_DOUBLE_EQ(gold.getDiscountPercentage(), 10.0);
    EXPECT_DOUBLE_EQ(student.getDiscountPercentage(), 10.0);
    EXPECT_FALSE(regular.hasFreeShipping());
    EXPECT_TRUE(gold.hasFreeShipping());
    EXPECT_FALSE(student.hasFreeShipping());
    EXPECT_FALSE(regular.isEligibleForLoyaltyProgram());
    EXPECT_TRUE(gold.isEligibleForLoyaltyProgram());
}

TEST(CustomerCategoryTest, UpgradeLogic) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory silver(CustomerCategory::Category::SILVER);
    EXPECT_TRUE(regular.canUpgrade(1500.0));
    EXPECT_FALSE(regular.canUpgrade(500.0));
    EXPECT_TRUE(silver.canUpgrade(6000.0));
    EXPECT_FALSE(silver.canUpgrade(4000.0));
    EXPECT_EQ(regular.getNextCategory(), CustomerCategory::Category::SILVER);
    EXPECT_EQ(silver.getNextCategory(), CustomerCategory::Category::GOLD);
}

// ==================== EmployeeRole Tests ====================
TEST(EmployeeRoleTest, RolePermissions) {
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    EXPECT_EQ(worker.toString(), "Warehouse Worker");
    EXPECT_EQ(manager.toString(), "Inventory Manager");
    EXPECT_FALSE(worker.canManageInventory());
    EXPECT_TRUE(manager.canManageInventory());
    EXPECT_TRUE(admin.canManageInventory());
    EXPECT_FALSE(worker.canManageUsers());
    EXPECT_FALSE(manager.canManageUsers());
    EXPECT_TRUE(admin.canManageUsers());
    EXPECT_DOUBLE_EQ(worker.getSalaryMultiplier(), 1.0);
    EXPECT_DOUBLE_EQ(manager.getSalaryMultiplier(), 1.5);
    EXPECT_DOUBLE_EQ(admin.getSalaryMultiplier(), 2.0);
}

TEST(EmployeeRoleTest, AccessLevels) {
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    EmployeeRole supervisor(EmployeeRole::Role::SUPERVISOR);
    EmployeeRole hr(EmployeeRole::Role::HR_MANAGER);
    EXPECT_EQ(cashier.getAccessLevel(), 2);
    EXPECT_EQ(supervisor.getAccessLevel(), 6);
    EXPECT_EQ(hr.getAccessLevel(), 7);
    EXPECT_TRUE(cashier.canProcessSales());
    EXPECT_TRUE(supervisor.canProcessSales());
    EXPECT_FALSE(hr.canProcessSales());
}

// ==================== Person Tests ====================
TEST(PersonTest, ValidPerson) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("john@test.com", "+1234567890");
    EXPECT_NO_THROW(Person person("P001", "John", "Doe", "1990-05-15", address, contact));
    Person person("P002", "Jane", "Smith", "1985-08-20", address, contact);
    EXPECT_EQ(person.getId(), "P002");
    EXPECT_EQ(person.getFullName(), "Jane Smith");
    EXPECT_EQ(person.getDateOfBirth(), "1985-08-20");
    EXPECT_TRUE(person.isAdult());
    EXPECT_GT(person.calculateAge(), 25);
}

TEST(PersonTest, PersonOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person person("P003", "Bob", "Johnson", "2000-01-01", address, contact);
    person.setFirstName("Robert");
    person.setLastName("Johnsonson");
    auto newAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "Canada");
    person.setAddress(newAddress);
    EXPECT_EQ(person.getFirstName(), "Robert");
    EXPECT_EQ(person.getFullName(), "Robert Johnsonson");
    EXPECT_EQ(person.getAddress()->getCity(), "Shelbyville");
}

// ==================== Customer Tests ====================
TEST(CustomerTest, ValidCustomer) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("customer@test.com", "+1234567890");
    CustomerCategory category(CustomerCategory::Category::SILVER);
    EXPECT_NO_THROW(
        Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                         "CUST001", category, "2024-01-15")
    );
    Customer customer("P002", "Jane", "Smith", "1985-08-20", address, contact,
                     "CUST002", category, "2024-01-16");
    EXPECT_EQ(customer.getCustomerId(), "CUST002");
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
    EXPECT_DOUBLE_EQ(customer.getTotalPurchases(), 0.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 0);
    EXPECT_TRUE(customer.isCustActive());
}

TEST(CustomerTest, CustomerOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                     "CUST001", regular, "2024-01-15");
    customer.addPurchase(100.0);
    customer.addLoyaltyPoints(50);
    EXPECT_DOUBLE_EQ(customer.getTotalPurchases(), 100.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 150); // 100 from purchase + 50 bonus
    customer.redeemLoyaltyPoints(30);
    EXPECT_EQ(customer.getLoyaltyPoints(), 120);
    EXPECT_THROW(customer.redeemLoyaltyPoints(200), InsufficientStockException);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    customer.setCategory(gold);
    EXPECT_DOUBLE_EQ(customer.calculateDiscount(), 10.0);
}

TEST(CustomerTest, CategoryUpgrade) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                     "CUST001", regular, "2024-01-15");
    customer.addPurchase(1500.0); // Above regular threshold (1000)
    EXPECT_TRUE(customer.isEligibleForUpgrade());
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
}

// ==================== Employee Tests ====================
TEST(EmployeeTest, ValidEmployee) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("employee@test.com", "+1234567890");
    EmployeeRole role(EmployeeRole::Role::WAREHOUSE_WORKER);
    EXPECT_NO_THROW(
        Employee employee("P001", "John", "Doe", "1990-05-15", address, contact,
                         "EMP001", role, "2024-01-15", 30000.0, "Warehouse")
    );
    Employee employee("P002", "Jane", "Smith", "1985-08-20", address, contact,
                     "EMP002", role, "2024-01-16", 35000.0, "Operations");
    EXPECT_EQ(employee.getEmployeeId(), "EMP002");
    EXPECT_EQ(employee.getRole().toString(), "Warehouse Worker");
    EXPECT_DOUBLE_EQ(employee.getBaseSalary(), 35000.0);
    EXPECT_EQ(employee.getDepartment(), "Operations");
    EXPECT_TRUE(employee.isEmplActive());
}

TEST(EmployeeTest, EmployeeOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    Employee employee("P001", "John", "Doe", "1990-05-15", address, contact,
                     "EMP001", worker, "2020-01-15", 30000.0, "Warehouse");
    EXPECT_GE(employee.calculateYearsOfService(), 4);
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 30000.0); // 30000 * 1.0    
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    employee.promote(manager, 45000.0);
    EXPECT_EQ(employee.getRole().toString(), "Inventory Manager");
    EXPECT_DOUBLE_EQ(employee.getBaseSalary(), 45000.0);
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 67500.0); // 45000 * 1.5
    EXPECT_TRUE(employee.canManageInventory());
    EXPECT_FALSE(employee.canManageUsers());
}

TEST(EmployeeTest, PermissionChecks) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    Employee cashierEmp("P001", "Cash", "Ier", "1995-01-01", address, contact,
                       "EMP001", cashier, "2024-01-15", 25000.0, "Sales");
    EXPECT_TRUE(cashierEmp.canProcessSales());
    EXPECT_FALSE(cashierEmp.canManageInventory());
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    Employee adminEmp("P002", "Admin", "User", "1980-01-01", address, contact,
                     "EMP002", admin, "2024-01-15", 60000.0, "IT");
    EXPECT_TRUE(adminEmp.canManageUsers());
    EXPECT_TRUE(adminEmp.canManageInventory());
}

// ==================== UserAccount Tests ====================
TEST(UserAccountTest, ValidUserAccount) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    EXPECT_NO_THROW(UserAccount account("johndoe", "SecurePass123", person));
    UserAccount account("janedoe", "StrongPass456", person);
    EXPECT_EQ(account.getUsername(), "janedoe");
    EXPECT_EQ(account.getPerson(), person);
    EXPECT_FALSE(account.isAccountLocked());
    EXPECT_EQ(account.getFailedLoginAttempts(), 0);
}

TEST(UserAccountTest, Authentication) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    UserAccount account("testuser", "MyPassword123", person);
    EXPECT_TRUE(account.authenticate("MyPassword123"));
    EXPECT_THROW(account.authenticate("wrongpassword"), AuthenticationException);
    for (int i = 0; i < 4; i++) {
        EXPECT_THROW(account.authenticate("wrong"), AuthenticationException);
    }
    EXPECT_THROW(account.authenticate("wrong"), AuthenticationException); // 5th attempt
    EXPECT_TRUE(account.isAccountLocked());
    EXPECT_THROW(account.authenticate("MyPassword123"), AuthenticationException);
    account.unlockAccount();
    EXPECT_FALSE(account.isAccountLocked());
    EXPECT_TRUE(account.authenticate("MyPassword123")); // Should work after unlock
}

TEST(UserAccountTest, PasswordManagement) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    UserAccount account("testuser", "OldPassword123", person);
    account.changePassword("OldPassword123", "NewPassword456");
    EXPECT_TRUE(account.authenticate("NewPassword456"));
    EXPECT_THROW(account.authenticate("OldPassword123"), AuthenticationException);
    EXPECT_THROW(account.changePassword("wrongold", "NewPass"), AuthenticationException);
    EXPECT_THROW(account.changePassword("NewPassword456", "short"), DataValidationException);
    account.resetPassword("ResetPass123");
    EXPECT_TRUE(account.authenticate("ResetPass123"));
}

TEST(UserAccountTest, PasswordExpiry) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("user@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-05-15", address, contact);
    UserAccount account("olduser", "Password123", person);
    EXPECT_FALSE(account.isPasswordExpired()); //false for new account
}

// ==================== Integration Tests ====================
TEST(PersonsIntegrationTest, CompletePersonSystem) {
    // Create address and contact
    auto address = std::make_shared<Address>("789 Business Blvd", "Metropolis", "54321", "USA");
    auto contact = std::make_shared<ContactInfo>("biz@company.com", "+1987654321");
    // Create person
    auto person = std::make_shared<Person>("P100", "Alice", "Wonderland", "1988-03-25", address, contact);
    // Create customer from person
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    Customer customer("P100", "Alice", "Wonderland", "1988-03-25", address, contact,
                     "CUST100", gold, "2024-01-01");
    // Create employee from same person
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    Employee employee("P100", "Alice", "Wonderland", "1988-03-25", address, contact,
                     "EMP100", manager, "2023-06-15", 50000.0, "Operations");
    // Create user account
    UserAccount account("alicew", "SecureAlice123", person);
    // Test customer operations
    customer.addPurchase(2000.0);
    customer.addLoyaltyPoints(100);
    EXPECT_DOUBLE_EQ(customer.calculateDiscount(), 10.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 2100);
    // Test employee operations
    EXPECT_TRUE(employee.canManageInventory());
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 75000.0); // 50000 * 1.5
    // Test authentication
    EXPECT_TRUE(account.authenticate("SecureAlice123"));
    EXPECT_EQ(account.getPerson()->getFullName(), "Alice Wonderland");
    // Verify all objects are properly linked
    EXPECT_EQ(customer.getFullName(), "Alice Wonderland");
    EXPECT_EQ(employee.getFullName(), "Alice Wonderland");
    EXPECT_EQ(account.getPerson()->getFullName(), "Alice Wonderland");
}

TEST(PersonsIntegrationTest, BusinessRules) {
    auto address = std::make_shared<Address>("123 Test St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person minor("PMIN", "Child", "Minor", "2010-01-01", address, contact);
    EXPECT_FALSE(minor.isAdult());
    Person adult("PADT", "Adult", "Person", "2000-01-01", address, contact);
    EXPECT_TRUE(adult.isAdult());
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("PCUST", "Test", "Customer", "1990-01-01", address, contact,
                     "CUST999", regular, "2024-01-01");
    customer.addPurchase(500.0);
    EXPECT_FALSE(customer.isEligibleForUpgrade());
    customer.addPurchase(600.0);
    EXPECT_TRUE(customer.isEligibleForUpgrade());
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
}

// ==================== Edge Case Tests ====================
TEST(PersonsEdgeCasesTest, BoundaryConditions) {
    auto address = std::make_shared<Address>("A", "B", "1", "C");
    auto contact = std::make_shared<ContactInfo>("a@b.c", "+1234567");
    EXPECT_NO_THROW(
        Person person("P1", "A", "B", "2000-01-01", address, contact)
    );
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P1", "A", "B", "2000-01-01", address, contact,
                     "C1", regular, "2024-01-01");
    customer.addPurchase(999999.99);
    EXPECT_DOUBLE_EQ(customer.getTotalPurchases(), 999999.99);
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EXPECT_NO_THROW(
        Employee employee("P1", "A", "B", "2000-01-01", address, contact,
                         "E1", worker, "2024-01-01", 0.0, "Dept")
    );
}

TEST(PersonsEdgeCasesTest, ErrorConditions) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EXPECT_THROW(
        Person person("", "John", "Doe", "1990-01-01", address, contact),
        DataValidationException
    );
    CustomerCategory platinum(CustomerCategory::Category::PLATINUM);
    Customer customer("P1", "John", "Doe", "1990-01-01", address, contact,
                     "C1", platinum, "2024-01-01");
    customer.addPurchase(100000.0);
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Platinum");
    auto person = std::make_shared<Person>("P1", "John", "Doe", "1990-01-01", address, contact);
    EXPECT_THROW(
        UserAccount account("user", "weak", person),
        DataValidationException
    );
}

// ==================== Performance Tests ====================
TEST(PersonsPerformanceTest, MultipleObjectCreation) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    for (int i = 0; i < 100; i++) {
        std::string id = "P" + std::to_string(i);
        EXPECT_NO_THROW(
            Person person(id, "First" + std::to_string(i), "Last" + std::to_string(i), 
                         "1990-01-01", address, contact)
        );
    }
}