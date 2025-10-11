#include "persons/EmployeeRole.hpp"

EmployeeRole::EmployeeRole(Role role) noexcept : role(role) {}

EmployeeRole::Role EmployeeRole::getRole() const noexcept {
    return role;
}

std::string EmployeeRole::toString() const noexcept {
    switch(role) {
        case Role::WAREHOUSE_WORKER: return "Warehouse Worker";
        case Role::INVENTORY_MANAGER: return "Inventory Manager";
        case Role::CASHIER: return "Cashier";
        case Role::SUPERVISOR: return "Supervisor";
        case Role::ADMINISTRATOR: return "Administrator";
        case Role::HR_MANAGER: return "HR Manager";
        case Role::FINANCE_OFFICER: return "Finance Officer";
        case Role::IT_SUPPORT: return "IT Support";
        default: return "Unknown";
    }
}

int EmployeeRole::getAccessLevel() const noexcept {
    switch(role) {
        case Role::WAREHOUSE_WORKER: return 1;
        case Role::CASHIER: return 2;
        case Role::INVENTORY_MANAGER: return 3;
        case Role::IT_SUPPORT: return 4;
        case Role::FINANCE_OFFICER: return 5;
        case Role::SUPERVISOR: return 6;
        case Role::HR_MANAGER: return 7;
        case Role::ADMINISTRATOR: return 10;
        default: return 0;
    }
}

bool EmployeeRole::canManageInventory() const noexcept {
    return role == Role::INVENTORY_MANAGER || role == Role::SUPERVISOR || role == Role::ADMINISTRATOR;
}

bool EmployeeRole::canProcessSales() const noexcept {
    return role == Role::CASHIER || role == Role::SUPERVISOR || role == Role::ADMINISTRATOR;
}

bool EmployeeRole::canManageUsers() const noexcept {
    return role == Role::ADMINISTRATOR || role == Role::HR_MANAGER;
}

bool EmployeeRole::canViewFinancialReports() const noexcept {
    return role == Role::FINANCE_OFFICER || role == Role::SUPERVISOR || role == Role::ADMINISTRATOR;
}

bool EmployeeRole::canApproveOrders() const noexcept {
    return role == Role::SUPERVISOR || role == Role::ADMINISTRATOR;
}

bool EmployeeRole::canManageEmployees() const noexcept {
    return role == Role::HR_MANAGER || role == Role::ADMINISTRATOR;
}

double EmployeeRole::getSalaryMultiplier() const noexcept {
    switch(role) {
        case Role::WAREHOUSE_WORKER: return 1.0;
        case Role::CASHIER: return 1.2;
        case Role::INVENTORY_MANAGER: return 1.5;
        case Role::IT_SUPPORT: return 1.4;
        case Role::FINANCE_OFFICER: return 1.6;
        case Role::SUPERVISOR: return 1.8;
        case Role::HR_MANAGER: return 1.7;
        case Role::ADMINISTRATOR: return 2.0;
        default: return 1.0;
    }
}

bool EmployeeRole::requiresSpecialTraining() const noexcept {
    return role == Role::INVENTORY_MANAGER || role == Role::FINANCE_OFFICER || 
           role == Role::IT_SUPPORT || role == Role::HR_MANAGER;
}

bool EmployeeRole::operator==(const EmployeeRole& other) const noexcept {
    return role == other.role;
}

bool EmployeeRole::operator!=(const EmployeeRole& other) const noexcept {
    return !(*this == other);
}