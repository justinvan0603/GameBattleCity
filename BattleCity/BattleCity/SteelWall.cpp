#include "SteelWall.h"



SteelWall::SteelWall()
{
	this->_isTerminated = false;
	this->_id = ID_STEELWALL;
}

SteelWall::SteelWall(Sprite* sprite, int type, D3DXVECTOR3 pos) :StaticObject(sprite, type, pos)
{
	this->_isTerminated = false;
	this->_id = ID_STEELWALL;
}

void SteelWall::Draw()
{
	StaticObject::Draw();
}

void SteelWall::Update()
{
	StaticObject::Update();
}

void SteelWall::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite,type,pos);
}

SteelWall::~SteelWall()
{
}
