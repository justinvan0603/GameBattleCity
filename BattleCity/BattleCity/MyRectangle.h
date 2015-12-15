#pragma once

//Lop co so dinh nghia 1 hinh chu nhat bao object trong game
class MyRectangle
{
protected:
	int _vx;
	int _vy;
	int _top;
	int _left;
	int _width;
	int _height;
public:
	MyRectangle();
	MyRectangle(int top, int left, int width, int height, int vx=0, int vy=0);
	int getTop();
	int getLeft();
	int getRight();
	int getBottom();
	int getVelocityX();
	int getVelocityY();
	int getWidth();
	int getHeight();
	int getPositionX();
	int getPositionY();
	void setPositionX(int newX);
	void setPositionY(int newY);
	void setVelocityX(int vx);
	void setVelocityY(int vy);
	void setRelativeVelocity(MyRectangle* moveObject);
	~MyRectangle();
};

