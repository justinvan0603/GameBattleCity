#pragma once
#include "DynamicObject.h"


class Bullet : public DynamicObject
{
private:

public:
	Bullet(LPD3DXSPRITE);
	void Draw();
	void Move();
	void Update();
	void Shoot(){};
	void setFireDirection(MoveDirection direction);
	~Bullet();
};

