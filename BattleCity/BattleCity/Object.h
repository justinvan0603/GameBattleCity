#pragma once
#include "Sprite.h"
#include "GameDefaultConstant.h"
#include "MyRectangle.h"

#include <time.h>
#include <vector>
#include <iostream>
using namespace std;
class Object : public MyRectangle
{
protected:
	int _id; //moi 1 loai doi tuong co ID rieng (Vi du: player id =1, brick id = 69....)
	int _objectType; //doi tuong muon khoi tao thuoc nhom doi tuong nao (Dynamic or Static ?)
	LPD3DXSPRITE _spriteHandler; //doi tuong dung de ve
	
public:
	bool _isTerminated;	//kiem tra xem object co bi tieu diet chua
	bool _isImmortal;	//object co dang o che do bat tu khong 
	Object();
	int getId();
	int getObjectType();
	D3DXVECTOR2 getPositionObjectInMap(int,int); //Dua tren toa do x, y cua object tinh ra toa do (row, column) trong file map 
	virtual void Draw();
	virtual void Update() = 0;
	~Object();
};

