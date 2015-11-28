#pragma once
#include "Enemy.h"
class LightTank: public Enemy
{
private:
	
public:
	LightTank(LPD3DXSPRITE);
	LightTank(LPD3DXSPRITE, D3DXVECTOR2);
	void Draw();
	void Shoot();
	void Update();
	void Move();
	~LightTank();
};

