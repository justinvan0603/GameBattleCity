#pragma once
#include "Sprite.h"
enum MoveDirection
{
	UP = 0,
	LEFT = 1,
	RIGHT = 2,
	DOWN = 4,
	NUM_OF_DIRECTION = 5
};

class DynamicObject
{
protected:
	Sprite* _listSprite; //Quan ly tat ca cac frame cho tat ca cac huong chuyen dong
	bool _isTerminated;
	int _hitPoint;
	RECT _size;
public:
	DynamicObject();
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual void Shoot() = 0;
	virtual void Update() = 0;
	~DynamicObject();
};

