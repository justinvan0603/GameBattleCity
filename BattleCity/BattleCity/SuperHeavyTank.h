#pragma once
#include "ShootableObject.h"
class SuperHeavyTank : public ShootableObject
{
private:
public:
	SuperHeavyTank(LPD3DXSPRITE);
	void Draw();
	void Move();
	void Update();
	void Shoot();
	~SuperHeavyTank();
};

