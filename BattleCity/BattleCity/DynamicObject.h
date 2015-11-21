#pragma once
#include "Object.h"
#include "GameDefaultConstant.h"
#include "Keyboard.h"
#include "StaticObject.h"
enum MoveDirection
{
	UP = 0,
	LEFT = 1,
	DOWN = 2,
	RIGHT = 3,
	NUM_OF_DIRECTION = 4
};

class DynamicObject : public Object
{
protected:
	int _level;
	Sprite** _listSprite; //Quan ly tat ca cac frame cho tat ca cac huong chuyen dong
	Sprite* _curSprite;
	int _hitPoint;
	MoveDirection _currentDirection;
	vector<Object*> _listCollisionObject;
	int*** _map;
	int _row;
	int _column;
	Object*** _listStaticObject;
	vector<vector<StaticObject*>>* _listNearByObject;
public:
	DynamicObject();
	MoveDirection getCurrentMoveDirection();
	void InitMapData(int*** map, int row, int column, Object** listStaticObject);
	void FindNearbyObject();
	virtual void Move() = 0;
	virtual void Update();
	~DynamicObject();
};


