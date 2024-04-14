#include "Title.h"

//===================================================================================================================
// constructor & destructor & initialization functions
//===================================================================================================================
AsTitle::~AsTitle()
{
	DeleteObject(Background_Bitmap);
	DeleteObject(Title_Upper_TextMask);
	DeleteObject(Title_Lower_TextMask);
	DeleteObject(Title_Upper_Submask);
	DeleteObject(Title_Lower_Submask);
}
//===================================================================================================================
AsTitle::AsTitle()
	:Title_X_Upper_Coord(0), Title_Y_Upper_Pos(0), Title_X_Lower_Coord(0), Title_Y_Lower_Pos(0), Y_Start_Animation(0),
	Title_Upper_Width(0), Title_Upper_Height(0), Title_Lower_Width(0), Title_Lower_Height(0), Mask_Animation_Pos(0),
	Mask_Step(0), Large_Font_Color_1_Pos(0), Large_Font_Color_2_Pos(0), Large_Font_Color_3_Pos(0),
	Large_Font_Color_4_Pos(0), Large_Font_Color_5_Pos(0), Large_Font_Color_6_Pos(0), Current_Y_Start_Animation(0),
	Background_X_Start_Pos_1(0), Background_X_Start_Pos_2(0), Box_Size(5), X_Step(30), Y_Step(15), Bg_Width(0),
	Bg_Height(0), Background_Bitmap(0), Title_Upper_TextMask(0), Title_Lower_TextMask(0), Title_Upper_Submask(0),
	Title_Lower_Submask(0), Additional_Dc(0), Mask_Dc(0)
{
	Title_Upper_Str_Len = wcslen(Title_Upper_Str);
	Title_Lower_Str_Len = wcslen(Title_Lower_Str);
	Info_Str_Len = wcslen(Info_Str);
}
//===================================================================================================================
void AsTitle::Init()
{
	SIZE text_size{};
	AsFrameDc* frameDc = AsFrameDc::Get_Instance();
	int margin = 50;

	//title rect settings
	Title_Rect.left = 10;
	Title_Rect.top = 100;
	Title_Rect.right = AsSettings::Screen_Width - 10 - 15;
	Title_Rect.bottom = AsSettings::Screen_Height - AsSettings::Screen_Height / 3;

	Bg_Width = Title_Rect.right - Title_Rect.left;
	Bg_Height = Title_Rect.bottom - Title_Rect.top;

	Additional_Dc = frameDc->Get_SecondDc();
	Mask_Dc = frameDc->Get_Third_Dc();

	SelectObject(Additional_Dc, AsFonts::Title_Font_Large);
	GetTextExtentPoint32(Additional_Dc, Title_Upper_Str, Title_Upper_Str_Len, &text_size);
	Title_X_Upper_Coord = Title_Rect.right - text_size.cx - margin;
	Title_Y_Upper_Pos = Title_Rect.top + 50;
	Title_Upper_Width = text_size.cx;
	Title_Upper_Height = text_size.cy;

	GetTextExtentPoint32(Additional_Dc, Title_Lower_Str, Title_Lower_Str_Len, &text_size);
	Title_X_Lower_Coord = Title_Rect.right - text_size.cx - margin;
	Title_Y_Lower_Pos = Title_Y_Upper_Pos + 120;
	Title_Lower_Width = text_size.cx;
	Title_Lower_Height = text_size.cy;

	Mask_Step = Title_Lower_Height / 6;
	Large_Font_Color_1_Pos = 0;
	Large_Font_Color_2_Pos = Mask_Step;
	Large_Font_Color_3_Pos = Mask_Step * 2;
	Large_Font_Color_4_Pos = Mask_Step * 3;
	Large_Font_Color_5_Pos = Mask_Step * 4;
	Large_Font_Color_6_Pos = Mask_Step * 5;

	Y_Start_Animation = Title_Rect.top + 15;
	Current_Y_Start_Animation = Y_Start_Animation;
	Background_X_Start_Pos_1 = Title_Rect.left + 15;
	Background_X_Start_Pos_2 = Title_Rect.left;

	//создаем сразу битмап заднего фона для ускорения отрисовки
	Init_Background();
	//создаются маски шрифтоф верхнего и нижнего
	SelectObject(Additional_Dc, AsFonts::Title_Font_Large);
	SetBkMode(Additional_Dc, OPAQUE);
	SetBkColor(Additional_Dc, AsColors::BG);
	SetTextColor(Additional_Dc, AsColors::MaskBg);
	Upper_Title_Mask();
	Lower_Title_Mask();
}
//===================================================================================================================
void AsTitle::Init_Background()
{
	Background_Bitmap = CreateCompatibleBitmap(Additional_Dc, Bg_Width, Bg_Height);
	SelectObject(Additional_Dc, Background_Bitmap);

	int i{}, j{};
	int x_1_pos{}, x_2_pos{};
	int margin = 5;
	int y_pos = 0;

	//draw bacground
	SelectObject(Additional_Dc, AsColors::Pen_RoyalBlue);
	SelectObject(Additional_Dc, AsColors::Brush_RoyalBlue);
	Rectangle(Additional_Dc, 0, 0, Bg_Width, Bg_Height);

	for (i; i < 29; ++i)
	{
		x_1_pos = 0 + 15;
		x_2_pos = 0;
		for (j = 0; j < 40; ++j)
		{
			if ((i + 1) % 2 == 0)
				Draw_Init_Elem(margin, y_pos, x_1_pos);
			else
				Draw_Init_Elem(margin, y_pos, x_2_pos);
		}
		y_pos += Y_Step;
	}
}
//===================================================================================================================
void AsTitle::Draw_Init_Elem(int margin, int y_pos, int &x_pos)
{
	SelectObject(Additional_Dc, AsColors::Pen_Bg);
	SelectObject(Additional_Dc, AsColors::Brush_Bg);
	Rectangle(Additional_Dc, x_pos - margin, y_pos,
		x_pos + Box_Size, y_pos + Box_Size + margin);

	SelectObject(Additional_Dc, AsColors::Pen_SkyBlue);
	SelectObject(Additional_Dc, AsColors::Brush_SkyBlue);
	Rectangle(Additional_Dc, x_pos - 2, y_pos,
		x_pos + Box_Size, y_pos + Box_Size + 2);

	SelectObject(Additional_Dc, AsColors::Pen_White);
	SelectObject(Additional_Dc, AsColors::Brush_White);
	Rectangle(Additional_Dc, x_pos + 1, y_pos,
		x_pos + Box_Size, y_pos + Box_Size - 1);
	x_pos += X_Step;
}
//===================================================================================================================
void AsTitle::Upper_Title_Mask()
{
	Title_Upper_TextMask = CreateCompatibleBitmap(Additional_Dc, Title_Upper_Width, Title_Upper_Height);
	Title_Upper_Submask = CreateCompatibleBitmap(Additional_Dc, Title_Upper_Width, Title_Upper_Height);
	SelectObject(Additional_Dc, Title_Upper_TextMask);

	TextOutW(Additional_Dc, 0, 0, Title_Upper_Str, Title_Upper_Str_Len);
}
//===================================================================================================================
void AsTitle::Lower_Title_Mask()
{
	Title_Lower_TextMask = CreateCompatibleBitmap(Additional_Dc, Title_Lower_Width, Title_Lower_Height);
	Title_Lower_Submask = CreateCompatibleBitmap(Additional_Dc, Title_Lower_Width, Title_Lower_Height);
	SelectObject(Additional_Dc, Title_Lower_TextMask);

	TextOutW(Additional_Dc, 0, 0, Title_Lower_Str, Title_Lower_Str_Len);
}
//===================================================================================================================
//public section:
//===================================================================================================================
void AsTitle::Draw(HDC hdc)
{
	Draw_Title_Background(hdc);

	// draw frame and text
	Draw_Text_Inside_Frame(hdc);

	//draw info game text
	Draw_Info_Text(hdc);

}
//===================================================================================================================
void AsTitle::Act()
{
	// Background Animation
	Current_Y_Start_Animation -= 2;

	if (Current_Y_Start_Animation <= Title_Rect.top - 15)
	{
		Current_Y_Start_Animation = Y_Start_Animation;
	}

	//Title Font animation
	--Large_Font_Color_1_Pos;
	if (Large_Font_Color_1_Pos + Mask_Step < 0)
		Large_Font_Color_1_Pos = Mask_Step * 5;
	
	--Large_Font_Color_2_Pos;
	if (Large_Font_Color_2_Pos + Mask_Step < 0)
		Large_Font_Color_2_Pos = Mask_Step * 5;

	--Large_Font_Color_3_Pos;
	if (Large_Font_Color_3_Pos + Mask_Step < 0)
		Large_Font_Color_3_Pos = Mask_Step * 5;

	--Large_Font_Color_4_Pos;
	if (Large_Font_Color_4_Pos + Mask_Step < 0)
		Large_Font_Color_4_Pos = Mask_Step * 5;

	--Large_Font_Color_5_Pos;
	if (Large_Font_Color_5_Pos + Mask_Step < 0)
		Large_Font_Color_5_Pos = Mask_Step * 5;

	--Large_Font_Color_6_Pos;
	if (Large_Font_Color_6_Pos + Mask_Step < 0)
		Large_Font_Color_6_Pos = Mask_Step * 5;
}
//===================================================================================================================
//private section:
//===================================================================================================================
void AsTitle::Draw_Title_Background(HDC hdc)
{
	
	AsFrameDc* frameDC = AsFrameDc::Get_Instance();
	HDC tick_dc = frameDC->Get_SecondDc();
	SelectObject(tick_dc, Background_Bitmap);

	BitBlt(hdc, Title_Rect.left, Current_Y_Start_Animation, Bg_Width, Bg_Height, tick_dc, 0, 0, SRCCOPY);
}
//===================================================================================================================
void AsTitle::Draw_Text_Inside_Frame(HDC hdc)
{
	//draw frame
	SelectObject(hdc, AsColors::Pen_15_White);
	MoveToEx(hdc, Title_Rect.left, Title_Rect.top, 0);
	LineTo(hdc, Title_Rect.right, Title_Rect.top);
	LineTo(hdc, Title_Rect.right, Title_Rect.bottom);
	LineTo(hdc, Title_Rect.left, Title_Rect.bottom);
	LineTo(hdc, Title_Rect.left, Title_Rect.top);

	
	Draw_Upper_SubMask(hdc);

	Draw_Lower_SubMask(hdc);
}
//===================================================================================================================
void AsTitle::Draw_Upper_SubMask(HDC hdc)
{
	//int Title_Upper_Width, Title_Upper_Height;
	int i{};
	int current_y{};

	SelectObject(Mask_Dc, Title_Upper_TextMask);
	SelectObject(Additional_Dc, Title_Upper_Submask);
	
	// draw shadow:
	GdiTransparentBlt(hdc, Title_X_Upper_Coord + Shadow_Margin_Large, Title_Y_Upper_Pos + Shadow_Margin_Large,
		Title_Upper_Width + Shadow_Margin_Large, Title_Upper_Height + Shadow_Margin_Large,
		Mask_Dc, 0, 0, Title_Upper_Width, Title_Upper_Height, AsColors::BG);

	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

	SelectObject(Additional_Dc, AsColors::Pen_LightPink);
	SelectObject(Additional_Dc, AsColors::Brush_LightPink);
	Rectangle(Additional_Dc, 0, Large_Font_Color_1_Pos, Title_Upper_Width, Large_Font_Color_1_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_Indigo);
	SelectObject(Additional_Dc, AsColors::Brush_Indigo);
	Rectangle(Additional_Dc, 0, Large_Font_Color_2_Pos, Title_Upper_Width, Large_Font_Color_2_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_DodgerBlue);
	SelectObject(Additional_Dc, AsColors::Brush_DodgerBlue);
	Rectangle(Additional_Dc, 0, Large_Font_Color_3_Pos, Title_Upper_Width, Large_Font_Color_3_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_RosyBrown);
	SelectObject(Additional_Dc, AsColors::Brush_RosyBrown);
	Rectangle(Additional_Dc, 0, Large_Font_Color_4_Pos, Title_Upper_Width, Large_Font_Color_4_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_DeepBlue);
	SelectObject(Additional_Dc, AsColors::Brush_DeepBlue);
	Rectangle(Additional_Dc, 0, Large_Font_Color_5_Pos, Title_Upper_Width, Large_Font_Color_5_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_SkyBlue);
	SelectObject(Additional_Dc, AsColors::Brush_SkyBlue);
	Rectangle(Additional_Dc, 0, Large_Font_Color_6_Pos, Title_Upper_Width, Large_Font_Color_6_Pos + Mask_Step);
	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.


	GdiTransparentBlt(Additional_Dc, 0, 0, Title_Upper_Width, Title_Upper_Height,
		Mask_Dc, 0, 0, Title_Upper_Width, Title_Upper_Height, AsColors::MaskBg);

	GdiTransparentBlt(hdc, Title_X_Upper_Coord, Title_Y_Upper_Pos,
		Title_Upper_Width, Title_Upper_Height,
		Additional_Dc, 0, 0, Title_Upper_Width, Title_Upper_Height, AsColors::BG);
}
//===================================================================================================================
void AsTitle::Draw_Lower_SubMask(HDC hdc)
{
	//int Title_Lower_Width, Title_Lower_Height;
	int i{};
	int current_y{};

	SelectObject(Mask_Dc, Title_Lower_TextMask);
	SelectObject(Additional_Dc, Title_Lower_Submask);

	// draw shadow:
	GdiTransparentBlt(hdc, Title_X_Lower_Coord + Shadow_Margin_Large, Title_Y_Lower_Pos + Shadow_Margin_Large,
		Title_Lower_Width + Shadow_Margin_Large, Title_Lower_Height + Shadow_Margin_Large,
		Mask_Dc, 0, 0, Title_Lower_Width, Title_Lower_Height, AsColors::BG);

	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

	SelectObject(Additional_Dc, AsColors::Pen_LightPink);
	SelectObject(Additional_Dc, AsColors::Brush_LightPink);
	Rectangle(Additional_Dc, 0, Large_Font_Color_1_Pos, Title_Lower_Width, Large_Font_Color_1_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_RoyalBlue);
	SelectObject(Additional_Dc, AsColors::Brush_RoyalBlue);
	Rectangle(Additional_Dc, 0, Large_Font_Color_2_Pos, Title_Lower_Width, Large_Font_Color_2_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_Indigo);
	SelectObject(Additional_Dc, AsColors::Brush_Indigo);
	Rectangle(Additional_Dc, 0, Large_Font_Color_3_Pos, Title_Lower_Width, Large_Font_Color_3_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_DodgerBlue);
	SelectObject(Additional_Dc, AsColors::Brush_DodgerBlue);
	Rectangle(Additional_Dc, 0, Large_Font_Color_4_Pos, Title_Lower_Width, Large_Font_Color_4_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_RosyBrown);
	SelectObject(Additional_Dc, AsColors::Brush_RosyBrown);
	Rectangle(Additional_Dc, 0, Large_Font_Color_5_Pos, Title_Lower_Width, Large_Font_Color_5_Pos + Mask_Step);

	SelectObject(Additional_Dc, AsColors::Pen_SkyBlue);
	SelectObject(Additional_Dc, AsColors::Brush_SkyBlue);
	Rectangle(Additional_Dc, 0, Large_Font_Color_6_Pos, Title_Lower_Width, Large_Font_Color_6_Pos + Mask_Step);
	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.


	GdiTransparentBlt(Additional_Dc, 0, 0, Title_Lower_Width, Title_Lower_Height,
		Mask_Dc, 0, 0, Title_Lower_Width, Title_Lower_Height, AsColors::MaskBg);

	GdiTransparentBlt(hdc, Title_X_Lower_Coord, Title_Y_Lower_Pos,
		Title_Lower_Width, Title_Lower_Height,
		Additional_Dc, 0, 0, Title_Lower_Width, Title_Lower_Height, AsColors::BG);
}
//===================================================================================================================
void AsTitle::Draw_Info_Text(HDC hdc)
{
	int y_offset{}, x_offset{};

	y_offset = Title_Rect.bottom + 40;
	x_offset = Title_Rect.left + 20;

	SelectObject(hdc, AsFonts::Title_Font_Small);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, AsColors::Black);
	TextOutW(hdc, x_offset + Shadow_Margin_Large, y_offset + Shadow_Margin_Large, Info_Str, Info_Str_Len);
	SetTextColor(hdc, AsColors::White);
	TextOutW(hdc, x_offset, y_offset, Info_Str, Info_Str_Len);
}
//===================================================================================================================

//===================================================================================================================