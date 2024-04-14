#include "Finish.h"

HBITMAP AFinish::Img = 0;
//========================================================================================================================
// constructor ^ destructor
//========================================================================================================================
AFinish::~AFinish()
{}
AFinish::AFinish(int ceil_x, int ceil_y)
	:AGame_Object(ceil_x, ceil_y, EObject_Type::Finish), Animation_Step(0), X_Texture_Shift(0), Is_Active(false)
{
}
//========================================================================================================================
void AFinish::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
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

	if (Is_Active)
		Active_Act();

	x_shift = X_Texture_Shift * ceil_size;
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

	SelectObject(hdc_2, AFinish::Img);

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_shift, y_shift, SRCCOPY);
}
//========================================================================================================================
void AFinish::Create_Bitmap()
{
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frame_dc = AsFrameDc::Get_Instance();
	HDC main_dc = frame_dc->Get_SecondDc();
	HDC hdc = frame_dc->Get_Third_Dc();
	HBITMAP frame_bitmap = CreateCompatibleBitmap(hdc, ceil_size, ceil_size);
	AFinish::Img = CreateCompatibleBitmap(main_dc, ceil_size * 3, ceil_size);

	SelectObject(main_dc, AFinish::Img);
	SelectObject(hdc, frame_bitmap);

	Create_1_Frame(main_dc, hdc);
	Create_2_Frame(main_dc, hdc);
	Create_3_Frame(main_dc, hdc);

	DeleteObject(frame_bitmap);
}
//========================================================================================================================
void AFinish::Act()
{
	++Animation_Step;
	if (Animation_Step > 15)
	{
		++X_Texture_Shift;
		if (X_Texture_Shift > 2)
			X_Texture_Shift = 1;
		Animation_Step = 0;
	}
}
//========================================================================================================================
// public section
//========================================================================================================================
void AFinish::Create_1_Frame(HDC main_dc, HDC hdc)
{
	int x_offset{};
	int ceil_size{};
	int margin_1{};
	int dimension_1{};

	int i{}, j{};
	int x_{}, y_{};

	x_offset = 0;
	ceil_size = AsSettings::Ceil_Size;

	//draw osnova

	SelectObject(hdc, AsColors::Pen_Peru);
	SelectObject(hdc, AsColors::Brush_Peru);

	Rectangle(hdc, 0, 0, ceil_size, ceil_size);

	//draw frame
	margin_1 = 5;

	SelectObject(hdc, AsColors::Pen_Bg);
	MoveToEx(hdc, ceil_size - margin_1, margin_1, 0);
	LineTo(hdc, ceil_size - margin_1, ceil_size - margin_1);
	LineTo(hdc, margin_1, ceil_size - margin_1);
	SelectObject(hdc, AsColors::Pen_LightPink);
	LineTo(hdc, margin_1, margin_1);
	LineTo(hdc, ceil_size - margin_1, margin_1);

	//draw rectangle inside
	dimension_1 = 5;

	SelectObject(hdc, AsColors::Brush_Bg);

	y_ = 12;
	for (i = 0; i < 2; ++i)
	{
		x_ = 12;
		for (j = 0; j < 2; ++j)
		{
			SelectObject(hdc, AsColors::Pen_Bg);
			Rectangle(hdc, x_, y_, x_ + dimension_1, y_ + dimension_1);
			SelectObject(hdc, AsColors::Pen_1_White);
			MoveToEx(hdc, x_, y_ + dimension_1, 0);
			LineTo(hdc, x_, y_);
			LineTo(hdc, x_ + dimension_1, y_);
			x_ += 12;
		}
		y_ += 12;
	}

	BitBlt(main_dc, x_offset * ceil_size, 0, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
}
//========================================================================================================================
void AFinish::Create_2_Frame(HDC main_dc, HDC hdc)
{
	int x_offset{};
	int ceil_size{};
	int margin_1{};
	int dimension_1{};


	x_offset = 1;
	ceil_size = AsSettings::Ceil_Size;

	//draw osnova

	SelectObject(hdc, AsColors::Pen_Peru);
	SelectObject(hdc, AsColors::Brush_Peru);

	Rectangle(hdc, 0, 0, ceil_size, ceil_size);

	//draw frame
	margin_1 = 5;

	SelectObject(hdc, AsColors::Pen_Bg);
	MoveToEx(hdc, ceil_size - margin_1, margin_1, 0);
	LineTo(hdc, ceil_size - margin_1, ceil_size - margin_1);
	LineTo(hdc, margin_1, ceil_size - margin_1);
	SelectObject(hdc, AsColors::Pen_LightPink);
	LineTo(hdc, margin_1, margin_1);
	LineTo(hdc, ceil_size - margin_1, margin_1);

	//draw rectangle inside

	margin_1 = 7;

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	Rectangle(hdc, margin_1, margin_1, ceil_size - margin_1, ceil_size - margin_1);

	BitBlt(main_dc, x_offset * ceil_size, 0, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
}
//========================================================================================================================
void AFinish::Create_3_Frame(HDC main_dc, HDC hdc)
{
	int x_offset{};
	int ceil_size{};
	int margin_1{};
	int dimension_1{};


	x_offset = 2;
	ceil_size = AsSettings::Ceil_Size;

	//draw osnova

	SelectObject(hdc, AsColors::Pen_Peru);
	SelectObject(hdc, AsColors::Brush_Peru);

	Rectangle(hdc, 0, 0, ceil_size, ceil_size);

	//draw frame
	margin_1 = 5;

	SelectObject(hdc, AsColors::Pen_Bg);
	MoveToEx(hdc, ceil_size - margin_1, margin_1, 0);
	LineTo(hdc, ceil_size - margin_1, ceil_size - margin_1);
	LineTo(hdc, margin_1, ceil_size - margin_1);
	SelectObject(hdc, AsColors::Pen_LightPink);
	LineTo(hdc, margin_1, margin_1);
	LineTo(hdc, ceil_size - margin_1, margin_1);

	//draw rectangle inside
	margin_1 = 7;

	SelectObject(hdc, AsColors::Pen_RosyBrown);
	SelectObject(hdc, AsColors::Brush_RosyBrown);
	Rectangle(hdc, margin_1, margin_1, ceil_size - margin_1, ceil_size - margin_1);

	BitBlt(main_dc, x_offset * ceil_size, 0, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
}
//========================================================================================================================
void AFinish::Active_Act()
{
	++Animation_Step;
	if (Animation_Step > 5)
	{
		Animation_Step = 0;
		++X_Texture_Shift;
		if (X_Texture_Shift > 2)
			X_Texture_Shift = 1;
	}
}
//========================================================================================================================
