#include "BrickWall.h"



BrickWall::BrickWall(Sprite* sprite, int typeBrick, D3DXVECTOR3 pos)
{
	this->_typeBrick = typeBrick;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	this->_id = 100;
	_isTerminated = false;
	_image = sprite; //new Sprite(_spriteHandler, MAP_RESOURCE_PATH_BRICKWALL, TILE_WIDTH, TILE_HEIGHT, 1, 1);
}

BrickWall::BrickWall()
{

}

void BrickWall::Draw()
{
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 0.0f);
	_image->Render(_typeBrick, position);
}

void BrickWall::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	this->_typeBrick = type;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; //new Sprite(_spriteHandler, MAP_RESOURCE_PATH_BRICKWALL, TILE_WIDTH, TILE_HEIGHT, 1, 1);
}

void BrickWall::Update()
{
}


BrickWall::~BrickWall()
{
	if (_image != NULL)
		_image = NULL;
}
