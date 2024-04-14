#pragma once

#include "Game_State.h"
#include "Info_Pannel.h"
#include "Title.h"
#include "Level.h"
#include "Camera.h"
#include "Moover.h"
#include "AsPlayer.h"

//==================================================================================================================
//==================================================================================================================
class AsEngine
{
public:
	~AsEngine();
	AsEngine();
	void Init(HWND hwnd);

	int On_Timer();
	void Draw_Frame(HDC hdc);
	int On_Key(Ekey_Type key_type, bool on_key_down);

private:
	const int Max_Levels = 2;

	int Lives;
	int Time;
	int Current_Level_Number;

	int Frame_Tick;

	void Timer();
	void Messege_Processing();
	void Restart_Level();
	void Next_Level();
	void Init_Audio();
	void Restart_Game();

	std::vector<EMessege> Game_Messages;

	HWND Hwnd;

	AsGame_State Game_State;
	AsInfo_Pannel Info_Pannel;
	AsTitle Game_Title;
	AsLevel Level;
	AsMoover Moover;

	AsPlayer* Player;
	AsCamera* Camera;

	Mix_Music* Main_Theme{nullptr};
	Mix_Chunk* Restart_Level_Sound{};
};
//==================================================================================================================
//==================================================================================================================