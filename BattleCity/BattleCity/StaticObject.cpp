#include "StaticObject.h"


void StaticObject::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
}

void StaticObject::Draw()
{
}

StaticObject::StaticObject()
{
	_objectType = STATIC_OBJECT;
	_width = DEFAULT_STATIC_WIDTH;
	_height = DEFAULT_STATIC_HEIGHT;
	_vx = 0;
	_vy = 0;
}


StaticObject::~StaticObject()
{
}
