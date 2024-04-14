#include "frameDc.h"

//===================================================================================================================
// static members
//===================================================================================================================
AsFrameDc* AsFrameDc::Self__ = nullptr;
//===================================================================================================================
// constructor % destructor
//===================================================================================================================
AsFrameDc::~AsFrameDc()
{

	DeleteObject(Frame_Dc__);
	DeleteObject(Frame_Dc_2__);
	DeleteObject(Frame_Dc_3__);
	DeleteObject(Frame_Bitmap__);
	DeleteObject(Initilization_Bitmap__);
}
//===================================================================================================================
AsFrameDc::AsFrameDc()
	:Hwnd__(0), FrameDc_Width__(0), FrameDc_Height__(0), Frame_Dc__(0), Frame_Dc_2__(0), Frame_Dc_3__(0)
{
}
//===================================================================================================================
// public static methods:
//===================================================================================================================
AsFrameDc *AsFrameDc::Get_Instance()
{
	if (Self__ == nullptr)
		Self__ = new AsFrameDc();
	return Self__;
}
//===================================================================================================================
void AsFrameDc::Delete_Instance()
{
	if (Self__ != nullptr)
		delete Self__;
}
//===================================================================================================================
// public section:
//===================================================================================================================
void AsFrameDc::Init(HWND hwnd)
{
	HDC cur_dc{};
	Hwnd__ = hwnd;

	cur_dc = GetDC(Hwnd__);
	Init_Frame_Dc(cur_dc);

	Init_InitializationDC__();
}
//===================================================================================================================
HDC AsFrameDc::Get_FrameDc()
{
	return Frame_Dc__;
}
//===================================================================================================================
HDC AsFrameDc::Get_SecondDc()
{
	SelectObject(Frame_Dc_2__, Initilization_Bitmap__);
	return Frame_Dc_2__;
}
//===================================================================================================================

//===================================================================================================================
HDC AsFrameDc::Get_Third_Dc()
{
	return Frame_Dc_3__;
}
//===================================================================================================================
// private section:
//===================================================================================================================
void AsFrameDc::Init_InitializationDC__()
{
	RECT area_rect;
	HDC current_dc;

	if (Frame_Dc_2__ == nullptr && Frame_Dc_3__ == nullptr, Initilization_Bitmap__ == nullptr )
	{
		current_dc = GetDC(Hwnd__);
		GetClientRect(Hwnd__, &area_rect);
		FrameDc_Width__ = area_rect.right - area_rect.left;
		FrameDc_Height__ = area_rect.bottom - area_rect.top;
		Frame_Dc_2__ = CreateCompatibleDC(current_dc);
		Frame_Dc_3__ = CreateCompatibleDC(current_dc);
		Initilization_Bitmap__ = CreateCompatibleBitmap(current_dc, FrameDc_Width__, FrameDc_Height__);
	}
}
//===================================================================================================================
void AsFrameDc::Init_Frame_Dc(HDC hdc)
{

	if (Frame_Dc__ == nullptr && Frame_Bitmap__ == nullptr)
	{
		RECT area_rect;

		GetClientRect(Hwnd__, &area_rect);
		FrameDc_Width__ = area_rect.right - area_rect.left;
		FrameDc_Height__ = area_rect.bottom - area_rect.top;
		Frame_Bitmap__ = CreateCompatibleBitmap(hdc, FrameDc_Width__, FrameDc_Height__);
		Frame_Dc__ = CreateCompatibleDC(hdc);

		SelectObject(Frame_Dc__, Frame_Bitmap__);
	}

}
//===================================================================================================================