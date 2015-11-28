#pragma once
#include "ShootableObject.h"

#include"GameTime.h"
#include "Effect.h"
class PlayerTank: public ShootableObject
{
private:
	int _life;
	int _immortalTime;
	GameTime *_bulletDelay;
	GameTime *_shieldDelay;
	Effect* _shieldEffect;
	//DWORD _shieldRoundTime;
	//time_t _shieldRoundTime;
	bool _isActiveShield;
public:
	
	//Bullet * _bullet;
	PlayerTank(LPD3DXSPRITE);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	void PlayerPromoted();
	void ActivateShield();
	
	~PlayerTank();
};

