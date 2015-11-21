#include "CollisionManager.h"
#include "EffectManager.h"

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

bool CollisionManager::CollisionPreventMove(Object* A, Object* B)
{
	// A chuyển động B đứng yên
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{

		A->setVelocityX(SPEED_NO);
		A->setVelocityY(SPEED_NO);
		return true;
	}
	return false;
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
bool CollisionManager::CollisionBulletWithObject(Bullet* A, Object* B)
{
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{
		if (A->getAllyObject() == ALLY_PLAYER)
		{
			if (B->getObjectType() == STATIC_OBJECT)
			{
				A->_isTerminated = true;
				//EffectManager::getInstance(0)->RenderEffect(ID_EFFECT_SHIELD, A->getLeft(), A->getTop());
				//B->_isTerminated = true;
				
			}
		}
		return true;
	}
	return false;
}
bool CollisionManager::CollisionWithScreen(Object* A)
{
	MyRectangle collisionRect = BroadphaseRect(A);
	if (collisionRect.getTop() <= POS_MAP_TOP_LEFT_Y)
		return true;
	if (collisionRect.getBottom()  >= POS_MAP_TOP_LEFT_Y + MAP_HEIGHT)
		return true;
	if (collisionRect.getLeft() <= POS_MAP_TOP_LEFT_X)
		return true;
	if (collisionRect.getRight() >= POS_MAP_TOP_LEFT_X + MAP_WIDTH)
		return true;
	return false;
}

bool CollisionManager::isCollision(Object* A, Object* B)
{
	MyRectangle collisionRect = BroadphaseRect(A);
	return CollisionManager::AABBCheck(&collisionRect, B);
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
