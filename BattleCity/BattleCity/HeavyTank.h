#pragma once
#include "Enemy.h"

//Co toc do dan bay cao nhat trong so cac enemy
class HeavyTank: public Enemy
{
public:
	HeavyTank(LPD3DXSPRITE);
	HeavyTank(LPD3DXSPRITE, D3DXVECTOR2, bool = false);
	void Draw();
	void Move();
	void Shoot();
	void Update();
	~HeavyTank();
};

