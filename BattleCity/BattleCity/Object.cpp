#include "Object.h"


Object::Object()
{
}

int Object::getPositionX()
{
	return this->_positionX;
}
int Object::getPositionY()
{
	return this->_positionY;
}
void Object::setPositionX(int newX)
{
	this->_positionX = newX;
}
void Object::setPositionY(int newY)
{
	this->_positionY = newY;
}

Object::~Object()
{
}
