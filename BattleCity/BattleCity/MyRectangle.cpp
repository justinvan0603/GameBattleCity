#include "MyRectangle.h"


MyRectangle::MyRectangle()
{
	this->_top = 0;
	this->_left = 0;
	this->_width = 0;
	this->_height = 0;

	this->_vx = 0;
	this->_vy = 0;
}
MyRectangle::MyRectangle(int top, int left, int width, int height, int vx, int vy)
{
	this->_top = top;
	this->_left = left;
	this->_width = width;
	this->_height =  height;

	this->_vx = vx;
	this->_vy = vy;
}
int MyRectangle::getWidth()
{
	return _width;
}
int MyRectangle::getHeight()
{
	return _height;
}
int MyRectangle::getTop()
{
	return this->_top;
}
int MyRectangle::getLeft()
{
	return this->_left;
}
//Khi lay right thi phai tru 1 pixel do truoc do la lay duong vien cua left
int MyRectangle::getRight()
{
	return this->_left + _width-1;
}
//Khi lay bottom thi phai tru 1 pixel do truoc do la lay duong vien cua top
int MyRectangle::getBottom()
{
	return this->_top + _height-1;
}
int MyRectangle::getVelocityX()
{
	return this->_vx;
}
int MyRectangle::getVelocityY()
{
	return this->_vy;
}

void MyRectangle::setVelocityX(int vx)
{
	_vx = vx;
}
void MyRectangle::setVelocityY(int vy)
{
	_vy = vy;
}

int  MyRectangle::getPositionX()
{
	return _left;
}
int  MyRectangle::getPositionY()
{
	return _top;
}
void MyRectangle::setPositionX(int newX)
{
	_left = newX;
}
void MyRectangle::setPositionY(int newY)
{
	_top = newY;
}

void MyRectangle::setRelativeVelocity(MyRectangle* moveObject)
{

}
MyRectangle::~MyRectangle()
{
}
