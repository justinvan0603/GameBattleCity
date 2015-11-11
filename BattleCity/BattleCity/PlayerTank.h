#pragma once
#include "ShootableObject.h"
#include "Bullet.h"
class PlayerTank: public ShootableObject
{
private:
	int _life;
	int _immortalTime;
	Bullet* _bullet;
	bool isCollide = false;
public:
	PlayerTank(LPD3DXSPRITE);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	void update();
	Bullet* getBullet();
	
	~PlayerTank();
};

