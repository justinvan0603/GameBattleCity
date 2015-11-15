#pragma once
#include "ShootableObject.h"
class MediumTank: ShootableObject
{
private:

public:
	MediumTank(LPD3DXSPRITE);
	void Draw();
	void Shoot();
	void Update();
	void Move();
	~MediumTank();
};

