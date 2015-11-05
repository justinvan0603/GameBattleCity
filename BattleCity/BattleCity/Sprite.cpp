#include "Sprite.h"

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
		int i = 10;
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
		D3DCOLOR_XRGB(88, 1, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		int i = 10;
	}

}

void Sprite::Next()
{
	this->_Index = (this->_Index + 1) % this->_Count;
}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, int index, D3DXVECTOR3 Location)
{
	this->Render(Target, index, Location.x, Location.y);
}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, int row, int col, D3DXVECTOR3 Location)
{
	RECT srect;

	srect.left = col * (_Width)+1;
	srect.top = row * (_Height)+1;
	srect.right = srect.left + _Width - 1;
	srect.bottom = srect.top + _Height - 1;

	this->_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&Location,
		D3DCOLOR_XRGB(255, 255, 255));

}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, int index, int X, int Y)
{
	this->_Index = index;
	this->Render(Target, X, Y);
}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, D3DXVECTOR3 Location)
{
	this->Render(Target, Location.x, Location.y);
}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, int X, int Y)
{
	RECT srect;

	srect.left = (_Index % _SpritePerRow) * (_Width);
	srect.top = (_Index / _SpritePerRow) * (_Height);
	srect.right = srect.left + _Width - 1;
	srect.bottom = srect.top + _Height - 1;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	this->_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255));

}

Sprite::~Sprite()
{

}
