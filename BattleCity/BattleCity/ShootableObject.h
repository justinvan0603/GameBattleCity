#pragma once
#include "DynamicObject.h"
class ShootableObject : public DynamicObject
{
protected:
	bool isShooting;
public:
	ShootableObject();
	virtual void Shoot() = 0;
	~ShootableObject();
};

