#pragma once
#include "Enemy.h"
class MediumTank: public Enemy
{
private:

public:
	MediumTank(LPD3DXSPRITE);
	MediumTank(LPD3DXSPRITE, D3DXVECTOR2);
	void Draw();
	void Shoot();
	void Update();
	void Move();
	~MediumTank();
};

