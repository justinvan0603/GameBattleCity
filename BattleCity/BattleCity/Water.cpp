#include "Water.h"

Water::Water(Sprite* sprite, int type, D3DXVECTOR3 pos):StaticObject(sprite, type, pos)
{
	this->_id = ID_WATER;
}

Water::Water()
{
	this->_id = ID_WATER;
}

void Water::Draw()
{
	StaticObject::Draw();
}

void Water::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite, type, pos);
}

void Water::Update()
{
	StaticObject::Update();
}


Water::~Water()
{
}
