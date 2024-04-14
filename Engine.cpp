#include "Engine.h"


//==================================================================================================================
// constructor & destructor struct SCurrent_Level:
//==================================================================================================================

//==================================================================================================================
// constructor & destructor
//==================================================================================================================
AsEngine::~AsEngine()
{
	//delete SDL
	SDL_Quit();
}
AsEngine::AsEngine()
	:Hwnd(0), Player(0), Lives(3), Time(0), Current_Level_Number(1), Frame_Tick(0)
{
}
//==================================================================================================================
// public section:
//==================================================================================================================
void AsEngine::Init(HWND hwnd)
{
	AsFrameDc* frameDc;
	HDC cur_dc = GetDC(Hwnd);

	Hwnd = hwnd;

	frameDc = AsFrameDc::Get_Instance();
	frameDc->Init(Hwnd);

	Camera = AsCamera::Get_Instance();
	Camera->Init(Hwnd);

	Info_Pannel.Init(&Moover, &Lives, &Time, &Current_Level_Number);

	Game_Title.Init();
	Level.Init(Camera, Player, &Moover, &Info_Pannel, &Game_Messages, &Time);

	//инициализация таймера
	//четвертый параметр = 0 так как для обработки событий таймера мы не будем регестрировать специальную фунцию для его обработки
	SetTimer(Hwnd, AsSettings::TimerId, 1000 / AsSettings::FPS, 0);

	//!!!!!!!!!!!!!!!!!!!!!for debagging!!!!!!!!!!
	Game_State = EGame_State::Title;


	//init level
	Level.Init_Level(Current_Level_Number, Player, &Moover, &Info_Pannel);

	//play musik
	Init_Audio();
}
//==================================================================================================================
int AsEngine::On_Timer()
{


	if (Game_State == EGame_State::Title)
	{
		Game_Title.Act();
		InvalidateRect(Hwnd, &AsSettings::Screen_Rect, FALSE);
	}
	if (Game_State == EGame_State::Play)
	{
		Level.Act();
		Moover.Act();
		InvalidateRect(Hwnd, 0, TRUE);

		Timer();

		Messege_Processing();
	}

	return 0;
}
//==================================================================================================================
void AsEngine::Draw_Frame(HDC hdc)
{

	if (Game_State == EGame_State::Title)
		Game_Title.Draw(hdc);

	if (Game_State == EGame_State::Play)
	{
		Camera->Draw(hdc);
		Info_Pannel.Draw_Game_Info_Panel(hdc);
	}

}
//==================================================================================================================
int AsEngine::On_Key(Ekey_Type key_type, bool on_key_down)
{
	if (Game_State == EGame_State::Play)
		return Player->On_Key(key_type, on_key_down);

	if (Game_State == EGame_State::Title)
		if (key_type == EKT_Space)
		{
			Mix_PauseMusic();
			Game_State = EGame_State::Play;
			Restart_Game();
		}

	return 0;
}
//==================================================================================================================
// private section:
//==================================================================================================================
void AsEngine::Timer()
{
	++Frame_Tick;
	if (Frame_Tick > AsSettings::FPS)
	{
		Frame_Tick = 0;
		--Time;
		if (Time <= 0)
			Game_Messages.push_back(EMessege::EM_Player_Hit);
	}
}
//==================================================================================================================
void AsEngine::Messege_Processing()
{
	EMessege cur_message{};
	std::vector<EMessege>::iterator it;


	for (it = Game_Messages.begin(); it != Game_Messages.end(); ++it)
	{
		cur_message = *(it);

		switch (cur_message)
		{
		case EMessege::EM_Player_Hit:
			Restart_Level();
			it = Game_Messages.erase(it);
			break;
		case EMessege::EM_Next_Level:
			Next_Level();
			it = Game_Messages.erase(it);
			break;
		default:
			break;
		}

		//защита от выхода за пределы списка при удалении ячейки
		if (it == Game_Messages.end())
			break;
	}
}
//==================================================================================================================
void AsEngine::Restart_Level()
{
	--Lives;
	if (Lives > 0)
	{
		Level.Init_Level(Current_Level_Number, Player, &Moover, &Info_Pannel);
		Moover.Clear_All_Data();
		Mix_PlayChannel(-1, Restart_Level_Sound, 0);
	}
	else
	{
		Mix_ResumeMusic();
		Game_State = EGame_State::Title;
		Moover.Clear_All_Data();
	}
}
//==================================================================================================================
void AsEngine::Next_Level()
{
	++Current_Level_Number;
	if (Current_Level_Number > Max_Levels)
	{
		Mix_ResumeMusic();
		Game_State = EGame_State::Title;
	}
	else
		Level.Init_Level(Current_Level_Number, Player, &Moover, &Info_Pannel);
}

void AsEngine::Init_Audio()
{
	//SDL init
	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Main_Theme = Mix_LoadMUS("sounds/main.mp3");

	Restart_Level_Sound = Mix_LoadWAV("sounds/restart_level.wav");

	//start to play main theme
	Mix_PlayMusic(Main_Theme, -1);
}
//================================================================================
void AsEngine::Restart_Game()
{
	Level.Init_Level(1, Player, &Moover, &Info_Pannel);
	Moover.Clear_All_Data();
	Lives = 3;
}
//=================================================================================