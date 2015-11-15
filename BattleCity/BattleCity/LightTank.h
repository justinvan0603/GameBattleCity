#pragma once
#include "ShootableObject.h"
class LightTank: public ShootableObject
{
private:
	Bullet* _bullet;
public:
	LightTank(LPD3DXSPRITE);
	void Draw();
	void Shoot(){};
	void Update();
	void Move();
	~LightTank();
};

