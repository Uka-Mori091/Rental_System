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
