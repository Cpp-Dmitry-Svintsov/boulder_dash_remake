#pragma once
#include "Settings.h"

class AsFrameDc
{
protected:
	~AsFrameDc();
	AsFrameDc();

public:
	AsFrameDc(AsFrameDc& other) = delete;
	void operator=(const AsFrameDc&) = delete;

	static AsFrameDc* Get_Instance();
	static void Delete_Instance();

	void Init(HWND hwnd);
	HDC Get_FrameDc();
	HDC Get_SecondDc();
	HDC Get_Third_Dc();

private:
	void Init_InitializationDC__();
	void Init_Frame_Dc(HDC hdc);
	int FrameDc_Width__;
	int FrameDc_Height__;

	HWND Hwnd__;
	HDC Frame_Dc__;
	HDC Frame_Dc_2__;
	HDC Frame_Dc_3__;
	HBITMAP Frame_Bitmap__;
	HBITMAP Initilization_Bitmap__;

	static AsFrameDc* Self__;

};