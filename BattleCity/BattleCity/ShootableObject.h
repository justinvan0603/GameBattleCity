#pragma once
#include "DynamicObject.h"
#include "Bullet.h"
#include "GameTime.h"
class ShootableObject : public DynamicObject
{
protected:
	bool isShooting;
	vector<Bullet*> _listBullet;
	DWORD _startTime;
public:
	ShootableObject();
	virtual void Shoot() = 0;
	virtual void Move() = 0;
	virtual void Update() = 0;
	vector<Bullet*> getListBullet();
	void DrawBullet();
	~ShootableObject();
};

