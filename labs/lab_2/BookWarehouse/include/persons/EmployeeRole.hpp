/**
 * @file EmployeeRole.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file with employee role enumeration and utilities
 * @version 0.1
 * @date 2025-10-11
 * 
 * 
 */

#pragma once
#include <string>

/**
 * @class EmployeeRole
 * @brief Class for working with employee roles and permissions
 * 
 * Defines employee roles with associated permissions, access levels,
 * and responsibilities. Provides role validation and permission checking.
 */
class EmployeeRole {
public:
    /**
     * @enum Role
     * @brief Enumeration of employee roles
     */
    enum class Role {
        WAREHOUSE_WORKER,   ///< Basic warehouse operations
        INVENTORY_MANAGER,  ///< Inventory management and stock control
        CASHIER,            ///< Point of sale and customer transactions
        SUPERVISOR,         ///< Team supervision and operational oversight
        ADMINISTRATOR,      ///< System administration and user management
        HR_MANAGER,         ///< Human resources and personnel management
        FINANCE_OFFICER,    ///< Financial operations and reporting
        IT_SUPPORT          ///< Technical support and system maintenance
    };

private:
    Role role;  ///< Current employee role

public:
    /**
     * @brief Construct a new EmployeeRole object
     * 
     * @param role Role value containing employee role
     */
    explicit EmployeeRole(Role role) noexcept;

    /**
     * @brief Get the role
     * 
     * @return Role containing current employee role
     */
    Role getRole() const noexcept;

    /**
     * @brief Convert role to string representation
     * 
     * @return std::string containing role description
     */
    std::string toString() const noexcept;

    /**
     * @brief Get access level for the role
     * 
     * @return int containing access level (1-10, higher means more access)
     */
    int getAccessLevel() const noexcept;

    /**
     * @brief Check if role can manage inventory
     * 
     * @return true if role can manage inventory
     * @return false if role cannot manage inventory
     */
    bool canManageInventory() const noexcept;

    /**
     * @brief Check if role can process sales
     * 
     * @return true if role can process sales
     * @return false if role cannot process sales
     */
    bool canProcessSales() const noexcept;

    /**
     * @brief Check if role can manage users
     * 
     * @return true if role can manage users
     * @return false if role cannot manage users
     */
    bool canManageUsers() const noexcept;

    /**
     * @brief Check if role can view financial reports
     * 
     * @return true if role can view financial reports
     * @return false if role cannot view financial reports
     */
    bool canViewFinancialReports() const noexcept;

    /**
     * @brief Check if role can approve orders
     * 
     * @return true if role can approve orders
     * @return false if role cannot approve orders
     */
    bool canApproveOrders() const noexcept;

    /**
     * @brief Check if role can manage employees
     * 
     * @return true if role can manage employees
     * @return false if role cannot manage employees
     */
    bool canManageEmployees() const noexcept;

    /**
     * @brief Get base salary multiplier for the role
     * 
     * @return double containing salary multiplier
     */
    double getSalaryMultiplier() const noexcept;

    /**
     * @brief Check if role requires special training
     * 
     * @return true if role requires special training
     * @return false if role does not require special training
     */
    bool requiresSpecialTraining() const noexcept;

    /**
     * @brief Equality comparison operator for employee roles
     * 
     * @param other constant reference to the employee role to compare with
     * 
     * @return true if employee roles are equal
     * @return false if employee roles are not equal
     */
    bool operator==(const EmployeeRole& other) const noexcept;

    /**
     * @brief Inequality comparison operator for employee roles
     * 
     * @param other constant reference to the employee role to compare with
     * 
     * @return true if employee roles are not equal
     * @return false if employee roles are equal
     */
    bool operator!=(const EmployeeRole& other) const noexcept;
};