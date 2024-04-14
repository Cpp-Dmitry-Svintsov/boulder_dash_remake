#pragma once
#include "Player_State.h"

class AsMoover;

class AsPlayer : public AGame_Object
{
public:
	~AsPlayer();
	AsPlayer(int x, int y, AsMoover* moover, EObject_Type type);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset);
	void Act();

	int On_Key(Ekey_Type key_type, bool on_key_down);
	static void Create_Bitmap();

	static HBITMAP Img;

private:
	//draw frames bitmap
	//bottom direction
	static void Draw_Bottom_F1(HDC hdc, HDC main_dc, int x_, int y_);
	static void Draw_Bottom_F2(HDC hdc, HDC main_dc, int x_, int y_);
	static void Draw_Bottom_F3(HDC hdc, HDC main_dc, int x_, int y_);
	//right direction
	static void Draw_Right_F2(HDC hdc, HDC main_dc, int x_, int y_);
	static void Draw_Right_F3(HDC hdc, HDC main_dc, int x_, int y_);
	//top direction
	static void Draw_Top_F2(HDC hdc, HDC main_dc, int x_, int y_);
	static void Draw_Top_F3(HDC hdc, HDC main_dc, int x_, int y_);

	int Y_Texture_Shift; // direction
	int X_Texture_Shift; // number of frame in animation
	int Frame_Tick;  // frame ticker
	const int Frame_Tick_Limit = 5; //frame in seconds (30 frame / 5 = 6 frame in second)

	bool Is_Mooving;

	AsPlayer_State Player_State;

	AsMoover* Moover;
};