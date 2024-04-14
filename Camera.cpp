#include "Camera.h"

//=======================================================================================================================
// staticfields members declaration:
//=======================================================================================================================
AsCamera *AsCamera::Self = nullptr;
//=======================================================================================================================
// constructor & destructor & init
//=======================================================================================================================
AsCamera::~AsCamera()
{
	int i{}, j{};

	Self = nullptr;
}
//=======================================================================================================================
AsCamera::AsCamera()
	:Hwnd(0), Frame_Dc_2(0), Frame_Dc_3(0), Cur_Level_Width(0), Cur_Level_Height(0),
	Cx(0), Cy(0), Rx(0.0), Ry(0.0), X_Pos(0.0), Y_Pos(0.0),
	Min_X_Pos(0.0), Min_Y_Pos(0.0), Max_X_Pos(0.0), Max_Y_Pos(0.0)
{
	Camera_Rect.left = AsSettings::Ceil_Size;
	Camera_Rect.top = AsSettings::Ceil_Size * 2;
	Camera_Rect.right = AsSettings::Game_Area_Width - AsSettings::Ceil_Size;
	Camera_Rect.bottom = AsSettings::Game_Area_Height - AsSettings::Ceil_Size;

	Border_Rect.left = 0;
	Border_Rect.top = AsSettings::Ceil_Size;
	Border_Rect.right = AsSettings::Game_Area_Width;
	Border_Rect.bottom = AsSettings::Game_Area_Height;
}
//=======================================================================================================================
void AsCamera::Init(HWND hwnd)
{
	AsFrameDc *frameDc = AsFrameDc::Get_Instance();

	Frame_Dc_2 = frameDc->Get_SecondDc();
	Frame_Dc_3 = frameDc->Get_Third_Dc();

	Border.Init(hwnd, Frame_Dc_2);

}
//=======================================================================================================================
//=======================================================================================================================
AsCamera* AsCamera::Get_Instance()
{
	if (Self == nullptr)
		Self = new AsCamera();

	return Self;
}
void AsCamera::Delete_Instance()
{
	if (Self != nullptr)
		delete Self;
}
//=======================================================================================================================
// public section:
//=======================================================================================================================
void AsCamera::Draw(HDC hdc)
{
	int i{}, j{}, index{};
	int cur_cx_pos{}, cur_cy_pos{}, max_cx_pos{}, max_cy_pos{};
	//-.-.-.-.-.-.-.-.-
	int x_1{}, y_1{}, x_2{}, y_2{};
	int width{}, height{}, x_texture_offset{}, y_texture_offset{};
	//-.-.-.-.-.-.-.-.-.
	int ceil_size = AsSettings::Ceil_Size;
	double d_ceil_size = (double)ceil_size;
	//-.-.-.-.-.-.-.-.-.
	bool w_owerflow = false;
	bool h_owerflow = false;
	//-.-.-.-.-.-.-.-.-.

	//X_Pos = 2.5;
	//Y_Pos = 2.5;

	cur_cx_pos = (int)X_Pos;
	cur_cy_pos = (int)Y_Pos;
	max_cx_pos = cur_cx_pos + Camera_Width;
	if ( max_cx_pos >= Cur_Level_Width - 1)
	{
		max_cx_pos = Cur_Level_Width;
		w_owerflow = true;
	}
	max_cy_pos = cur_cy_pos + Camera_Height;
	if ( max_cy_pos >= Cur_Level_Height - 1 )
	{
		max_cy_pos = Cur_Level_Height;
		h_owerflow = true;
	}


	Border.Clear_Game_Area(hdc);

	height = (int)((Y_Pos - (double)((int)X_Pos)) * ceil_size);
	y_1 = AsSettings::Y_Game_Area_Offset;

	for (i = cur_cy_pos; i < max_cy_pos; i++)
	{
		y_texture_offset = 0;

		height = ceil_size;
		if (i == cur_cy_pos && Y_Pos != 0)
		{
			height = (int)((Y_Pos - (int)Y_Pos) * d_ceil_size);
			y_texture_offset = ceil_size - height;
		}
		else if (i == max_cy_pos - 1 && !h_owerflow)
			height = ceil_size - (int)((Y_Pos - (int)Y_Pos) * d_ceil_size);

		y_2 = y_1 + height;

		x_1 = AsSettings::X_Game_Area_Offset;

		for (j = cur_cx_pos; j < max_cx_pos; j++)
		{
			index = (i * Cur_Level_Width) + j;
		
				x_texture_offset = 0;
				width = ceil_size;
				if (j == cur_cx_pos && X_Pos != 0)
				{
					width = (int)((X_Pos - (int)X_Pos) * d_ceil_size);
					x_texture_offset = ceil_size - width;
				}
				else if (j == max_cx_pos - 1 && !w_owerflow)
					width = ceil_size - (int)((X_Pos - (int)X_Pos) * d_ceil_size);

				x_2 = x_1 + width;

				//if (Curr_Level_Array[index] != 0)
				if (Game_Objects_Support_Pointer_Array[index] != nullptr)
				{
					Game_Objects_Support_Pointer_Array[index]->Draw(hdc, Frame_Dc_2, Frame_Dc_3,
						x_1, y_1, width, height, x_texture_offset, y_texture_offset);
				}

			x_1 = x_2;
		}

		y_1 = y_2;
	}

}
//=======================================================================================================================
void AsCamera::Act()
{
	InvalidateRect(Hwnd, 0, TRUE);
}
//=======================================================================================================================
void AsCamera::Moove(double dx, double dy)
{
	double new_y_pos{};
	double new_x_pos{};

	new_y_pos = Y_Pos + dy;
	new_x_pos = X_Pos + dx;

	new_x_pos = min( max( new_x_pos, 0.0 ), Max_X_Pos );
	new_y_pos = min( max( new_y_pos, 0.0 ), Max_Y_Pos );

	X_Pos = new_x_pos;
	Y_Pos = new_y_pos;
}
//=======================================================================================================================
void AsCamera::Player_Moove(double dx, double dy, double px, double py, EMooving_State direction)
{
	const int camera_offset = 8;

	double new_y_pos{};
	double new_x_pos{};

	new_y_pos = Y_Pos + dy;
	new_x_pos = X_Pos + dx;

	new_x_pos = min(max(new_x_pos, 0.0), Max_X_Pos);
	new_y_pos = min(max(new_y_pos, 0.0), Max_Y_Pos);


	if (py - new_y_pos > Camera_Height - camera_offset && direction == EMooving_State::EMS_Down )
		Y_Pos = new_y_pos;

	if (py - new_y_pos < camera_offset && direction == EMooving_State::EMS_Up )
		Y_Pos = new_y_pos;


	if (px - new_x_pos > Camera_Width - camera_offset && direction == EMooving_State::EMS_Right )
		X_Pos = new_x_pos;

	if (px - new_x_pos < camera_offset && direction == EMooving_State::EMS_Left)
		X_Pos = new_x_pos;
}
//=======================================================================================================================
void AsCamera::Get_Pos(double &x, double &y)
{
	x = X_Pos;
	y = Y_Pos;
}
//=======================================================================================================================
void AsCamera::Set_Curr_Level(int width, int height, unsigned char* cur_lvl_arr, AGame_Object* *pointer_arr)
{
	Cur_Level_Width = width;
	Cur_Level_Height = height;

	Curr_Level_Array = cur_lvl_arr;

	Game_Objects_Support_Pointer_Array = pointer_arr;

	//Определение минимальной и максимальной позиции камеры
	Min_X_Pos = 0.0;
	Min_Y_Pos = 0.0;
	Max_X_Pos = width - (Camera_Width) - 1;
	Max_Y_Pos = height - (Camera_Height) - 1;

	//Max_X_Pos = Camera_Width * AsSettings::Ceil_Size + (double)(width * AsSettings::Ceil_Size - Camera_Width * AsSettings::Ceil_Size);
	//Max_Y_Pos = Camera_Height * AsSettings::Ceil_Size + (double)(height * AsSettings::Ceil_Size - Camera_Height * AsSettings::Ceil_Size);
	X_Pos = 0.0;
	Y_Pos = 0.0;
}
//=======================================================================================================================
// private section:
//=======================================================================================================================
void AsCamera::Get_Texture_Offsets_Pos(int& w_, int& h_)
{
	double ceil_size = (double)AsSettings::Ceil_Size;

	w_ = (X_Pos - (double)((int)X_Pos)) * ceil_size;
	h_ = (Y_Pos - (double)((int)X_Pos)) * ceil_size;
}
//=======================================================================================================================
