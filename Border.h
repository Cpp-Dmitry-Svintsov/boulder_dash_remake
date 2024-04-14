#pragma once
#include "common.h"

class AsBorder
{
public:
	~AsBorder();
	AsBorder();

	void Init(HWND hwnd, HDC hdc_2);

	void Clear_Game_Area(HDC hdc);

private:
	void Draw_Border(HDC hdc);
	void Draw_Border_Elem(HDC hdc, int x, int y);

	HDC Hdc_2;
	HBITMAP Border_Map;
};