#pragma once
#include "Border.h"

class AsCamera
{
protected:
	~AsCamera();
	AsCamera();


public:
	AsCamera(AsCamera& other) = delete;
	void operator=(const AsCamera&) = delete;

	void Init(HWND hwnd);

	void Draw(HDC hdc);
	void Act();

	void Moove(double dx, double dy);
	void Player_Moove(double dx, double dy, double px, double py, EMooving_State direction);
	void Get_Pos(double &x, double &y);

	static AsCamera *Get_Instance();
	static void Delete_Instance();

	void Set_Curr_Level(int width, int height, unsigned char* cur_lvl_arr, AGame_Object** pointer_arr);

private:
	void Get_Texture_Offsets_Pos(int& w_, int& h_);

	static AsCamera* Self;
	const int Camera_Width = AsSettings::Game_Area_Ceil_Width;
	const int Camera_Height = AsSettings::Game_Area_Ceil_Height;
	const int X_Camera_Margin = 1 * AsSettings::Ceil_Size;
	const int Y_Camera_Margin = 2 * AsSettings::Ceil_Size;

	int Cur_Level_Width, Cur_Level_Height;
	int Cx, Cy;
	
	double Rx, Ry;
	double X_Pos;
	double Y_Pos;

	double Min_X_Pos, Min_Y_Pos;
	double Max_X_Pos, Max_Y_Pos;

	HWND Hwnd;
	HDC Frame_Dc_2, Frame_Dc_3;
	RECT Camera_Rect;
	RECT Border_Rect;

	unsigned char* Curr_Level_Array;

	AGame_Object* *Game_Objects_Support_Pointer_Array;

	AsBorder Border;
};