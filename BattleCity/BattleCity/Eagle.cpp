#include "Eagle.h"



Eagle::Eagle()
{
	_status = EAGLE_STATUS::LIVE;
}

Eagle::Eagle(Sprite * sprite, D3DXVECTOR3 position)
{
	this->_id = ID_EAGLE;
	this->_objectType = STATIC_OBJECT;
	this->_left = (int)position.x;
	this->_top = (int)position.y;
	this->_width = SPRITE_WIDTH;
	this->_height = SPRITE_HEIGHT;
	_image = sprite;
	_status = EAGLE_STATUS::LIVE;
}

void Eagle::Update()
{
}

void Eagle::Draw()
{
	D3DXVECTOR3 position((float)this->_left, (float) this->_top, 0.0f);
	if (_status == EAGLE_STATUS::LIVE)
	{
		_image->Render(0, 0, position);	//s?ng
	}
	else
	{
		_image->Render(0, 1, position);	//ch?t
	}
		
}

void Eagle::Init(Sprite* sprite, int type, D3DXVECTOR3 pos)
{

}

//---------------------------------------
// Set tr?ng thái live hay dead cho eagle
//---------------------------------------
void Eagle::setEagleStatus(EAGLE_STATUS status)
{
	_status = status;
}

//----------------------------------
// L?y tr?ng thái c?a eagle
//----------------------------------
EAGLE_STATUS Eagle::getEagleStatus()
{
	return _status;
}

Eagle::~Eagle()
{
}
