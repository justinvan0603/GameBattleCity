#include "Object.h"


Object::Object()
{
}
Object::~Object()
{
}

int Object::getId()
{
  	return this->_id;
}
int Object::getObjectType()
{
	return this->_objectType;
}
void Object::Draw()
{
	if (_vy == 0)
		_left += _vx;
	else
		_top += _vy;
}

D3DXVECTOR2  Object::getPositionObjectInMap(int x, int y)
{
	D3DXVECTOR2 position;
	position.x = (x - POS_MAP_TOP_LEFT_X) / TILE_WIDTH;
	position.y = (y - POS_MAP_TOP_LEFT_Y) / TILE_HEIGHT;
	return position;
}