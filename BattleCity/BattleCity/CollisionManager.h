#pragma once
#include "Object.h"



class CollisionManager
{
public:
	CollisionManager();
	static MyRectangle BroadphaseRect(Object *A);
	static bool isCollision(MyRectangle* A, MyRectangle* B);
	static bool AABBCheck(MyRectangle* A, MyRectangle* B);
	static void CollictionPreventMove(Object* A, Object* B);
	//static void CalculateSpeedAfterCollision(Object* A, Object* B);
	~CollisionManager();
};

