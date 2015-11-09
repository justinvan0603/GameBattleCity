#pragma once
#include "DynamicObject.h"


class Bullet : public DynamicObject
{
private:
public:
	Bullet(LPD3DXSPRITE);
	Bullet(LPD3DXSPRITE, MoveDirection, int, int);
	void Draw();
	void Move();
	void Update();
	void setFireDirection(MoveDirection direction);
	~Bullet();
};

