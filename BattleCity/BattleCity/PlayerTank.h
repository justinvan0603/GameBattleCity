#pragma once
#include "ShootableObject.h"

#include"GameTime.h"

class PlayerTank: public ShootableObject
{
private:
	int _life;
	int _immortalTime;
	GameTime *_bulletDelay;
	bool isCollide = false;
	
	bool isShooting;
public:

	Bullet * _bullet;
	PlayerTank(LPD3DXSPRITE);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	void update();
	
	~PlayerTank();
};

