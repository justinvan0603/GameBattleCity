#pragma once
#include "Object.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "PlayerTank.h"
#include <vector>
using namespace std;
#include "Enemy.h"
//Quan ly va cham
class CollisionManager
{
public:
	CollisionManager();
	static MyRectangle BroadphaseRect(Object *A);	//Ham tao hinh chu nhat broadphase trong thuat toan broad-phasing
	static bool isCollision(Object* A, Object* B);	
	static bool AABBCheck(MyRectangle* A, MyRectangle* B);	//Xet va cham AABB
	static bool CollisionPreventMove(Object* A, Object* B);	//Xet va cham voi object tinh va ngan chan di chuyen
	static void CollisionStopMoving(Object* A, Object* B);
	static bool CollisionBulletWithObject(Bullet* A, Object* B);	//Xet va cham dan voi object
	static bool CollisionWithScreen(Object* A);	//Xet va cham object dong voi man hinh
	static bool CollisionChangeDirection(DynamicObject *A, DynamicObject *B);	//Xet va cham giua player- enemy neu co va cham chuyen huong enenmy
	static bool CollisionEnemy(DynamicObject* A, DynamicObject* B);	//Xet va cham giua 2 enemy
	static bool CollisionWithItem(PlayerTank* A, PowerUp *B);	//Xet va cham giua player va item
	static int FindRespawnPosition(vector<MyRectangle*>* listposition, int currentposition, PlayerTank* A, vector<Enemy*>* enemyOnMap);
	static int FindRespawnPosition(vector<MyRectangle*>* listposition, int currentposition, vector<Enemy*>* enemyOnMap);
	//Tim vi tri xuat hien cua enemy ma tai do khong co bat ky object nao dang dung tai vi tri do

	~CollisionManager();
};

