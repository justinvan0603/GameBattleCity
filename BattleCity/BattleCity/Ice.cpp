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
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, -1.0f);
	_image->Render(_type, position);
}

void Ice::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite, type, pos);
}

Ice::~Ice()
{
}
