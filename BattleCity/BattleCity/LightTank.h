#pragma once
#include "Enemy.h"
//Light tank co dac diem:
//--Toc do di chuyen nhanh = 4
//--Toc do ban co ban = 6
class LightTank: public Enemy
{
private:
	
public:
	LightTank(LPD3DXSPRITE);
	LightTank(LPD3DXSPRITE, D3DXVECTOR2, bool = false);
	void Draw();
	void Shoot();
	void Update();
	void Move();
	~LightTank();
};

