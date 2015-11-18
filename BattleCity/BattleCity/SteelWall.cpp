#include "SteelWall.h"



SteelWall::SteelWall()
{
}

SteelWall::SteelWall(Sprite* sprite, int typeSteel, D3DXVECTOR3 pos)
{
	this->_typeSteel = typeSteel;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; // new Sprite(_spriteHandler, MAP_RESOURCE_PATH_STEELWALL, TILE_WIDTH, TILE_HEIGHT, 1, 1);
}

void SteelWall::Draw()
{
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 0.0f);
	switch (_typeSteel)
	{
	case 17:
	{
		_image->Render(0, 0, position);
		break;
	}
	case 18:
	{
		_image->Render(0, 1, position);
		break;
	}
	case 25:
	{
		_image->Render(1, 0, position);
		break;
	}
	case 26:
	{
		_image->Render(1, 1, position);
		break;
	}
	default:
		break;
	}
}

void SteelWall::Update()
{

}

SteelWall::~SteelWall()
{
	if (_image != NULL)
		_image = NULL;
}
