#pragma once
#include "Sprite.h"
#include "GameDefaultConstant.h"

class Object
{
protected:
	int _id; //moi 1 loai doi tuong co ID rieng (Vi du: player id =1, brick id = 69....)
	short _objectType; //doi tuong muon khoi tao thuoc nhom doi tuong nao (Dynamic or Static ?)
	LPD3DXSPRITE _spriteHandler;
	bool _isTerminated;
	int _positionX;
	int _positionY;
	RECT _size;
	//Rectangle _collisionRectangle;
public:
	Object();
	int getPositionX();
	int getPositionY();
	void setPositionX(int newX);
	void setPositionY(int newY);
	void setRectangle(int, int, int, int);
	RECT getRectangle();
	virtual void Draw() = 0;
	virtual void Update() = 0;
	~Object();
};

