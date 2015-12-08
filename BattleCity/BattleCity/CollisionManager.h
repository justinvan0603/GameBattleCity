#pragma once
#include "Object.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "PlayerTank.h"
#include <vector>
using namespace std;
#include "Enemy.h"

class CollisionManager
{
public:
	CollisionManager();
	static MyRectangle BroadphaseRect(Object *A);
	static MyRectangle BroadphaseRectWithRelativeSpeed(Object* A, Object* B);
	static bool isCollision(Object* A, Object* B);
	static bool AABBCheck(MyRectangle* A, MyRectangle* B);
	static bool CollisionPreventMove(Object* A, Object* B);
	static void CollisionStopMoving(Object* A, Object* B);
	static bool CollisionBulletWithObject(Bullet* A, Object* B);
	static bool CollisionWithScreen(Object* A);
	static bool CollisionChangeDirection(DynamicObject *A, DynamicObject *B);
	static bool CollisionEnemy(DynamicObject* A, DynamicObject* B);
	static bool CollisionWithItem(PlayerTank* A, PowerUp *B);
	static int FindRespawnPosition(vector<MyRectangle*>* listposition, int currentposition, PlayerTank* A, vector<Enemy*>* enemyOnMap);
//	static bool CollisionPlayerWithEnemy(PlayerTank* player, vector<Enemy*> listEnemy);
	//static void CalculateSpeedAfterCollision(Object* A, Object* B);
	~CollisionManager();
};

