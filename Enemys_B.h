#pragma once
#include "Enemys_A.h"

class AEnemy_B : public AGame_Object
{
public:
	~AEnemy_B();
	AEnemy_B(int x, int y);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);
	virtual void Act();

	static void Create_Bitmap();

	static HBITMAP Img;

private:
	static void Draw_Frame(HDC hdc, HDC main_dc, int frame_number, HBRUSH brush);
};