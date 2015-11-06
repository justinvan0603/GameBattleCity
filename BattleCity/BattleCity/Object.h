#pragma once
#include "Sprite.h"
class Object
{
protected:
	int _id;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DDEVICE9 _device;
	bool _isTerminated;
	int _positionX;
	int _positionY;
	RECT _size;
public:
	Object();
	virtual void Draw() = 0;
	virtual void Update() = 0;
	~Object();
};

