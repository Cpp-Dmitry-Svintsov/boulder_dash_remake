#include "Colors.h"


//====================================================================================================================
//определение статических данных класса AsColors
// ==================Black & BG & White colors===============================================
const COLORREF AsColors::Black = RGB(0, 0, 0);

const COLORREF AsColors::BG = RGB(0, 0, 0);
const HBRUSH AsColors::Brush_Bg = CreateSolidBrush( AsColors::BG);
const HPEN AsColors::Pen_Bg = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::BG );
const HPEN AsColors::Pen_1_Bg = CreatePen(PS_SOLID, 1, AsColors::BG);

const COLORREF AsColors::MaskBg = RGB(2, 2, 2);
const HBRUSH AsColors::Brush_MaskBg = CreateSolidBrush(AsColors::MaskBg);
const HPEN AsColors::Pen_MaskBg = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::MaskBg);

const COLORREF AsColors::Gray = RGB(128, 128, 128);
const HBRUSH AsColors::Brush_Gray = CreateSolidBrush(AsColors::Gray);
const HPEN AsColors::Pen_Gray = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::Gray);

const COLORREF AsColors::White = RGB(255, 255, 255);
const HBRUSH AsColors::Brush_White = CreateSolidBrush(AsColors::White);
const HPEN AsColors::Pen_White = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::White);
const HPEN AsColors::Pen_1_White = CreatePen(PS_SOLID, 1, AsColors::White);
const HPEN AsColors::Pen_15_White = CreatePen(PS_SOLID, 10 * AsSettings::Global_Scale, AsColors::White);

// =====================================Red colors colors===============================================

const COLORREF AsColors::DarkRed = RGB(139, 0, 0);
const HBRUSH AsColors::Brush_DarkRed = CreateSolidBrush(AsColors::DarkRed);
const HPEN AsColors::Pen_DarkRed = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::DarkRed);

const COLORREF AsColors::FireBrick = RGB(178, 34, 34);
const HBRUSH AsColors::Brush_FireBrick = CreateSolidBrush(AsColors::FireBrick);
const HPEN AsColors::Pen_FireBrick = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::FireBrick);

// =====================================Rozy colors===============================================

const COLORREF AsColors::LightPink = RGB(255, 182, 193);
const HBRUSH AsColors::Brush_LightPink = CreateSolidBrush(AsColors::LightPink);
const HPEN AsColors::Pen_LightPink = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::LightPink);

const COLORREF AsColors::PeachPuff = RGB(255, 218, 185);
const HBRUSH AsColors::Brush_PeachPuff = CreateSolidBrush(AsColors::PeachPuff);
const HPEN AsColors::Pen_PeachPuff = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::PeachPuff);

const COLORREF AsColors::MediumVioletRed = RGB(199, 21, 133);
const HBRUSH AsColors::Brush_MediumVioletRed = CreateSolidBrush(AsColors::MediumVioletRed);
const HPEN AsColors::Pen_MediumVioletRed = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::MediumVioletRed);

// =====================================Violet colors===============================================

const COLORREF AsColors::Orchid = RGB(218, 112, 214);
const HBRUSH AsColors::Brush_Orchid = CreateSolidBrush(AsColors::Orchid);
const HPEN AsColors::Pen_Orchid = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::Orchid);

const COLORREF AsColors::Indigo = RGB(75, 0, 130);
const HBRUSH AsColors::Brush_Indigo = CreateSolidBrush(AsColors::Indigo);
const HPEN AsColors::Pen_Indigo = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::Indigo);

//======================================  Moron colors  ==============================================

const COLORREF AsColors::RosyBrown = RGB(188, 143, 143);
const HBRUSH AsColors::Brush_RosyBrown = CreateSolidBrush(AsColors::RosyBrown);
const HPEN AsColors::Pen_RosyBrown = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::RosyBrown);

const COLORREF AsColors::Peru = RGB(205, 133, 63); // block colors
const HBRUSH AsColors::Brush_Peru = CreateSolidBrush(AsColors::Peru);
const HPEN AsColors::Pen_Peru = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::Peru);

//======================================  Green colors  ===============================================

const COLORREF AsColors::MediumSeaGreen = RGB(60, 179, 113);
const HBRUSH AsColors::Brush_MediumSeaGreen = CreateSolidBrush(AsColors::MediumSeaGreen);
const HPEN AsColors::Pen_MediumSeaGreen = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::MediumSeaGreen);

const COLORREF AsColors::DarkGreen = RGB(0, 100, 0);
const HBRUSH AsColors::Brush_DarkGreen = CreateSolidBrush(AsColors::DarkGreen);
const HPEN AsColors::Pen_DarkGreen = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::DarkGreen);

//======================================  Blue colors  ================================================

const COLORREF AsColors::DodgerBlue = RGB(30, 144, 255);
const HBRUSH AsColors::Brush_DodgerBlue = CreateSolidBrush(AsColors::DodgerBlue);
const HPEN AsColors::Pen_DodgerBlue = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::DodgerBlue);

const COLORREF AsColors::DeepBlue = RGB(0, 47, 85);
const HBRUSH AsColors::Brush_DeepBlue = CreateSolidBrush(AsColors::DeepBlue);
const HPEN AsColors::Pen_DeepBlue = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::DeepBlue);

const COLORREF AsColors::RoyalBlue = RGB(65, 105, 225);
const HBRUSH AsColors::Brush_RoyalBlue = CreateSolidBrush(AsColors::RoyalBlue);
const HPEN AsColors::Pen_RoyalBlue = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::RoyalBlue);

const COLORREF AsColors::SkyBlue = RGB(135, 206, 235);
const HBRUSH AsColors::Brush_SkyBlue = CreateSolidBrush(AsColors::SkyBlue);
const HPEN AsColors::Pen_SkyBlue = CreatePen(PS_SOLID, AsSettings::Global_Scale, AsColors::SkyBlue);

//====================================================================================================================
//====================================================================================================================
AsColors::~AsColors()
{
}
//====================================================================================================================
AsColors::AsColors()
{
}
//====================================================================================================================
