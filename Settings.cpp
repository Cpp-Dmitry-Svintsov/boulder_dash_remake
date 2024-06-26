#include "Settings.h"

//=======================================================================================================================
// static members section:
//=======================================================================================================================
int AsSettings::Screen_Width = AsSettings::Game_Area_Width;
int AsSettings::Screen_Height = AsSettings::Game_Area_Height;

RECT AsSettings::Screen_Rect = AsSettings::Get_Rect(0, 0, AsSettings::Screen_Width, AsSettings::Screen_Height);
//=======================================================================================================================
// costructor & destructor
//=======================================================================================================================
AsSettings::~AsSettings()
{
}
AsSettings::AsSettings()
{
}
//=======================================================================================================================
// static public methods:
//=======================================================================================================================
RECT AsSettings::Get_Rect(int x_1, int y_1, int x_2, int y_2)
{
	RECT rect{};
	rect.left = x_1;
	rect.top = y_1;
	rect.right = x_2;
	rect.bottom = y_2;
	return rect;
}
//=======================================================================================================================