#pragma once
#include "Sprite.h"
#include "GameDefaultConstant.h"
#include "MyRectangle.h"
class Object : public MyRectangle
{
protected:
	int _id; //moi 1 loai doi tuong co ID rieng (Vi du: player id =1, brick id = 69....)
	short _objectType; //doi tuong muon khoi tao thuoc nhom doi tuong nao (Dynamic or Static ?)
	LPD3DXSPRITE _spriteHandler;
	bool _isTerminated;
public:
	Object();

	virtual void Draw();
	virtual void Update() = 0;
	~Object();
};

