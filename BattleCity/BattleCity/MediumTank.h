#pragma once
#include "Enemy.h"
//Dac diem: Tank yeu nhat game
//Toc do di chuyen: 2
//Toc do bay cua dan: 6
class MediumTank: public Enemy
{
private:

public:
	MediumTank(LPD3DXSPRITE);
	MediumTank(LPD3DXSPRITE, D3DXVECTOR2, bool = false);
	void Draw();
	void Shoot();
	void Update();
	void Move();
	~MediumTank();
};

