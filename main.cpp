#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Structure to hold product details
struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

// Helper function to rewrite the entire inventory vector to the text file
void saveInventory(const vector<Item>& inventory) {
    ofstream outFile("inventory.txt");
    if (outFile.is_open()) {
        for (size_t i = 0; i < inventory.size(); i++) {
            outFile << inventory[i].id << " " 
                    << inventory[i].name << " " 
                    << inventory[i].quantity << " " 
                    << inventory[i].price << "\n";
        }
        outFile.close();
    }
}

int main() {
    vector<Item> inventory;
    int choice;

    // 1. LOAD DATA: Read existing items from text file when program starts
    ifstream inFile("inventory.txt");
    if (inFile.is_open()) {
        Item temp;
        while (inFile >> temp.id >> temp.name >> temp.quantity >> temp.price) {
            inventory.push_back(temp);
        }
        inFile.close();
    }

    do {
        cout << "\n=====================================\n";
        cout << "     INVENTORY MANAGEMENT SYSTEM     \n";
        cout << "=====================================\n";
        cout << "1. Add New Item\n";
        cout << "2. View All Items\n";
        cout << "3. Search Item by ID\n";
        cout << "4. Update Item Quantity / Price\n";
        cout << "5. Delete Item\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Item newItem;
                cout << "\nEnter Item ID: ";
                cin >> newItem.id;
                cout << "Enter Item Name (use underscores instead of spaces, e.g., Gaming_Mouse): ";
                cin >> newItem.name;
                cout << "Enter Quantity: ";
                cin >> newItem.quantity;
                cout << "Enter Price: ";
                cin >> newItem.price;

                inventory.push_back(newItem);
                saveInventory(inventory); // Save changes to file
                cout << "-> Item added and saved successfully!\n";
                break;
            }
            case 2: {
                if (inventory.empty()) {
                    cout << "\n-> Inventory is currently empty.\n";
                } else {
                    cout << "\n--- Current Inventory List ---\n";
                    for (size_t i = 0; i < inventory.size(); i++) {
                        cout << "ID: " << inventory[i].id 
                             << " | Name: " << inventory[i].name 
                             << " | Qty: " << inventory[i].quantity 
                             << " | Price: $" << inventory[i].price << "\n";
                    }
                }
                break;
            }
            case 3: {
                int searchId;
                cout << "\nEnter ID to search: ";
                cin >> searchId;
                bool found = false;

                for (size_t i = 0; i < inventory.size(); i++) {
                    if (inventory[i].id == searchId) {
                        cout << "-> Found! Name: " << inventory[i].name 
                             << ", Quantity: " << inventory[i].quantity 
                             << ", Price: $" << inventory[i].price << "\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "-> Item with ID " << searchId << " not found.\n";
                }
                break;
            }
            case 4: {
                int updateId;
                cout << "\nEnter ID of item to update: ";
                cin >> updateId;
                bool found = false;

                for (size_t i = 0; i < inventory.size(); i++) {
                    if (inventory[i].id == updateId) {
                        cout << "Current -> Name: " << inventory[i].name 
                             << ", Qty: " << inventory[i].quantity 
                             << ", Price: $" << inventory[i].price << "\n";
                        
                        cout << "Enter new Quantity: ";
                        cin >> inventory[i].quantity;
                        cout << "Enter new Price: ";
                        cin >> inventory[i].price;

                        saveInventory(inventory); // Save updated list to file
                        cout << "-> Item updated and saved successfully!\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "-> Item with ID " << updateId << " not found.\n";
                }
                break;
            }
            case 5: {
                int deleteId;
                cout << "\nEnter ID of item to delete: ";
                cin >> deleteId;
                bool found = false;

                for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                    if (it->id == deleteId) {
                        inventory.erase(it);
                        saveInventory(inventory); // Save changes after deletion
                        cout << "-> Item deleted successfully!\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "-> Item with ID " << deleteId << " not found.\n";
                }
                break;
            }
            case 6:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\n-> Invalid choice! Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}