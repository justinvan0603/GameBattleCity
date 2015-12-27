#include "Water.h"
#include "GameTime.h"

Water::Water(Sprite* sprite, int type, D3DXVECTOR3 pos):StaticObject(sprite, type, pos)
{
	this->_id = ID_WATER;
	_delayTime = DELAY_TIME_NEXT_SPRITE_WATER;
	_indexDistance = 0;
}

Water::Water()
{
	this->_id = ID_WATER;
}

void Water::Draw()
{
	D3DXVECTOR3 position((float)this->_left, (float)this->_top, 0.0f);	
	if(_type < 10)
	{
		_image->Render(_type - 4 + _indexDistance, position);
	}
	else
	{
		_image->Render(_type - 12 + _indexDistance, position);
	}
	if(GameTime::DelayTime(_delayTime))
	{
		_delayTime = DELAY_TIME_NEXT_SPRITE_WATER;
		(_indexDistance == 0 ? _indexDistance = 4 : _indexDistance = 0);
	}
		/*4 0 4 
		5 1	5
		14 2 6
		15 3 7*/
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
