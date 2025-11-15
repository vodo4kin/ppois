#include <gtest/gtest.h>
#include <memory>
#include "exceptions/WarehouseExceptions.hpp"
#include "EmployeeRole.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "UserAccount.hpp"

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

TEST(AddressTest, AddressEdgeCases) {
    EXPECT_NO_THROW(Address addr("A", "B", "1", "C"));
    Address minAddr("A", "B", "1", "C");
    EXPECT_TRUE(minAddr.isComplete());
    std::string longStreet(100, 'a');
    std::string longCity(50, 'b');
    std::string longPostal(20, 'c');
    std::string longCountry(30, 'd');
    EXPECT_THROW(Address addr(longStreet, longCity, longPostal, longCountry), DataValidationException);
}

TEST(AddressTest, AddressEquality) {
    Address addr1("123 St", "City", "12345", "Country");
    Address addr2("123 St", "City", "12345", "Country");
    Address addr3("456 St", "City", "12345", "Country");
    EXPECT_EQ(addr1, addr2);
    EXPECT_NE(addr1, addr3);
    EXPECT_EQ(addr1, addr1);
}

TEST(AddressTest, AddressInfo) {
    Address addr("123 Main St", "Springfield", "12345", "USA");
    std::string info = addr.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("123 Main St"), std::string::npos);
}

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

TEST(ContactInfoTest, ContactEdgeCases) {
    EXPECT_NO_THROW(ContactInfo info("a@b.c", "+1234567"));
    ContactInfo emptyInfo("", "");
    EXPECT_FALSE(emptyInfo.hasValidContact());
    EXPECT_EQ(emptyInfo.getPrimaryContact(), "No contact information");
    ContactInfo onlyEmail("test@test.com", "");
    EXPECT_TRUE(onlyEmail.hasEmail());
    EXPECT_FALSE(onlyEmail.hasPhoneNumber());
    ContactInfo onlyPhone("", "+1234567890");
    EXPECT_FALSE(onlyPhone.hasEmail());
    EXPECT_TRUE(onlyPhone.hasPhoneNumber());
}

TEST(ContactInfoTest, ContactEquality) {
    ContactInfo info1("test@test.com", "+1234567890");
    ContactInfo info2("test@test.com", "+1234567890");
    ContactInfo info3("different@test.com", "+1234567890");
    EXPECT_EQ(info1, info2);
    EXPECT_NE(info1, info3);
}

TEST(CustomerCategoryTest, AllCategoryTypes) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory silver(CustomerCategory::Category::SILVER);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    CustomerCategory platinum(CustomerCategory::Category::PLATINUM);
    CustomerCategory student(CustomerCategory::Category::STUDENT);
    CustomerCategory corporate(CustomerCategory::Category::CORPORATE);
    EXPECT_EQ(regular.toString(), "Regular");
    EXPECT_EQ(silver.toString(), "Silver");
    EXPECT_EQ(gold.toString(), "Gold");
    EXPECT_EQ(platinum.toString(), "Platinum");
    EXPECT_EQ(student.toString(), "Student");
    EXPECT_EQ(corporate.toString(), "Corporate");
}

TEST(CustomerCategoryTest, DiscountPercentages) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory silver(CustomerCategory::Category::SILVER);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    CustomerCategory platinum(CustomerCategory::Category::PLATINUM);
    EXPECT_DOUBLE_EQ(regular.getDiscountPercentage(), 0.0);
    EXPECT_DOUBLE_EQ(silver.getDiscountPercentage(), 5.0);
    EXPECT_DOUBLE_EQ(gold.getDiscountPercentage(), 10.0);
    EXPECT_DOUBLE_EQ(platinum.getDiscountPercentage(), 15.0);
}

TEST(CustomerCategoryTest, Benefits) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    CustomerCategory platinum(CustomerCategory::Category::PLATINUM);
    CustomerCategory corporate(CustomerCategory::Category::CORPORATE);
    EXPECT_FALSE(regular.hasFreeShipping());
    EXPECT_TRUE(gold.hasFreeShipping());
    EXPECT_TRUE(platinum.hasFreeShipping());
    EXPECT_TRUE(corporate.hasFreeShipping());
    EXPECT_FALSE(regular.hasPrioritySupport());
    EXPECT_FALSE(gold.hasPrioritySupport());
    EXPECT_TRUE(platinum.hasPrioritySupport());
    EXPECT_TRUE(corporate.hasPrioritySupport());
    EXPECT_FALSE(regular.isEligibleForLoyaltyProgram());
    EXPECT_TRUE(gold.isEligibleForLoyaltyProgram());
}

TEST(CustomerCategoryTest, UpgradeLogic) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory silver(CustomerCategory::Category::SILVER);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    EXPECT_TRUE(regular.canUpgrade(1500.0));
    EXPECT_FALSE(regular.canUpgrade(500.0));
    EXPECT_TRUE(silver.canUpgrade(6000.0));
    EXPECT_FALSE(silver.canUpgrade(4000.0));
    EXPECT_TRUE(gold.canUpgrade(16000.0));
    EXPECT_FALSE(gold.canUpgrade(14000.0));
    EXPECT_EQ(regular.getNextCategory(), CustomerCategory::Category::SILVER);
    EXPECT_EQ(silver.getNextCategory(), CustomerCategory::Category::GOLD);
    EXPECT_EQ(gold.getNextCategory(), CustomerCategory::Category::PLATINUM);
}

TEST(CustomerCategoryTest, UpgradeThresholds) {
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    CustomerCategory silver(CustomerCategory::Category::SILVER);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    CustomerCategory platinum(CustomerCategory::Category::PLATINUM);
    EXPECT_DOUBLE_EQ(regular.getUpgradeThreshold(), 1000.0);
    EXPECT_DOUBLE_EQ(silver.getUpgradeThreshold(), 5000.0);
    EXPECT_DOUBLE_EQ(gold.getUpgradeThreshold(), 15000.0);
    EXPECT_DOUBLE_EQ(platinum.getUpgradeThreshold(), 50000.0);
}

TEST(CustomerCategoryTest, CategoryEquality) {
    CustomerCategory cat1(CustomerCategory::Category::GOLD);
    CustomerCategory cat2(CustomerCategory::Category::GOLD);
    CustomerCategory cat3(CustomerCategory::Category::SILVER);
    EXPECT_EQ(cat1, cat2);
    EXPECT_NE(cat1, cat3);
}

TEST(EmployeeRoleTest, AllRoleTypes) {
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    EmployeeRole supervisor(EmployeeRole::Role::SUPERVISOR);
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    EmployeeRole hr(EmployeeRole::Role::HR_MANAGER);
    EmployeeRole finance(EmployeeRole::Role::FINANCE_OFFICER);
    EmployeeRole it(EmployeeRole::Role::IT_SUPPORT);
    EXPECT_EQ(worker.toString(), "Warehouse Worker");
    EXPECT_EQ(manager.toString(), "Inventory Manager");
    EXPECT_EQ(cashier.toString(), "Cashier");
    EXPECT_EQ(supervisor.toString(), "Supervisor");
    EXPECT_EQ(admin.toString(), "Administrator");
    EXPECT_EQ(hr.toString(), "HR Manager");
    EXPECT_EQ(finance.toString(), "Finance Officer");
    EXPECT_EQ(it.toString(), "IT Support");
}

TEST(EmployeeRoleTest, RolePermissions) {
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    EXPECT_FALSE(worker.canManageInventory());
    EXPECT_TRUE(manager.canManageInventory());
    EXPECT_FALSE(cashier.canManageInventory());
    EXPECT_TRUE(admin.canManageInventory());
    EXPECT_FALSE(worker.canProcessSales());
    EXPECT_FALSE(manager.canProcessSales());
    EXPECT_TRUE(cashier.canProcessSales());
    EXPECT_TRUE(admin.canProcessSales());
    EXPECT_FALSE(worker.canManageUsers());
    EXPECT_FALSE(manager.canManageUsers());
    EXPECT_FALSE(cashier.canManageUsers());
    EXPECT_TRUE(admin.canManageUsers());
}

TEST(EmployeeRoleTest, AccessLevels) {
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    EmployeeRole supervisor(EmployeeRole::Role::SUPERVISOR);
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    EXPECT_EQ(worker.getAccessLevel(), 1);
    EXPECT_EQ(cashier.getAccessLevel(), 2);
    EXPECT_EQ(manager.getAccessLevel(), 3);
    EXPECT_EQ(supervisor.getAccessLevel(), 6);
    EXPECT_EQ(admin.getAccessLevel(), 10);
}

TEST(EmployeeRoleTest, SalaryMultipliers) {
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    EmployeeRole itSupport(EmployeeRole::Role::IT_SUPPORT);
    EmployeeRole financeOfficer(EmployeeRole::Role::FINANCE_OFFICER);
    EmployeeRole supervisor(EmployeeRole::Role::SUPERVISOR);
    EmployeeRole hrManager(EmployeeRole::Role::HR_MANAGER);
    EXPECT_DOUBLE_EQ(worker.getSalaryMultiplier(), 1.0);
    EXPECT_DOUBLE_EQ(cashier.getSalaryMultiplier(), 1.2);
    EXPECT_DOUBLE_EQ(manager.getSalaryMultiplier(), 1.5);
    EXPECT_DOUBLE_EQ(itSupport.getSalaryMultiplier(), 1.4);
    EXPECT_DOUBLE_EQ(financeOfficer.getSalaryMultiplier(), 1.6);
    EXPECT_DOUBLE_EQ(supervisor.getSalaryMultiplier(), 1.8);
    EXPECT_DOUBLE_EQ(hrManager.getSalaryMultiplier(), 1.7);
    EXPECT_DOUBLE_EQ(admin.getSalaryMultiplier(), 2.0);
}

TEST(EmployeeRoleTest, AdditionalPermissions) {
    EmployeeRole finance(EmployeeRole::Role::FINANCE_OFFICER);
    EmployeeRole supervisor(EmployeeRole::Role::SUPERVISOR);
    EmployeeRole hr(EmployeeRole::Role::HR_MANAGER);
    EmployeeRole it(EmployeeRole::Role::IT_SUPPORT);
    EXPECT_TRUE(finance.canViewFinancialReports());
    EXPECT_TRUE(supervisor.canViewFinancialReports());
    EXPECT_TRUE(hr.canManageEmployees());
    EXPECT_TRUE(it.requiresSpecialTraining());
}

TEST(EmployeeRoleTest, RoleEquality) {
    EmployeeRole role1(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole role2(EmployeeRole::Role::WAREHOUSE_WORKER);
    EmployeeRole role3(EmployeeRole::Role::INVENTORY_MANAGER);
    EXPECT_EQ(role1, role2);
    EXPECT_NE(role1, role3);
}

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

TEST(PersonTest, InvalidPerson) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EXPECT_THROW(Person person("", "John", "Doe", "1990-01-01", address, contact), DataValidationException);
    EXPECT_THROW(Person person("P001", "", "Doe", "1990-01-01", address, contact), DataValidationException);
    EXPECT_THROW(Person person("P001", "John", "", "1990-01-01", address, contact), DataValidationException);
    EXPECT_THROW(Person person("P001", "John", "Doe", "invalid-date", address, contact), DataValidationException);
}

TEST(PersonTest, PersonOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person person("P003", "Bob", "Johnson", "2000-01-01", address, contact);
    person.setFirstName("Robert");
    person.setLastName("Johnsonson");
    auto newAddress = std::make_shared<Address>("456 Oak Ave", "Shelbyville", "67890", "Canada");
    person.setAddress(newAddress);
    auto newContact = std::make_shared<ContactInfo>("new@test.com", "+9999999999");
    person.setContactInfo(newContact);
    EXPECT_EQ(person.getFirstName(), "Robert");
    EXPECT_EQ(person.getLastName(), "Johnsonson");
    EXPECT_EQ(person.getFullName(), "Robert Johnsonson");
    EXPECT_EQ(person.getAddress()->getCity(), "Shelbyville");
    EXPECT_EQ(person.getContactInfo()->getEmail(), "new@test.com");
}

TEST(PersonTest, AgeCalculations) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person minor("PM001", "Child", "Minor", "2010-01-01", address, contact);
    EXPECT_FALSE(minor.isAdult());
    Person adult("PA001", "Adult", "Person", "2000-01-01", address, contact);
    EXPECT_TRUE(adult.isAdult());
    Person newborn("PN001", "New", "Born", "2023-01-01", address, contact);
    EXPECT_FALSE(newborn.isAdult());
}

TEST(PersonTest, PersonInfo) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person person("P004", "Alice", "Wonderland", "1988-03-25", address, contact);
    std::string info = person.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("Alice Wonderland"), std::string::npos);
    EXPECT_NE(info.find("123 Main St"), std::string::npos);
}

TEST(PersonTest, PersonEquality) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    Person person1("P001", "John", "Doe", "1990-01-01", address, contact);
    Person person2("P001", "Jane", "Smith", "1985-01-01", address, contact);
    Person person3("P002", "John", "Doe", "1990-01-01", address, contact);
    EXPECT_EQ(person1, person2);
    EXPECT_NE(person1, person3);
}

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

TEST(CustomerTest, InvalidCustomer) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory category(CustomerCategory::Category::REGULAR);
    EXPECT_THROW(Customer customer("P001", "John", "Doe", "1990-01-01", address, contact,
                                  "", category, "2024-01-01"), DataValidationException);
    EXPECT_THROW(Customer customer("P001", "John", "Doe", "1990-01-01", address, contact,
                                  "CUST001", category, "invalid-date"), DataValidationException);
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
    EXPECT_EQ(customer.getLoyaltyPoints(), 150);
    customer.redeemLoyaltyPoints(30);
    EXPECT_EQ(customer.getLoyaltyPoints(), 120);
    EXPECT_THROW(customer.redeemLoyaltyPoints(200), InsufficientStockException);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    customer.setCategory(gold);
    EXPECT_DOUBLE_EQ(customer.calculateDiscount(), 10.0);
    customer.setActive(false);
    EXPECT_FALSE(customer.isCustActive());
}

TEST(CustomerTest, PurchaseValidation) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P001", "John", "Doe", "1990-01-01", address, contact,
                     "CUST001", regular, "2024-01-01");
    EXPECT_THROW(customer.addPurchase(-100.0), DataValidationException);
    EXPECT_NO_THROW(customer.addPurchase(0.0));
    EXPECT_NO_THROW(customer.addPurchase(999999.99));
}

TEST(CustomerTest, CategoryUpgrade) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory regular(CustomerCategory::Category::REGULAR);
    Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                     "CUST001", regular, "2024-01-15");
    customer.addPurchase(500.0);
    EXPECT_FALSE(customer.isEligibleForUpgrade());
    customer.addPurchase(600.0); // Total 1100, above 1000 threshold
    EXPECT_TRUE(customer.isEligibleForUpgrade());
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Silver");
    customer.addPurchase(5000.0); // Total 6100, above 5000 threshold
    customer.upgradeCategory();
    EXPECT_EQ(customer.getCategory().toString(), "Gold");
}

TEST(CustomerTest, CustomerInfo) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    Customer customer("P001", "John", "Doe", "1990-05-15", address, contact,
                     "CUST001", gold, "2024-01-15");
    customer.addPurchase(1500.0);
    customer.addLoyaltyPoints(100);
    std::string info = customer.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("CUST001"), std::string::npos);
    EXPECT_NE(info.find("Gold"), std::string::npos);
    EXPECT_NE(info.find("1500"), std::string::npos);
}

TEST(CustomerTest, CustomerEquality) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    CustomerCategory category(CustomerCategory::Category::REGULAR);
    Customer cust1("P001", "John", "Doe", "1990-01-01", address, contact,
                  "CUST001", category, "2024-01-01");
    Customer cust2("P002", "Jane", "Smith", "1985-01-01", address, contact,
                  "CUST001", category, "2024-01-01");
    Customer cust3("P001", "John", "Doe", "1990-01-01", address, contact,
                  "CUST002", category, "2024-01-01");
    EXPECT_EQ(cust1, cust2);
    EXPECT_NE(cust1, cust3);
}

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

TEST(EmployeeTest, InvalidEmployee) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole role(EmployeeRole::Role::WAREHOUSE_WORKER);
    EXPECT_THROW(Employee employee("P001", "John", "Doe", "1990-01-01", address, contact,
                                  "", role, "2024-01-01", 30000.0, "Dept"), DataValidationException);
    EXPECT_THROW(Employee employee("P001", "John", "Doe", "1990-01-01", address, contact,
                                  "EMP001", role, "invalid-date", 30000.0, "Dept"), DataValidationException);
    EXPECT_THROW(Employee employee("P001", "John", "Doe", "1990-01-01", address, contact,
                                  "EMP001", role, "2024-01-01", -1000.0, "Dept"), DataValidationException);
    EXPECT_THROW(Employee employee("P001", "John", "Doe", "1990-01-01", address, contact,
                                  "EMP001", role, "2024-01-01", 30000.0, ""), DataValidationException);
}

TEST(EmployeeTest, EmployeeOperations) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole worker(EmployeeRole::Role::WAREHOUSE_WORKER);
    Employee employee("P001", "John", "Doe", "1990-05-15", address, contact,
                     "EMP001", worker, "2020-01-15", 30000.0, "Warehouse");
    EXPECT_GE(employee.calculateYearsOfService(), 4);
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 30000.0);
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    employee.promote(manager, 45000.0);
    EXPECT_EQ(employee.getRole().toString(), "Inventory Manager");
    EXPECT_DOUBLE_EQ(employee.getBaseSalary(), 45000.0);
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 67500.0);
    employee.setDepartment("New Department");
    EXPECT_EQ(employee.getDepartment(), "New Department");
    employee.setActive(false);
    EXPECT_FALSE(employee.isEmplActive());
}

TEST(EmployeeTest, SalaryCalculations) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    Employee cashierEmp("P001", "Cash", "Ier", "1995-01-01", address, contact,
                       "EMP001", cashier, "2024-01-15", 25000.0, "Sales");
    EXPECT_DOUBLE_EQ(cashierEmp.calculateSalary(), 30000.0); // 25000 * 1.2
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    Employee adminEmp("P002", "Admin", "User", "1980-01-01", address, contact,
                     "EMP002", admin, "2024-01-15", 60000.0, "IT");
    EXPECT_DOUBLE_EQ(adminEmp.calculateSalary(), 120000.0); // 60000 * 2.0
}

TEST(EmployeeTest, PermissionChecks) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole cashier(EmployeeRole::Role::CASHIER);
    Employee cashierEmp("P001", "Cash", "Ier", "1995-01-01", address, contact,
                       "EMP001", cashier, "2024-01-15", 25000.0, "Sales");
    EXPECT_TRUE(cashierEmp.canProcessSales());
    EXPECT_FALSE(cashierEmp.canManageInventory());
    EXPECT_FALSE(cashierEmp.canManageUsers());
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    Employee managerEmp("P002", "Manager", "User", "1985-01-01", address, contact,
                       "EMP002", manager, "2024-01-15", 50000.0, "Warehouse");
    EXPECT_TRUE(managerEmp.canManageInventory());
    EXPECT_FALSE(managerEmp.canManageUsers());
    EmployeeRole admin(EmployeeRole::Role::ADMINISTRATOR);
    Employee adminEmp("P003", "Admin", "User", "1980-01-01", address, contact,
                     "EMP003", admin, "2024-01-15", 60000.0, "IT");
    EXPECT_TRUE(adminEmp.canManageInventory());
    EXPECT_TRUE(adminEmp.canManageUsers());
}

TEST(EmployeeTest, EmployeeInfo) {
    auto address = std::make_shared<Address>("123 Main St", "Springfield", "12345", "USA");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole role(EmployeeRole::Role::INVENTORY_MANAGER);
    Employee employee("P001", "John", "Doe", "1990-05-15", address, contact,
                     "EMP001", role, "2020-01-15", 50000.0, "Warehouse");
    std::string info = employee.getInfo();
    EXPECT_FALSE(info.empty());
    EXPECT_NE(info.find("EMP001"), std::string::npos);
    EXPECT_NE(info.find("Inventory Manager"), std::string::npos);
    EXPECT_NE(info.find("75000"), std::string::npos); // 50000 * 1.5
}

TEST(EmployeeTest, EmployeeEquality) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    EmployeeRole role(EmployeeRole::Role::WAREHOUSE_WORKER);
    Employee emp1("P001", "John", "Doe", "1990-01-01", address, contact,
                 "EMP001", role, "2024-01-01", 30000.0, "Dept");
    Employee emp2("P002", "Jane", "Smith", "1985-01-01", address, contact,
                 "EMP001", role, "2024-01-01", 35000.0, "Dept");
    Employee emp3("P001", "John", "Doe", "1990-01-01", address, contact,
                 "EMP002", role, "2024-01-01", 30000.0, "Dept");
    EXPECT_EQ(emp1, emp2);
    EXPECT_NE(emp1, emp3);
}

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

TEST(UserAccountTest, InvalidUserAccount) {
    auto address = std::make_shared<Address>("123 St", "City", "12345", "Country");
    auto contact = std::make_shared<ContactInfo>("test@test.com", "+1234567890");
    auto person = std::make_shared<Person>("P001", "John", "Doe", "1990-01-01", address, contact);
    EXPECT_THROW(UserAccount account("", "Password123", person), DataValidationException);
    EXPECT_THROW(UserAccount account("user", "weak", person), DataValidationException);
    EXPECT_THROW(UserAccount account("user", "Password123", nullptr), DataValidationException);
}

TEST(PersonsIntegrationTest, CompletePersonSystem) {
    auto address = std::make_shared<Address>("789 Business Blvd", "Metropolis", "54321", "USA");
    auto contact = std::make_shared<ContactInfo>("biz@company.com", "+1987654321");
    auto person = std::make_shared<Person>("P100", "Alice", "Wonderland", "1988-03-25", address, contact);
    CustomerCategory gold(CustomerCategory::Category::GOLD);
    Customer customer("P100", "Alice", "Wonderland", "1988-03-25", address, contact,
                     "CUST100", gold, "2024-01-01");
    EmployeeRole manager(EmployeeRole::Role::INVENTORY_MANAGER);
    Employee employee("P100", "Alice", "Wonderland", "1988-03-25", address, contact,
                     "EMP100", manager, "2023-06-15", 50000.0, "Operations");
    UserAccount account("alicew", "SecureAlice123", person);
    customer.addPurchase(2000.0);
    customer.addLoyaltyPoints(100);
    EXPECT_DOUBLE_EQ(customer.calculateDiscount(), 10.0);
    EXPECT_EQ(customer.getLoyaltyPoints(), 2100);
    EXPECT_TRUE(employee.canManageInventory());
    EXPECT_DOUBLE_EQ(employee.calculateSalary(), 75000.0); // 50000 * 1.5
    EXPECT_TRUE(account.authenticate("SecureAlice123"));
    EXPECT_EQ(account.getPerson()->getFullName(), "Alice Wonderland");
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