#include "Level.h"
#include "Moover.h"
#include "AsPlayer.h"

//======================================================================================================================
// constructor & destructor:
//======================================================================================================================
AsLevel::~AsLevel()
{
	int i{};
	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
	//удаление массива с проинциализированными уровнями игры
	for (auto* level : Levels)
		delete level;

	Levels.erase(Levels.begin(), Levels.end());
	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

	Clear_Data();

	//delete all bitmaps
	Delete_Bitmaps();
}
//======================================================================================================================
AsLevel::AsLevel()
	:Cur_Level_Width(0), Cur_Level_Height(0), Player(0)
{
}
//======================================================================================================================
// public section:
//======================================================================================================================
void AsLevel::Init(AsCamera* camera, AsPlayer* player, AsMoover* moover, AsInfo_Pannel *info_pannel,
	std::vector<EMessege> *messeges, int* time)
{
	Camera = camera;
	Time = time;
	Game_Messages = messeges;

	Add_Levels();

	//create bitmaps
	Create_Bitmaps();
}
//======================================================================================================================
void AsLevel::Act()
{
	int i{};

	//Animation_of_diamand
	ADiamonds::Animation_Step += 1;
	ADiamonds::Animation_Step = ADiamonds::Animation_Step % AsSettings::FPS;

	//Animation_of_enemy_a
	++AEnemy_A::Frame_Tick;
	if (AEnemy_A::Frame_Tick >= AEnemy_A::Frame_Tick_Limit)
	{
		AEnemy_A::Frame_Tick = 0;
		++AEnemy_A::X_Texture_Shift;
		AEnemy_A::X_Texture_Shift = AEnemy_A::X_Texture_Shift % 3;
	}

	Player->Act();

	//Act of all fallen objects
	Stones_Act();


	//read game messages
	Message_Processing();
}
//======================================================================================================================
void AsLevel::Draw(HDC hdc)
{

}
//======================================================================================================================
void AsLevel::Init_Level(int level, AsPlayer* player, AsMoover* moover, AsInfo_Pannel* info_pannel )
{
	int i{}, j{}, len{}, size{};
	int index{};
	double x_pos{}, y_pos{};
	AGame_Object* new_game_obj;
	AsCamera* camera = AsCamera::Get_Instance();
	int target{};

	Pressed_Key = EKT_None;

	//clear all arrays width current dimensions
	Clear_Data();

	Moover = moover;

	Current_Level = Levels[level];
	Cur_Level_Array = Current_Level->Init(Cur_Level_Width, Cur_Level_Height, target, *(Time) );

	len = Cur_Level_Width * Cur_Level_Height;

	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

	Game_Objects_Support_Pointer_Array = new AGame_Object * [len];
	size = len * sizeof(Game_Objects_Support_Pointer_Array);
	memset(Game_Objects_Support_Pointer_Array, 0, size);

	//Передаем указатели проинициализированных массив класу что будет заниматеся их отрисовкой
	camera->Set_Curr_Level(Cur_Level_Width, Cur_Level_Height, Cur_Level_Array, Game_Objects_Support_Pointer_Array);
	//Передаем указатели проинициализированных массив класу что будет заниматеся перемещением сущностей
	moover->Init(Game_Objects_Support_Pointer_Array, Cur_Level_Array, camera, Cur_Level_Width, Cur_Level_Height,
		target, Game_Messages);

	index = 0;
	for (i = 0; i < Cur_Level_Height; ++i)
	{
		for (j = 0; j < Cur_Level_Width; ++j)
		{
			x_pos = (double)(j * AsSettings::Ceil_Size);
			y_pos = (double)(i * AsSettings::Ceil_Size);

			//terra blocks
			if (Cur_Level_Array[index] == 1)
			{
				new_game_obj = new ATerra(j, i, EObject_Type::Terra);
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;
			}

			//stone blocks
			if (Cur_Level_Array[index] == 2)
			{
				new_game_obj = new AStone(j, i, EObject_Type::Stone);
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;

			}

			//diamonds blocks
			if (Cur_Level_Array[index] == 3)
			{
				new_game_obj = new ADiamonds(j, i );
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;

			}

			//walls blocks
			if (Cur_Level_Array[index] == 4)
			{
				new_game_obj = new AWalls(j, i, EObject_Type::Wall );
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;

			}

			//init enemy type b
			if (Cur_Level_Array[index] == 7)
			{
				new_game_obj = new AEnemy_B(j, i);
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;
			}

			//init enemy type a
			if (Cur_Level_Array[index] == 8)
			{
				new_game_obj = new AEnemy_A(j, i);
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;
			}

			//init player
			if (Cur_Level_Array[index] == 9)
			{
				Player = new AsPlayer(j, i, moover, EObject_Type::Player);
				new_game_obj = Player;
				Game_Objects_Support_Pointer_Array[index] = new_game_obj;
				player = Player;
			}

			//init finish
			if (Cur_Level_Array[index] == 10)
			{
				Finish = new AFinish(j, i);
				Game_Objects_Support_Pointer_Array[index] = Finish;
			}

			++index;
		}
	}
}
//======================================================================================================================
// private section:
//======================================================================================================================
void AsLevel::Add_Levels()
{
	ALevel_Data* new_level;
	// int level_width & level_height & target diamonds & time

	new_level = new ALevel_Data(*AsLevels_Arrays::Level_Test, 70, 30, 5, 200);
	Levels.push_back(new_level);

	new_level = new ALevel_Data(*AsLevels_Arrays::Level_1, 50, 22, 10, 80);
	Levels.push_back(new_level);

	new_level = new ALevel_Data(*AsLevels_Arrays::Level_2, 48, 18, 13, 50);
	Levels.push_back(new_level);
}
//======================================================================================================================
void AsLevel::Clear_Data()
{
	int i{};
	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
	//Удаление текущего массива с уровнем с текущими размерами
	if (Cur_Level_Array != nullptr)
		delete[] Cur_Level_Array;

	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
	//Удаление сущностей в массивe указателей
	for (i; i < Cur_Level_Width * Cur_Level_Height; ++i)
	{
		if (Game_Objects_Support_Pointer_Array[i] != nullptr)
		{
			delete Game_Objects_Support_Pointer_Array[i];
			Game_Objects_Support_Pointer_Array[i] = nullptr;
		}
	}
	//удаление массива указателей текущего размера
	delete[] Game_Objects_Support_Pointer_Array;
	//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
	
}
//======================================================================================================================
void AsLevel::Stones_Act()
{
	int level_arry_len{};
	int i{};
	AGame_Object* cur_object{};
	EObject_Type cur_object_type{};

	level_arry_len = Cur_Level_Width * Cur_Level_Height;

	for (i = level_arry_len - 1; i >= 0; --i)
	{
		cur_object = Game_Objects_Support_Pointer_Array[i];
		if (cur_object == nullptr )
			continue;
		else
		{
			cur_object_type = cur_object->Get_Type();
			if (cur_object_type == EObject_Type::Stone || cur_object_type == EObject_Type::Diamond)
				if (cur_object->Mooving_State == EMooving_State::EMS_None)
					Stones_SubAct(i, level_arry_len, cur_object);

			if (cur_object_type == EObject_Type::Enemy_A || cur_object_type == EObject_Type::Enemy_B)
				Moover->Enemys_Moove(i, level_arry_len, cur_object);

			else
				continue;
		}
	}
}
void AsLevel::Stones_SubAct(int cur_ind, int level_arry_len, AGame_Object* obj)
{
	int ocx{}, ocy{};

	int x_ind_1{}, y_ind_1{};
	int x_ind_2{}, y_ind_2{};
	int x_ind_3{}, y_ind_3{};
	int x_ind_4{}, y_ind_4{};
	int x_ind_5{}, y_ind_5{};

	int find_index{};

	int obj_direction{};

	bool is_type_b{};

	bool is_left_result{}, is_right_result{};

	AGame_Object* near_object_1{};
	AGame_Object* near_object_2{};
	AGame_Object* near_object_3{};
	AGame_Object* near_object_4{};
	AGame_Object* near_object_5{};

	EObject_Type object_type_1{};
	EObject_Type object_type_2{};
	EObject_Type object_type_3{};
	EObject_Type object_type_4{};
	EObject_Type object_type_5{};

	EMooving_State object_1_mooving_state{};
	
	is_left_result = true;
	is_right_result = true;


	obj->Get_Ceil_Pos(ocx, ocy);

	if (ocy >= Cur_Level_Height - 1)
		return;

	//fall dawn
	y_ind_1 = ocy + 1;
	find_index = y_ind_1 * Cur_Level_Width + ocx;
	near_object_1 = Game_Objects_Support_Pointer_Array[find_index];
	if (near_object_1 == nullptr)
	{
		Moover->Moove_Object(2, obj);
		obj->Direction = 2;
		return;
	}
	
	else
	{
		object_type_1 = near_object_1->Get_Type();
		if (object_type_1 != EObject_Type::Player && object_type_1 != EObject_Type::Enemy_A && object_type_1 != EObject_Type::Enemy_B )
			obj->Direction = 0;

		object_type_1 = near_object_1->Get_Type();
		object_1_mooving_state = near_object_1->Mooving_State;
		obj_direction = obj->Direction;
		//kill the monsters if black is fall down
		if (obj_direction == 2)
			if (object_type_1 == EObject_Type::Enemy_A || object_type_1 == EObject_Type::Enemy_B)
			{
				//delete stone
				Moover->Destroy_Object(cur_ind, obj);

				//kill the monster
				near_object_1->Get_Ceil_Pos(x_ind_1, y_ind_1);
				find_index = y_ind_1 * Cur_Level_Width + x_ind_1;

				Moover->Destroy_Object(find_index, near_object_1);

				//delete nearly object and create diamonds if monster type_b
				if (object_type_1 == EObject_Type::Enemy_A)
					is_type_b = false;
				else
					is_type_b = true;

				Monster_Kill_Act(ocx, ocy, is_type_b);

				return;
			}
			else if (object_type_1 == EObject_Type::Player)
			{
				//delete stone
				Moover->Destroy_Object(cur_ind, obj);

				//kill the player
				near_object_1->Get_Ceil_Pos(x_ind_1, y_ind_1);
				find_index = y_ind_1 * Cur_Level_Width + x_ind_1;
				Moover->Destroy_Object(find_index, near_object_1);

				Game_Messages->push_back(EMessege::EM_Player_Hit);

				Monster_Kill_Act(ocx, ocy, true);
			}


		if ( (object_type_1 == EObject_Type::Stone || object_type_1 == EObject_Type::Diamond) &&
			object_1_mooving_state == EMooving_State::EMS_None)
		{
			//top block
			if (ocy > 0)
			{
				x_ind_2 = ocx;
				y_ind_2 = ocy - 1;
				find_index = y_ind_2 * Cur_Level_Width + x_ind_2;
				near_object_2 = Game_Objects_Support_Pointer_Array[find_index];

			}

			//fall in the left side
			if (ocx > 0)
			{
				//left bottom block
				x_ind_3 = ocx - 1;
				y_ind_3 = ocy + 1;
				find_index = y_ind_3 * Cur_Level_Width + x_ind_3;
				near_object_3 = Game_Objects_Support_Pointer_Array[find_index];

				//left block
				x_ind_4 = ocx - 1;
				y_ind_4 = ocy;
				find_index = y_ind_4 * Cur_Level_Width + x_ind_4;
				near_object_4 = Game_Objects_Support_Pointer_Array[find_index];


				if (near_object_3 == nullptr && near_object_4 == nullptr)
				{
					//left top block
					if (ocy > 0)
					{
						x_ind_5 = ocx - 1;
						y_ind_5 = ocy - 1;
						find_index = y_ind_5 * Cur_Level_Width + x_ind_5;
						near_object_5 = Game_Objects_Support_Pointer_Array[find_index];
						if (near_object_5 != nullptr)
						{
							object_type_5 = near_object_5->Get_Type();
							if (object_type_5 == EObject_Type::Stone || object_type_5 == EObject_Type::Diamond)
								is_left_result = false;
						}
						else
						{
							if(near_object_2 != nullptr)
							{
								object_type_2 = near_object_2->Get_Type();
								if (object_type_2 == EObject_Type::Stone || object_type_2 == EObject_Type::Diamond)
									is_left_result = false;
							}
						}

					}

					if (is_left_result)
					{
						Moover->Moove_Object(3, obj);
						obj->Direction = 3;
						return;
					}
				}
			}

			//fall in the right side
			if (ocx < Cur_Level_Width - 2)
			{
				//right bottom block
				x_ind_3 = ocx + 1;
				y_ind_3 = ocy + 1;
				find_index = y_ind_3 * Cur_Level_Width + x_ind_3;
				near_object_3 = Game_Objects_Support_Pointer_Array[find_index];

				//right block
				x_ind_4 = ocx + 1;
				y_ind_4 = ocy;
				find_index = y_ind_4 * Cur_Level_Width + x_ind_4;
				near_object_4 = Game_Objects_Support_Pointer_Array[find_index];


				if (near_object_3 == nullptr && near_object_4 == nullptr)
				{
					//right top block
					if (ocy > 0)
					{
						x_ind_5 = ocx + 1;
						y_ind_5 = ocy - 1;
						find_index = y_ind_5 * Cur_Level_Width + x_ind_5;
						near_object_5 = Game_Objects_Support_Pointer_Array[find_index];
						if (near_object_5 != nullptr)
						{
							object_type_5 = near_object_5->Get_Type();
							if (object_type_5 == EObject_Type::Stone || object_type_5 == EObject_Type::Diamond)
								is_right_result = false;
						}
						else
						{
							if (near_object_2 != nullptr)
							{
								object_type_2 = near_object_2->Get_Type();
								if (object_type_2 == EObject_Type::Stone || object_type_2 == EObject_Type::Diamond)
									is_right_result = false;
							}
						}
					}

					if (is_right_result)
					{
						Moover->Moove_Object(1, obj);
						obj->Direction = 1;
						return;
					}
				}
			}

		}
	}

}
//======================================================================================================================
//======================================================================================================================
void AsLevel::Stones_SubAct1(int cur_ind, int level_arry_len, AGame_Object* obj)
{
	int ocx{}, ocy{};

	int x_ind_1{}, y_ind_1{};
	int x_ind_2{}, y_ind_2{};
	int x_ind_3{}, y_ind_3{};
	int x_ind_4{}, y_ind_4{};
	int x_ind_5{}, y_ind_5{};

	int find_index{};

	int obj_direction{};

	bool is_type_b{};

	AGame_Object* near_object_1{};
	AGame_Object* near_object_2{};
	AGame_Object* near_object_3{};
	AGame_Object* near_object_4{};
	AGame_Object* near_object_5{};

	EObject_Type object_type_1{};
	EObject_Type object_type_2{};
	EObject_Type object_type_3{};
	EObject_Type object_type_4{};
	EObject_Type object_type_5{};

	EMooving_State object_1_mooving_state{};

	bool left_result{};
	bool right_result{};

	obj->Get_Ceil_Pos(ocx, ocy);

	if (ocy >= Cur_Level_Height - 1)
		return;

	//падение вниз
	y_ind_1 = ocy + 1;
	find_index = y_ind_1 * Cur_Level_Width + ocx;
	near_object_1 = Game_Objects_Support_Pointer_Array[find_index];
	if (near_object_1 == nullptr)
	{
		Moover->Moove_Object(2, obj);
		obj->Direction = 2;
		return;
	}
	else
	{
		object_type_1 = near_object_1->Get_Type();
		object_1_mooving_state = near_object_1->Mooving_State;
		obj_direction = obj->Direction;
		//kill the monsters if black is fall down
		if (obj_direction == 2)
			if (object_type_1 == EObject_Type::Enemy_A || object_type_1 == EObject_Type::Enemy_B)
			{
				//delete stone
				Moover->Destroy_Object(cur_ind, obj);

				//kill the monster
				near_object_1->Get_Ceil_Pos(x_ind_1, y_ind_1);
				find_index = y_ind_1 * Cur_Level_Width + x_ind_1;

				Moover->Destroy_Object(find_index, near_object_1);

				//delete nearly object and create diamonds if monster type_b
				if (object_type_1 == EObject_Type::Enemy_A)
					is_type_b = false;
				else
					is_type_b = true;

				Monster_Kill_Act(ocx, ocy, is_type_b);

				return;
			}
	}

	//падение в левый бок
	left_result = false;

	if (ocx > 0)
	{
		//нижний блок
		y_ind_1 = ocy + 1;
		x_ind_1 = ocx;
		find_index = y_ind_1 * Cur_Level_Width + x_ind_1;
		near_object_1 = Game_Objects_Support_Pointer_Array[find_index];
		object_type_1 = near_object_1->Get_Type();
		object_1_mooving_state = near_object_1->Mooving_State;

		//левый нижний блок
		y_ind_2 = ocy + 1;
		x_ind_2 = ocx - 1;
		find_index = y_ind_2 * Cur_Level_Width + x_ind_2;
		near_object_2 = Game_Objects_Support_Pointer_Array[find_index];

		//левый блок
		y_ind_3 = ocy;
		x_ind_3 = ocx - 1;
		find_index = y_ind_3 * Cur_Level_Width + x_ind_3;
		near_object_3 = Game_Objects_Support_Pointer_Array[find_index];
		
		if (ocy > 0)
		{
			//верхний левый блок
			y_ind_4 = ocy - 1;
			x_ind_4 = ocx - 1;
			find_index = y_ind_4 * Cur_Level_Width + x_ind_4;
			near_object_4 = Game_Objects_Support_Pointer_Array[find_index];
			object_type_4 = near_object_1->Get_Type();

			//верхний блок
			y_ind_5 = ocy - 1;
			x_ind_5 = ocx;
			find_index = y_ind_5 * Cur_Level_Width + x_ind_5;
			near_object_5 = Game_Objects_Support_Pointer_Array[find_index];
			object_type_5 = near_object_1->Get_Type();
		}

		if (
			(object_type_1 == EObject_Type::Stone || object_type_1 == EObject_Type::Diamond) && object_1_mooving_state == EMooving_State::EMS_None &&
			near_object_2 == nullptr &&
			near_object_3 == nullptr
			)
		{
			left_result = true;

			if (ocy > 0)
			{
				if (near_object_4 == nullptr)
				{
					if (near_object_5 == nullptr)
						left_result = true;
					else if ( object_type_5 != EObject_Type::Stone || object_type_5 != EObject_Type::Diamond)
						left_result = true;
				}
				else if (object_type_4 != EObject_Type::Stone || object_type_4 != EObject_Type::Diamond)
					left_result = true;

			}

		}

		if (left_result)
		{
			Moover->Moove_Object(3, obj);
			return;
		}

	}


	//падение в правый бок
	right_result = false;

	if (ocy < Cur_Level_Width - 2)
	{
		//нижний блок
		y_ind_1 = ocy + 1;
		x_ind_1 = ocx;
		find_index = y_ind_1 * Cur_Level_Width + x_ind_1;
		near_object_1 = Game_Objects_Support_Pointer_Array[find_index];
		object_type_1 = near_object_1->Get_Type();
		object_1_mooving_state = near_object_1->Mooving_State;

		//левый правый блок
		y_ind_2 = ocy + 1;
		x_ind_2 = ocx + 1;
		find_index = y_ind_2 * Cur_Level_Width + x_ind_2;
		near_object_2 = Game_Objects_Support_Pointer_Array[find_index];

		//правый блок
		y_ind_3 = ocy;
		x_ind_3 = ocx + 1;
		find_index = y_ind_3 * Cur_Level_Width + x_ind_3;
		near_object_3 = Game_Objects_Support_Pointer_Array[find_index];

		if (ocy > 0)
		{
			//верхний правый блок
			y_ind_4 = ocy - 1;
			x_ind_4 = ocx + 1;
			find_index = y_ind_4 * Cur_Level_Width + x_ind_4;
			near_object_4 = Game_Objects_Support_Pointer_Array[find_index];
			object_type_4 = near_object_1->Get_Type();

			//верхний блок
			y_ind_5 = ocy - 1;
			x_ind_5 = ocx;
			find_index = y_ind_5 * Cur_Level_Width + x_ind_5;
			near_object_5 = Game_Objects_Support_Pointer_Array[find_index];
			object_type_5 = near_object_1->Get_Type();
		}

		if (
			(object_type_1 == EObject_Type::Stone || object_type_1 == EObject_Type::Diamond) && object_1_mooving_state == EMooving_State::EMS_None &&
			near_object_2 == nullptr &&
			near_object_3 == nullptr
			)
		{
			right_result = true;

			if (ocy > 0)
			{
				if (near_object_4 == nullptr)
				{
					if (near_object_5 == nullptr)
						right_result = true;
					else if (object_type_5 != EObject_Type::Stone || object_type_5 != EObject_Type::Diamond)
						right_result = true;
				}
				else if (object_type_4 != EObject_Type::Stone || object_type_4 != EObject_Type::Diamond)
					right_result = true;

			}

		}

		if (right_result)
		{
			Moover->Moove_Object(1, obj);
			return;
		}

	}
}
//======================================================================================================================
void AsLevel::Monster_Kill_Act(int x, int y, bool is_type_b)
{
	int i{}, j{};
	int cur_x{}, cur_y{};
	int min_x{}, min_y{}, max_x{}, max_y{};
	int cur_index{};

	AGame_Object* cur_object{};
	EObject_Type cur_object_type{};
	EMooving_State cur_object_mooving_state{};

	min_x = x > 0 ? -1 : 0;
	max_x = x < Cur_Level_Width - 1 ? 2 : 1;

	min_y = -1;
	max_y = y < Cur_Level_Height - 1 ? 2 : 1;

	for (i = min_y; i < max_y; ++i )
	{
		for (j = min_x; j < max_y; ++j)
		{
			cur_x = x + j;
			cur_y = y + i;
			cur_index = cur_y * Cur_Level_Width + cur_x;
			cur_object = Game_Objects_Support_Pointer_Array[cur_index];
			//delete object
			if (cur_object != nullptr)
			{
				cur_object_type = cur_object->Get_Type();

				if (cur_object_type != EObject_Type::Player && cur_object_type != EObject_Type::Enemy_A && cur_object_type != EObject_Type::Enemy_B)
					Moover->Destroy_Object(cur_index, cur_object);
			}
			//create diamonds
			if ( is_type_b == true && Game_Objects_Support_Pointer_Array[cur_index] == nullptr )
				Game_Objects_Support_Pointer_Array[cur_index] = new ADiamonds(cur_x, cur_y);
		}
	}

}
//======================================================================================================================
void AsLevel::Create_Bitmaps()
{

	if (AsPlayer::Img == 0)
		AsPlayer::Create_Bitmap();

	if (ADiamonds::Img == nullptr)
		ADiamonds::Create_Bitmap();

	if (AEnemy_A::Img == 0)
		AEnemy_A::Create_Bitmap();

	if (AEnemy_B::Img == 0)
		AEnemy_B::Create_Bitmap();

	if (AStone::Img == nullptr)
		AStone::Create_Bitmap();

	if (ATerra::Img == nullptr)
		ATerra::Create_Bitmap();

	if (AWalls::Img == nullptr)
		AWalls::Create_Bitmap();

	if (AFinish::Img == nullptr)
		AFinish::Create_Bitmap();
}
//======================================================================================================================
void AsLevel::Delete_Bitmaps()
{

	if (AsPlayer::Img != 0)
	{
		DeleteObject(AsPlayer::Img);
		AsPlayer::Img = 0;
	}

	if (ATerra::Img != 0)
	{
		DeleteObject(ATerra::Img);
		ATerra::Img = 0;
	}

	if (AStone::Img != nullptr)
	{
		DeleteObject(AStone::Img);
		AStone::Img = nullptr;
	}

	if (AWalls::Img != nullptr)
	{
		DeleteObject(AWalls::Img);
		AWalls::Img = nullptr;
	}

	//diamonds bitmaps
	if (ADiamonds::Img != 0)
	{
		DeleteObject(ADiamonds::Img);
		ADiamonds::Img = 0;
	}

	if (ADiamonds::Fon_Img != 0)
	{
		DeleteObject(ADiamonds::Img);
		ADiamonds::Fon_Img = 0;
	}

	if (ADiamonds::Mask_Img != 0)
	{
		DeleteObject(ADiamonds::Img);
		ADiamonds::Mask_Img = 0;
	}

	//enemys image:
	if (AEnemy_A::Img != 0)
	{
		DeleteObject(AEnemy_A::Img);
		AEnemy_A::Img = 0;
	}

	if (AEnemy_B::Img != 0)
	{
		DeleteObject(AEnemy_B::Img);
		AEnemy_B::Img = 0;
	}
}
//======================================================================================================================
void AsLevel::Message_Processing()
{
	std::vector<EMessege>::iterator it{};
	EMessege message{};
	bool result{};
	result = false;

	for (it = Game_Messages->begin(); it != Game_Messages->end(); ++it)
	{
		message = (*it);
		switch (message)
		{
		case EMessege::EM_All_Diamond_Collected:
			Finish->Is_Active = true;
			it = Game_Messages->erase(it);
			break;
		case EMessege::EM_Player_In_Finish:
			it = Game_Messages->erase(it);
			result = true;
			break;
		default:
			break;
		}

		if (it == Game_Messages->end())
			break;
	}

	if (result)
		if (Finish->Is_Active == true)
			Game_Messages->push_back(EMessege::EM_Next_Level);
}
//======================================================================================================================