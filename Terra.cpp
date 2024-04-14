#include "Terra.h"


HBITMAP ATerra::Img = 0;
//================================================================================================================
// constructor & destructor
//================================================================================================================
ATerra::~ATerra()
{
}
//================================================================================================================
ATerra::ATerra(int ceil_x, int ceil_y, EObject_Type type)
	:AGame_Object(ceil_x, ceil_y, type)
{
}
//================================================================================================================
// public section:
//================================================================================================================
void ATerra::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
	int y_texture_offset)
{
	double d_ceil_size = (double)AsSettings::Ceil_Size;
	int y_top_offset = AsSettings::Y_Game_Area_Offset;
	int x_left_offset = AsSettings::X_Game_Area_Offset;
	int y_bottom_offset = AsSettings::Y_Game_Area_Bottom_Offset;
	int x_right_offset = AsSettings::X_Game_Area_Right_Offset;
	int rx{}, ry{};
	int x_difference{}, y_difference{};

	rx = x_ + (int)(Rx * d_ceil_size);
	ry = y_ + (int)(Ry * d_ceil_size);

	if (ry < y_top_offset)
	{
		y_difference = y_top_offset - ry;
		ry = y_top_offset;
		height -= y_difference;
		y_texture_offset += y_difference;
	}

	if ( (ry + height) > y_bottom_offset)
	{
		y_difference = (ry + height) - y_bottom_offset;
		height = y_difference;
	}

	if (rx < x_left_offset)
	{
		x_difference = x_left_offset - rx;
		rx = x_left_offset;
		width -= x_difference;
		x_texture_offset += x_difference;
	}

	if ((rx + width) > x_right_offset)
	{
		x_difference = (rx + width) - x_right_offset;
		width = x_difference;
	}

	SelectObject(hdc_2, ATerra::Img);

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_texture_offset, y_texture_offset, SRCCOPY);
}
//================================================================================================================
void ATerra::Act()
{
}
//================================================================================================================
void ATerra::Create_Bitmap()
{
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frameDC = AsFrameDc::Get_Instance();
	HDC hdc = frameDC->Get_SecondDc();
	ATerra::Img = CreateCompatibleBitmap(hdc, AsSettings::Ceil_Size, AsSettings::Ceil_Size);
	SelectObject(hdc, ATerra::Img);

	SelectObject(hdc, AsColors::Pen_PeachPuff);
	SelectObject(hdc, AsColors::Brush_PeachPuff);
	Rectangle(hdc, 1, 1, AsSettings::Ceil_Size - 2, AsSettings::Ceil_Size - 2);


	SelectObject(hdc, AsColors::Pen_White);
	MoveToEx(hdc, 2, ceil_size - 2, 0);
	LineTo(hdc, 2, 2);
	LineTo(hdc, ceil_size - 2, 2);
	SelectObject(hdc, AsColors::Pen_DarkRed);
	LineTo(hdc, ceil_size - 2, ceil_size - 2);
	LineTo(hdc, 2, ceil_size - 2);



}
//================================================================================================================