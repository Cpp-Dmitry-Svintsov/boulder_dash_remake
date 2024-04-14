#include "Enemys_B.h"

HBITMAP AEnemy_B::Img = 0;
//========================================================================================================
// constructor & destructor
//========================================================================================================
AEnemy_B::~AEnemy_B()
{}
//========================================================================================================
AEnemy_B::AEnemy_B(int x, int y)
	:AGame_Object(x, y, EObject_Type::Enemy_B )
{

}
//========================================================================================================
// public section:
//========================================================================================================
void AEnemy_B::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
	int y_texture_offset)
{
	int ceil_size = AsSettings::Ceil_Size;
	double d_ceil_size = (double)ceil_size;
	int y_top_offset = AsSettings::Y_Game_Area_Offset;
	int x_left_offset = AsSettings::X_Game_Area_Offset;
	int y_bottom_offset = AsSettings::Y_Game_Area_Bottom_Offset;
	int x_right_offset = AsSettings::X_Game_Area_Right_Offset;
	int rx{}, ry{};
	int x_difference{}, y_difference{};
	int x_shift{}, y_shift{};

	x_shift = AEnemy_A::X_Texture_Shift * ceil_size;
	y_shift = 0;

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

	x_shift += x_texture_offset;
	y_shift += y_texture_offset;

	SelectObject(hdc_2, AEnemy_B::Img);

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_shift, y_shift, SRCCOPY);
}
//========================================================================================================
void AEnemy_B::Act()
{

}
//========================================================================================================
void AEnemy_B::Create_Bitmap()
{
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frame_dc_instance = AsFrameDc::Get_Instance();
	HDC main_dc = frame_dc_instance->Get_SecondDc();
	HDC hdc = frame_dc_instance->Get_Third_Dc();
	AEnemy_B::Img = CreateCompatibleBitmap(hdc, 4 * ceil_size, ceil_size);
	HBITMAP One_Frame_Img = CreateCompatibleBitmap(hdc, ceil_size, ceil_size);

	SelectObject(main_dc, AEnemy_B::Img);
	SelectObject(hdc, One_Frame_Img);


	Draw_Frame(hdc, main_dc, 0, AsColors::Brush_DodgerBlue);
	Draw_Frame(hdc, main_dc, 1, AsColors::Brush_DeepBlue);
	Draw_Frame(hdc, main_dc, 2, AsColors::Brush_RoyalBlue);
	Draw_Frame(hdc, main_dc, 3, AsColors::Brush_SkyBlue);


	DeleteObject(One_Frame_Img);

}
//========================================================================================================
// private section:
//========================================================================================================
void AEnemy_B::Draw_Frame(HDC hdc, HDC main_dc, int frame_number, HBRUSH brush)
{
	int frame_x_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int x_start_point{};

	int wings_step = 4;

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	Rectangle(hdc, 0, 0, ceil_size, ceil_size);
	//draw butterfly wings
	SelectObject(hdc, AsColors::Pen_SkyBlue);
	x_start_point = 0 + wings_step * frame_number;
	//left wing
	MoveToEx(hdc, x_start_point, 0, 0);
	LineTo(hdc, half_ceil_size, half_ceil_size);
	LineTo(hdc, x_start_point, ceil_size);
	LineTo(hdc, x_start_point, 0);

	SelectObject(hdc, brush);
	ExtFloodFill(hdc, x_start_point + 2, half_ceil_size, AsColors::BG, FLOODFILLSURFACE);
	//draw stretches
	SelectObject(hdc, AsColors::Pen_DeepBlue);
	MoveToEx(hdc, x_start_point, half_ceil_size, 0);
	LineTo(hdc, half_ceil_size, half_ceil_size);

	MoveToEx(hdc, x_start_point,  5, 0);
	LineTo(hdc, x_start_point + 4, 5);

	MoveToEx(hdc, x_start_point, 10, 0);
	LineTo(hdc, x_start_point + 9, 10);

	MoveToEx(hdc, x_start_point, 15, 0);
	LineTo(hdc, x_start_point + 15, 15);

	MoveToEx(hdc, x_start_point, 25, 0);
	LineTo(hdc, x_start_point + 15, 25);

	MoveToEx(hdc, x_start_point, 30, 0);
	LineTo(hdc, x_start_point + 9, 30);

	MoveToEx(hdc, x_start_point, 35, 0);
	LineTo(hdc, x_start_point + 4, 35);

	//right wing
	SelectObject(hdc, AsColors::Pen_SkyBlue);
	MoveToEx(hdc, ceil_size - x_start_point, 0, 0);
	LineTo(hdc, half_ceil_size, half_ceil_size);
	LineTo(hdc, ceil_size - x_start_point, ceil_size);
	LineTo(hdc, ceil_size - x_start_point, 0);

	ExtFloodFill(hdc, ceil_size- x_start_point - 2, half_ceil_size, AsColors::BG, FLOODFILLSURFACE);

	//draw stretches
	x_start_point = ceil_size - x_start_point;

	SelectObject(hdc, AsColors::Pen_DeepBlue);
	MoveToEx(hdc, x_start_point, half_ceil_size, 0);
	LineTo(hdc, half_ceil_size, half_ceil_size);


	MoveToEx(hdc, x_start_point, 5, 0);
	LineTo(hdc, x_start_point - 4, 5);

	MoveToEx(hdc, x_start_point, 10, 0);
	LineTo(hdc, x_start_point - 9, 10);

	MoveToEx(hdc, x_start_point, 15, 0);
	LineTo(hdc, x_start_point - 15, 15);

	MoveToEx(hdc, x_start_point, 25, 0);
	LineTo(hdc, x_start_point - 15, 25);

	MoveToEx(hdc, x_start_point, 30, 0);
	LineTo(hdc, x_start_point - 9, 30);

	MoveToEx(hdc, x_start_point, 35, 0);
	LineTo(hdc, x_start_point - 4, 35);

	//draw body
	SelectObject(hdc, AsColors::Pen_LightPink);
	SelectObject(hdc, AsColors::Brush_LightPink);
	Ellipse(hdc, half_ceil_size - 3, half_ceil_size - 5, half_ceil_size + 3, half_ceil_size + 5);
	
	frame_x_offset = frame_number * AsSettings::Ceil_Size;
	BitBlt(main_dc, frame_x_offset, 0, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
}
//========================================================================================================