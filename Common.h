#pragma once

#include "Fonts.h"

//=================================================================================================================
//key types enumerate
// перемная для глобального доступа к нажатой клавише
//=================================================================================================================
enum Ekey_Type
{
	EKT_None,
	EKT_Up,
	EKT_Right,
	EKT_Down,
	EKT_Left,
	EKT_Space,

};

static Ekey_Type Pressed_Key;
//=================================================================================================================
//game message enumerate
//=================================================================================================================
enum class EMessege : unsigned char
{
	EM_Player_Hit,
	EM_Player_Dead,
	EM_Next_Level,
	EM_All_Diamond_Collected,
	EM_Player_In_Finish,
};
//=================================================================================================================
// интрфесы для доступа к данным уровня
//=================================================================================================================
enum class EMooving_State : unsigned char
{
	EMS_None,
	EMS_Up,
	EMS_Right,
	EMS_Down,
	EMS_Left
};

enum class EObject_Type : unsigned char
{
	None,
	Player,
	Terra,
	Stone,
	Diamond,
	Wall,
	Enemy_A,
	Enemy_B,
	Finish,
	Tranformator,
	Lava
};

class AGame_Object
{
public:
	virtual ~AGame_Object();
	AGame_Object(int x, int y, EObject_Type type);

	virtual void Draw(HDC hdc, HDC hdc_2, HDC hdc_3, int x_, int y_, int width, int height, int x_texture_offset,
		int y_texture_offset ) = 0;

	void Get_Pos(double& cx, double& cy, double &rx, double &ry);
	void Set_Pos(double cx, double cy, double rx, double & ry);
	void Get_Ceil_Pos(int& x, int &y);
	EObject_Type Get_Type();

	int Direction;
	int Destination[2]{};
	int Start[2]{};

	EMooving_State Mooving_State;

protected:
	EObject_Type Object_Type;

	int Cx, Cy;
	double Rx, Ry;

};
//=================================================================================================================
//=================================================================================================================
// класс одиночка сообщений
//=================================================================================================================

//=================================================================================================================