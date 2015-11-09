#pragma once
class MyRectangle
{
private:
	int _vx;
	int _vy;
	int _top;
	int _left;
	int _bottom;
	int _right;
public:
	MyRectangle();
	MyRectangle(int top, int left, int right, int bottom, int vx=0, int vy=0);
	MyRectangle* getCheckCollisionRectangle();

	~MyRectangle();
};

