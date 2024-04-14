#include "Info_Pannel.h"
#include "Moover.h"

//=====================================================================================================================
// constructor & destructor:
//=====================================================================================================================
AsInfo_Pannel::~AsInfo_Pannel()
{
}
//=====================================================================================================================
AsInfo_Pannel::AsInfo_Pannel()
	:Diamonds(nullptr), Target(0)
{
}
//=====================================================================================================================
// public section:
//=====================================================================================================================
void AsInfo_Pannel::Init(AsMoover* moover, int *lives, int* time, int* level_number)
{
	Moover = moover;
	Lives = lives;
	Time = time;
	Level_Number = level_number;
}
//=====================================================================================================================
void AsInfo_Pannel::Act()
{

}
//=====================================================================================================================
void AsInfo_Pannel::Draw_Game_Info_Panel(HDC hdc)
{
	int target{}, diamonds{};

	const int target_str_len = 12;
	wchar_t target_str[target_str_len];
	int target_str_pos = 20;

	const int diamonds_str_len = 11;
	wchar_t diamonds_str[diamonds_str_len];
	int value_str_pos = target_str_pos + 250;

	const int lives_str_len = 10;
	wchar_t lives_str[lives_str_len];
	int lives_str_pos = value_str_pos + 300;
	int lives{};

	const int time_str_len = 10;
	wchar_t time_str[time_str_len];
	int time_str_pos = lives_str_pos + 250;
	int time{};

	const int level_number_str_len = 10;
	wchar_t level_number_str[level_number_str_len];
	int level_number_str_pos = time_str_pos + 200;
	int level_number{};


	Moover->Get_Count_Of_Diamonds(target, diamonds);

	//Target str

	swprintf(target_str, target_str_len, L"TARGET: %0*d", 3, target);

	SelectObject(hdc, AsFonts::Info_Pannel_Score_Font);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, AsColors::Indigo );
	TextOutW(hdc, target_str_pos + Shadow_Margin, 0 + Shadow_Margin, target_str, target_str_len);
	SetTextColor(hdc, AsColors::White );
	TextOutW(hdc, target_str_pos, 0, target_str, target_str_len);

	//value str

	swprintf(diamonds_str, diamonds_str_len, L"VALUE: %0*d", 3, diamonds);

	SetTextColor(hdc, AsColors::Indigo);
	TextOutW(hdc, value_str_pos + Shadow_Margin, 0 + Shadow_Margin, diamonds_str, diamonds_str_len);
	SetTextColor(hdc, AsColors::White);
	TextOutW(hdc, value_str_pos, 0, diamonds_str, diamonds_str_len);

	//Lives str

	lives = *(Lives);

	swprintf(lives_str, lives_str_len, L"Lifes: %0*d", 2, lives);

	SetTextColor(hdc, AsColors::Indigo);
	TextOutW(hdc, lives_str_pos + Shadow_Margin, 0 + Shadow_Margin, lives_str, lives_str_len);
	SetTextColor(hdc, AsColors::White);
	TextOutW(hdc, lives_str_pos, 0, lives_str, lives_str_len);

	//time str

	time = *(Time);

	swprintf(time_str, time_str_len, L"TIME: %0*d", 3, time);

	SetTextColor(hdc, AsColors::Indigo);
	TextOutW(hdc, time_str_pos + Shadow_Margin, 0 + Shadow_Margin, time_str, time_str_len);
	SetTextColor(hdc, AsColors::White);
	TextOutW(hdc, time_str_pos, 0, time_str, time_str_len);

	//time str

	level_number = *(Level_Number);

	swprintf(level_number_str, level_number_str_len, L"LEVEL: %0*d", 2, level_number);

	SetTextColor(hdc, AsColors::Indigo);
	TextOutW(hdc, level_number_str_pos + Shadow_Margin, 0 + Shadow_Margin, level_number_str, level_number_str_len);
	SetTextColor(hdc, AsColors::White);
	TextOutW(hdc, level_number_str_pos, 0, level_number_str, level_number_str_len);

}
//=====================================================================================================================

//=====================================================================================================================
// private section:
//=====================================================================================================================

//=====================================================================================================================

//=====================================================================================================================