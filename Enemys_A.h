#pragma once
#include "Common.h"

class AEnemy_A : public AGame_Object
{
public:
	~AEnemy_A();
	AEnemy_A(int x, int y);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);
	virtual void Act();

	static void Create_Bitmap();

	static int Frame_Tick;  // frame ticker
	static const int Frame_Tick_Limit = 3; //frame in seconds (30 frame / 5 = 6 frame in second)
	static int X_Texture_Shift;

	static HBITMAP Img;

private:
	static void Draw_Frame(HDC hdc, HDC main_dc, HPEN pen_1, HBRUSH brush_1,HPEN pen_2, HBRUSH brush_2,
		HPEN pen_3, HBRUSH brush_3, HPEN pen_4, HBRUSH brush_4, int frame_number);
};
