#pragma once
#include "Enemy.h"
class SuperHeavyTank : public Enemy
{
private:
	int _hitPoint;
public:
	SuperHeavyTank(LPD3DXSPRITE);
	SuperHeavyTank(LPD3DXSPRITE, D3DXVECTOR2);
	void Draw();
	void Move();
	void Update();
	void Shoot();
	~SuperHeavyTank();
};

