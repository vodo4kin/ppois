/**
 * @file Admin.hpp
 * @author George (BSUIR, Gr.421702)
 * @brief Header file of the Admin class for administrator management
 * @version 0.1
 * @date 2025-11-15
 * 
 * 
 */

#pragma once
#include "Customer.hpp"
#include "Booking.hpp"
#include <vector>
#include <string>

/**
 * @class Admin
 * @brief Class representing administrator type user
 * 
 * Extends User with admin-specific properties like permissions and system access.
 * Provides functionality for user management, booking control, and system administration.
 */
class Admin : public User {
public:
    /**
     * @enum Permission
     * @brief Enumeration of administrative permissions
     */
    enum class Permission {
        MANAGE_USERS,                                       ///< Permission to manage users
        MANAGE_BOOKINGS,                                    ///< Permission to manage bookings
        VIEW_REPORTS,                                       ///< Permission to view reports
        SYSTEM_CONFIG,                                      ///< Permission to configure system
        ALL_ACCESS                                          ///< Full system access permission
    };
    
    /**
     * @enum AdminLevel
     * @brief Enumeration of admin privilege levels
     */
    enum class AdminLevel {
        MODERATOR,                                          ///< Moderator level admin
        SUPER_ADMIN                                         ///< Super administrator level
    };

private:
    AdminLevel adminLevel;                                  ///< Admin privilege level
    std::vector<Permission> permissions;                    ///< Collection of granted permissions
    std::string department;                                 ///< Admin department
    
    /**
     * @brief Initialize permissions based on admin level
     */
    void initializePermissions();

public:
    /**
     * @brief Construct a new Admin object
     * 
     * @param name constant reference to the string containing admin name
     * @param email constant reference to the string containing email address
     * @param password constant reference to the string containing password
     * @param birthDate constant reference to the string containing birth date
     * @param level AdminLevel value containing admin level
     * @param department constant reference to the string containing department
     */
    Admin(const std::string& name, const std::string& email, 
        const std::string& password, const std::string& birthDate,
        AdminLevel level = AdminLevel::MODERATOR,
        const std::string& department = "Administration");
    
    /**
     * @brief Get the admin role
     * 
     * @return std::string containing "Admin"
     */
    std::string getUserRole() const override;
    
    /**
     * @brief Get the admin level
     * 
     * @return AdminLevel containing admin level enum value
     */
    AdminLevel getAdminLevel() const noexcept;
    
    /**
     * @brief Get the admin level as string
     * 
     * @return std::string containing admin level description
     */
    std::string getAdminLevelStr() const noexcept;
    
    /**
     * @brief Set the admin level
     * 
     * @param newLevel AdminLevel value containing new admin level
     */
    void setAdminLevel(AdminLevel newLevel);
    
    /**
     * @brief Get the department
     * 
     * @return std::string containing department name
     */
    std::string getDepartment() const noexcept;
    
    /**
     * @brief Set the department
     * 
     * @param newDepartment constant reference to the string containing new department
     */
    void setDepartment(const std::string& newDepartment);
    
    /**
     * @brief Check if admin has specific permission
     * 
     * @param permission Permission value containing permission to check
     * 
     * @return true if permission is granted
     * @return false if permission is not granted
     */
    bool hasPermission(Permission permission) const noexcept;
    
    /**
     * @brief Grant permission to admin
     * 
     * @param permission Permission value containing permission to grant
     */
    void grantPermission(Permission permission);
    
    /**
     * @brief Revoke permission from admin
     * 
     * @param permission Permission value containing permission to revoke
     */
    void revokePermission(Permission permission);
    
    /**
     * @brief Get all permissions
     * 
     * @return const std::vector<Permission>& containing all granted permissions
     */
    const std::vector<Permission>& getPermissions() const noexcept;
    
    /**
     * @brief Check if admin can manage users
     * 
     * @return true if user management permission granted
     * @return false if user management permission not granted
     */
    bool canManageUsers() const noexcept;
    
    /**
     * @brief Check if admin can manage bookings
     * 
     * @return true if booking management permission granted
     * @return false if booking management permission not granted
     */
    bool canManageBookings() const noexcept;
    
    /**
     * @brief Check if admin can view reports
     * 
     * @return true if report viewing permission granted
     * @return false if report viewing permission not granted
     */
    bool canViewReports() const noexcept;
    
    /**
     * @brief Check if admin can configure system
     * 
     * @return true if system configuration permission granted
     * @return false if system configuration permission not granted
     */
    bool canConfigureSystem() const noexcept;
    
    /**
     * @brief Check if admin has full access
     * 
     * @return true if full access permission granted
     * @return false if full access permission not granted
     */
    bool hasFullAccess() const noexcept;
    
    /**
     * @brief Get comprehensive admin information
     * 
     * @return std::string containing formatted admin details
     */
    std::string getAdminInfo() const noexcept;
    
    /**
     * @brief Promote admin to super admin level
     */
    void promoteToSuperAdmin();
    
    /**
     * @brief Demote admin to moderator level
     */
    void demoteToModerator();
    
    /**
     * @brief Deactivate user account
     * 
     * @param user shared pointer to the User object to deactivate
     * 
     * @return true if deactivation successful
     * @return false if deactivation failed
     */
    bool deactivateUser(std::shared_ptr<User> user) const;
    
    /**
     * @brief Activate user account
     * 
     * @param user shared pointer to the User object to activate
     * 
     * @return true if activation successful
     * @return false if activation failed
     */
    bool activateUser(std::shared_ptr<User> user) const;
    
    /**
     * @brief Cancel any booking in system
     * 
     * @param booking shared pointer to the Booking object to cancel
     * 
     * @return true if cancellation successful
     * @return false if cancellation failed
     */
    bool cancelAnyBooking(std::shared_ptr<Booking> booking) const;
    
    /**
     * @brief Calculate total revenue from customers
     * 
     * @param customers constant reference to the vector containing customer objects
     * 
     * @return double containing total revenue amount
     */
    double calculateTotalRevenue(const std::vector<std::shared_ptr<Customer>>& customers) const;
    
    /**
     * @brief Get count of active users
     * 
     * @param users constant reference to the vector containing user objects
     * 
     * @return int containing active users count
     */
    int getActiveUsersCount(const std::vector<std::shared_ptr<User>>& users) const;
    
    /**
     * @brief Check if admin can perform specific action
     * 
     * @param action constant reference to the string containing action to check
     * 
     * @return true if action is permitted
     * @return false if action is not permitted
     */
    bool canPerformAction(const std::string& action) const;
    
    /**
     * @brief Get admin capabilities summary
     * 
     * @return std::string containing formatted capabilities
     */
    std::string getAdminCapabilities() const noexcept;
    
    /**
     * @brief Check system load capacity
     * 
     * @param concurrentUsers integer value containing concurrent users count
     */
    void checkSystemLoad(int concurrentUsers) const;
};