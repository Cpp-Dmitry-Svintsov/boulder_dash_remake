#pragma once
#include "Common.h"

class AWalls : public AGame_Object
{
public:
	~AWalls();
	AWalls(int ceil_x, int ceil_y, EObject_Type type);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);
	virtual void Act();

	static void Create_Bitmap();


	static HBITMAP Img;
private:
};
