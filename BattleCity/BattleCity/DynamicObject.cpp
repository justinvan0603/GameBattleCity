#include "DynamicObject.h"


DynamicObject::DynamicObject()
{
}



DynamicObject::~DynamicObject()
{
	for (int i = 0; i < NUM_OF_DIRECTION; i++)
	{
		delete this->_listSprite[i];
	}
	delete this->_listSprite;
}
