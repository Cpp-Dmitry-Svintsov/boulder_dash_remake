#include "Walls.h"


HBITMAP AWalls::Img = 0;
//================================================================================================================
// constructor & destructor
//================================================================================================================
AWalls::~AWalls()
{
}
//================================================================================================================
AWalls::AWalls(int ceil_x, int ceil_y, EObject_Type type)
	:AGame_Object(ceil_x, ceil_y, type)
{
}
//================================================================================================================
// public section:
//================================================================================================================
void AWalls::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
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

	if ((ry + height) > y_bottom_offset)
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

	SelectObject(hdc_2, AWalls::Img);

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_texture_offset, y_texture_offset, SRCCOPY);
}
//================================================================================================================
void AWalls::Act()
{
}
//================================================================================================================
void AWalls::Create_Bitmap()
{
	int step_size{};
	int i{};
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frameDC = AsFrameDc::Get_Instance();
	HDC hdc = frameDC->Get_SecondDc();
	HDC hdc_2 = frameDC->Get_Third_Dc();
	HBITMAP additional_btmap{};
	AWalls::Img = CreateCompatibleBitmap(hdc, AsSettings::Ceil_Size, AsSettings::Ceil_Size);
	int shadow_margin{};
	int interior_rectangle{};

	SelectObject(hdc, AWalls::Img);

	shadow_margin = 1;
	interior_rectangle = 12;

	SelectObject(hdc, AsColors::Pen_DarkRed);
	SelectObject(hdc, AsColors::Brush_DarkRed);

	Rectangle(hdc, 0, 0, ceil_size, ceil_size);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);

	Rectangle(hdc, 10 + shadow_margin, 10 + shadow_margin, ceil_size - 10 + shadow_margin, ceil_size - 10+ shadow_margin);

	SelectObject(hdc, AsColors::Pen_FireBrick);
	SelectObject(hdc, AsColors::Brush_FireBrick);

	Rectangle(hdc, 10 - shadow_margin, 10 - shadow_margin, ceil_size - 10 - shadow_margin, ceil_size - 10 - shadow_margin);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);

	Rectangle(hdc, interior_rectangle - shadow_margin, interior_rectangle - shadow_margin,
		ceil_size - interior_rectangle - shadow_margin, ceil_size - interior_rectangle - shadow_margin);

	SelectObject(hdc, AsColors::Pen_Indigo);
	MoveToEx(hdc, interior_rectangle - shadow_margin, ceil_size - interior_rectangle - shadow_margin, 0);
	LineTo(hdc, interior_rectangle - shadow_margin, interior_rectangle - shadow_margin);
	LineTo(hdc, ceil_size - interior_rectangle - shadow_margin, interior_rectangle - shadow_margin);
}


//================================================================================================================