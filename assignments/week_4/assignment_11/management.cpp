#include "management.h"

void User::accessLevel() {
    cout << "General Access\n";
}

void Employee::accessLevel() {
    cout << "Employee Access\n";
}

void InventoryManager::accessLevel() {
    cout << "Full Inventory Management Access\n";
}