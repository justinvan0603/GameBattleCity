#pragma once
#include "DynamicObject.h"

class PlayerTank: public DynamicObject
{
private:
	int _life;
	int _immortalTime;
	int _speed_last;
	
public:
	PlayerTank(LPDIRECT3DDEVICE9 device);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	~PlayerTank();
};

