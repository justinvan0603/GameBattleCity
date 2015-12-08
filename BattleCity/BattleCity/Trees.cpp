#include "Trees.h"


Trees::Trees(Sprite* sprite, int type, D3DXVECTOR3 pos) :StaticObject(sprite, type, pos)
{
	this->_id = ID_TREES;
}

Trees::Trees()
{
	this->_id = ID_TREES;
}

void Trees::Update()
{
	StaticObject::Update();
}

void Trees::Draw()
{
	StaticObject::Draw();
}

void Trees::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite, type, pos);
}

Trees::~Trees()
{
}
