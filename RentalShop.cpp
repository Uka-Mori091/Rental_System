#include "RentalShop.h"
#include <sstream>

bool RentalShop::addItem(int id, const std::wstring& name, double price, int quantity) {
    items[id] = { name, price, quantity };
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
        ss << L"ID: " << pair.first
           << L", Name: " << pair.second.name
           << L", Price: " << pair.second.price
           << L", Quantity: " << pair.second.quantity << L"\n";
    }
    return ss.str();
}
