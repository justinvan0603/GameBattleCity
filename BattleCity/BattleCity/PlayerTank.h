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
	DWORD _shieldTime;
	//DWORD _shieldRoundTime;
	//time_t _shieldRoundTime;
	bool _isMoving;
	bool _isActiveShield;
public:
	
	PlayerTank(LPD3DXSPRITE);
	void Draw();
	void Update();
	void Move();
	void Shoot();
	int getLife();
	void addLife();
	void update();
	void SetDirection(MoveDirection direction);
	void Respawn();
	void PlayerPromoted();
	void ActivateShield();
	
	~PlayerTank();
};

