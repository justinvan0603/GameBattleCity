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
	int _delayShield;
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
	void reset();
	void SetDirection(MoveDirection direction);
	void Respawn();
	void PlayerPromoted();
	void ActivateShield();
	
	~PlayerTank();
};

