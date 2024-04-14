#pragma once

#include "Engine.h"


//=================================================================================================================
//=================================================================================================================
class AsWindow
{
public:
	~AsWindow();
	AsWindow();
	int APIENTRY Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

private:
	static const int MAX_LOADSTRING = 100;

	static AsWindow* Self__;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	ATOM MyRegisterClass();
	BOOL InitInstance(int nCmdShow);
	void On_Paint();

	// Global Variables:
	HINSTANCE Instance;										// current instance
	WCHAR szTitle[AsWindow::MAX_LOADSTRING];                // The title bar text
	WCHAR szWindowClass[AsWindow::MAX_LOADSTRING];          // the main window class name
	HWND Hwnd;
	AsEngine Engine;
	HDC Frame_Dc;
};
