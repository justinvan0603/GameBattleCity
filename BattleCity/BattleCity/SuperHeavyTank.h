#pragma once
#include "Enemy.h"

//Co hitpoint = 3 toc do di chuyen= 2 toc do dan = 6
class SuperHeavyTank : public Enemy
{
private:
	int _hitPoint;
	int _index;
public:
	SuperHeavyTank(LPD3DXSPRITE);
	SuperHeavyTank(LPD3DXSPRITE, D3DXVECTOR2, bool =false);
	int getHitPoint();
	void lostHitPoint();	//khi bi player ban thi giam hitpoint
	void Draw();
	void Move();
	void Update();
	void Shoot();
	~SuperHeavyTank();
};

