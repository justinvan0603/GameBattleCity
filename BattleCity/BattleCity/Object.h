#pragma once
#include "Sprite.h"
#include "GameDefaultConstant.h"
class Object
{
protected:
	int _id;
	LPD3DXSPRITE _spriteHandler;
	bool _isTerminated;
	int _positionX;
	int _positionY;
	RECT _size;
public:
	Object();
	int getPositionX();
	int getPositionY();
	void setPositionX(int newX);
	void setPositionY(int newY);
	virtual void Draw() = 0;
	virtual void Update() = 0;
	~Object();
};

