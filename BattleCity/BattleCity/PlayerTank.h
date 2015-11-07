#pragma once
#include "DynamicObject.h"
#include "Bullet.h"
class PlayerTank: public DynamicObject
{
private:
	int _life;
	int _immortalTime;
	Bullet* _bullet;
	bool isShooting;
public:
	PlayerTank(LPD3DXSPRITE);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	~PlayerTank();
};

