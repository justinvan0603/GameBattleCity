#pragma once
#include "ShootableObject.h"
class Enemy : public ShootableObject
{

protected:
	bool _isBonusTank;
	bool _isFreeze;
public:
	bool _isCollied;
	Enemy();
	virtual void Draw()=0; 
	void Move()=0;
	void MoveWithCollision();
	void Shoot();
	void Update() = 0;
	void RandomShoot();
	bool isBonusTank();
	void ActivateFreeze();
	void DeactivateFreeze();
	~Enemy();
};

