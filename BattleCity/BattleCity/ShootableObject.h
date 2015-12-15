#pragma once
#include "DynamicObject.h"
#include "Bullet.h"
#include "GameTime.h"
//Lop quan ly cac doi tuong co the ban duoc
class ShootableObject : public DynamicObject
{
protected:
	bool isShooting;

	DWORD _startTime;	//Bien thoi gian de tinh toan khoang thoi gian giua 2 loat dan

public:
	ShootableObject();
	virtual void Shoot() = 0;
	virtual void Move() = 0;
	virtual void Update() = 0;
	D3DXVECTOR2 CalculateBulletPosition(int left, int top, MoveDirection currentDirection);	//Tinh toan xuat hien vien dan

	~ShootableObject();
};

