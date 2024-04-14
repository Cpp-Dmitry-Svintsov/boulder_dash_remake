#pragma once
#include "Common.h"

class AsMoover;
//============================================================================================================================
class AsInfo_Pannel
{
public:
	~AsInfo_Pannel();
	AsInfo_Pannel();
	void Init(AsMoover *moover, int* lives, int *time, int *level_number);

	void Act();
	void Draw_Game_Info_Panel(HDC hdc);

private:
	int* Diamonds;
	int* Lives;
	int* Time;
	int* Level_Number;
	int Target;

	int Shadow_Margin = 3;

	AsMoover* Moover;
};