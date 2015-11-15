#pragma once
#include "DynamicObject.h"
#include "Bullet.h"
class ShootableObject : public DynamicObject
{
protected:
	bool isShooting;
	vector<Bullet*> _listBullet;
public:
	ShootableObject();
	virtual void Shoot() = 0;
	~ShootableObject();
};

