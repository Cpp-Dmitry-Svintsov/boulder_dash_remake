#include "Level_Data.h"


//======================================================================================================================
// Constructor and Destructor & init funcions
//======================================================================================================================
ALevel_Data::~ALevel_Data()
{
}
//======================================================================================================================
ALevel_Data::ALevel_Data(unsigned char* level_array, int width, int height, int target, int time)
	:Level_Width(width), Level_Height(height), Target(target), Time(time)
{
	//int arr_len = *(&level_array + 1) - level_array;
	Level_Array = level_array;
}
//======================================================================================================================
unsigned char* ALevel_Data::Init(int &arr_width, int &arr_height, int &target, int &time)
{
	unsigned char* copy_cur_level;

	int len = Level_Width * Level_Height;

	arr_width = Level_Width;
	arr_height = Level_Height;

	target = Target;
	time = Time;

	copy_cur_level = new unsigned char[len];

	//clear current array
	memset(copy_cur_level, 0, len);
	////copy af arrays
	memcpy(copy_cur_level, Level_Array, len);

	return copy_cur_level;

}
//======================================================================================================================

//======================================================================================================================

//======================================================================================================================