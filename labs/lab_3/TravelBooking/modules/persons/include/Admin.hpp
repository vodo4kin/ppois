#pragma once
#include "Customer.hpp"
#include "Booking.hpp"
#include <vector>
#include <string>

class Admin : public User {
public:
    enum class Permission {
        MANAGE_USERS,
        MANAGE_BOOKINGS,
        VIEW_REPORTS,
        SYSTEM_CONFIG,
        ALL_ACCESS
    };
    enum class AdminLevel {
        MODERATOR,
        SUPER_ADMIN
    };

private:
AdminLevel adminLevel;
std::vector<Permission> permissions;
std::string department;
void initializePermissions();
public:
Admin(const std::string& name, const std::string& email, 
    const std::string& password, const std::string& birthDate,
    AdminLevel level = AdminLevel::MODERATOR,
    const std::string& department = "Administration");
    std::string getUserRole() const override;
    AdminLevel getAdminLevel() const noexcept;
    std::string getAdminLevelStr() const noexcept;
    void setAdminLevel(AdminLevel newLevel);
    std::string getDepartment() const noexcept;
    void setDepartment(const std::string& newDepartment);
    bool hasPermission(Permission permission) const noexcept;
    void grantPermission(Permission permission);
    void revokePermission(Permission permission);
    const std::vector<Permission>& getPermissions() const noexcept;
    bool canManageUsers() const noexcept;
    bool canManageBookings() const noexcept;
    bool canViewReports() const noexcept;
    bool canConfigureSystem() const noexcept;
    bool hasFullAccess() const noexcept;
    std::string getAdminInfo() const noexcept;
    void promoteToSuperAdmin();
    void demoteToModerator();
    bool deactivateUser(std::shared_ptr<User> user) const;
    bool activateUser(std::shared_ptr<User> user) const;
    bool cancelAnyBooking(std::shared_ptr<Booking> booking) const;
    double calculateTotalRevenue(const std::vector<std::shared_ptr<Customer>>& customers) const;
    int getActiveUsersCount(const std::vector<std::shared_ptr<User>>& users) const;
    bool canPerformAction(const std::string& action) const;
    std::string getAdminCapabilities() const noexcept;
    void checkSystemLoad(int concurrentUsers) const;
};