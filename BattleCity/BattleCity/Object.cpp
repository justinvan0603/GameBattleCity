#include "Object.h"


Object::Object()
{
}
Object::~Object()
{
}


void Object::Draw()
{
	if (_vy == 0)
		_left += _vx;
	else
		_top += _vy;
}
