// KhomyakovaKr2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "KhomyakovaKr2.h"
#include "vector";
#include "string";

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name
std::vector<std::wstring> ListItems;

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
    LoadStringW(hInstance, IDC_KHOMYAKOVAKR2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KHOMYAKOVAKR2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KHOMYAKOVAKR2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KHOMYAKOVAKR2);
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
    {
        HWND hwndList = GetDlgItem(hDlg, IDC_LIST4);
        for (int i = 0; i < ListItems.size(); i++)
        {
            int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
                (LPARAM)ListItems[i].c_str());
            // Set the array index of the player as item data.
            // This enables us to retrieve the item from the array
            // even after the items are sorted by the list box.
            SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
        }
        // Set input focus to the list box.
        SetFocus(hwndList);
        return TRUE;
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        switch (wParam)
        {
        case IDC_BUTTON1: {
            auto hTextBox = GetDlgItem(hDlg, IDC_EDIT1);
            auto length = SendMessage(hTextBox, WM_GETTEXTLENGTH, NULL, NULL);
            auto buffer = new wchar_t[length + 1];
            SendMessage(hTextBox, WM_GETTEXT, length + 1, (LPARAM)buffer);

            auto s = std::wstring(buffer, length);
            //auto list = GetDlgItem(hDlg, IDC_LIST4);
            ListItems.push_back(s);
            HWND hwndList = GetDlgItem(hDlg, IDC_LIST4);
            SendMessage(hwndList, LB_ADDSTRING, 0,
                (LPARAM)ListItems[ListItems.size() - 1].c_str());


            UpdateWindow(hDlg);

        }
            break;
        case IDC_BUTTON2:
        {
            auto List = GetDlgItem(hDlg, IDC_LIST4);
            auto Edit1 = GetDlgItem(hDlg, IDC_EDIT1);
            auto width = SendMessage(Edit1, WM_GETTEXTLENGTH, NULL, NULL);
            auto buffer = new wchar_t[width + 1];
            SendMessage(Edit1, WM_GETTEXT, width + 1, (LPARAM)buffer);
            int row = (int)SendMessage(List, LB_FINDSTRING, 0, (LPARAM)(LPSTR)buffer);
            SendMessage(List, LB_DELETESTRING, row, 0);

        }
        break;
        case IDC_BUTTON3:
        {
            auto List = GetDlgItem(hDlg, IDC_LIST4);
            SendMessage(List, LB_RESETCONTENT, 0, 0);

        }
        }

    }
    return (INT_PTR)FALSE;
}
