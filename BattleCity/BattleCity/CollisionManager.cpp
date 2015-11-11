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

void CollisionManager::CollictionPreventMove(Object* A, Object* B)
{
	// A chuyển động B đứng yên
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{

		A->setVelocityX(0);
		A->setVelocityY(0);
		// tam thoi vay da

	}
}

bool CollisionManager::isCollision(MyRectangle* A, MyRectangle* B)
{
	return CollisionManager::AABBCheck(A, B);
}
bool CollisionManager::AABBCheck(MyRectangle* A, MyRectangle* B)
{
	//return (A->getLeft() <= B->getRight() && A->getRight() >= B->getLeft() && A->getTop() >= B->getBottom() && A->gGetBottom() <= b2->GetTop());
	return (A->getLeft() < B->getRight() && A->getRight() > B->getLeft() && A->getBottom() > B->getTop() && A->getTop() < B->getBottom());
}

CollisionManager::~CollisionManager()
{
}
