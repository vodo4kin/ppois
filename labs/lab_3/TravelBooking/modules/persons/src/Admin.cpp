#include "Admin.hpp"
#include "configs/PersonsConfig.hpp"
#include "exceptions/TravelBookingExceptions.hpp"
#include <algorithm>

Admin::Admin(const std::string& name, const std::string& email, 
             const std::string& password, const std::string& birthDate,
             AdminLevel level, const std::string& department)
    : User(name, email, password, birthDate), adminLevel(level), department(department) {
    if (department.empty()) {
        throw InvalidDataException("department", "cannot be empty");
    }
    initializePermissions();
}

void Admin::initializePermissions() {
    permissions.clear();
    permissions = {
        Permission::MANAGE_USERS,
        Permission::VIEW_REPORTS
    };
    if (adminLevel == AdminLevel::SUPER_ADMIN) {
        permissions.push_back(Permission::MANAGE_BOOKINGS);
        permissions.push_back(Permission::SYSTEM_CONFIG);
        permissions.push_back(Permission::ALL_ACCESS);
    }
}

std::string Admin::getUserRole() const {
    return "Administrator";
}

Admin::AdminLevel Admin::getAdminLevel() const noexcept {
    return adminLevel;
}

std::string Admin::getAdminLevelStr() const noexcept {
    switch (adminLevel) {
        case AdminLevel::MODERATOR: return "Moderator";
        case AdminLevel::SUPER_ADMIN: return "Super Admin";
        default: return "Unknown";
    }
}

void Admin::setAdminLevel(AdminLevel newLevel) {
    if (adminLevel != newLevel) {
        adminLevel = newLevel;
        initializePermissions();
    }
}

std::string Admin::getDepartment() const noexcept {
    return department;
}

void Admin::setDepartment(const std::string& newDepartment) {
    if (newDepartment.empty()) {
        throw InvalidDataException("department", "cannot be empty");
    }
    department = newDepartment;
}

bool Admin::hasPermission(Permission permission) const noexcept {
    if (std::find(permissions.begin(), permissions.end(), Permission::ALL_ACCESS) != permissions.end()) {
        return true;
    }
    return std::find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

void Admin::grantPermission(Permission permission) {
    if (!hasPermission(permission)) {
        permissions.push_back(permission);
    }
}

void Admin::revokePermission(Permission permission) {
    if (permission == Permission::ALL_ACCESS && adminLevel == AdminLevel::SUPER_ADMIN) {
        return;
    }
    auto it = std::find(permissions.begin(), permissions.end(), permission);
    if (it != permissions.end()) {
        permissions.erase(it);
    }
}

const std::vector<Admin::Permission>& Admin::getPermissions() const noexcept {
    return permissions;
}

bool Admin::canManageUsers() const noexcept {
    return hasPermission(Permission::MANAGE_USERS);
}

bool Admin::canManageBookings() const noexcept {
    return hasPermission(Permission::MANAGE_BOOKINGS);
}

bool Admin::canViewReports() const noexcept {
    return hasPermission(Permission::VIEW_REPORTS);
}

bool Admin::canConfigureSystem() const noexcept {
    return hasPermission(Permission::SYSTEM_CONFIG);
}

bool Admin::hasFullAccess() const noexcept {
    return hasPermission(Permission::ALL_ACCESS);
}

std::string Admin::getAdminInfo() const noexcept {
    std::string info = User::getInfo();
    info += "\n--- Administrator Information ---\n";
    info += "Role: " + getUserRole() + "\n";
    info += "Level: " + getAdminLevelStr() + "\n";
    info += "Department: " + department + "\n";
    info += "Permissions: " + std::to_string(permissions.size()) + " granted\n";
    info += "Access to: ";
    std::vector<std::string> accessList;
    if (canManageUsers()) accessList.push_back("Users");
    if (canManageBookings()) accessList.push_back("Bookings");
    if (canViewReports()) accessList.push_back("Reports");
    if (canConfigureSystem()) accessList.push_back("System Config");
    if (hasFullAccess()) accessList.push_back("Full System");
    for (size_t i = 0; i < accessList.size(); ++i) {
        info += accessList[i];
        if (i < accessList.size() - 1) info += ", ";
    }
    return info;
}

void Admin::promoteToSuperAdmin() {
    if (adminLevel != AdminLevel::SUPER_ADMIN) {
        adminLevel = AdminLevel::SUPER_ADMIN;
        initializePermissions();
    }
}

void Admin::demoteToModerator() {
    if (adminLevel != AdminLevel::MODERATOR) {
        adminLevel = AdminLevel::MODERATOR;
        initializePermissions();
    }
}

bool Admin::deactivateUser(std::shared_ptr<User> user) const {
    if (!user || !canManageUsers()) return false;
    user->deactivate();
    return true;
}

bool Admin::activateUser(std::shared_ptr<User> user) const {
    if (!user || !canManageUsers()) return false;
    user->activate();
    return true;
}

bool Admin::cancelAnyBooking(std::shared_ptr<Booking> booking) const {
    if (!booking || !canManageBookings()) return false;
    booking->setStatus(Booking::Status::CANCELLED);
    return true;
}

double Admin::calculateTotalRevenue(const std::vector<std::shared_ptr<Customer>>& customers) const {
    if (!canViewReports()) return 0.0;
    double total = 0.0;
    for (const auto& customer : customers) {
        total += customer->getTotalSpent();
    }
    return total;
}

int Admin::getActiveUsersCount(const std::vector<std::shared_ptr<User>>& users) const {
    if (!canViewReports()) return 0;
    int activeCount = 0;
    for (const auto& user : users) {
        if (user->getIsActive()) {
            activeCount++;
        }
    }
    return activeCount;
}

bool Admin::canPerformAction(const std::string& action) const {
    if (action == "deactivate_user" || action == "activate_user" || action == "reset_password") {
        return canManageUsers();
    }
    if (action == "cancel_booking" || action == "modify_booking") {
        return canManageBookings();
    }
    if (action == "view_reports" || action == "generate_stats") {
        return canViewReports();
    }
    if (action == "system_config") {
        return canConfigureSystem();
    }
    return false;
}

std::string Admin::getAdminCapabilities() const noexcept {
    std::string capabilities = "Admin can: ";
    if (canManageUsers()) capabilities += "manage users, ";
    if (canManageBookings()) capabilities += "manage bookings, ";
    if (canViewReports()) capabilities += "view reports, ";
    if (canConfigureSystem()) capabilities += "configure system, ";
    if (hasFullAccess()) capabilities += "full access";
    if (capabilities.back() == ' ') {
        capabilities = capabilities.substr(0, capabilities.length() - 2);
    }
    return capabilities;
}