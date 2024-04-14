#include "Moover.h"
#include "Camera.h"

//================================================================================================================================
// constructor & destructor & initialization
//================================================================================================================================
AsMoover::~AsMoover()
{}
//================================================================================================================================
AsMoover::AsMoover()
	: Target(0), Diamonds(0)
{

}
//================================================================================================================================
void AsMoover::Init(AGame_Object** pointer_arr, unsigned char* collision_level_array, AsCamera* camera,
	int width, int height, int target, std::vector<EMessege>* messeges)
{
	Level_Width = width;
	Level_Height = height;

	Target = target;

	Game_Messages = messeges;

	Diamonds = 0;

	Game_Objects_Support_Pointer_Array = pointer_arr;
	Collision_Level_Array = collision_level_array;
	Camera = camera;

	Load_Sounds();
}
//================================================================================================================================
// public section:
//============================================================================================================================
void AsMoover::Moove_Object(int direction, AGame_Object* object)
{
	if (object->Mooving_State != EMooving_State::EMS_None)
		return;

	int start_x{}, start_y{}, end_x{}, end_y{};
	int start_index{}, end_index{};
	double rx{}, ry{};
	EObject_Type object_type{};

	object->Get_Ceil_Pos(start_x, start_y);
	end_x = Ways_Int[direction * 2] + start_x;
	end_y = Ways_Int[direction * 2 + 1] + start_y;

	if (end_x < 0 || end_y < 0 || end_x > Level_Width - 1 || end_y > Level_Height - 1)
	{
		object->Mooving_State = EMooving_State::EMS_None;
		return;
	}

	//make sound
	object_type = object->Get_Type();
	switch (object_type)
	{
	case EObject_Type::Stone:
		Mix_PlayChannel(-1, Stone_Sound, 0);
		break;
	case EObject_Type::Diamond:
		Mix_PlayChannel(-1, Diamond_Fallen_Sound, 0);
		break;
	default:
		break;
	}

	object->Mooving_State = (EMooving_State)(direction + 1);

	object->Start[0] = start_x;
	object->Start[1] = start_y;
	object->Destination[0] = end_x;
	object->Destination[1] = end_y;

	object->Direction = direction;

	start_index = start_y * Level_Width + start_x;
	end_index = end_y * Level_Width + end_x;
	std::swap(Game_Objects_Support_Pointer_Array[start_index], Game_Objects_Support_Pointer_Array[end_index]);

	rx = start_x - end_x;
	ry = start_y - end_y;

	object->Set_Pos(end_x, end_y, rx, ry);

	Object_On_Moovable.push_back(object);
}
//===========================================================================================================================
void AsMoover::Destroy_Object(int obj_index, AGame_Object* object)
{
	Game_Objects_Support_Pointer_Array[obj_index] = nullptr;

	Object_To_Destroy.push_back(object);
}
//===========================================================================================================================
bool AsMoover::Player_Moove(int px, int py, int player_direction, AGame_Object* player)
{
	if (player->Mooving_State != EMooving_State::EMS_None)
		return false;

	int next_c_x{}, next_c_y{};
	int next_c_index{};
	AGame_Object* cur_object{};
	EObject_Type object_type{};

	next_c_x = px + Ways[player_direction * 2];
	next_c_y = py + Ways[player_direction * 2 + 1];

	if (next_c_x < 0)
		next_c_x = 0;

	if (next_c_x >= Level_Width)
		next_c_x = Level_Width - 1;

	if (next_c_y < 0)
		next_c_y = 0;

	if (next_c_y >= Level_Height)
		next_c_y = Level_Height - 1;

	next_c_index = next_c_y * Level_Width + next_c_x;

	cur_object = Game_Objects_Support_Pointer_Array[next_c_index];

	if (cur_object == nullptr)
		return true;
	else
	{

		object_type = cur_object->Get_Type();

		switch (object_type)
		{
		case EObject_Type::Terra:
			Destroy_Object(next_c_index, cur_object);
			Mix_PlayChannel(-1, Pass_Sound, 0);
			return true;
			break;
		case EObject_Type::Stone:
			if (player_direction != 0)
				Moove_Stone(cur_object, player_direction);
			break;
		case EObject_Type::Diamond:
			Destroy_Object(next_c_index, cur_object);
			++Diamonds;
			Mix_PlayChannel(-1, Diamond_Take_Sound, 0);
			if (Diamonds == Target)
			{
				Game_Messages->push_back(EMessege::EM_All_Diamond_Collected);
				Mix_PlayChannel(-1, Finish_Sound, 0);
			}
			return true;
			break;
		case EObject_Type::Finish:
			Game_Messages->push_back(EMessege::EM_Player_In_Finish);
			break;
		default:
			break;
		}

	}

	return false;
}
//===========================================================================================================================
void AsMoover::Enemys_Moove(int cur_ind, int level_arry_len, AGame_Object* object)
{
	int obj_x{}, obj_y{};
	int next_x_pos{}, next_y_pos{};
	int obj_direction{};
	int new_direction{}; // rule of right side
	int new_direction_reverse{};
	int index{};
	AGame_Object* near_object{};
	EObject_Type object_type{};

	if (object->Mooving_State != EMooving_State::EMS_None)
		return;

	object->Get_Ceil_Pos(obj_x, obj_y);
	obj_direction = object->Direction;
	new_direction = obj_direction + 1;
	new_direction %= 4;

	next_x_pos = obj_x + Ways[new_direction * 2];
	if (next_x_pos < 0)
		next_x_pos = 0;
	if (next_y_pos > Level_Width - 1)
		next_y_pos = Level_Width - 1;
	next_y_pos = obj_y + Ways[new_direction * 2 + 1];
	if (next_y_pos < 0)
		next_y_pos = 0;
	if (next_y_pos > Level_Height - 1)
		next_y_pos = Level_Height - 1;

	index = next_y_pos * Level_Width + next_x_pos;

	near_object = Game_Objects_Support_Pointer_Array[index];

	if (near_object == nullptr)
	{
		Moove_Object(new_direction, object);
		object->Direction = new_direction;
	}
	else
	{
		//player_hit
		object_type = near_object->Get_Type();
		if (object_type == EObject_Type::Player)
			Game_Messages->push_back(EMessege::EM_Player_Hit);

		//else

		next_x_pos = obj_x + Ways[obj_direction * 2];
		if (next_x_pos < 0)
			next_x_pos = 0;
		if (next_y_pos > Level_Width - 1)
			next_y_pos = Level_Width - 1;
		next_y_pos = obj_y + Ways[obj_direction * 2 + 1];
		if (next_y_pos < 0)
			next_y_pos = 0;
		if (next_y_pos > Level_Height - 1)
			next_y_pos = Level_Height - 1;

		index = next_y_pos * Level_Width + next_x_pos;

		near_object = Game_Objects_Support_Pointer_Array[index];

		if (near_object == nullptr)
			Moove_Object(obj_direction, object);
		else
		{
			new_direction_reverse = obj_direction - 1;
			if (new_direction_reverse < 0)
				new_direction_reverse = 3;

			next_x_pos = obj_x + Ways[new_direction_reverse * 2];
			if (next_x_pos < 0)
				next_x_pos = 0;
			if (next_y_pos > Level_Width - 1)
				next_y_pos = Level_Width - 1;
			next_y_pos = obj_y + Ways[new_direction_reverse * 2 + 1];
			if (next_y_pos < 0)
				next_y_pos = 0;
			if (next_y_pos > Level_Height - 1)
				next_y_pos = Level_Height - 1;

			index = next_y_pos * Level_Width + next_x_pos;

			near_object = Game_Objects_Support_Pointer_Array[index];

			if (near_object == nullptr)
			{
				Moove_Object(new_direction_reverse, object);
				object->Direction = new_direction_reverse;
			}
			else
				object->Direction = new_direction;
		}
	}
	

}
//===========================================================================================================================
void AsMoover::Get_Count_Of_Diamonds(int& target, int& diamonds)
{
	target = Target;
	diamonds = Diamonds;
}
//===========================================================================================================================
void AsMoover::Act()
{
	if (Object_On_Moovable.size() == 0)
		return;

	{
		EObject_Type object_type{};

		int cur_direction{};
		double cur_cx{}, cur_cy{}, cur_rx{}, cur_ry{};

		double cur_speed{};

		double d_ceil_size = (double)AsSettings::Ceil_Size;
		double rdx{}, rdy{};
		double next_pos_rx{}, next_pos_ry{};
		double dx{}, dy{};

		double difference_x{}, difference_y{};

		double camera_x{}, camera_y{};


		EMooving_State object_direction{};

		std::vector<AGame_Object*>::iterator it;

		// moove object
		for (it = Object_On_Moovable.begin(); it != Object_On_Moovable.end(); ++it)
		{
			cur_direction = (*it)->Direction;
			object_type = (*it)->Get_Type();

			if (object_type == EObject_Type::Enemy_A || object_type == EObject_Type::Enemy_B)
				cur_speed = Enemy_Speed;
			else if (object_type == EObject_Type::Player)
				cur_speed = Player_Speed;
			else
				cur_speed = Stone_Speed;
			
			(*it)->Get_Pos(cur_cx, cur_cy, cur_rx, cur_ry);

			rdx = Ways[cur_direction * 2] * cur_speed;
			rdy = Ways[cur_direction * 2 + 1] * cur_speed;

			next_pos_rx = cur_rx + rdx;
			next_pos_ry = cur_ry + rdy;


			if ( (cur_rx > -0.05 && cur_rx < 0.05) && (cur_ry > -0.05 && cur_ry < 0.05))
			{
				next_pos_rx = 0.0;
				next_pos_ry = 0.0;

				(*it)->Set_Pos(cur_cx, cur_cy, next_pos_rx, next_pos_ry);
				(*it)->Mooving_State = EMooving_State::EMS_None;
				it = Object_On_Moovable.erase(it);

				if (object_type == EObject_Type::Player)
				{
					object_direction = (EMooving_State)(cur_direction + 1);

					dx = Ways[cur_direction * 2];
					dy = Ways[cur_direction * 2 + 1];
					Camera->Player_Moove(dx, dy, cur_cx, cur_cy, object_direction);
				}
			}

			else
			{
				(*it)->Set_Pos(cur_cx, cur_cy, next_pos_rx, next_pos_ry);
			}



			if (it == Object_On_Moovable.end())
				break;

		}
	}

}
//===========================================================================================================================
void AsMoover::Act1()
{
	if (Object_On_Moovable.size() == 0)
		return;

	EObject_Type object_type{};

	int cur_direction{};
	double cur_cx{}, cur_cy{}, cur_rx{}, cur_ry{};
	double next_rx{}, next_ry{};
	double difference_x{}, difference_y{};

	double cur_speed{};

	double d_ceil_size = (double)AsSettings::Ceil_Size;
	double dx{}, dy{};

	double camera_x{}, camera_y{};


	EMooving_State object_direction{};

	std::vector<AGame_Object*>::iterator it;
	
	// moove object
	for (it = Object_On_Moovable.begin(); it != Object_On_Moovable.end(); ++it)
	{
		cur_direction = (*it)->Direction;
		object_type = (*it)->Get_Type();
		(*it)->Get_Pos(cur_cx, cur_cy, cur_rx, cur_ry);

		if (object_type == EObject_Type::Enemy_A || object_type == EObject_Type::Enemy_B)
			cur_speed = Enemy_Speed;
		else
			cur_speed = Player_Speed;

		dx = Ways[cur_direction * 2] * cur_speed;
		dy = Ways[cur_direction * 2 + 1] * cur_speed;



		next_rx = cur_rx + dx;
		next_ry = cur_ry + dy;

		difference_x = 1 - abs(next_rx);
		if (difference_x == 1.0)
			difference_x = 0.0;
		difference_y = 1 - abs(next_ry);
		if (difference_y == 1.0)
			difference_y = 0.0;

		if (difference_x > 0.75 || difference_y > 0.75)
		{
			next_rx = 0.0;
			next_ry = 0.0;

			(*it)->Set_Pos(cur_cx, cur_cy, next_rx, next_ry);
			(*it)->Mooving_State = EMooving_State::EMS_None;
			it = Object_On_Moovable.erase(it);

			if (object_type == EObject_Type::Player)
			{
				object_direction = (EMooving_State)(cur_direction + 1);

				dx = Ways[cur_direction * 2];
				dy = Ways[cur_direction * 2 + 1];
				Camera->Player_Moove(dx, dy, cur_cx, cur_cy, object_direction);
			}
		}

		else
		{
			(*it)->Set_Pos(cur_cx, cur_cy, next_rx, next_ry);
		}

			

		if (it == Object_On_Moovable.end())
			break;
	}


	//destroy object
	for (it = Object_To_Destroy.begin(); it < Object_To_Destroy.end(); ++it)
	{

		if ((*it)->Mooving_State == EMooving_State::EMS_None)
		{
			delete (*it);
			it = Object_To_Destroy.erase(it);
		}

		if (it == Object_To_Destroy.end())
			break;

	}
}
//==========================================================================================================================
void AsMoover::Clear_All_Data()
{
	Object_On_Moovable.erase(Object_On_Moovable.begin(), Object_On_Moovable.end());
}
//==========================================================================================================================
// pricate section:
//==========================================================================================================================
bool AsMoover::Moove_Stone(AGame_Object* object, int direction)
{
	int x{}, y{};
	int next_x{}, next_y{};
	int index{};

	object->Get_Ceil_Pos(x, y);
	next_x = x + Ways[direction * 2];
	next_y = y + Ways[direction * 2 + 1];
	index = next_y * Level_Width + next_x;
	if (Game_Objects_Support_Pointer_Array[index] == nullptr)
	{
		Moove_Object(direction, object);
		return true;
	}

	return false;
}
//==========================================================================================================================
void AsMoover::Load_Sounds()
{
	Pass_Sound = Mix_LoadWAV("sounds/pass.wav");
	Stone_Sound = Mix_LoadWAV("sounds/stone.wav");
	Diamond_Take_Sound = Mix_LoadWAV("sounds/diamond_take.wav");
	Diamond_Fallen_Sound = Mix_LoadWAV("sounds/diamond_fallen.wav");
	Finish_Sound = Mix_LoadWAV("sounds/finish.wav");
}
//==========================================================================================================================