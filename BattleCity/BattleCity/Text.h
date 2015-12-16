#ifndef __TEXT_H__
#define __TEXT_H__

#include <d3dx9.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include "GameDefaultConstant.h"

class Text
{
public:
	Text(LPD3DXSPRITE& spriteHandler);
	~Text(void);
	void drawText(std::string Content, D3DXVECTOR3 Position, D3DCOLOR Color = D3DCOLOR_XRGB(0, 0, 0),
					int Size = DEFAULT_FONTSIZE, UINT DT_Type = DT_LEFT, int Max_Lengh = 0, int Max_Line = 0);

private:
	void setFontSize(int newSize);
	void initializeFont();

private:

	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DDEVICE9 _d3dDevice;
	ID3DXFont *_font;				//Doi tuong font dung de ve
	LPCTSTR _fontFace;				//Loai font chu
	int _fontSize;					//Kich co chu
};
#endif

