#include "StaticObject.h"


void StaticObject::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	this->_type = type;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; 

}

void StaticObject::Draw()
{
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 0.0f);
	_image->Render(_type, position);
}

void StaticObject::Update()
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

StaticObject::StaticObject(Sprite* sprite, int type, D3DXVECTOR3 pos)
{
	_objectType = STATIC_OBJECT;
	_width = DEFAULT_STATIC_WIDTH;
	_height = DEFAULT_STATIC_HEIGHT;
	_vx = 0;
	_vy = 0;
	this->_type = type;
	this->_left = (int)pos.x;
	this->_top = (int)pos.y;
	_image = sprite; 

}

StaticObject::~StaticObject()
{
	if (_image != NULL)
		_image = NULL;
}
