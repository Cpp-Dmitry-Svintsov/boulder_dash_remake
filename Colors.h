#pragma once

#include "frameDc.h"

//===========================================================================================================
//===========================================================================================================
class AsColors
{
protected:
	~AsColors();
	AsColors();

public:
	AsColors(AsColors& other) = delete;
	void operator=(const AsColors &) = delete;

	//=========================Black, Gray colors and White colors==================================
	static const COLORREF Black;

	static const COLORREF BG;
	static const HBRUSH Brush_Bg;
	static const HPEN Pen_Bg;
	static const HPEN Pen_1_Bg;

	static const COLORREF MaskBg;
	static const HBRUSH Brush_MaskBg;
	static const HPEN Pen_MaskBg;

	static const COLORREF Gray;
	static const HBRUSH Brush_Gray;
	static const HPEN Pen_Gray;

	static const COLORREF White;
	static const HBRUSH Brush_White;
	static const HPEN Pen_White;
	static const HPEN Pen_1_White;
	static const HPEN Pen_15_White;

	// =====================================Red colors===============================================

	static const COLORREF DarkRed; //Walls
	static const HBRUSH Brush_DarkRed;
	static const HPEN Pen_DarkRed;

	static const COLORREF FireBrick; //Walls
	static const HBRUSH Brush_FireBrick;
	static const HPEN Pen_FireBrick;

	// =====================================Rozy colors===============================================

	static const COLORREF LightPink;
	static const HBRUSH Brush_LightPink;
	static const HPEN Pen_LightPink;

	static const COLORREF PeachPuff; // terra
	static const HBRUSH Brush_PeachPuff;
	static const HPEN Pen_PeachPuff;

	static const COLORREF MediumVioletRed; // stones
	static const HBRUSH Brush_MediumVioletRed;
	static const HPEN Pen_MediumVioletRed;

	//=====================================  Violet colors  ===============================================

	static const COLORREF Orchid;
	static const HBRUSH Brush_Orchid;
	static const HPEN Pen_Orchid;

	static const COLORREF Indigo;
	static const HBRUSH Brush_Indigo;
	static const HPEN Pen_Indigo;

	//======================================  Moron colors  ==============================================

	static const COLORREF RosyBrown;
	static const HBRUSH Brush_RosyBrown;
	static const HPEN Pen_RosyBrown;

	static const COLORREF Peru; // Border
	static const HBRUSH Brush_Peru;
	static const HPEN Pen_Peru;

	//======================================  Green colors  ===============================================

	static const COLORREF MediumSeaGreen;  //player body
	static const HBRUSH Brush_MediumSeaGreen;
	static const HPEN Pen_MediumSeaGreen;

	static const COLORREF DarkGreen;
	static const HBRUSH Brush_DarkGreen;
	static const HPEN Pen_DarkGreen;

	//======================================  Blue colors  ================================================

	static const COLORREF DodgerBlue; 
	static const HBRUSH Brush_DodgerBlue;
	static const HPEN Pen_DodgerBlue;

	static const COLORREF DeepBlue;
	static const HBRUSH Brush_DeepBlue;
	static const HPEN Pen_DeepBlue;

	static const COLORREF RoyalBlue;
	static const HBRUSH Brush_RoyalBlue;
	static const HPEN Pen_RoyalBlue;

	static const COLORREF SkyBlue;
	static const HBRUSH Brush_SkyBlue;
	static const HPEN Pen_SkyBlue;
};
