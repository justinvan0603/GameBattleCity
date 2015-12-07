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
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 1.0f);
	_image->Render(_type, position);
}

void Trees::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	StaticObject::Init(sprite, type, pos);
}

Trees::~Trees()
{
}
