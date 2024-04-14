#pragma once
#include "Camera.h"

//================================================================================================================================
class AsMoover
{
public:
	~AsMoover();
	AsMoover();
	void Init(AGame_Object** pointer_arr, unsigned char* collision_level_array, AsCamera *camera,
		int width, int height, int target, std::vector<EMessege>* messeges);

	void Moove_Object(int direction, AGame_Object *object);
	void Destroy_Object(int obj_index, AGame_Object* object);

	bool Player_Moove(int px, int py, int direction, AGame_Object* player);
	void Enemys_Moove(int cur_ind, int level_arry_len, AGame_Object* obj);

	void Get_Count_Of_Diamonds(int& target, int& diamonds);

	void Act();
	void Act1();

	void Clear_All_Data();

private:
	bool Moove_Stone(AGame_Object* object, int direction);
	void Load_Sounds();

	int Level_Width;
	int Level_Height;

	int Diamonds;
	int Target;

	int const Ways_Int[8] =
	{
		0, -1,
		1, 0,
		0, 1,
		-1, 0
	};

	double const Ways[8] =
	{	
		0.0, -1.0,
		1.0, 0.0,
		0.0, 1.0,
		-1.0, 0.0
	};

	double const Player_Speed = 0.2;
	double const Enemy_Speed = 0.12;
	double const Stone_Speed = 0.16;

	std::vector<AGame_Object*> Object_On_Moovable;
	std::vector<AGame_Object*> Object_To_Destroy;
	std::vector<EMessege>* Game_Messages;

	unsigned char* Collision_Level_Array;
	AGame_Object** Game_Objects_Support_Pointer_Array;
	AsCamera* Camera;

	Mix_Chunk* Pass_Sound;
	Mix_Chunk* Stone_Sound;
	Mix_Chunk* Diamond_Take_Sound;
	Mix_Chunk* Diamond_Fallen_Sound;
	Mix_Chunk* Finish_Sound;
};
//================================================================================================================================