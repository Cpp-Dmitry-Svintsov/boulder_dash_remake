#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "resource.h"
#include "framework.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <stdexcept>

//sounds
#include "SDL.h"
#include "SDL_mixer.h"
//===================================================================================================================
class AsSettings
{
protected:
	~AsSettings();
	AsSettings();

public:
	AsSettings(AsSettings& other) = delete;
	void operator=(const AsSettings&) = delete;

	static RECT Get_Rect(int x_1, int y_1, int x_2, int y_2);
	
	static const int Global_Scale = 3; 
	static const int TimerId = WM_USER + 1;
	static const int FPS = 30;
	static const int Ceil_Size = 40;
	static const int Game_Area_Width = 1200;
	static const int Game_Area_Height = 720;
	static int Screen_Width;
	static int Screen_Height;

	static const int X_Game_Area_Offset = Ceil_Size;
	static const int Y_Game_Area_Offset = Ceil_Size * 2;
	static const int Game_Area_Ceil_Width = 28;
	static const int Game_Area_Ceil_Height = 15;
	static const int X_Game_Area_Right_Offset = X_Game_Area_Offset + Game_Area_Ceil_Width * Ceil_Size;
	static const int Y_Game_Area_Bottom_Offset = Y_Game_Area_Offset + Game_Area_Ceil_Height * Ceil_Size;

	static RECT Screen_Rect;
};
//===================================================================================================================