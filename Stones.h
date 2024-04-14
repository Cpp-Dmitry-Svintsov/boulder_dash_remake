#pragma once
#include "Common.h"

class AStone : public AGame_Object
{
public:
	~AStone();
	AStone(int x, int y, EObject_Type type);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);
	virtual void Act();

	static void Create_Bitmap();

	static HBITMAP Img;
private:
};