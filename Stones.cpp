#include "Stones.h"

HBITMAP AStone::Img = 0;
//================================================================================================================
// constructor & destructor
//================================================================================================================
AStone::~AStone()
{
}
//================================================================================================================
AStone::AStone(int ceil_x, int ceil_y, EObject_Type type)
	:AGame_Object(ceil_x, ceil_y, type)
{
}
//================================================================================================================
// public section:
//================================================================================================================
void AStone::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
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

	SelectObject(hdc_2, AStone::Img);


	BitBlt(hdc, rx, ry, width, height, hdc_2, x_texture_offset, y_texture_offset, SRCCOPY);
}
//================================================================================================================
void AStone::Act()
{
}
//================================================================================================================
void AStone::Create_Bitmap()
{
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frameDC = AsFrameDc::Get_Instance();
	HDC hdc = frameDC->Get_SecondDc();
	AStone::Img = CreateCompatibleBitmap(hdc, AsSettings::Ceil_Size, AsSettings::Ceil_Size);
	SelectObject(hdc, AStone::Img);

	SelectObject(hdc, AsColors::Pen_MediumVioletRed);
	SelectObject(hdc, AsColors::Brush_MediumVioletRed);
	Ellipse(hdc, 1, 1, AsSettings::Ceil_Size - 2, AsSettings::Ceil_Size - 2);

	//Рисуем световой блик
	SelectObject(hdc, AsColors::Pen_White);

	Arc(hdc, 3, 3, AsSettings::Ceil_Size - 6, AsSettings::Ceil_Size - 6,
		5, 0, 0, 5);
	Arc(hdc, 5, 5, AsSettings::Ceil_Size - 10, AsSettings::Ceil_Size - 10,
		10, 0, 0, 10);

	//Рисуем тень
	SelectObject(hdc, AsColors::Pen_DarkRed);

	Arc(hdc, 1, 1, AsSettings::Ceil_Size - 2, AsSettings::Ceil_Size - 2,
		AsSettings::Ceil_Size - 25, AsSettings::Ceil_Size, AsSettings::Ceil_Size, AsSettings::Ceil_Size - 25);

	SelectObject(hdc, AsColors::Pen_Indigo);
	Arc(hdc, 1, 1, AsSettings::Ceil_Size - 2, AsSettings::Ceil_Size - 2,
		AsSettings::Ceil_Size - 10, AsSettings::Ceil_Size, AsSettings::Ceil_Size, AsSettings::Ceil_Size - 10);

	SelectObject(hdc, AsColors::Pen_FireBrick);
	Arc(hdc, 2, 2, AsSettings::Ceil_Size - 4, AsSettings::Ceil_Size - 4,
		AsSettings::Ceil_Size - 15, AsSettings::Ceil_Size, AsSettings::Ceil_Size, AsSettings::Ceil_Size - 15);
}