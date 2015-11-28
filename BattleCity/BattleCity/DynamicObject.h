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
	int** _map;

	//Object*** _listStaticObject;
	vector<vector<StaticObject*>>* _listNearByObject;
public:
	
	DynamicObject();
	MoveDirection getCurrentMoveDirection();
	void setCurrentMoveDirection(MoveDirection direction);
	void InitMapData(int** map, vector<vector<StaticObject*>>* listNearByObject);
	void FindNearbyObject();
	MoveDirection RandomDirection();
	void RandomChangeDirection();
	void InvertDirection();
	int GetLevel();
	virtual void Move() = 0;
	virtual void Update();
	~DynamicObject();
};


