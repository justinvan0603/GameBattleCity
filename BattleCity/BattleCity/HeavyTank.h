#pragma once
#include "ShootableObject.h"
class HeavyTank:ShootableObject
{
public:
	HeavyTank(LPD3DXSPRITE);
	void Draw();
	void Move();
	void Shoot();
	void Update();
	~HeavyTank();
};

