#include "MyRectangle.h"


MyRectangle::MyRectangle()
{
}
MyRectangle::MyRectangle(int top, int left, int right, int bottom, int vx, int vy)
{
	this->_top = top;
	this->_left = left;
	this->_right = right;
	this->_bottom = bottom;
	this->_vx = vx;
	this->_vy = vy;
}
MyRectangle* MyRectangle::getCheckCollisionRectangle()
{

	if (_vy == 0)
	{
		if (_vx > 0)
			_right += _vx;
		else if (_vx < 0)
			_left += _vx;
	}
	if (_vx == 0)
	{
		if (_vy > 0)
		{
			_bottom += _vy;
		}
		else if (_vy < 0)
		{
			_top += _vy;
		}
	}
}
MyRectangle::~MyRectangle()
{
}
