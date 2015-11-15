#pragma once
#include "Sprite.h"
#include "GameDefaultConstant.h"
#include "MyRectangle.h"
#include <vector>
#include <iostream>
using namespace std;
class Object : public MyRectangle
{
protected:
	int _id; //moi 1 loai doi tuong co ID rieng (Vi du: player id =1, brick id = 69....)
	short _objectType; //doi tuong muon khoi tao thuoc nhom doi tuong nao (Dynamic or Static ?)
	LPD3DXSPRITE _spriteHandler;
	
public:
	bool _isTerminated;
	Object();
	int getId();
	short getObjectType();
	
	virtual void Draw();
	virtual void Update() = 0;
	~Object();
};

