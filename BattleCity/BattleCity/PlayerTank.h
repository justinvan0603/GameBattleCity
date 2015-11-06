#pragma once
#include "DynamicObject.h"
#include "Bullet.h"
class PlayerTank: public DynamicObject
{
private:
	int _life;
	int _immortalTime;
	Bullet* _bullet;
public:
	PlayerTank(LPDIRECT3DDEVICE9 device);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	~PlayerTank();
};

