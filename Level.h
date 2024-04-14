#pragma once
#include "Level_Data.h"
#include "Terra.h"
#include "Stones.h"
#include "Diamonds.h"
#include "Walls.h"
#include "AsPlayer.h"
#include "Info_Pannel.h"
#include "Enemys_B.h" //include Enymes_A
#include "Finish.h"

class AsLevel
{
public:
	~AsLevel();
	AsLevel();

	void Init(AsCamera *camera, AsPlayer* player, AsMoover* moover, AsInfo_Pannel* info_pannel,
		std::vector<EMessege>* messeges, int *time);

	void Act();
	void Draw(HDC hdc);

	void Init_Level(int level, AsPlayer *player, AsMoover *moover, AsInfo_Pannel* info_pannel);

private:
	void Add_Levels();
	void Clear_Data();

	void Stones_Act();
	void Stones_SubAct(int cur_ind, int level_arry_len, AGame_Object* obj);
	void Stones_SubAct1(int cur_ind, int level_arry_len, AGame_Object* obj);
	void Monster_Kill_Act(int x, int y, bool is_type_b);
	void Create_Bitmaps();
	void Delete_Bitmaps();
	void Message_Processing();

	int Cur_Level_Width;
	int Cur_Level_Height;

	int *Time;

	std::vector<ALevel_Data*> Levels;
	std::vector<EMessege> *Game_Messages;

	ALevel_Data *Current_Level;
	unsigned char* Cur_Level_Array;

	AGame_Object** Game_Objects_Support_Pointer_Array;

	AsPlayer* Player;

	AFinish* Finish;

	AsMoover* Moover;

	AsCamera* Camera;
};