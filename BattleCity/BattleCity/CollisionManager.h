#pragma once
#include "Object.h"
#include "Bullet.h"


class CollisionManager
{
public:
	CollisionManager();
	static MyRectangle BroadphaseRect(Object *A);
	static bool isCollision(Object* A, Object* B);
	static bool AABBCheck(MyRectangle* A, MyRectangle* B);
	static bool CollisionPreventMove(Object* A, Object* B);
	static void CollisionStopMoving(Object* A, Object* B);
	static bool CollisionBulletWithObject(Bullet* A, Object* B);
	static bool CollisionWithScreen(Object* A);
	static bool CollisionChangeDirection(DynamicObject *A, DynamicObject *B);
	static bool CollisionEnemy(DynamicObject* A, DynamicObject* B);
	//static void CalculateSpeedAfterCollision(Object* A, Object* B);
	~CollisionManager();
};

