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
