#include "Eagle.h"



Eagle::Eagle()
{
	_status = EAGLE_STATUS::LIVE;
}

Eagle::Eagle(Sprite * sprite, D3DXVECTOR3 position)
{
	this->_left = position.x;
	this->_top = position.y;
	_image = sprite;
	_status = EAGLE_STATUS::LIVE;
}

void Eagle::Update()
{
}

void Eagle::Draw()
{
	D3DXVECTOR3 position(this->_left, this->_top, 0.0f);
	if (_status == EAGLE_STATUS::LIVE)
	{
		_image->Render(0, 0, position);
	}
	else
	{
		_image->Render(0, 1, position);
	}
		
}

void Eagle::setEagleStatus(EAGLE_STATUS status)
{
	_status = status;
}


Eagle::~Eagle()
{
}
