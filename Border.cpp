#include "Border.h"

//==================================================================================================================
// constructor & destructor % init
//==================================================================================================================
AsBorder::~AsBorder()
{
	DeleteObject(Border_Map);
}
//==================================================================================================================
AsBorder::AsBorder()
	:Hdc_2(0), Border_Map(0)
{
}
//==================================================================================================================
void AsBorder::Init(HWND hwnd, HDC hdc_2)
{
	Hdc_2 = hdc_2;
	Border_Map = CreateCompatibleBitmap(hdc_2, AsSettings::Screen_Width, AsSettings::Screen_Height);
	SelectObject(Hdc_2, Border_Map);
	Draw_Border(Hdc_2);
}
//==================================================================================================================
// public section:
//==================================================================================================================
void AsBorder::Clear_Game_Area(HDC hdc)
{
	int a{};
	SelectObject(Hdc_2, Border_Map);

	BitBlt(hdc, 0, 0, AsSettings::Screen_Width, AsSettings::Screen_Height, Hdc_2, 0, 0, SRCCOPY);
	//Draw_Border(hdc);
}
//==================================================================================================================
// private section:
//==================================================================================================================
void AsBorder::Draw_Border(HDC hdc)
{
	int i{};
	//SelectObject(Hdc_2, Bit_Map);

	//draw right border
	for (i = 0; i < 17; ++i)
		Draw_Border_Elem(hdc, 0, AsSettings::Ceil_Size * (i + 1));

	//draw left border
	for (i = 0; i < 17; ++i)
		Draw_Border_Elem(hdc, AsSettings::Game_Area_Width - AsSettings::Ceil_Size, AsSettings::Ceil_Size * (i + 1));

	//draw top border
	for (i = 0; i < 28; ++i)
		Draw_Border_Elem(hdc, AsSettings::Ceil_Size * (i + 1), AsSettings::Ceil_Size);

	//draw bottom border
	for (i = 0; i < 28; ++i)
		Draw_Border_Elem(hdc, AsSettings::Ceil_Size * (i + 1), AsSettings::Game_Area_Height - AsSettings::Ceil_Size);


}
//==================================================================================================================
void AsBorder::Draw_Border_Elem(HDC hdc, int x, int y)
{
	SelectObject(hdc, AsColors::Pen_Peru);
	SelectObject(hdc, AsColors::Brush_Peru);

	Rectangle(hdc, x, y, x + AsSettings::Ceil_Size, y + AsSettings::Ceil_Size);

	SelectObject(hdc, AsColors::Pen_Bg);
	SelectObject(hdc, AsColors::Brush_Bg);

	Rectangle(hdc, x + 5, y + 5, x + 15, y + 15);
	Rectangle(hdc, x + AsSettings::Ceil_Size - 5, y + 5, x + AsSettings::Ceil_Size - 15, y + 15);
	Rectangle(hdc, x + AsSettings::Ceil_Size - 5, y + AsSettings::Ceil_Size - 5,
		x + AsSettings::Ceil_Size - 15, y + AsSettings::Ceil_Size - 15);
	Rectangle(hdc, x + 5, y + AsSettings::Ceil_Size - 5, x + 15, y + AsSettings::Ceil_Size - 15);
}
//==================================================================================================================