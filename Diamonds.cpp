#include "Diamonds.h"



int ADiamonds::Animation_Step = 0;
HBITMAP ADiamonds::Img = 0;
HBITMAP ADiamonds::Fon_Img = 0;
HBITMAP ADiamonds::Mask_Img = 0;
//================================================================================================================
// constructor & destructor
//================================================================================================================
ADiamonds::~ADiamonds()
{
}
//================================================================================================================
ADiamonds::ADiamonds(int ceil_x, int ceil_y)
	:AGame_Object(ceil_x, ceil_y, EObject_Type::Diamond )
{
}
//================================================================================================================
// public section:
//================================================================================================================
void ADiamonds::Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
	int y_texture_offset)
{
	double d_ceil_size = (double)AsSettings::Ceil_Size;
	int y_top_offset = AsSettings::Y_Game_Area_Offset;
	int x_left_offset = AsSettings::X_Game_Area_Offset;
	int y_bottom_offset = AsSettings::Y_Game_Area_Bottom_Offset;
	int x_right_offset = AsSettings::X_Game_Area_Right_Offset;
	int rx{}, ry{};
	int x_difference{}, y_difference{};

	Draw_Diamond_Animation(hdc_2, hdc_3);

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

	BitBlt(hdc, rx, ry, width, height, hdc_2, x_texture_offset, y_texture_offset, SRCCOPY);
}
//================================================================================================================
void ADiamonds::Create_Bitmap()
{
	int fon_step_size{};
	int y_offset{};
	int ceil_size = AsSettings::Ceil_Size;
	AsFrameDc* frameDC = AsFrameDc::Get_Instance();
	HDC hdc = frameDC->Get_SecondDc();
	ADiamonds::Img = CreateCompatibleBitmap(hdc, AsSettings::Ceil_Size, AsSettings::Ceil_Size);
	ADiamonds::Fon_Img = CreateCompatibleBitmap(hdc, AsSettings::Ceil_Size, AsSettings::Ceil_Size * 2);
	ADiamonds::Mask_Img = CreateCompatibleBitmap(hdc, AsSettings::Ceil_Size, AsSettings::Ceil_Size);

	//Создается маска для брилиантов
	SelectObject(hdc, ADiamonds::Mask_Img);

	SelectObject(hdc, AsColors::Pen_MaskBg);
	SelectObject(hdc, AsColors::Brush_MaskBg);
	Ellipse(hdc, 1, 1, ceil_size - 2, ceil_size - 2);

	//Создается задний фон для маски

	fon_step_size = 5;
	SelectObject(hdc, ADiamonds::Fon_Img);

	SelectObject(hdc, AsColors::Pen_Indigo);
	SelectObject(hdc, AsColors::Brush_Indigo);
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;

	SelectObject(hdc, AsColors::Pen_SkyBlue);
	SelectObject(hdc, AsColors::Brush_SkyBlue);
	y_offset = fon_step_size;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;
	Rectangle(hdc, 0, y_offset, ceil_size, y_offset + fon_step_size);
	y_offset += fon_step_size * 3;

}
//================================================================================================================
// private section:
//================================================================================================================
void ADiamonds::Draw_Diamond_Animation(HDC hdc_2, HDC hdc_3)
{
	int y_anim_offset{};
	int ceil_size = AsSettings::Ceil_Size;

	SelectObject(hdc_2, ADiamonds::Img);
	//копируем задний фон
	y_anim_offset = 3 * 5  - (ADiamonds::Animation_Step) / 2;
	SelectObject(hdc_3, ADiamonds::Fon_Img);
	BitBlt(hdc_2, 0, 0, ceil_size, ceil_size, hdc_3, 0, y_anim_offset, SRCCOPY);
	//копируем маску
	SelectObject(hdc_3, ADiamonds::Mask_Img);
	GdiTransparentBlt(hdc_2, 0, 0, ceil_size, ceil_size, hdc_3, 0, 0, ceil_size, ceil_size, AsColors::MaskBg);

	//Рисуем световой блик
	SelectObject(hdc_2, AsColors::Pen_White);

	Arc(hdc_2, 1, 1, AsSettings::Ceil_Size - 2, AsSettings::Ceil_Size - 2,
		20, 0, 0, 20);

	Arc(hdc_2, 8, 8, AsSettings::Ceil_Size - 16, AsSettings::Ceil_Size - 16,
		7, 0, 0, 7);


}
//================================================================================================================