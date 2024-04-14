#pragma once
#include "Common.h"

//===============================================================================================================
class AFinish : public AGame_Object
{
public:
	~AFinish();
	AFinish(int ceil_x, int ceil_y);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);

	static void Create_Bitmap();
	void Act();

	static HBITMAP Img;

	bool Is_Active;

private:
	static void Create_1_Frame(HDC main_dc, HDC hdc);
	static void Create_2_Frame(HDC main_dc, HDC hdc);
	static void Create_3_Frame(HDC main_dc, HDC hdc);

	void Active_Act();

	int Animation_Step;
	int X_Texture_Shift;
};