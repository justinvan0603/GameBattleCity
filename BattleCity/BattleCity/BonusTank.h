#pragma once
#include "Enemy.h"
class BonusTank : public Enemy
{
private:
	DWORD _lastTime;
public:
	BonusTank(LPD3DXSPRITE, D3DXVECTOR2 );
	void Draw();
	void Shoot();
	void Move();
	void Update();
	~BonusTank();
};

