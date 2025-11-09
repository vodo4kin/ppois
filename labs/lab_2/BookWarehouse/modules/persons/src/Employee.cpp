#include "Employee.hpp"
#include "utils/Utils.hpp"
#include "exceptions/WarehouseExceptions.hpp"
#include "config/PersonConfig.hpp"

bool Employee::isValidSalary(double salary) const {
    return salary >= 0.0;
}

bool Employee::isValidEmployeeId(const std::string& employeeId) const {
    return !employeeId.empty() && employeeId.length() <= PersonConfig::Employee::MAX_EMPLOYEE_ID_LENGTH && StringValidation::isValidName(employeeId);
}

bool Employee::isValidDepartment(const std::string& department) const {
    return StringValidation::isValidName(department, PersonConfig::Employee::MAX_DEPARTMENT_LENGTH);
}

Employee::Employee(const std::string& personId, const std::string& firstName, const std::string& lastName,
                   const std::string& dateOfBirth, std::shared_ptr<Address> address,
                   std::shared_ptr<ContactInfo> contactInfo, const std::string& employeeId,
                   EmployeeRole role, const std::string& hireDate, double baseSalary,
                   const std::string& department)
    : Person(personId, firstName, lastName, dateOfBirth, address, contactInfo),
      role(role) {
    if (!isValidEmployeeId(employeeId)) {
        throw DataValidationException("Invalid employee ID: " + employeeId);
    }
    if (!StringValidation::isValidDate(hireDate)) {
        throw DataValidationException("Invalid hire date: " + hireDate);
    }
    if (!isValidSalary(baseSalary)) {
        throw DataValidationException("Invalid base salary: " + std::to_string(baseSalary));
    }
    if (!isValidDepartment(department)) {
        throw DataValidationException("Invalid department: " + department);
    }
    this->employeeId = employeeId;
    this->hireDate = hireDate;
    this->baseSalary = baseSalary;
    this->department = department;
    this->isActive = true;
}

std::string Employee::getEmployeeId() const noexcept {
    return employeeId;
}

EmployeeRole Employee::getRole() const noexcept {
    return role;
}

std::string Employee::getHireDate() const noexcept {
    return hireDate;
}

double Employee::getBaseSalary() const noexcept {
    return baseSalary;
}

std::string Employee::getDepartment() const noexcept {
    return department;
}

bool Employee::isEmplActive() const noexcept {
    return isActive;
}

void Employee::setRole(EmployeeRole role) noexcept {
    this->role = role;
}

void Employee::setBaseSalary(double salary) {
    if (!isValidSalary(salary)) {
        throw DataValidationException("Invalid salary: " + std::to_string(salary));
    }
    this->baseSalary = salary;
}

void Employee::setDepartment(const std::string& department) {
    if (!isValidDepartment(department)) {
        throw DataValidationException("Invalid department: " + department);
    }
    this->department = department;
}

void Employee::setActive(bool active) noexcept {
    this->isActive = active;
}

double Employee::calculateSalary() const noexcept {
    return baseSalary * role.getSalaryMultiplier();
}

int Employee::calculateYearsOfService() const {
    std::string currentDate = DateUtils::getCurrentDate();
    int hireYear = std::stoi(hireDate.substr(0, 4));
    int currentYear = std::stoi(currentDate.substr(0, 4));
    return currentYear - hireYear;
}

bool Employee::canManageInventory() const noexcept {
    return role.canManageInventory();
}

bool Employee::canProcessSales() const noexcept {
    return role.canProcessSales();
}

bool Employee::canManageUsers() const noexcept {
    return role.canManageUsers();
}

void Employee::promote(EmployeeRole newRole, double newSalary) {
    setRole(newRole);
    setBaseSalary(newSalary);
}

std::string Employee::getInfo() const noexcept {
    std::string info = Person::getInfo();
    info += ", Employee ID: " + employeeId;
    info += ", Role: " + role.toString();
    info += ", Department: " + department;
    info += ", Salary: " + std::to_string(calculateSalary());
    info += ", Years of Service: " + std::to_string(calculateYearsOfService());
    info += ", Active: " + std::string(isActive ? "Yes" : "No");
    return info;
}

bool Employee::operator==(const Employee& other) const noexcept {
    return employeeId == other.employeeId;
}

bool Employee::operator!=(const Employee& other) const noexcept {
    return !(*this == other);
}