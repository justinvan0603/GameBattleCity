﻿#include "Sprite.h"

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, char* Path, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	this->_Image = NULL;
	this->_SpriteHandler = SpriteHandler;
	this->_Width = Width;
	this->_Height = Height;
	this->_Count = Count;
	this->_SpritePerRow = SpritePerRow;
	this->_Index = 0;

	this->_CurrentSpriteLocation.x = 0.0f;
	this->_CurrentSpriteLocation.y = 0.0f;
	this->_CurrentSpriteLocation.z = 0.0f;

	result = D3DXGetImageInfoFromFile(Path, &info);
	if (result != D3D_OK)
	{
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		Path,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(81, 1, 0),
		&info,
		NULL,
		&_Image);


}

void Sprite::Next()
{
	this->_Index = (this->_Index + 1) % this->_Count;

}
void Sprite::Next(bool& isCompleted)
{
	this->_Index = (this->_Index + 1) % this->_Count;
	if (_Index == _Count -1)
		isCompleted = true;
}
void Sprite::Next(int startFrame)
{
	this->_Index = (this->_Index + 1) % this->_Count;
	if (this->_Index == _Count - 1)
		this->_Index = startFrame;
}
//Chuyen frame cho super heavy dung sprite vi du khi dang bi dong bang
void Sprite::NextInCurRow()
{
	this->_Index++;
	if (this->_Index == _SpritePerRow)
	{
		this->_Index = 0;
	}
	if (this->_Index == _Count)
	{
		this->_Index = _SpritePerRow;
	}
}
void Sprite::NextColumn()
{

		this->_Index += _SpritePerRow;
		if (this->_Index >= _Count)
			this->_Index -= 2 * _SpritePerRow;
	

}
void Sprite::Previous()
{
	this->_Index--;
}
void Sprite::Render(int index, D3DXVECTOR3 Location)
{
	this->Render(index, Location.x, Location.y);
}

void Sprite::Render(int row, int col, D3DXVECTOR3 Location)
{
	RECT srect;

	srect.left = col * (_Width);
	srect.top = row * (_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&Location,
		D3DCOLOR_XRGB(255, 255, 255));
	_SpriteHandler->End();
}

void Sprite::Render(int index, int X, int Y)
{
	this->_Index = index;
	this->Render(X, Y);
}

void Sprite::Render(D3DXVECTOR3 Location)
{
	this->Render(Location.x, Location.y);
}

void Sprite::Render(int X, int Y)
{
	RECT srect;

	srect.left = (_Index % _SpritePerRow) * (_Width);
	srect.top = (_Index / _SpritePerRow) * (_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	D3DXVECTOR3 position((float)X, (float)Y, 0);
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255,255 ));
	_SpriteHandler->End();
}

Sprite::~Sprite()
{

}

int Sprite::getWidth()
{
	return this->_Width;
}
int Sprite::getHeight()
{
	return this->_Height;
}
void Sprite::setWidth(int width)
{
	_Width = width;
}
void Sprite::setHeight(int height)
{
	_Height = height;
}
int Sprite::getIndex()
{
	return _Index;
}
void Sprite::setStartFrame(int startFrame)
{
	this->_Index = startFrame;
}
