#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

struct Item {
    string id;
    string name;
    double price;
    int quantity;
};

struct Room {
    string roomNumber;
    string guestName;
    string checkInDate;
    string checkOutDate;
    bool isReserved;
};

vector<Item> itemsList;
vector<Room> roomList;

void showMainMenu() {
    cout << "\n========= AEPS SYSTEM MAIN MENU =========\n";
    cout << "1. Item Rental System\n";
    cout << "2. Room Reservation System\n";
    cout << "3. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
}

void showItemMenu() {
    cout << "\n========= ITEM RENTAL MENU =========\n";
    cout << "1. Add Item\n";
    cout << "2. Show Items\n";
    cout << "3. Search Item\n";
    cout << "4. Update Item\n";
    cout << "5. Delete Item\n";
    cout << "6. Back to Main Menu\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

void showRoomMenu() {
    cout << "\n========= ROOM RESERVATION MENU =========\n";
    cout << "1. Reserve Room\n";
    cout << "2. Show Reservations\n";
    cout << "3. Search Reservation\n";
    cout << "4. Update Reservation\n";
    cout << "5. Cancel Reservation\n";
    cout << "6. Back to Main Menu\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
}

void addItem() {
    Item newItem;
    char confirm;
    cout << "Enter Item ID: ";
    cin >> newItem.id;
    cout << "Enter Item Name: ";
    cin.ignore();
    getline(cin, newItem.name);
    cout << "Enter Item Price: ";
    cin >> newItem.price;
    cout << "Enter Item Quantity: ";
    cin >> newItem.quantity;
    cout << "Confirm adding item (Y/N): ";
    cin >> confirm;
    if (toupper(confirm) == 'Y') {
        itemsList.push_back(newItem);
        cout << "Item added successfully!\n";
    }
    else {
        cout << "Item addition cancelled.\n";
    }
}

void showItems() {
    cout << "\n====================== ITEMS LIST ======================\n";
    cout << left << setw(10) << "ID"
        << setw(25) << "Name"
        << setw(15) << "Price"
        << setw(10) << "Quantity" << "\n";
    cout << "--------------------------------------------------------\n";
    if (itemsList.empty()) {
        cout << "No items found.\n";
    }
    else {
        for (const auto& item : itemsList) {
            cout << left << setw(10) << item.id
                << setw(25) << item.name
                << "₱" << fixed << setprecision(2) << setw(13) << item.price
                << setw(10) << item.quantity << "\n";
        }
    }
    cout << "========================================================\n";
}

void searchItem() {
    string searchId;
    cout << "Enter Item ID to search: ";
    cin >> searchId;
    bool found = false;
    for (const auto& item : itemsList) {
        if (item.id == searchId) {
            cout << "\n--- Item Found ---\n";
            cout << "ID:       " << item.id << "\n";
            cout << "Name:     " << item.name << "\n";
            cout << "Price:    ₱" << fixed << setprecision(2) << item.price << "\n";
            cout << "Quantity: " << item.quantity << "\n";
            cout << "------------------\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Item with ID '" << searchId << "' not found.\n";
    }
}

void updateItem() {
    string updateId;
    cout << "Enter Item ID to update: ";
    cin >> updateId;
    for (auto& item : itemsList) {
        if (item.id == updateId) {
            cout << "--- Updating Item ID: " << item.id << " ---\n";
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, item.name);
            cout << "Enter new price: ";
            cin >> item.price;
            cout << "Enter new quantity: ";
            cin >> item.quantity;
            cout << "Item updated successfully!\n";
            return;
        }
    }
    cout << "Item with ID '" << updateId << "' not found.\n";
}

void deleteItem() {
    string deleteId;
    char confirm;
    cout << "Enter Item ID to delete: ";
    cin >> deleteId;

    auto it = find_if(itemsList.begin(), itemsList.end(),
        [&](const Item& item) {
            return item.id == deleteId;
        });

    if (it != itemsList.end()) {
        cout << "Delete this item? (Y/N): ";
        cin >> confirm;
        if (toupper(confirm) == 'Y') {
            itemsList.erase(it);
            cout << "Item deleted successfully!\n";
        }
        else {
            cout << "Item deletion cancelled.\n";
        }
    }
    else {
        cout << "Item with ID '" << deleteId << "' not found.\n";
    }
}

void reserveRoom() {
    Room newRoom;
    cout << "Enter Room Number: ";
    cin >> newRoom.roomNumber;
    cout << "Enter Guest Name: ";
    cin.ignore();
    getline(cin, newRoom.guestName);
    cout << "Enter Check-In Date (YYYY-MM-DD): ";
    cin >> newRoom.checkInDate;
    cout << "Enter Check-Out Date (YYYY-MM-DD): ";
    cin >> newRoom.checkOutDate;
    newRoom.isReserved = true;
    roomList.push_back(newRoom);
    cout << "Room reserved successfully!\n";
}

void showReservations() {
    cout << "\n================== ROOM RESERVATIONS ==================\n";
    if (roomList.empty()) {
        cout << "No reservations found.\n";
    }
    else {
        for (const auto& room : roomList) {
            cout << "Room: " << room.roomNumber
                << ", Guest: " << room.guestName
                << ", Check-In: " << room.checkInDate
                << ", Check-Out: " << room.checkOutDate << "\n";
        }
    }
    cout << "=======================================================\n";
}

void searchReservation() {
    string roomNum;
    cout << "Enter Room Number to search: ";
    cin >> roomNum;
    bool found = false;
    for (const auto& room : roomList) {
        if (room.roomNumber == roomNum) {
            cout << "Reservation Found:\n";
            cout << "Guest: " << room.guestName << "\n";
            cout << "Check-In: " << room.checkInDate << "\n";
            cout << "Check-Out: " << room.checkOutDate << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "No reservation found for Room " << roomNum << ".\n";
    }
}

void updateReservation() {
    string roomNum;
    cout << "Enter Room Number to update: ";
    cin >> roomNum;
    for (auto& room : roomList) {
        if (room.roomNumber == roomNum) {
            cout << "Enter new Guest Name: ";
            cin.ignore();
            getline(cin, room.guestName);
            cout << "Enter new Check-In Date: ";
            cin >> room.checkInDate;
            cout << "Enter new Check-Out Date: ";
            cin >> room.checkOutDate;
            cout << "Reservation updated successfully!\n";
            return;
        }
    }
    cout << "Reservation not found.\n";
}

void cancelReservation() {
    string roomNum;
    cout << "Enter Room Number to cancel: ";
    cin >> roomNum;
    auto it = remove_if(roomList.begin(), roomList.end(), [&](const Room& r) {
        return r.roomNumber == roomNum;
        });
    if (it != roomList.end()) {
        roomList.erase(it, roomList.end());
        cout << "Reservation cancelled successfully.\n";
    }
    else {
        cout << "Reservation not found.\n";
    }
}

int main() {
    int mainChoice, subChoice;

    do {
        showMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            do {
                showItemMenu();
                cin >> subChoice;
                switch (subChoice) {
                case 1: addItem(); break;
                case 2: showItems(); break;
                case 3: searchItem(); break;
                case 4: updateItem(); break;
                case 5: deleteItem(); break;
                case 6: break;
                default: cout << "Invalid choice.\n"; break;
                }
            } while (subChoice != 6);
            break;

        case 2:
            do {
                showRoomMenu();
                cin >> subChoice;
                switch (subChoice) {
                case 1: reserveRoom(); break;
                case 2: showReservations(); break;
                case 3: searchReservation(); break;
                case 4: updateReservation(); break;
                case 5: cancelReservation(); break;
                case 6: break;
                default: cout << "Invalid choice.\n"; break;
                }
            } while (subChoice != 6);
            break;

        case 3:
            cout << "Exiting AEPS System. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (mainChoice != 3);

    return 0;
}
