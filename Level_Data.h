#pragma once
#include "Levels_Arrays.h"
#include "Camera.h"

class ALevel_Data
{
public:
	~ALevel_Data();
	ALevel_Data(unsigned char *level_array, int width, int height, int target, int time);
	unsigned char* Init(int& arr_width, int& arr_height, int& target, int &time);

private:
	int Level_Width;
	int Level_Height;
	int Target;
	int Time;
	unsigned char* Level_Array;
};
