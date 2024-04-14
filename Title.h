#pragma once
#include "Common.h"

class AsTitle
{
public:
	~AsTitle();
	AsTitle();
	void Init();

	void Draw(HDC hdc);
	void Act();

private:
	void Init_Background();
	void Draw_Init_Elem(int margin, int y_pos, int& x_pos);
	void Upper_Title_Mask();
	void Lower_Title_Mask();

	void Draw_Title_Background(HDC hdc);
	void Draw_Text_Inside_Frame(HDC hdc);
	void Draw_Upper_SubMask(HDC hdc);
	void Draw_Lower_SubMask(HDC hdc);
	void Draw_Info_Text(HDC hdc);

	const int Shadow_Margin_Large = 5;

	const wchar_t* Title_Upper_Str = L"LITTLE";
	const wchar_t* Title_Lower_Str = L"FROG";
	const wchar_t* Info_Str = L"Boulder Dash remake by Svintsov Dmytro 2024";

	int Title_Upper_Str_Len, Title_Lower_Str_Len, Info_Str_Len;
	int Title_X_Upper_Coord;
	int Title_Y_Upper_Pos;
	int Title_X_Lower_Coord;
	int Title_Y_Lower_Pos;
	int Title_Upper_Width, Title_Upper_Height;
	int Title_Lower_Width, Title_Lower_Height;
	int Mask_Animation_Pos;
	int Mask_Step;
	int Large_Font_Color_1_Pos, Large_Font_Color_2_Pos, Large_Font_Color_3_Pos;
	int Large_Font_Color_4_Pos, Large_Font_Color_5_Pos, Large_Font_Color_6_Pos;
	

	int Y_Start_Animation;
	int Current_Y_Start_Animation;
	int Background_X_Start_Pos_1;
	int Background_X_Start_Pos_2;
	int Box_Size;
	int X_Step, Y_Step;
	int Bg_Width, Bg_Height;

	RECT Title_Rect;
	HBITMAP Background_Bitmap;
	HBITMAP Title_Upper_TextMask, Title_Lower_TextMask, Title_Upper_Submask, Title_Lower_Submask;

	HDC Additional_Dc;
	HDC Mask_Dc;
};