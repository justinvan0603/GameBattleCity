#pragma once
#include "Object.h"
#include "GameDefaultConstant.h"
#include "Keyboard.h"
#include "StaticObject.h"

//cac huong di chuyen cua 1 object dong
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
	int _level;	//cap do cua object
	Sprite** _listSprite; //Quan ly tat ca cac frame cho tat ca cac huong chuyen dong
	Sprite* _curSprite; //sprite hien tai dang ve cua object
	int _hitPoint;	//mau cua object
	MoveDirection _currentDirection;	//Huong di chuyen hien tai cua object
	vector<Object*> _listCollisionObject;	//list toan bo object tinh trong map
	int** _map;	//ma tran map

	//Object*** _listStaticObject;
	vector<vector<StaticObject*>>* _listNearByObject;	//list cac object tinh xung quanh object dong can xet va cham
public:
	
	DynamicObject();
	MoveDirection getCurrentMoveDirection();	//Lay huong di chuyen hien tai
	void setCurrentMoveDirection(MoveDirection direction);	//Set huong di chuyen
	void InitMapData(int** map, vector<vector<StaticObject*>>* listNearByObject);	//gan ma tran map va cac object tinh cho object dong
	void FindNearbyObject();	//tim cac phan tu xung quanh vi tri cua object hien tai
	MoveDirection RandomDirection();	//Phat sinh ngau nhien huong di chuyen
	void RandomChangeDirection();	//Phat sinh ngau nhien huong di chuyen khong trung voi huong ban dau
	void InvertDirection();	//Dao nguoc huong di chuyen
	int GetLevel();	//Lay level cua object
	virtual void Move() = 0;
	virtual void Update();
	~DynamicObject();
};


