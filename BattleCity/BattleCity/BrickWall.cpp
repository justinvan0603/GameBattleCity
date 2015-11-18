#include "BrickWall.h"



BrickWall::BrickWall(Sprite* sprite, int typeBrick, D3DXVECTOR3 pos)
{
	this->_typeBrick = typeBrick;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; //new Sprite(_spriteHandler, MAP_RESOURCE_PATH_BRICKWALL, TILE_WIDTH, TILE_HEIGHT, 1, 1);
}

void BrickWall::Draw()
{
	StaticObject::Draw();
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 0.0f);
	switch (_typeBrick)
	{
	case 1:
	{
		_image->Render(0, 0, position);
		break;
	}
	case 2:
	{
		_image->Render(0, 1, position);
		break;
	}
	case 9:
	{
		_image->Render(1, 0, position);
		break;
	}
	case 10:
	{
		_image->Render(1, 1, position);
		break;
	}
	default:
		break;
	}
}

void BrickWall::Update()
{
}


BrickWall::~BrickWall()
{
	if (_image != NULL)
		_image = NULL;
}
