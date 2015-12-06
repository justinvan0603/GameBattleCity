#include "CollisionManager.h"
#include "EffectManager.h"
#include "PlayerTank.h"
#include "SuperHeavyTank.h"
#include "EffectManager.h"
#include "GameSound.h"
CollisionManager::CollisionManager()
{
}
MyRectangle CollisionManager::BroadphaseRectWithRelativeSpeed(Object *A, Object* B)
{
	int vxA, vyA;
	vxA = A->getVelocityX() - B->getVelocityX();
	vyA = A->getVelocityY() - B->getVelocityY();
	int x, y, width, height;
	x = A->getPositionX();
	if (A->getVelocityX() < 0)
		x = A->getPositionX() + vxA;
	y = A->getPositionY();
	if (A->getVelocityY() < 0)
		y = A->getPositionY() + vyA;
	width = A->getWidth() + abs(vxA);
	height = A->getHeight() + abs(vyA);
	//width = vxA > 0 ? vxA + A->getWidth() : A->getWidth() - vxA;
	//height = vyA > 0 ? vyA + A->getHeight() : A->getHeight() - vyA;
	return MyRectangle(y, x, width, height);
}

MyRectangle  CollisionManager::BroadphaseRect(Object *A)
{
	//Ham tao broadphase co van toc tuong doi
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

	float v2x, v2y;
	v2x = B->getVelocityX();
	v2y = B->getVelocityY();
	A->setVelocityX(A->getVelocityX() - v2x);
	A->setVelocityY(A->getVelocityY() - v2y);

	
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{
		
		B->setVelocityX(0);
		B->setVelocityY(0);
		A->setVelocityX(0);
		A->setVelocityY(0);

		if (A->getTop() < B->getBottom() && A->getBottom() > B->getTop())
		{
			//A->setVelocityX(0);
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
			//A->setVelocityY(0);
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
	A->setVelocityX(A->getVelocityX() + v2x);
	A->setVelocityY(A->getVelocityY() + v2y);
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
			if (B->getId() == ID_BULLET)
			{
				B->_isTerminated = true;
				return true;
			}
			D3DXVECTOR2 position;
			position.x = A->getLeft() - SPRITE_WIDTH/2;
			position.y = A->getTop() - SPRITE_HEIGHT/2;
			EffectManager::getInstance(0)->AddBulletEffect(position);
			if (B->getObjectType() == STATIC_OBJECT)
			{
				//if (B->getId() == )
				if (B->getId() == ID_STEELWALL)
				{
					//GameSound::getInstance(0)->Play(ID_SOUND_BULLET_EXPLODE);
					if (A->GetLevel() == LEVEL_FOUR)
						B->_isTerminated = true;
					return true;

				}
				if (B->getId() == ID_WATER)
				{

					A->_isTerminated = false;
					return true;
				}
				if (B->getId() == ID_BRICKWALL);
				{
					//GameSound::getInstance(0)->Play(ID_SOUND_BULLET_EXPLODE);
					B->_isTerminated = true;
					return true;
				}
			}
			else
			{
				if (A->getAllyObject() == ALLY_PLAYER)
				{
					if (B->getObjectType() == ENEMY_OBJECT_TYPE)
					{
						//B->_isTerminated = true;
						if (B->getId() != ID_SUPER_HEAVY_TANK)
						{
							//GameSound::getInstance(0)->Play(ID_SOUND_TANK_EXPLODE);
							B->_isTerminated = true;
						}
						else
						{
							SuperHeavyTank* superHeavy = dynamic_cast<SuperHeavyTank*>(B);
							if (superHeavy != NULL)
							{
								if (superHeavy->getHitPoint() == 0)
								{
									//GameSound::getInstance(0)->Play(ID_SOUND_TANK_EXPLODE);
									B->_isTerminated = true;
								}
								else
								{
									superHeavy->lostHitPoint();
									//GameSound::getInstance(0)->Play(ID_SOUND_TANK_HIT);
								}
								
							}
						}
					}
				}
				else
				{
					if (A->getId() == ID_PLAYER)
					{
						if (!A->_isImmortal)
						{
							//GameSound::getInstance(0)->Play(ID_SOUND_ALLY_EXPLODE);
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

	return false;
}
bool CollisionManager::CollisionChangeDirection(DynamicObject *A, DynamicObject *B)
{

	MyRectangle broadphaseA = BroadphaseRect(A);
	MyRectangle broadphaseB = BroadphaseRect(B);
	//X
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
		if (A->getCurrentMoveDirection() == B->getCurrentMoveDirection())
		{
			return true;
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
		if (A->getCurrentMoveDirection() != B->getCurrentMoveDirection())
		{
			A->InvertDirection();
			B->InvertDirection();
			return true;
		}
		if (A->getCurrentMoveDirection() == B->getCurrentMoveDirection())
		{
			if (A->getRight() < B->getLeft() || A->getTop() > B->getBottom())
				A->InvertDirection();
			else
				B->InvertDirection();
			return true;
		}
		
	}
	return false;
}
bool CollisionManager::CollisionWithItem(PlayerTank* A,PowerUp* B)
{
	MyRectangle broadphaseRectA = BroadphaseRect(A);
	if (AABBCheck(&broadphaseRectA, B))
	{
		if (B->getType() == 1) //Star
		{
			A->PlayerPromoted();
			B->setEaten();
			return true;
		}
		if (B->getType() == 2) //Shield
		{
			A->ActivateShield();
			B->setEaten();
			return true;
		}
		if (B->getType() == 3) //Bomb
		{
			B->setEaten();
			return true;
		}
		if (B->getType() == 4) //Freeze
		{
			B->setEaten();
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
