#include "Enemys_A.h"

HBITMAP AEnemy_A::Img = 0;
int AEnemy_A::Frame_Tick = 0;
int AEnemy_A::X_Texture_Shift = 0;
//========================================================================================================
// constructor & destructor
//========================================================================================================
AEnemy_A::~AEnemy_A()
{}
//========================================================================================================
AEnemy_A::AEnemy_A(int x, int y)
	:AGame_Object(x, y, EObject_Type::Enemy_A )
{
}
//========================================================================================================
// public section:
//========================================================================================================
void AEnemy_A::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
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

	SelectObject(hdc_2, AEnemy_A::Img);

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_shift, y_shift, SRCCOPY);
}
//========================================================================================================
void AEnemy_A::Act()
{

}
//========================================================================================================
void AEnemy_A::Create_Bitmap()
{
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frame_dc_instance = AsFrameDc::Get_Instance();
	HDC main_dc = frame_dc_instance->Get_SecondDc();
	HDC hdc = frame_dc_instance->Get_Third_Dc();
	AEnemy_A::Img = CreateCompatibleBitmap(hdc, 4 * ceil_size, ceil_size);
	HBITMAP One_Frame_Img = CreateCompatibleBitmap(hdc, ceil_size, ceil_size);

	SelectObject(main_dc, AEnemy_A::Img);
	SelectObject(hdc, One_Frame_Img );

	Draw_Frame(hdc, main_dc, AsColors::Pen_Bg, AsColors::Brush_Bg, AsColors::Pen_DarkRed, AsColors::Brush_DarkRed,
		AsColors::Pen_RoyalBlue, AsColors::Brush_RoyalBlue, AsColors::Pen_White, AsColors::Brush_White, 0);

	Draw_Frame(hdc, main_dc, AsColors::Pen_DarkRed, AsColors::Brush_DarkRed, AsColors::Pen_RoyalBlue, AsColors::Brush_RoyalBlue,
		AsColors::Pen_White, AsColors::Brush_White, AsColors::Pen_Bg, AsColors::Brush_Bg, 1);

	Draw_Frame(hdc, main_dc, AsColors::Pen_RoyalBlue, AsColors::Brush_RoyalBlue, AsColors::Pen_White, AsColors::Brush_White,
		AsColors::Pen_Bg, AsColors::Brush_Bg, AsColors::Pen_DarkRed, AsColors::Brush_DarkRed, 2);

	Draw_Frame(hdc, main_dc, AsColors::Pen_White, AsColors::Brush_White, AsColors::Pen_Bg, AsColors::Brush_Bg,
		AsColors::Pen_DarkRed, AsColors::Brush_DarkRed, AsColors::Pen_RoyalBlue, AsColors::Brush_RoyalBlue, 3);

	DeleteObject(One_Frame_Img);

}
//========================================================================================================
// private section:
//========================================================================================================
void AEnemy_A::Draw_Frame(HDC hdc, HDC main_dc, HPEN pen_1, HBRUSH brush_1, HPEN pen_2, HBRUSH brush_2,
	HPEN pen_3, HBRUSH brush_3, HPEN pen_4, HBRUSH brush_4, int frame_number)
{
	int frame_x_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int half_square_1 = half_ceil_size;
	int half_square_2 = 15;
	int half_square_3 = 10;
	int half_square_4 = 5;

	SelectObject(hdc, pen_1);
	SelectObject(hdc, brush_1);
	Rectangle(hdc, half_ceil_size - half_square_1, half_ceil_size - half_square_1,
		half_ceil_size + half_square_1, half_ceil_size + half_square_1);

	SelectObject(hdc, pen_2);
	SelectObject(hdc, brush_2);
	Rectangle(hdc, half_ceil_size - half_square_2, half_ceil_size - half_square_2,
		half_ceil_size + half_square_2, half_ceil_size + half_square_2);

	SelectObject(hdc, pen_3);
	SelectObject(hdc, brush_3);
	Rectangle(hdc, half_ceil_size - half_square_3, half_ceil_size - half_square_3,
		half_ceil_size + half_square_3, half_ceil_size + half_square_3);

	SelectObject(hdc, pen_4);
	SelectObject(hdc, brush_4);
	Rectangle(hdc, half_ceil_size - half_square_4, half_ceil_size - half_square_4,
		half_ceil_size + half_square_4, half_ceil_size + half_square_4);
	
	frame_x_offset = frame_number * AsSettings::Ceil_Size;
	BitBlt(main_dc, frame_x_offset, 0, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
}
//========================================================================================================