#include "BrickWall.h"



BrickWall::BrickWall(Sprite* sprite, int type, D3DXVECTOR3 pos):StaticObject(sprite,type,pos)
{
	this->_isTerminated = false;
	this->_id = ID_BRICKWALL;
}

BrickWall::BrickWall()
{
	this->_isTerminated = false;
	this->_id = ID_BRICKWALL;
}

void BrickWall::Draw()
{
	StaticObject::Draw();
}

void BrickWall::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite, type, pos);
}

void BrickWall::Update()
{
	StaticObject::Update();
}


BrickWall::~BrickWall()
{
	
}
