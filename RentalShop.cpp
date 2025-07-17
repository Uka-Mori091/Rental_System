#include "framework.h"
#include "AEPS Residences.h"
#include <string>
#include <map>
#include <sstream>


// Rental system controls
HWND hId, hName, hPrice, hQty, hOutput;
HWND hAddBtn, hSearchBtn, hDeleteBtn, hShowBtn;

// RentalShop logic
struct Item {
    std::wstring name;
    double price;
    int quantity;
};

class RentalShop {
public:
    bool addItem(int id, const std::wstring& name, double price, int quantity);
    bool searchItem(int id, Item& item) const;
    bool deleteItem(int id);
    std::wstring showItems() const;
    bool updateItem(int id, const Item& updatedItem);
    bool reserveItem(int id, int qty, std::wstring& result);
    bool addRoom(int roomNumber, const std::wstring& name, double price, int quantity);
    bool reserveRoom(int roomNumber, int qty); // reserve x rooms
    std::map<int, Item> getAllRooms() const;

private:
    std::map<int, Item> rooms; // Use room number as key
    std::map<int, Item> items;
};

bool RentalShop::addItem(int id, const std::wstring& name, double price, int quantity) {
    if (items.find(id) != items.end())
        return false;
    Item item = { name, price, quantity };
    items[id] = item;
    return true;
}

bool RentalShop::searchItem(int id, Item& item) const {
    auto it = items.find(id);
    if (it != items.end()) {
        item = it->second;
        return true;
    }
    return false;
}

bool RentalShop::deleteItem(int id) {
    return items.erase(id) > 0;
}

std::wstring RentalShop::showItems() const {
    std::wstringstream ss;
    for (const auto& pair : items) {
        int id = pair.first;
        const Item& item = pair.second;

        ss << L"ID: " << id
            << L", Name: " << item.name
            << L", Price: ₱" << item.price
            << L", Quantity: " << item.quantity
            << L", Status: " << (item.quantity > 0 ? L"Available" : L"Out of Stock") << L"\n";
    }
    return ss.str();
}

bool reserveItem(int id, int qty) {
    auto it = items.find(id);
    if (it != items.end() && it->second.quantity >= qty) {
        it->second.quantity -= qty;
        return true;
    }
    return false;
}

bool RentalShop::updateItem(int id, const Item& updatedItem) {
    auto it = items.find(id);
    if (it != items.end()) {
        items[id] = updatedItem;
        return true;
    }
    return false;
}

bool RentalShop::addRoom(int roomNumber, const std::wstring& name, double price, int quantity) {
    if (rooms.count(roomNumber)) return false; // already exists
    rooms[roomNumber] = { name, price, quantity };
    return true;
}

bool RentalShop::reserveRoom(int roomNumber, int qty) {
    auto it = rooms.find(roomNumber);
    if (it != rooms.end() && it->second.quantity >= qty) {
        it->second.quantity -= qty;
        return true;
    }
    return false; // not enough or doesn't exist
}

std::map<int, Item> RentalShop::getAllRooms() const {
    return items;  // assuming `items` is your internal map of roomNumber → Item
}

RentalShop shop;
