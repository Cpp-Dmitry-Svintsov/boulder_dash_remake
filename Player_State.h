#pragma once
#include "Common.h"

//===================================================================================================================
enum class EMooving_Substate : unsigned char
{
	EMS_None,
	EMS_Go_Up,
	EMS_Go_Right,
	EMS_Go_Down,
	EMS_Go_Left
};
//===================================================================================================================
class AsPlayer_State
{
public:
	~AsPlayer_State();
	AsPlayer_State();

	operator EMooving_Substate() const;
	void operator=(EMooving_Substate new_state);

private:
	static EMooving_Substate Mooving_State;
};
