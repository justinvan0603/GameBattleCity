#pragma once
#include "DynamicObject.h"


class Bullet : public DynamicObject
{
private:

public:
	Bullet(LPDIRECT3DDEVICE9 device);
	void Draw();
	void Move();
	void Update();
	void Shoot(){};
	void setFireDirection(MoveDirection direction);
	~Bullet();
};

