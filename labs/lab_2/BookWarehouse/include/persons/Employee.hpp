/**
 * @file Employee.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Employee class for working with employees
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>
#include <memory>
#include "persons/Person.hpp"
#include "persons/EmployeeRole.hpp"

/**
 * @class Employee
 * @brief Class for working with employees in the book warehouse system
 * 
 * Extends Person class with employee-specific functionality including
 * role management, salary information, and employment details.
 */
class Employee : public Person {
private:
    std::string employeeId;                  ///< Unique employee identifier
    EmployeeRole role;                       ///< Employee role and permissions
    std::string hireDate;                    ///< Date when employee was hired
    double baseSalary;                       ///< Base salary amount
    std::string department;                  ///< Department assignment
    bool isActive;                           ///< Employment status

    /**
     * @brief Private method to validate employee ID
     * 
     * @param employeeId constant reference to the string containing employee ID to validate
     * 
     * @return true if employee ID is valid
     * @return false if employee ID is invalid
     */
    bool isValidEmployeeId(const std::string& employeeId) const;

    /**
     * @brief Private method to validate salary amount
     * 
     * @param salary double value containing salary to validate
     * 
     * @return true if salary is valid
     * @return false if salary is invalid
     */
    bool isValidSalary(double salary) const;

    /**
     * @brief Private method to validate department name
     * 
     * @param department constant reference to the string containing department to validate
     * 
     * @return true if department is valid
     * @return false if department is invalid
     */
    bool isValidDepartment(const std::string& department) const;

public:
    /**
     * @brief Construct a new Employee object
     * 
     * @param personId constant reference to the string containing person identifier
     * @param firstName constant reference to the string containing first name
     * @param lastName constant reference to the string containing last name
     * @param dateOfBirth constant reference to the string containing date of birth
     * @param address shared pointer to the Address object
     * @param contactInfo shared pointer to the ContactInfo object
     * @param employeeId constant reference to the string containing employee identifier
     * @param role EmployeeRole value containing employee role
     * @param hireDate constant reference to the string containing hire date
     * @param baseSalary double value containing base salary
     * @param department constant reference to the string containing department
     */
    Employee(const std::string& personId, const std::string& firstName, const std::string& lastName,
             const std::string& dateOfBirth, std::shared_ptr<Address> address,
             std::shared_ptr<ContactInfo> contactInfo, const std::string& employeeId,
             EmployeeRole role, const std::string& hireDate, double baseSalary,
             const std::string& department);

    /**
     * @brief Get the employee identifier
     * 
     * @return std::string containing employee identifier
     */
    std::string getEmployeeId() const noexcept;

    /**
     * @brief Get the employee role
     * 
     * @return EmployeeRole containing employee role
     */
    EmployeeRole getRole() const noexcept;

    /**
     * @brief Get the hire date
     * 
     * @return std::string containing hire date
     */
    std::string getHireDate() const noexcept;

    /**
     * @brief Get the base salary
     * 
     * @return double containing base salary
     */
    double getBaseSalary() const noexcept;

    /**
     * @brief Get the department
     * 
     * @return std::string containing department
     */
    std::string getDepartment() const noexcept;

    /**
     * @brief Check if employee is active
     * 
     * @return true if employee is active
     * @return false if employee is not active
     */
    bool isEmplActive() const noexcept;

    /**
     * @brief Set the employee role
     * 
     * @param role EmployeeRole value containing new role
     */
    void setRole(EmployeeRole role) noexcept;

    /**
     * @brief Set the base salary
     * 
     * @param salary double value containing new base salary
     */
    void setBaseSalary(double salary);

    /**
     * @brief Set the department
     * 
     * @param department constant reference to the string containing new department
     */
    void setDepartment(const std::string& department);

    /**
     * @brief Set the employee active status
     * 
     * @param active boolean value containing new active status
     */
    void setActive(bool active) noexcept;

    /**
     * @brief Calculate current salary with role multiplier
     * 
     * @return double containing calculated salary
     */
    double calculateSalary() const noexcept;

    /**
     * @brief Calculate years of service
     * 
     * @return int containing years of service
     */
    int calculateYearsOfService() const;

    /**
     * @brief Check if employee can manage inventory
     * 
     * @return true if employee can manage inventory
     * @return false if employee cannot manage inventory
     */
    bool canManageInventory() const noexcept;

    /**
     * @brief Check if employee can process sales
     * 
     * @return true if employee can process sales
     * @return false if employee cannot process sales
     */
    bool canProcessSales() const noexcept;

    /**
     * @brief Check if employee can manage users
     * 
     * @return true if employee can manage users
     * @return false if employee cannot manage users
     */
    bool canManageUsers() const noexcept;

    /**
     * @brief Promote employee to new role
     * 
     * @param newRole EmployeeRole value containing new role
     * @param newSalary double value containing new salary
     */
    void promote(EmployeeRole newRole, double newSalary);

    /**
     * @brief Get employee information
     * 
     * @return std::string containing formatted employee information
     */
    std::string getInfo() const noexcept override;

    /**
     * @brief Equality comparison operator for employees
     * 
     * @param other constant reference to the employee to compare with
     * 
     * @return true if employees are equal
     * @return false if employees are not equal
     */
    bool operator==(const Employee& other) const noexcept;

    /**
     * @brief Inequality comparison operator for employees
     * 
     * @param other constant reference to the employee to compare with
     * 
     * @return true if employees are not equal
     * @return false if employees are equal
     */
    bool operator!=(const Employee& other) const noexcept;
};