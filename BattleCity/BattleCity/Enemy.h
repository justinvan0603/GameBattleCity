#pragma once
#include "ShootableObject.h"
class Enemy : public ShootableObject
{
private:
	
	bool _isStopped;
public:
	bool _isCollied;
	Enemy();
	virtual void Draw()=0; 
	void Move()=0;
	void MoveWithCollision();
	void Shoot();
	void Update() = 0;
	MoveDirection RandomDirection();
	void RandomShoot();
	~Enemy();
};

