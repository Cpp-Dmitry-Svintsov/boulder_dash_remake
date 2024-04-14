#pragma once
#include "Common.h"

class ADiamonds: public AGame_Object
{
public:
	~ADiamonds();
	ADiamonds(int ceil_x, int ceil_y);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);

	static void Create_Bitmap();
	static int Animation_Step;

	static HBITMAP Img;
	static HBITMAP Fon_Img;
	static HBITMAP Mask_Img;

private:
	void Draw_Diamond_Animation(HDC hdc_2, HDC hdc_3);

};