#pragma once
#include "Enemy.h"
class LightTank: public Enemy
{
private:
	
public:
	LightTank(LPD3DXSPRITE);
	void Draw();
	void Shoot();
	void Update();
	void Move();
	~LightTank();
};

