#include "Ice.h"



Ice::Ice()
{
	this->_id = ID_ICE;
}

Ice::Ice(Sprite* sprite, int type, D3DXVECTOR3 pos) : StaticObject(sprite, type, pos)
{
	this->_id = ID_ICE;
}

void Ice::Update()
{
	StaticObject::Update();
}

void Ice::Draw()
{
	StaticObject::Draw();
}

void Ice::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite, type, pos);
}

Ice::~Ice()
{
}
