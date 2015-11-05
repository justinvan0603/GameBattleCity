#pragma once
#include "Sprite.h"
class StaticObject
{
protected:
	Sprite* _image;
	int _id;
	LPD3DXSPRITE _spriteHandler;
	bool _isTerminated;
	RECT _size;
	int _positionX;
	int _positionY;
public:
	StaticObject();
	~StaticObject();
};

