#include "main.h"

//=====================================================================================================================
//=====================================================================================================================
// Global variables:
//=====================================================================================================================
AsWindow Window;
//=====================================================================================================================
// function main -> point of start
//=====================================================================================================================
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    //Создания класа окна
    return Window.Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
//=====================================================================================================================
//=====================================================================================================================
// class AsWindow
//=====================================================================================================================
// static fields members
//=====================================================================================================================
AsWindow* AsWindow::Self__ = nullptr;
//=====================================================================================================================
// constructor & destructor
//=====================================================================================================================
AsWindow::~AsWindow()
{
    Self__ = nullptr;

    //delete all singeltons
    AsFrameDc::Delete_Instance();
    AsCamera::Delete_Instance();
}
//=====================================================================================================================
AsWindow::AsWindow()
    :Instance{}, szTitle{}, szWindowClass{}, Hwnd{}, Frame_Dc{}
{
    Self__ = this;
}
//=====================================================================================================================
//public section:
//=====================================================================================================================
int APIENTRY AsWindow::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    Instance = hInstance;

    // Initialize global strings
    LoadStringW(Instance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(Instance, IDC_BOULDERDASH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass();

    // Perform application initialization:
    if (!InitInstance (nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(Instance, MAKEINTRESOURCE(IDC_BOULDERDASH));

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
//=====================================================================================================================
//private section:
//=====================================================================================================================
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
LRESULT CALLBACK AsWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            DialogBox(Self__->Instance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
        Self__->On_Paint();
        break;

    case WM_TIMER:
        if (wParam == AsSettings::TimerId)
            return Self__->Engine.On_Timer();
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:
            return Self__->Engine.On_Key(EKT_Up, true);
        case VK_RIGHT:
            return Self__->Engine.On_Key(EKT_Right, true);
        case VK_DOWN:
            return Self__->Engine.On_Key(EKT_Down, true);
        case VK_LEFT:
            return Self__->Engine.On_Key(EKT_Left, true);
        case VK_SPACE:
            return Self__->Engine.On_Key(EKT_Space, true);
        }
        break;

    case WM_KEYUP:
        switch (wParam)
        {
        case VK_UP:
            return Self__->Engine.On_Key(EKT_Up, false);
        case VK_RIGHT:
            return Self__->Engine.On_Key(EKT_Right, false);
        case VK_DOWN:
            return Self__->Engine.On_Key(EKT_Down, false);
        case VK_LEFT:
            return Self__->Engine.On_Key(EKT_Left, false);
        }
        break;



    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_ERASEBKGND:
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK AsWindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM AsWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = Instance;
    wcex.hIcon          = LoadIcon(Instance, MAKEINTRESOURCE(IDI_BOULDERDASH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = AsColors::Brush_Bg;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BOULDERDASH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
//=====================================================================================================================
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL AsWindow::InitInstance(int nCmdShow)
{
    //Подсчитываем правильный размер окна
    AdjustWindowRect(&AsSettings::Screen_Rect, WS_OVERLAPPEDWINDOW - WS_THICKFRAME, TRUE);
    AsSettings::Screen_Width = AsSettings::Screen_Rect.right - AsSettings::Screen_Rect.left;
    AsSettings::Screen_Height = AsSettings::Screen_Rect.bottom - AsSettings::Screen_Rect.top;

    //WS_OVERLAPPEDWINDOW - WS_THICKFRAME чтобы размер окна нельзя бло изменить
    Hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW - WS_THICKFRAME,
        0, 0, AsSettings::Screen_Width, AsSettings::Screen_Height,
        nullptr, nullptr, Instance, nullptr);

    //init Engine and FrameDc class
    Engine.Init(Hwnd);
    AsFrameDc* ClassFrameDc = AsFrameDc::Get_Instance();
    Frame_Dc = ClassFrameDc->Get_FrameDc();

    if (!Hwnd)
    {
        return FALSE;
    }

    ShowWindow(Hwnd, nCmdShow);
    UpdateWindow(Hwnd);

    return TRUE;
}
//=====================================================================================================================
void AsWindow::On_Paint()
{
    PAINTSTRUCT ps{};
    HDC hdc{};

    hdc = BeginPaint(Hwnd, &ps);

    Engine.Draw_Frame(Frame_Dc);
    //Engine.Draw_Frame(hdc);

    BitBlt(hdc, 0, 0, AsSettings::Screen_Width, AsSettings::Screen_Height, Frame_Dc, 0, 0, SRCCOPY);

    EndPaint(Hwnd, &ps);
}
//=====================================================================================================================
