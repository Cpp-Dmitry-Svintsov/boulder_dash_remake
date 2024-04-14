#pragma once
#include "Colors.h"
#include "commdlg.h"



class AsFonts
{
protected:
	~AsFonts();
	AsFonts();

public:
	AsFonts(AsFonts& other) = delete;
	void operator=(const AsFonts&) = delete;

	static HFONT Greate_Font();
	static HFONT Get_Font(int height, int weight, int family, const wchar_t* arial_name);
	static void Center_Text_To_Rect(HDC hdc, RECT rect, int str_len, const wchar_t* str, int &x_offset, int &y_offset);

	static HFONT Title_Font_Large;
	static HFONT Title_Font_Small;
	static HFONT Info_Pannel_Score_Font;
};
