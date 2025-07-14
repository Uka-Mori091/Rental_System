#pragma once
#include <string>
#include <map>

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

private:
    std::map<int, Item> items;
};
