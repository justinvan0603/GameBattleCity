#pragma once
#include "Enemy.h"
class HeavyTank: public Enemy
{
public:
	HeavyTank(LPD3DXSPRITE);
	HeavyTank(LPD3DXSPRITE, D3DXVECTOR2);
	void Draw();
	void Move();
	void Shoot();
	void Update();
	~HeavyTank();
};

