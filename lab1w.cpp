// lab1w.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab1w.h"
#define _USE_MATH_DEFINES

#include <WinUser.h>
#include <math.h>
#include <string>
#include <cmath>
LOGBRUSH LogBrush;
const int R = 200;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_LAB1W, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1W));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1W));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1W);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        static int width, height;
        int middleX, middleY, x, y, x_circle, y_circle;
        double angle;
        static double t;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_SIZE:

        width = LOWORD(lParam); 	
        height = HIWORD(lParam);	
        break;
    case WM_CREATE:
        SetTimer(hWnd, 1, 125, NULL);
        break;
    case WM_TIMER:

        t += 0.025;
        if (t >= M_PI * 2) {
            KillTimer(hWnd, 1);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;

        LogBrush.lbColor = RGB(255, 180, 31);
        LogBrush.lbStyle = BS_SOLID;
        HPEN hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &LogBrush, 0, NULL);

        HPEN hPsol = CreatePen(PS_SOLID, 1, RGB(224, 0, 15));
        HDC hdc = BeginPaint(hWnd, &ps);
        middleX = width / 2;  
middleY = height / 2;
        x = middleX;
        y = middleY;

        SelectObject(hdc, hPen);
        MoveToEx(hdc, 0, middleY, NULL);
        LineTo(hdc, width, middleY);
        LineTo(hdc, width - 10, middleY - 20);
        MoveToEx(hdc, width, middleY, NULL);
        LineTo(hdc, width - 10, middleY + 20);
        MoveToEx(hdc, middleX, height, NULL);
        LineTo(hdc, middleX, 0);
        LineTo(hdc, middleX - 20, 10);
        MoveToEx(hdc, middleX, 0, NULL);
        LineTo(hdc, middleX + 20, 10);
        SelectObject(hdc, hPsol);
        for (int i = 0; i <= middleX; i += 30) {
            MoveToEx(hdc, middleX + i, middleY, NULL);
            LineTo(hdc, middleX + i, middleY + 6);
            LineTo(hdc, middleX + i, middleY - 6);
        }
        for (int i = 0; i <= middleX; i += 30) {
            MoveToEx(hdc, middleX - i, middleY, NULL);
            LineTo(hdc, middleX - i, middleY + 6);
            LineTo(hdc, middleX - i, middleY - 6);
        }
        for (int i = 0; i <= middleY; i += 30) {
            MoveToEx(hdc, middleX, middleY + i, NULL);
            LineTo(hdc, middleX + 6, middleY + i);
            LineTo(hdc, middleX - 6, middleY + i);
        }
        for (int i = 0; i <= middleY; i += 30) {
            MoveToEx(hdc, middleX, middleY - i, NULL);
            LineTo(hdc, middleX + 6, middleY - i);
            LineTo(hdc, middleX - 6, middleY - i);
        }
        DeleteObject(hPen);
        DeleteObject(hPsol);


        MoveToEx(hdc, middleX, middleY, NULL);

        for (angle = 0.025; angle <= t; angle += 0.025)
        {
            x = middleX + R * sin(3 * angle/7.0) * cos(angle);
            y = middleY + R * sin(3 * angle/7.0) * sin(angle);
            LineTo(hdc, x, y);
            MoveToEx(hdc, x, y, NULL);

        }
        x_circle = middleX + R * sin(3 * t/7.0) * cos(t);
        y_circle = middleY + R * sin(3 * t/7.0) * sin(t);
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, RGB(244, 0, 15));
        Ellipse(hdc, x_circle - 4, y_circle - 4, x_circle + 4, y_circle + 4);
        auto text = std::to_string(x_circle) + ", " + std::to_string(y_circle);
        auto rect = RECT{ 0, 0, 500, 500 };
        std::wstring stemp = std::wstring(text.begin(), text.end());
        LPCWSTR sw = stemp.c_str();
        SetTextColor(hdc, RGB(244, 0, 15));
        DrawText(hdc, sw, -1, &rect, DT_BOTTOM);
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
