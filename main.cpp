#include <windows.h>
#include "RentalShop.h"
#include <string>
#include <sstream>

RentalShop shop;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);

HWND hId, hName, hPrice, hQty, hOutput;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"RentalShopWindow";
    wc.lpfnWndProc = WndProc;

    RegisterClassW(&wc);

    CreateWindowW(L"RentalShopWindow", L"Rental Shop GUI", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 500, 400, NULL, NULL, NULL, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void AddControls(HWND hWnd) {
    CreateWindowW(L"static", L"ID:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 20, hWnd, NULL, NULL, NULL);
    hId = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 20, 100, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Name:", WS_VISIBLE | WS_CHILD, 20, 50, 80, 20, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 50, 150, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Price:", WS_VISIBLE | WS_CHILD, 20, 80, 80, 20, hWnd, NULL, NULL, NULL);
    hPrice = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 80, 100, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Quantity:", WS_VISIBLE | WS_CHILD, 20, 110, 80, 20, hWnd, NULL, NULL, NULL);
    hQty = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 110, 100, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"button", L"Add Item", WS_VISIBLE | WS_CHILD, 20, 150, 100, 30, hWnd, (HMENU)1, NULL, NULL);
    CreateWindowW(L"button", L"Search Item", WS_VISIBLE | WS_CHILD, 130, 150, 100, 30, hWnd, (HMENU)2, NULL, NULL);
    CreateWindowW(L"button", L"Delete Item", WS_VISIBLE | WS_CHILD, 240, 150, 100, 30, hWnd, (HMENU)3, NULL, NULL);
    CreateWindowW(L"button", L"Show Items", WS_VISIBLE | WS_CHILD, 350, 150, 100, 30, hWnd, (HMENU)4, NULL, NULL);

    hOutput = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
                            20, 200, 440, 150, hWnd, NULL, NULL, NULL);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        AddControls(hWnd);
        break;
    case WM_COMMAND:
        if (wp == 1) { // Add
            wchar_t idStr[10], name[100], priceStr[20], qtyStr[10];
            GetWindowTextW(hId, idStr, 10);
            GetWindowTextW(hName, name, 100);
            GetWindowTextW(hPrice, priceStr, 20);
            GetWindowTextW(hQty, qtyStr, 10);
            int id = _wtoi(idStr);
            double price = _wtof(priceStr);
            int qty = _wtoi(qtyStr);
            shop.addItem(id, name, price, qty);
            SetWindowTextW(hOutput, L"Item added.");
        } else if (wp == 2) { // Search
            wchar_t idStr[10];
            GetWindowTextW(hId, idStr, 10);
            int id = _wtoi(idStr);
            Item item;
            if (shop.searchItem(id, item)) {
                std::wstringstream ss;
                ss << L"ID: " << id << L"\nName: " << item.name << L"\nPrice: " << item.price << L"\nQty: " << item.quantity;
                SetWindowTextW(hOutput, ss.str().c_str());
            } else {
                SetWindowTextW(hOutput, L"Item not found.");
            }
        } else if (wp == 3) { // Delete
            wchar_t idStr[10];
            GetWindowTextW(hId, idStr, 10);
            int id = _wtoi(idStr);
            if (shop.deleteItem(id)) {
                SetWindowTextW(hOutput, L"Item deleted.");
            } else {
                SetWindowTextW(hOutput, L"Item not found.");
            }
        } else if (wp == 4) { // Show
            std::wstring list = shop.showItems();
            SetWindowTextW(hOutput, list.c_str());
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}
