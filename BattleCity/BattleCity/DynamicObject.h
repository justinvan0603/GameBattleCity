#pragma once
#include "Sprite.h"
#include "GameDefaultConstant.h"
enum MoveDirection
{
	UP = 0,
	LEFT = 1,
	DOWN = 2,
	RIGHT = 3,
	NUM_OF_DIRECTION = 4
};

class DynamicObject
{
protected:
	int _id;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DDEVICE9 _device;
	bool _isTerminated;
	RECT _size;
	int _positionX;
	int _positionY;
	int _speedX;
	int _speedY;
	int _level;
	Sprite** _listSprite; //Quan ly tat ca cac frame cho tat ca cac huong chuyen dong
	int _hitPoint;
	MoveDirection _currentDirection;


public:
	DynamicObject();
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual void Shoot() = 0;
	virtual void Update() = 0;
	~DynamicObject();
};

