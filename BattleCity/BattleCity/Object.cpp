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
void Object::setRectangle(int left, int top, int width, int height)
{
	this->_size.left = left;
	this->_size.top = top;
	this->_size.right = this->_size.left + width;
	this->_size.bottom = this->_size.top + height;
}

Object::~Object()
{
}
