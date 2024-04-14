#include "AsPlayer.h"
#include "Moover.h"


//==================================================================================================================
// staticfield initialization
//==================================================================================================================
HBITMAP AsPlayer::Img = 0;
//==================================================================================================================
// constructor & destructor
//==================================================================================================================
AsPlayer::~AsPlayer()
{
}
//==================================================================================================================
AsPlayer::AsPlayer(int x, int y, AsMoover* moover, EObject_Type type)
	:AGame_Object(x, y, type), Moover(moover), Y_Texture_Shift(0), X_Texture_Shift(0), Frame_Tick(0), Is_Mooving(false)
{
}
//==================================================================================================================
// public section
//==================================================================================================================
void AsPlayer::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
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

	x_shift = X_Texture_Shift * ceil_size;
	y_shift = Y_Texture_Shift * ceil_size;

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

	SelectObject(hdc_2, AsPlayer::Img);

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_shift, y_shift, SRCCOPY);
}
//==================================================================================================================
void AsPlayer::Act()
{
	switch ( Pressed_Key )
	{
	case EKT_Up:
		Y_Texture_Shift = 2;
		if ( Moover->Player_Moove(Cx, Cy, 0, this ) )
			Moover->Moove_Object( 0, this );
		break;

	case EKT_Right:
		Y_Texture_Shift = 1;
		if (Moover->Player_Moove(Cx, Cy, 1, this))
			Moover->Moove_Object( 1, this);
		break;

	case EKT_Down:
		Y_Texture_Shift = 0;
		if (Moover->Player_Moove(Cx, Cy, 2, this))
			Moover->Moove_Object( 2, this);
		break;

	case EKT_Left:
		Y_Texture_Shift = 3;
		if (Moover->Player_Moove(Cx, Cy, 3, this))
			Moover->Moove_Object( 3, this);
		break;

	default:
		break;
	}

	if ( Mooving_State != EMooving_State::EMS_None || Pressed_Key != EKT_None )
	{
		++Frame_Tick;
		if (Frame_Tick >= Frame_Tick_Limit)
		{
			Frame_Tick = 0;
			++X_Texture_Shift;
			X_Texture_Shift = X_Texture_Shift % 3;
			if (X_Texture_Shift == 0)
				X_Texture_Shift = 1;
		}
	}
	else
		X_Texture_Shift = 0;

}
//==================================================================================================================
int AsPlayer::On_Key(Ekey_Type key_type, bool on_key_down)
{
	switch (key_type)
	{
	case EKT_Up:
		if (Pressed_Key == EKT_Up)
		{
			if (!on_key_down)
			{
				Pressed_Key = EKT_None;
				break;
			}
		}
		else if (on_key_down)
			Pressed_Key = EKT_Up;
		break;
	case EKT_Right:
		if ( Pressed_Key == EKT_Right )
		{
			if (!on_key_down)
			{
				Pressed_Key = EKT_None;
				break;
			}
		}
		else if (on_key_down)
			Pressed_Key = EKT_Right;
		break;
	case EKT_Down:
		if (Pressed_Key == EKT_Down )
		{
			if (!on_key_down)
			{
				Pressed_Key = EKT_None;
				break;
			}
		}
		else if (on_key_down)
			Pressed_Key = EKT_Down;
		break;
	case EKT_Left:
		if ( Pressed_Key == EKT_Left )
		{
			if (!on_key_down)
			{
				Pressed_Key = EKT_None;
				break;
			}
		}
		else if (on_key_down)
			Pressed_Key = EKT_Left;
		break;
	default:
		break;
	}
	return 0;
}
//==================================================================================================================
// private section:
//==================================================================================================================
void AsPlayer::Create_Bitmap()
{
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frame_dc_instance = AsFrameDc::Get_Instance();
	HDC hdc = frame_dc_instance->Get_SecondDc();
	HDC hdc_2 = frame_dc_instance->Get_Third_Dc();
	AsPlayer::Img = CreateCompatibleBitmap(hdc, 3 * ceil_size, 4 * ceil_size);
	
	SelectObject(hdc, Img);

	//moove to bottom direction
	Draw_Bottom_F1(hdc_2, hdc, 0, 0);
	Draw_Bottom_F2(hdc_2, hdc, 1, 0);
	Draw_Bottom_F3(hdc_2, hdc, 2, 0);

	//moove to right
	Draw_Bottom_F1(hdc_2, hdc, 0, 1);
	Draw_Right_F2(hdc_2, hdc, 1, 1);
	Draw_Right_F3(hdc_2, hdc, 2, 1);

	//moove to top direction
	Draw_Bottom_F1(hdc_2, hdc, 0, 2);
	Draw_Top_F2(hdc_2, hdc, 1, 2);
	Draw_Top_F3(hdc_2, hdc, 2, 2);

	//draw left direction
	Draw_Bottom_F1(hdc_2, hdc, 0, 3);
	StretchBlt(hdc, 1 * ceil_size, 3 * ceil_size, ceil_size, ceil_size,
		hdc, 2 * ceil_size, 1 * ceil_size, -ceil_size, ceil_size, SRCINVERT);
	StretchBlt(hdc, 2 * ceil_size, 3 * ceil_size, ceil_size, ceil_size,
		hdc, 3 * ceil_size, 1 * ceil_size, -ceil_size, ceil_size, SRCINVERT);
}
//==================================================================================================================
void AsPlayer::Draw_Bottom_F1(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	Ellipse(hdc, 10, top_margin, ceil_size - 10, top_margin + head_size);
	//rojki
	Rectangle(hdc, 14, 2, 14 + 2, top_margin + 2);
	Rectangle(hdc, ceil_size - 14, 2, ceil_size - 14 - 2, top_margin + 2);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//shoulders
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + 3, half_ceil_size + half_shoulders, top_margin + head_size + 3 + 2);
	//foots
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height, half_ceil_size + half_shoulders, top_margin + head_size + body_height + 2);
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height + 2, half_ceil_size - half_shoulders + 2, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders - 2, top_margin + head_size + body_height + 2, half_ceil_size + half_shoulders, ceil_size);
	//strechs
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hands
	SelectObject(hdc, AsColors::Pen_White);
	SelectObject(hdc, AsColors::Brush_White);
	Rectangle(hdc, half_ceil_size - half_shoulders - 5, top_margin + head_size + 3 + 3,
		half_ceil_size - half_shoulders - 5 + 4, top_margin + head_size + 3 + 3 + 4);
	Rectangle(hdc, half_ceil_size + half_shoulders + 5, top_margin + head_size + 3 + 3,
		half_ceil_size + half_shoulders + 5 - 4, top_margin + head_size + 3 + 3 + 4);
	//legs
	Rectangle(hdc, half_ceil_size - half_shoulders - 4, ceil_size - 2, half_ceil_size - half_shoulders, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders, ceil_size - 2, half_ceil_size + half_shoulders + 4, ceil_size);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	//eyes
	Rectangle(hdc, 14, top_margin + head_size / 2 - 1, 14 + 2, top_margin + head_size / 2 + 1);
	Rectangle(hdc, ceil_size - 14, top_margin + head_size / 2 - 1, ceil_size - 14 - 2, top_margin + head_size / 2 + 1);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================
void AsPlayer::Draw_Bottom_F2(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	Ellipse(hdc, 10, top_margin, ceil_size - 10, top_margin + head_size);
	//rojki
	Rectangle(hdc, 14, 2, 14 + 2, top_margin + 2);
	Rectangle(hdc, ceil_size - 14, 2, ceil_size - 14 - 2, top_margin + 2);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//shoulders
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + 3, half_ceil_size + half_shoulders, top_margin + head_size + 3 + 2);
	//foots
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height, half_ceil_size + half_shoulders, top_margin + head_size + body_height + 2);
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height + 2, half_ceil_size - half_shoulders + 2, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders - 2, top_margin + head_size + body_height + 2, half_ceil_size + half_shoulders, ceil_size - 3);
	//strechs
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hands
	SelectObject(hdc, AsColors::Pen_White);
	SelectObject(hdc, AsColors::Brush_White);
	Rectangle(hdc, half_ceil_size - half_shoulders - 5, top_margin + head_size + 3 + 3 + 3,
		half_ceil_size - half_shoulders - 5 + 4, top_margin + head_size + 3 + 3 + 4 + 3);
	Rectangle(hdc, half_ceil_size + half_shoulders + 5, top_margin + head_size + 3,
		half_ceil_size + half_shoulders + 5 - 4, top_margin + head_size + 3 + 4);
	//legs
	Rectangle(hdc, half_ceil_size - half_shoulders - 4, ceil_size - 2, half_ceil_size - half_shoulders, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders, ceil_size - 5, half_ceil_size + half_shoulders + 4, ceil_size - 3);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	//eyes
	Rectangle(hdc, 14, top_margin + head_size / 2 - 1, 14 + 2, top_margin + head_size / 2 + 1);
	Rectangle(hdc, ceil_size - 14, top_margin + head_size / 2 - 1, ceil_size - 14 - 2, top_margin + head_size / 2 + 1);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================
void AsPlayer::Draw_Bottom_F3(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	Ellipse(hdc, 10, top_margin, ceil_size - 10, top_margin + head_size);
	//rojki
	Rectangle(hdc, 14, 2, 14 + 2, top_margin + 2);
	Rectangle(hdc, ceil_size - 14, 2, ceil_size - 14 - 2, top_margin + 2);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//shoulders
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + 3, half_ceil_size + half_shoulders, top_margin + head_size + 3 + 2);
	//foots
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height, half_ceil_size + half_shoulders, top_margin + head_size + body_height + 2);
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height + 2, half_ceil_size - half_shoulders + 2, ceil_size - 3);
	Rectangle(hdc, half_ceil_size + half_shoulders - 2, top_margin + head_size + body_height + 2, half_ceil_size + half_shoulders, ceil_size);
	//strechs
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hands
	SelectObject(hdc, AsColors::Pen_White);
	SelectObject(hdc, AsColors::Brush_White);
	Rectangle(hdc, half_ceil_size - half_shoulders - 5, top_margin + head_size + 3 + 3 - 3,
		half_ceil_size - half_shoulders - 5 + 4, top_margin + head_size + 3 + 3 + 4 - 3);
	Rectangle(hdc, half_ceil_size + half_shoulders + 5, top_margin + head_size + 3 + 3 + 3,
		half_ceil_size + half_shoulders + 5 - 4, top_margin + head_size + 3 + 3 + 4 + 3);
	//legs
	Rectangle(hdc, half_ceil_size - half_shoulders - 4, ceil_size - 5, half_ceil_size - half_shoulders, ceil_size - 3);
	Rectangle(hdc, half_ceil_size + half_shoulders, ceil_size - 2, half_ceil_size + half_shoulders + 4, ceil_size);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	//eyes
	Rectangle(hdc, 14, top_margin + head_size / 2 - 1, 14 + 2, top_margin + head_size / 2 + 1);
	Rectangle(hdc, ceil_size - 14, top_margin + head_size / 2 - 1, ceil_size - 14 - 2, top_margin + head_size / 2 + 1);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================
void AsPlayer::Draw_Right_F2(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	MoveToEx(hdc, 10, 5, 0);
	LineTo(hdc, half_ceil_size, 3);
	LineTo(hdc, ceil_size - 10, 6);
	LineTo(hdc, half_ceil_size , 10);
	LineTo(hdc, 10, 8);
	LineTo(hdc, 10, 5);
	FloodFill(hdc, 13, 6, AsColors::MediumSeaGreen);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//foots
	//right
	Rectangle(hdc, half_ceil_size, top_margin + head_size + body_height - 2,
		half_ceil_size + half_shoulders + 2, top_margin + head_size + body_height);
	Rectangle(hdc, half_ceil_size + half_shoulders, top_margin + head_size + body_height - 2,
		half_ceil_size + half_shoulders + 2, ceil_size);

	//left
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size + body_height,
		half_ceil_size - half_body_with + 2, ceil_size - 3);
	Rectangle(hdc, half_ceil_size - half_shoulders - 3, ceil_size - 5,
		half_ceil_size - half_body_with + 2, ceil_size - 3);
	
	//strechs
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hand
	Rectangle(hdc, half_ceil_size, top_margin + head_size + 6,
		half_ceil_size + 10, top_margin + head_size + 9);
	SelectObject(hdc, AsColors::Pen_White);
	SelectObject(hdc, AsColors::Brush_White);
	Rectangle(hdc, half_ceil_size + 10 - 2, top_margin + head_size + 9 - 4,
		half_ceil_size + 10 + 2, top_margin + head_size + 9);
	//legs
	Rectangle(hdc, half_ceil_size - half_shoulders - 2, ceil_size - 5, half_ceil_size - half_shoulders, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders, ceil_size - 2, half_ceil_size + half_shoulders + 4, ceil_size);


	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	//eye
	Rectangle(hdc, ceil_size - 18, 6, ceil_size - 16, 8);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================
void AsPlayer::Draw_Right_F3(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	MoveToEx(hdc, 10, 5, 0);
	LineTo(hdc, half_ceil_size, 3);
	LineTo(hdc, ceil_size - 10, 6);
	LineTo(hdc, half_ceil_size, 10);
	LineTo(hdc, 10, 8);
	LineTo(hdc, 10, 5);
	FloodFill(hdc, 13, 6, AsColors::MediumSeaGreen);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//foots
	//left
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size + body_height,
		half_ceil_size - half_body_with + 2, ceil_size - 3);
	//right
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	Rectangle(hdc, half_ceil_size + half_body_with - 2, top_margin + head_size + body_height,
		half_ceil_size + half_body_with, ceil_size);

	//strechs
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hand
	Rectangle(hdc, half_ceil_size, top_margin + head_size + 6,
		half_ceil_size + 10, top_margin + head_size + 9);
	SelectObject(hdc, AsColors::Pen_White);
	SelectObject(hdc, AsColors::Brush_White);
	Rectangle(hdc, half_ceil_size + 10 - 2, top_margin + head_size + 9 - 4,
		half_ceil_size + 10 + 2, top_margin + head_size + 9);
	//legs
	Rectangle(hdc, half_ceil_size - half_body_with - 2, ceil_size - 5, half_ceil_size - half_body_with, ceil_size);
	Rectangle(hdc, half_ceil_size + half_body_with - 2, ceil_size - 2, half_ceil_size + half_body_with + 3, ceil_size);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);
	//eye
	Rectangle(hdc, ceil_size - 18, 6, ceil_size - 16, 8);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================
void AsPlayer::Draw_Top_F2(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	Ellipse(hdc, 10, top_margin, ceil_size - 10, top_margin + head_size);
	//rojki
	Rectangle(hdc, 14, 2, 14 + 2, top_margin + 2);
	Rectangle(hdc, ceil_size - 14, 2, ceil_size - 14 - 2, top_margin + 2);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//shoulders
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + 3, half_ceil_size + half_shoulders, top_margin + head_size + 3 + 2);
	//foots
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height, half_ceil_size + half_shoulders, top_margin + head_size + body_height + 2);
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height + 2, half_ceil_size - half_shoulders + 2, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders - 2, top_margin + head_size + body_height + 2, half_ceil_size + half_shoulders, ceil_size - 3);
	//strechs
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hands
	Rectangle(hdc, half_ceil_size - half_shoulders - 5, top_margin + head_size + 3 + 3 + 3,
		half_ceil_size - half_shoulders - 5 + 4, top_margin + head_size + 3 + 3 + 4 + 3);
	Rectangle(hdc, half_ceil_size + half_shoulders + 5, top_margin + head_size + 3,
		half_ceil_size + half_shoulders + 5 - 4, top_margin + head_size + 3 + 4);
	//legs
	Rectangle(hdc, half_ceil_size - half_shoulders - 4, ceil_size - 2, half_ceil_size - half_shoulders, ceil_size);
	Rectangle(hdc, half_ceil_size + half_shoulders, ceil_size - 5, half_ceil_size + half_shoulders + 4, ceil_size - 3);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================
void AsPlayer::Draw_Top_F3(HDC hdc, HDC main_dc, int x_, int y_)
{
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	int half_ceil_size = ceil_size / 2;
	int top_margin = 5;
	int head_size = 7;
	int body_height = 18;
	int half_body_with = 3;
	int half_shoulders = 7;

	HBITMAP cur_frame_bitmap = CreateCompatibleBitmap(main_dc, ceil_size, ceil_size);
	SelectObject(hdc, cur_frame_bitmap);

	SelectObject(hdc, AsColors::Pen_MediumSeaGreen);
	SelectObject(hdc, AsColors::Brush_MediumSeaGreen);
	//head
	Ellipse(hdc, 10, top_margin, ceil_size - 10, top_margin + head_size);
	//rojki
	Rectangle(hdc, 14, 2, 14 + 2, top_margin + 2);
	Rectangle(hdc, ceil_size - 14, 2, ceil_size - 14 - 2, top_margin + 2);
	//body
	Rectangle(hdc, half_ceil_size - half_body_with, top_margin + head_size, half_ceil_size + half_body_with, top_margin + head_size + body_height);
	//shoulders
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + 3, half_ceil_size + half_shoulders, top_margin + head_size + 3 + 2);
	//foots
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height, half_ceil_size + half_shoulders, top_margin + head_size + body_height + 2);
	Rectangle(hdc, half_ceil_size - half_shoulders, top_margin + head_size + body_height + 2, half_ceil_size - half_shoulders + 2, ceil_size - 3);
	Rectangle(hdc, half_ceil_size + half_shoulders - 2, top_margin + head_size + body_height + 2, half_ceil_size + half_shoulders, ceil_size);
	//strechs
	SelectObject(hdc, AsColors::Pen_DarkGreen);
	SelectObject(hdc, AsColors::Brush_Bg);
	y_offset = top_margin + head_size + 3;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	y_offset += 6;
	Rectangle(hdc, half_ceil_size - half_body_with, y_offset, half_ceil_size + half_body_with, y_offset + 2);
	//hands
	Rectangle(hdc, half_ceil_size - half_shoulders - 5, top_margin + head_size + 3 + 3 - 3,
		half_ceil_size - half_shoulders - 5 + 4, top_margin + head_size + 3 + 3 + 4 - 3);
	Rectangle(hdc, half_ceil_size + half_shoulders + 5, top_margin + head_size + 3 + 3 + 3,
		half_ceil_size + half_shoulders + 5 - 4, top_margin + head_size + 3 + 3 + 4 + 3);
	//legs
	Rectangle(hdc, half_ceil_size - half_shoulders - 4, ceil_size - 5, half_ceil_size - half_shoulders, ceil_size - 3);
	Rectangle(hdc, half_ceil_size + half_shoulders, ceil_size - 2, half_ceil_size + half_shoulders + 4, ceil_size);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);

	BitBlt(main_dc, x_ * ceil_size, y_ * ceil_size, ceil_size, ceil_size, hdc, 0, 0, SRCCOPY);
	DeleteObject(cur_frame_bitmap);
}
//==================================================================================================================