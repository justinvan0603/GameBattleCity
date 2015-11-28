#include "Text.h"


Text::Text(LPD3DXSPRITE& spriteHandler)
{
	_fontFace = DEFAULT_FONTFACE;
	_fontSize = DEFAULT_FONTSIZE;
	_spriteHandler = spriteHandler;
	_spriteHandler->GetDevice(&_d3dDevice);
	AddFontResourceEx(DEFAULT_FONTPATH, FR_PRIVATE, 0);

	initializeFont();
}

void Text::initializeFont()
{
	HRESULT hr = D3DXCreateFont(_d3dDevice, _fontSize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, _fontFace, &_font);
}


void Text::drawText(std::string Content, D3DXVECTOR3 Position, D3DCOLOR Color, int Size , UINT DT_Type, int Max_Lengh)
{
	if (Size != _fontSize)
		setFontSize(Size);
	RECT fRectangle;
	int n;
	if (Max_Lengh == 0)
		n = Content.length();
	else
		n = Max_Lengh;
	SetRect(&fRectangle, Position.x, Position.y, Position.x + _fontSize*n, Position.y + _fontSize);
	_font->DrawTextA(NULL, Content.c_str(), -1, &fRectangle, DT_Type, Color);
}


void Text::setFontSize(int newSize)
{
	_font->Release();
	_fontSize = newSize;
	initializeFont();
}

Text::~Text(void)
{
	_font->Release();
	RemoveFontResource(DEFAULT_FONTPATH);
}
