// AEPS Residences.cpp : Defines the entry point for the application.
//
#include "Resource.h"
#include "framework.h"
#include "AEPS Residences.h"
#include "RentalShop.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//Declare the buttons
HWND hBtnMainMenu[6];  // 6 buttons: Inventory, Room Availability, About Us, etc.

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_AEPSRESIDENCES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AEPSRESIDENCES));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AEPSRESIDENCES));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_AEPSRESIDENCES);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

INT_PTR CALLBACK HowDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}

INT_PTR CALLBACK InventoryDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BTN_ADD:
        {
            wchar_t idBuf[10], nameBuf[100], priceBuf[20], qtyBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ID, idBuf, 10);
            GetDlgItemTextW(hDlg, IDC_EDIT_NAME, nameBuf, 100);
            GetDlgItemTextW(hDlg, IDC_EDIT_PRICE, priceBuf, 20);
            GetDlgItemTextW(hDlg, IDC_EDIT_QTY, qtyBuf, 10);

            int id = _wtoi(idBuf);
            double price = _wtof(priceBuf);
            int qty = _wtoi(qtyBuf);

            shop.addItem(id, nameBuf, price, qty);
            SetDlgItemTextW(hDlg, IDC_LIST1, L"Item added.");
        }
        break;

        case IDC_BTN_SEARCH:
        {
            wchar_t idBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ID, idBuf, 10);
            int id = _wtoi(idBuf);

            Item foundItem;
            if (shop.searchItem(id, foundItem))
            {
                std::wstringstream ss;
                ss << L"Found:\nName: " << foundItem.name
                    << L"\nPrice: " << foundItem.price
                    << L"\nQuantity: " << foundItem.quantity;

                SetDlgItemTextW(hDlg, IDC_LIST1, ss.str().c_str());
            }
            else
            {
                SetDlgItemTextW(hDlg, IDC_LIST1, L"Item not found.");
            }
        }
        break;

        case IDC_BTN_DELETE:
        {
            wchar_t idBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ID, idBuf, 10);
            int id = _wtoi(idBuf);

            if (shop.deleteItem(id))
            {
                SetDlgItemTextW(hDlg, IDC_LIST1, L"Item deleted.");
            }
            else
            {
                SetDlgItemTextW(hDlg, IDC_LIST1, L"Item not found. Cannot delete.");
            }
        }
        break;

        case IDC_BTN_SHOW:
        {
            std::wstring allItems = shop.showItems();
            if (allItems.empty())
                allItems = L"No items in inventory.";
            SetDlgItemTextW(hDlg, IDC_LIST1, allItems.c_str());
        }
        break;

        case IDC_BTN_RESERVE:
        {
            wchar_t idBuf[10], qtyBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ID, idBuf, 10);
            GetDlgItemTextW(hDlg, IDC_EDIT_QTY, qtyBuf, 10);

            int itemId = _wtoi(idBuf);
            int qtyToReserve = _wtoi(qtyBuf);

            std::wstring resultMessage;
            if (shop.reserveItem(itemId, qtyToReserve, resultMessage)) {
                SetDlgItemTextW(hDlg, IDC_LIST1, resultMessage.c_str());
            }
            else {
                MessageBoxW(hDlg, resultMessage.c_str(), L"Reservation Error", MB_OK | MB_ICONERROR);
            }
        }
        break;

        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RoomManagementProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BTN_ROOM_ADD:
        {
            wchar_t idBuf[10], nameBuf[50], priceBuf[20], qtyBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM, idBuf, 10);
            GetDlgItemTextW(hDlg, IDC_EDIT_TYPE, nameBuf, 50);
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM_PRICE, priceBuf, 20);
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM_QTY, qtyBuf, 10);

            int id = _wtoi(idBuf);
            std::wstring name = nameBuf;
            double price = _wtof(priceBuf);
            int qty = _wtoi(qtyBuf);

            std::wstringstream ss;
            if (shop.addItem(id, name, price, qty)) {
                ss << L"Room added successfully:\n"
                    << L"Room: " << id << L"\n"
                    << L"Name: " << name << L"\n"
                    << L"Price: ₱" << price << L"\n"
                    << L"Quantity: " << qty;
            }
            else {
                MessageBoxW(hDlg, L"Room ID already exists.", L"Error", MB_OK | MB_ICONERROR);
                break;
            }
            SetDlgItemTextW(hDlg, IDC_LIST2, ss.str().c_str());
        }
        break;

        case IDC_BTN_ROOM_DELETE:
        {
            wchar_t idBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM, idBuf, 10);
            int id = _wtoi(idBuf);

            std::wstringstream ss;
            if (shop.deleteItem(id)) {
                ss << L"Room: " << id << L" deleted.";
            }
            else {
                MessageBoxW(hDlg, L"Room not found.", L"Error", MB_OK | MB_ICONERROR);
                break;
            }
            SetDlgItemTextW(hDlg, IDC_LIST2, ss.str().c_str());
        }
        break;

        case IDC_BTN_ROOM_SEARCH:
        {
            wchar_t idBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM, idBuf, 10);
            int id = _wtoi(idBuf);

            Item item;
            std::wstringstream ss;
            if (shop.searchItem(id, item)) {
                ss << L"Room found:\n"
                    << L"Room: " << id << L"\n"
                    << L"Name: " << item.name << L"\n"
                    << L"Price: ₱" << item.price << L"\n"
                    << L"Quantity: " << item.quantity;
            }
            else {
                MessageBoxW(hDlg, L"Room not found.", L"Error", MB_OK | MB_ICONERROR);
                break;
            }
            SetDlgItemTextW(hDlg, IDC_LIST2, ss.str().c_str());
        }
        break;

        case IDC_BTN_SHOWROOMS:
        {
            std::wstring data = shop.showItems();
            SetDlgItemTextW(hDlg, IDC_LIST2, data.c_str());
        }
        break;

        case IDC_BTN_RESERVE:  // <- Make sure to define this in your resource header
        {
            wchar_t idBuf[10], qtyBuf[10];
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM, idBuf, 10);
            GetDlgItemTextW(hDlg, IDC_EDIT_ROOM_QTY, qtyBuf, 10);

            int id = _wtoi(idBuf);
            int qty = _wtoi(qtyBuf);

            std::wstring result;
            if (shop.reserveItem(id, qty, result)) {
                SetDlgItemTextW(hDlg, IDC_LIST2, result.c_str());
            }
            else {
                std::wstringstream error;
                error << L"Reserve failed:\n" << result;
                SetDlgItemTextW(hDlg, IDC_LIST2, error.str().c_str());
            }
        }
        break;

        case IDOK:

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    LPCWSTR buttonLabels[] = {
     L"Inventory",
     L"Room Availability",
     L"About Us",
     L"How We Work",
     L"Frequently Asked Questions",
     L"Terms of Service"
    };

    const int buttonCount = sizeof(buttonLabels) / sizeof(buttonLabels[0]);

    int spacing = 5;
    int yPos = 150;

    for (int i = 0; i < buttonCount; ++i)
    {
        SIZE textSize;
        HDC hdc = GetDC(hWnd);
        GetTextExtentPoint32W(hdc, buttonLabels[i], wcslen(buttonLabels[i]), &textSize);
        ReleaseDC(hWnd, hdc);

        int btnWidth = textSize.cx + 20;
        int btnHeight = textSize.cy + 10;

        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int xPos = (rcClient.right - btnWidth) / 2;

        // Store button handle in array
        hBtnMainMenu[i] = CreateWindowW(
            L"BUTTON", buttonLabels[i],
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            xPos, yPos, btnWidth, btnHeight,
            hWnd, (HMENU)(1001 + i), hInst, NULL
        );
        yPos += btnHeight + spacing;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE: Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case 1001://Inventory Button
            DialogBox(hInst, MAKEINTRESOURCE(IDD_INVENTORY_DIALOG), hWnd, InventoryDialogProc);
            break;

        case 1002:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ROOM_DIALOG), hWnd, RoomManagementProc);
            break;

        case 1003: // "About Us" button
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTUS), hWnd, HowDialogProc);
            break;

        case 1004://How We Work
            DialogBox(hInst, MAKEINTRESOURCE(IDD_HOW), hWnd, HowDialogProc);
            break;

        case 1005: // FAQs
            DialogBox(hInst, MAKEINTRESOURCE(IDD_FAQs), hWnd, HowDialogProc);
            break;

        case 1006: // Terms of Service
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ToS), hWnd, HowDialogProc);
            break;



        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
