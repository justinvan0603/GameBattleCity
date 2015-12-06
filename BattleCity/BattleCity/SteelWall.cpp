#include "SteelWall.h"



SteelWall::SteelWall()
{
}

SteelWall::SteelWall(Sprite* sprite, int typeSteel, D3DXVECTOR3 pos)
{
	this->_id = ID_STEELWALL;
	this->_typeSteel = typeSteel;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; // new Sprite(_spriteHandler, MAP_RESOURCE_PATH_STEELWALL, TILE_WIDTH, TILE_HEIGHT, 1, 1);
}

void SteelWall::Draw()
{
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 0.0f);
	_image->Render(_typeSteel, position);
}

void SteelWall::Update()
{

}

void SteelWall::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	this->_typeSteel = type;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; // new Sprite(_spriteHandler, MAP_RESOURCE_PATH_STEELWALL, TILE_WIDTH, TILE_HEIGHT, 1, 1);
}

SteelWall::~SteelWall()
{
	if (_image != NULL)
		_image = NULL;
}
