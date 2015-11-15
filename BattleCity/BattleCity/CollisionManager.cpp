#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}

MyRectangle  CollisionManager::BroadphaseRect(Object *A)
{
	int x, y, width, height;
	x = A->getPositionX();
	if (A->getVelocityX() < 0)
		x = A->getPositionX() + A->getVelocityX();
	y = A->getPositionY();
	if (A->getVelocityY()<0)
		y = A->getPositionY() +A->getVelocityY();
	width = A->getWidth() + abs(A->getVelocityX());
	height = A->getHeight() + abs(A->getVelocityY());
	return MyRectangle(y, x, width, height);
}

void CollisionManager::CollisionPreventMove(Object* A, Object* B)
{
	// A chuyển động B đứng yên
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{

		A->setVelocityX(SPEED_NO);
		A->setVelocityY(SPEED_NO);

	}
}
void CollisionManager::CollisionStopMoving(Object* A, Object* B)
{
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{

		A->setVelocityX(SPEED_NO);
		A->setVelocityY(SPEED_NO);
		B->setVelocityX(SPEED_NO);
		B->setVelocityY(SPEED_NO);

	}
}
void CollisionManager::CollisionBulletWithObject(Bullet* A, Object* B)
{
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{
		if (A->getAllyObject() == ALLY_PLAYER)
		{
			if (B->getId() == ID_LIGHT_TANK)
			{
				A->_isTerminated = true;
				B->_isTerminated = true;
			}
		}
	}
}
bool CollisionManager::isCollision(MyRectangle* A, MyRectangle* B)
{
	return CollisionManager::AABBCheck(A, B);
}
bool CollisionManager::AABBCheck(MyRectangle* A, MyRectangle* B)
{
	return (A->getLeft() < B->getRight() 
		&& A->getRight() > B->getLeft() 
		&& A->getBottom() > B->getTop() 
		&& A->getTop() < B->getBottom());
}

CollisionManager::~CollisionManager()
{
}
