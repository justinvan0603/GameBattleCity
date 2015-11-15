#pragma once
#include "Object.h"
#include "Bullet.h"


class CollisionManager
{
public:
	CollisionManager();
	static MyRectangle BroadphaseRect(Object *A);
	static bool isCollision(MyRectangle* A, MyRectangle* B);
	static bool AABBCheck(MyRectangle* A, MyRectangle* B);
	static void CollisionPreventMove(Object* A, Object* B);
	static void CollisionStopMoving(Object* A, Object* B);
	static void CollisionBulletWithObject(Bullet* A, Object* B);
	//static void CalculateSpeedAfterCollision(Object* A, Object* B);
	~CollisionManager();
};

