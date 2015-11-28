#include "CollisionManager.h"
#include "EffectManager.h"
#include "PlayerTank.h"
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
	width = A->getWidth()+ abs(A->getVelocityX());
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
		if (A->getTop() < B->getBottom() && A->getBottom() > B->getTop())
		{
			if (A->getLeft() < B->getLeft())
			{
				A->setPositionX(A->getPositionX() + B->getLeft() - A->getRight() - 1);

				return true;
			}
			if (A->getRight() > B->getRight())
			{
				A->setPositionX(A->getPositionX() + B->getRight() - A->getLeft() + 1);

				return true;
			}
		}

		if (A->getRight() > B->getLeft() && A->getLeft() < B->getRight())
		{
			if (A->getTop() < B->getTop())
			{
				A->setPositionY(A->getPositionY() + B->getTop() - A->getBottom() - 1);

				return true;
			}
			if (A->getBottom() > B->getBottom())
			{
				A->setPositionY(A->getPositionY() + B->getBottom() - A->getTop() + 1);

				return true;
			}
		}
		
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
			A->_isTerminated = true;
			if (B->getObjectType() == STATIC_OBJECT)
			{
				if (B->getId() == ID_STEELWALL)
				{
					if (A->GetLevel() == 4)
						B->_isTerminated = true;
				}
				else
					B->_isTerminated = true;
			}
			else
			{
				if (A->getAllyObject() == ALLY_PLAYER)
				{
					if (B->getObjectType() == ENEMY_OBJECT_TYPE)
					{
						B->_isTerminated = true;
					}
				}
				else
				{
					if (A->getId() == ID_PLAYER)
					{
						if (!A->_isImmortal)
						{
							A->_isTerminated = true;
						}
					}
				}
			}
		return true;
	}
	return false;
}
bool CollisionManager::CollisionWithScreen(Object* A)
{
	MyRectangle collisionRect = BroadphaseRect(A);
	if (collisionRect.getTop() < POS_MAP_TOP_LEFT_Y)
	{
		A->setPositionY(A->getPositionY() + POS_MAP_TOP_LEFT_Y- A->getTop());
		if (A->getId() == ID_BULLET)
			A->_isTerminated = true;
		return true;
	}
	if (collisionRect.getBottom() > POS_MAP_TOP_LEFT_Y + MAP_HEIGHT)
	{
		A->setPositionY(A->getPositionY() +POS_MAP_TOP_LEFT_Y + MAP_HEIGHT -A->getBottom());
		if (A->getId() == ID_BULLET)
			A->_isTerminated = true;
		return true;
	}
	if (collisionRect.getLeft() < POS_MAP_TOP_LEFT_X)
	{
		A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X- A->getLeft());
		if (A->getId() == ID_BULLET)
			A->_isTerminated = true;
		return true;
		 
	}
	if (collisionRect.getRight() > POS_MAP_TOP_LEFT_X + MAP_WIDTH)
	{
		A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X + MAP_WIDTH- A->getRight());
		if (A->getId() == ID_BULLET)
			A->_isTerminated = true;
		return true;
	}
	//if (A->getTop()<= POS_MAP_TOP_LEFT_Y)
	//	return true;
	//if (A->getBottom()  >= POS_MAP_TOP_LEFT_Y + MAP_HEIGHT)
	//	return true;
	//if (A->getLeft() <= POS_MAP_TOP_LEFT_X)
	//	return true;
	//if (A->getRight() >= POS_MAP_TOP_LEFT_X + MAP_WIDTH)
	//	return true;
	return false;
}
bool CollisionManager::CollisionChangeDirection(DynamicObject *A, DynamicObject *B)
{
	MyRectangle broadphaseA = BroadphaseRect(A);
	MyRectangle broadphaseB = BroadphaseRect(B);
	if (AABBCheck(&broadphaseA, &broadphaseB))
	{
		A->setVelocityX(SPEED_NO);
		A->setVelocityY(SPEED_NO);
		B->setVelocityX(SPEED_NO);
		B->setVelocityY(SPEED_NO);
		if (A->getTop() < B->getBottom() && A->getBottom() > B->getTop())
		{
			if (A->getLeft() < B->getLeft())
			{
				A->setPositionX(A->getPositionX() + B->getLeft() - A->getRight() - 1);


			}
			if (A->getRight() > B->getRight())
			{
				A->setPositionX(A->getPositionX() + B->getRight() - A->getLeft() + 1);


			}
		}
		if (A->getRight() > B->getLeft() && A->getLeft() < B->getRight())
		{
			if (A->getTop() < B->getTop())
			{
				A->setPositionY(A->getPositionY() + B->getTop() - A->getBottom() - 1);


			}
			if (A->getBottom() > B->getBottom())
			{
				A->setPositionY(A->getPositionY() + B->getBottom() - A->getTop() + 1);
			}
		}
		B->RandomChangeDirection();
		return true;
	}
	return false;
}
bool CollisionManager::CollisionEnemy(DynamicObject* A, DynamicObject* B)
{
	MyRectangle broadphaseA = BroadphaseRect(A);
	MyRectangle broadphaseB = BroadphaseRect(B);
	if (AABBCheck(&broadphaseA, &broadphaseB))
	{
		A->setVelocityX(SPEED_NO);
		A->setVelocityY(SPEED_NO);
		B->setVelocityX(SPEED_NO);
		B->setVelocityY(SPEED_NO);

		if (A->getTop() < B->getBottom() && A->getBottom() > B->getTop())
		{
			if (A->getLeft() < B->getLeft())
			{
				A->setPositionX(A->getPositionX() + B->getLeft() - A->getRight() - 1);


			}
			if (A->getRight() > B->getRight())
			{
				A->setPositionX(A->getPositionX() + B->getRight() - A->getLeft() + 1);


			}
		}
		if (A->getRight() > B->getLeft() && A->getLeft() < B->getRight())
		{
			if (A->getTop() < B->getTop())
			{
				A->setPositionY(A->getPositionY() + B->getTop() - A->getBottom() - 1);


			}
			if (A->getBottom() > B->getBottom())
			{
				A->setPositionY(A->getPositionY() + B->getBottom() - A->getTop() + 1);
			}
		}

		if (A->getCurrentMoveDirection() == RIGHT && B->getCurrentMoveDirection() == LEFT ||
			A->getCurrentMoveDirection() == LEFT && B->getCurrentMoveDirection() == RIGHT ||
			A->getCurrentMoveDirection() == UP  && B->getCurrentMoveDirection() == DOWN ||
			A->getCurrentMoveDirection() == DOWN && B->getCurrentMoveDirection() == UP)
		{
			A->InvertDirection();
			B->InvertDirection();
			return true;
		}
		if (A->getCurrentMoveDirection() == DOWN &&
			(B->getCurrentMoveDirection() == LEFT ||
			B->getCurrentMoveDirection() == RIGHT ||
			B->getCurrentMoveDirection() == DOWN))
		{
			if (A->getBottom() < B->getTop())
				A->InvertDirection();
			else if (A->getTop() > B->getBottom())
				B->InvertDirection();
			return true;
		}
		if (A->getCurrentMoveDirection() == LEFT &&
			(B->getCurrentMoveDirection() == LEFT ||
			B->getCurrentMoveDirection() == UP ||
			B->getCurrentMoveDirection() == DOWN))
		{
			if (A->getLeft() > B->getRight())
			{
				A->InvertDirection();
			}
			else if (A->getRight() < B->getLeft())
			{
				B->InvertDirection();
			}
			return true;
		}
		if (A->getCurrentMoveDirection() == RIGHT &&
			(B->getCurrentMoveDirection() == RIGHT ||
			B->getCurrentMoveDirection() == UP ||
			B->getCurrentMoveDirection() == DOWN))
		{
			if (A->getLeft() > B->getRight())
			{
				A->InvertDirection();
			}
			else if (A->getRight() < B->getLeft())
			{
				B->InvertDirection();
			}
			return true;
		}
		if (A->getCurrentMoveDirection() == UP &&
			(B->getCurrentMoveDirection() == RIGHT ||
			B->getCurrentMoveDirection() == UP ||
			B->getCurrentMoveDirection() == LEFT))
		{
			if (A->getTop() > B->getBottom())
			{
				A->InvertDirection();
			}
			else if (A->getBottom() < B->getTop())
			{
				B->InvertDirection();
			}
			return true;
		}
		
	}
	return false;
}

bool CollisionManager::isCollision(Object* A, Object* B)
{
	MyRectangle collisionRect = BroadphaseRect(A);
	return CollisionManager::AABBCheck(&collisionRect, B);
}
bool CollisionManager::AABBCheck(MyRectangle* A, MyRectangle* B)
{
	if (A->getLeft() <= B->getRight()
		&& A->getRight() >= B->getLeft()
		&& A->getBottom() >= B->getTop()
		&& A->getTop() <= B->getBottom())
		return true;
	return false;
}


CollisionManager::~CollisionManager()
{
}
