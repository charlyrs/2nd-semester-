// KR2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "KR2.h"
#include <string>
#include <algorithm>
#include <sstream>

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
    LoadStringW(hInstance, IDC_KR2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KR2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KR2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KR2);
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
    case WM_CHAR:
    {
        if (wParam == 'p')
        {
            break;
        }

        break;
    }

    case WM_KEYDOWN:
    {
        if (wParam == 0x50)
        {
            break;
        }

        break;
    }

    case WM_LBUTTONDOWN:
    {  
        if (GetKeyState(VK_LCONTROL) < 0)
        {
            if (MessageBox(hWnd, L"Сообщение ✅", L"⛔️ Заголовок", MB_ICONERROR | MB_YESNO) == IDYES)
            {
                break;
            }
        }

        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        break;
    }

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_CHANGE_SIZE_MENU:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
                break;

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

// 1.a
bool IsValidNumber1a(std::wstring s)
{
    for (auto i = 0; i < s.size(); ++i)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

// 1.b
bool IsValidNumber1b(std::wstring s)
{
    auto isValid = true;
    for (auto i = 0; i < s.size(); ++i)
    {
        isValid &= isdigit(s[i]);
    }

    return isValid;
}

// 1.c
bool IsValidNumber1c(std::wstring s)
{
    auto isValid = true;
    for (auto ch : s)
    {
        isValid &= isdigit(ch);
    }

    return isValid;
}

// 2.
bool IsValidNumber2(std::wstring s)
{
    return std::all_of(s.cbegin(), s.cend(), isdigit);
}

// 1.a
int Parse1a(std::wstring s)
{
    return std::stoi(s);
}

// 3.
bool TryParse(std::wstring s, int* a)
{
    std::wstringstream stream;
    stream << s;
    if (stream >> *a)
    {
        return true;
    }
    return false;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        auto hSlider = GetDlgItem(hDlg, IDC_SIZE_SLIDER);
        SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(3, 12));
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_SIZE_OK)
        {
            auto hSlider = GetDlgItem(hDlg, IDC_SIZE_SLIDER);
            auto value = SendMessage(hSlider, TBM_GETPOS, TRUE, MAKELPARAM(3, 12));
            break;
        }

        if (LOWORD(wParam) == IDOK)
        {
            auto hTextBox = GetDlgItem(hDlg, IDC_SIZE_EDIT);
            auto length = SendMessage(hTextBox, WM_GETTEXTLENGTH, NULL, NULL);
            auto buffer = new wchar_t[length + 1];
            SendMessage(hTextBox, WM_GETTEXT, length + 1, (LPARAM) buffer);

            auto s = std::wstring(buffer, length);

            auto isValid1 = IsValidNumber1a(s);
            auto isValid2 = IsValidNumber2(s);

            int a;
            if (TryParse(s, &a))
            {
                EndDialog(hDlg, LOWORD(wParam));              
            }
            else
            {
                MessageBox(hDlg, L"Ошибка", L"", MB_ICONERROR);
            } 

            return (INT_PTR)TRUE;
       }

        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
