#include "DynamicObject.h"


DynamicObject::DynamicObject()
{
	_objectType = DYNAMIC_OBJECT;

}

MoveDirection DynamicObject::getCurrentMoveDirection()
{
	return this->_currentDirection;
}

DynamicObject::~DynamicObject()
{
	for (int i = 0; i < NUM_OF_DIRECTION; i++)
	{
		delete this->_listSprite[i];
	}
	delete this->_listSprite;
}
