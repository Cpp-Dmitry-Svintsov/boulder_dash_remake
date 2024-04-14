#include "Fonts.h"


//=====================================================================================================================
//static const date section:
//=====================================================================================================================
HFONT AsFonts::Title_Font_Large = AsFonts::Get_Font(-96, 700, 82, L"Ravie"); // Ravie bold 72
HFONT AsFonts::Title_Font_Small = AsFonts::Get_Font(-35, 400, 34, L"Arial Rounded MT Bold"); //Arial rounded bold/2 26
HFONT AsFonts::Info_Pannel_Score_Font = AsFonts::Get_Font(-32, 400, 82, L"Algerian"); //Algerian normal 24
//=====================================================================================================================
// static functions section:
//=====================================================================================================================
HFONT AsFonts::Greate_Font()
{
	CHOOSEFONT cf{};
	LOGFONT lf{};
	HFONT hfont{};

	// Initialize members of the CHOOSEFONT structure.  

	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = (HWND)NULL;
	cf.hDC = (HDC)NULL;
	cf.lpLogFont = &lf;
	cf.iPointSize = 0;
	cf.Flags = CF_SCREENFONTS;
	cf.rgbColors = RGB(0, 0, 0);
	cf.lCustData = 0L;
	cf.lpfnHook = NULL;
	cf.lpTemplateName = NULL;
	cf.hInstance = NULL;
	cf.lpszStyle = NULL;
	cf.nFontType = SCREEN_FONTTYPE;
	cf.nSizeMin = 0;
	cf.nSizeMax = 0;

	// Display the CHOOSEFONT common-dialog box.  

	ChooseFont(&cf);

	// Create a logical font based on the user's  
	// selection and return a handle identifying  
	// that font.  

	hfont = CreateFontIndirect(cf.lpLogFont);
	return (hfont);
}
//=====================================================================================================================
HFONT AsFonts::Get_Font(int height, int weight, int family, const wchar_t *arial_name)
{
	LOGFONT log_font{};
	HFONT hfont{};

	//настройка шрифта
	log_font.lfHeight = height;
	log_font.lfWeight = weight;
	log_font.lfOutPrecision = 3;
	log_font.lfClipPrecision = 2;
	log_font.lfQuality = 1;
	log_font.lfPitchAndFamily = family;
	//log_font.lfFaceName = "Arial Black";
	wcscpy_s(log_font.lfFaceName, arial_name);

	hfont = CreateFontIndirect(&log_font);

	return hfont;
}
//=====================================================================================================================
void AsFonts::Center_Text_To_Rect(HDC hdc, RECT rect, int str_len, const wchar_t* str, int &x_offset, int& y_offset)
{
	//Метод высчитывает координаты начала вывода текста так чтобы текст распологался по центру выбранного прямоугольника
	SIZE text_size;
	GetTextExtentPoint32(hdc, str, str_len, &text_size);
	x_offset = rect.left + (rect.right - rect.left) / 2 - (text_size.cx / 2);
	y_offset = rect.top + (rect.bottom - rect.top) / 2 - (text_size.cy / 2);
}
//=====================================================================================================================
//=====================================================================================================================
AsFonts::~AsFonts()
{

}
//=====================================================================================================================
AsFonts::AsFonts()
{

}
//=====================================================================================================================