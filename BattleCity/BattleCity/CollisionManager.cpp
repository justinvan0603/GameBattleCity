#include "CollisionManager.h"
#include "EffectManager.h"
#include "PlayerTank.h"
#include "SuperHeavyTank.h"
#include "EffectManager.h"
#include "GameSound.h"
#include "ScoreManager.h"

CollisionManager::CollisionManager()
{
}

//Tao hinh chu nhat broad-phasing
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
//Xet va cham giua doi tuong dong va doi tuong tinh
bool CollisionManager::CollisionPreventMove(Object* A, Object* B)
{
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{
		A->setVelocityX(SPEED_NO);
		A->setVelocityY(SPEED_NO);
		//Set lai vi tri sau khi phat hien va cham de ngan khong cho doi tuong di chuyen lun vao
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
		Enemy* enemy = dynamic_cast<Enemy*>(A);
		if (enemy != NULL)
			enemy->InvertDirection();
	}
}
//Xet va cham giua dan va cac object
bool CollisionManager::CollisionBulletWithObject(Bullet* A, Object* B)
{
	MyRectangle broadphase = BroadphaseRect(A);
	if (AABBCheck(&broadphase, B))
	{
			//A->_isTerminated = true;
			//Dan player va enemy va cham se bi huy
			if (B->getId() == ID_BULLET && A->getAllyObject() == ALLY_PLAYER)
			{
				A->_isTerminated = true;
				B->_isTerminated = true;
				return true;
			}
			D3DXVECTOR2 position;
			position.x = A->getLeft() - SPRITE_WIDTH/2;
			position.y = A->getTop() - SPRITE_HEIGHT/2;
			//Neu dan va cham voi doi tuong tinh
			if (B->getObjectType() == STATIC_OBJECT)
			{
				//Dan va cham voi dai bang
				if (B->getId() == ID_EAGLE)
				{
					A->_isTerminated = true;
					D3DXVECTOR2 pos;
					pos.x = B->getLeft();
					pos.y = B->getTop();
					EffectManager::getInstance()->AddDestroyEffect(pos);
					B->_isTerminated = true;
					GameSound::getInstance()->Play(ID_SOUND_ALLY_EXPLODE);
					return true;
				}
				//Dan va cham voi tuong thep
				if (B->getId() == ID_STEELWALL)
				{
					EffectManager::getInstance()->AddBulletEffect(position);
					A->_isTerminated = true;
					//De pha huy tuong thep thi dan phai dat level 4
					if (A->GetLevel() == LEVEL_FOUR)
					{

						if (A->getAllyObject() == ALLY_PLAYER)
							GameSound::getInstance()->Play(ID_SOUND_BRICK_EXPLODE);
						B->_isTerminated = true;
					}
					else
					{ 
						if (A->getAllyObject() == ALLY_PLAYER)
							GameSound::getInstance()->Play(ID_SOUND_STEEL_WALL_EXPLODE);
					}
					return true;

				}
				//Dan khong bi huy khi va cham voi nuoc
				if (B->getId() == ID_WATER)
				{

					A->_isTerminated = false;
					B->_isTerminated = false;
					return true;
				}
				//Dan va cham voi gach
				if (B->getId() == ID_BRICKWALL);
				{
					A->_isTerminated = true;
					B->_isTerminated = true;
					EffectManager::getInstance()->AddBulletEffect(position);
					if (A->getAllyObject() == ALLY_PLAYER)
						GameSound::getInstance()->Play(ID_SOUND_BRICK_EXPLODE);
					
					return true;
				}

	
			}
			else
			{
				//Neu dan do player ban ra
				if (A->getAllyObject() == ALLY_PLAYER)
				{
					A->_isTerminated = true;
					//Doi tuong trung dan la enemy
					if (B->getObjectType() == ENEMY_OBJECT_TYPE)
					{
						D3DXVECTOR2 pos;
						pos.x = B->getLeft();
						pos.y = B->getTop();
						//B->_isTerminated = true;
						//Neu khong phai super heavy tank thi chet ngay
						if (B->getId() != ID_SUPER_HEAVY_TANK)
						{
							GameSound::getInstance()->Play(ID_SOUND_TANK_EXPLODE);
							ScoreManager::getInstance()->addKillTankScore(B->getId());
							
							EffectManager::getInstance()->AddDestroyEffect(pos);
							B->_isTerminated = true;
						}
						//Nguoc lai la superheavytank thi phai kiem tra mau
						else
						{
							SuperHeavyTank* superHeavy = dynamic_cast<SuperHeavyTank*>(B);
							if (superHeavy != NULL)
							{
								superHeavy->lostHitPoint();
								if (superHeavy->getHitPoint() <= 0)
								{
									GameSound::getInstance()->Play(ID_SOUND_TANK_EXPLODE);
									ScoreManager::getInstance()->addKillTankScore(B->getId());
									EffectManager::getInstance()->AddDestroyEffect(pos);
									B->_isTerminated = true;
								}
								else
								{
									EffectManager::getInstance()->AddBulletEffect(position);
									GameSound::getInstance()->Play(ID_SOUND_TANK_HIT);
								}
								
							}
						}
					}
				}
				//Neu dan do enemy ban ra 
				else
				{
					D3DXVECTOR2 pos;
					pos.x = B->getLeft();
					pos.y = B->getTop();
					A->_isTerminated = true;
					//Neu dan trung player
					if (B->getId() == ID_PLAYER)
					{
						//Player dang khong o trang thai bat tu
						if (!B->_isImmortal)
						{
							EffectManager::getInstance()->AddDestroyEffect(pos);
							GameSound::getInstance()->Play(ID_SOUND_ALLY_EXPLODE);
							B->_isTerminated = true;
						}
						else
						{
							EffectManager::getInstance()->AddBulletEffect(pos);
							B->_isTerminated = false;
						}
					}
				}
			}

		return true;
	}
	return false;
}
//Xet va cham giua doi tuong dong voi man hinh
bool CollisionManager::CollisionWithScreen(Object* A)
{
	MyRectangle collisionRect = BroadphaseRect(A);
	if (A->getObjectType() == ENEMY_OBJECT_TYPE)
	{
		Enemy * enemy = dynamic_cast<Enemy*>(A);
		if (collisionRect.getTop() < POS_MAP_TOP_LEFT_Y && enemy->getCurrentMoveDirection() == UP )
		{
			A->setPositionY(A->getPositionY() + POS_MAP_TOP_LEFT_Y - A->getTop() +1);
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;
		}
		if (collisionRect.getBottom() > POS_MAP_TOP_LEFT_Y + MAP_HEIGHT && enemy->getCurrentMoveDirection() == DOWN)
		{
			A->setPositionY(A->getPositionY() + POS_MAP_TOP_LEFT_Y + MAP_HEIGHT - A->getBottom() -1);
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;
		}
		if (collisionRect.getLeft() < POS_MAP_TOP_LEFT_X && enemy->getCurrentMoveDirection() == LEFT)
		{
			A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X - A->getLeft() +1);
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;

		}
		if (collisionRect.getRight() > POS_MAP_TOP_LEFT_X + MAP_WIDTH && enemy->getCurrentMoveDirection() == RIGHT)
		{
			A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X + MAP_WIDTH - A->getRight() -1);
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;
		}
	}
	else
	{
		if (collisionRect.getTop() < POS_MAP_TOP_LEFT_Y)
		{
			A->setPositionY(A->getPositionY() + POS_MAP_TOP_LEFT_Y - A->getTop());
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;
		}
		if (collisionRect.getBottom() > POS_MAP_TOP_LEFT_Y + MAP_HEIGHT)
		{
			A->setPositionY(A->getPositionY() + POS_MAP_TOP_LEFT_Y + MAP_HEIGHT - A->getBottom());
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;
		}
		if (collisionRect.getLeft() < POS_MAP_TOP_LEFT_X)
		{
			A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X - A->getLeft());
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;

		}
		if (collisionRect.getRight() > POS_MAP_TOP_LEFT_X + MAP_WIDTH)
		{
			A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X + MAP_WIDTH - A->getRight());
			if (A->getId() == ID_BULLET)
				A->_isTerminated = true;
			return true;
		}
	}

	return false;
	
	//MyRectangle collisionRect = BroadphaseRect(A);
	//if (collisionRect.getTop() < POS_MAP_TOP_LEFT_Y)
	//{
	//	A->setPositionY(A->getPositionY() + POS_MAP_TOP_LEFT_Y- A->getTop());
	//	if (A->getId() == ID_BULLET)
	//		A->_isTerminated = true;
	//	return true;
	//}
	//if (collisionRect.getBottom() > POS_MAP_TOP_LEFT_Y + MAP_HEIGHT )
	//{
	//	A->setPositionY(A->getPositionY() +POS_MAP_TOP_LEFT_Y + MAP_HEIGHT -A->getBottom());
	//	if (A->getId() == ID_BULLET)
	//		A->_isTerminated = true;
	//	return true;
	//}
	//if (collisionRect.getLeft() < POS_MAP_TOP_LEFT_X)
	//{
	//	A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X- A->getLeft());
	//	if (A->getId() == ID_BULLET)
	//		A->_isTerminated = true;
	//	return true;
	//	 
	//}
	//if (collisionRect.getRight() > POS_MAP_TOP_LEFT_X + MAP_WIDTH )
	//{
	//	A->setPositionX(A->getPositionX() + POS_MAP_TOP_LEFT_X + MAP_WIDTH- A->getRight());
	//	if (A->getId() == ID_BULLET)
	//		A->_isTerminated = true;
	//	return true;
	//}

	//return false;
}
//Kiem tra va cham player va enemy
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
				B->RandomChangeDirection();
				return true;

			}
			if (A->getRight() > B->getRight())
			{
				A->setPositionX(A->getPositionX() + B->getRight() - A->getLeft() + 1);
				B->RandomChangeDirection();
				return true;

			}
		}
		if (A->getRight() > B->getLeft() && A->getLeft() < B->getRight())
		{
			if (A->getTop() < B->getTop())
			{
				A->setPositionY(A->getPositionY() + B->getTop() - A->getBottom() - 1);
				B->RandomChangeDirection();
				return true;

			}
			if (A->getBottom() > B->getBottom())
			{
				A->setPositionY(A->getPositionY() + B->getBottom() - A->getTop() + 1);
				B->RandomChangeDirection();
				return true;
			}
		}
		if (A->getCurrentMoveDirection() == B->getCurrentMoveDirection())
		{
			if (B->getRight() < A->getLeft() || B->getBottom() < A->getTop())
				B->InvertDirection();
			return true;
		}
		B->InvertDirection();
		//B->RandomChangeDirection();
		return true;
	}
	return false;
}
//Kiem tra va cham giua enemy vs enemy
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
			if (A->getRight() > B->getRight())
			{
				A->setPositionX(A->getPositionX() + B->getRight() - A->getLeft() + 1);

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
		}
		if (A->getRight() > B->getLeft() && A->getLeft() < B->getRight())
		{
			if (A->getTop() < B->getTop())
			{
				A->setPositionY(A->getPositionY() + B->getTop() - A->getBottom() - 1);

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
			if (A->getBottom() > B->getBottom())
			{
				A->setPositionY(A->getPositionY() + B->getBottom() - A->getTop() + 1);

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
//Kiem tra va cham voi item
bool CollisionManager::CollisionWithItem(PlayerTank* A,PowerUp* B)
{
	MyRectangle broadphaseRectA = BroadphaseRect(A);
	if (AABBCheck(&broadphaseRectA, B))
	{
		ScoreManager::getInstance()->addPowerUpScore();
		B->setEaten();
		if (B->getType() == ID_POWER_EXTRA_LIFE)
		{
			GameSound::getInstance()->Play(ID_SOUND_LIFE_UP);
		}
		else
			GameSound::getInstance()->Play(ID_SOUND_ITEM_EAT);
		return true;
	}
	return false;
}
int CollisionManager::FindRespawnPosition(vector<MyRectangle*>* listposition, int currentposition, vector<Enemy*>* enemyOnMap)
{
	bool isEnemyCollided = false;
	int length = enemyOnMap->size();
	for (int i = 0; i < length; i++)
	{
		MyRectangle enemyBroadphase = BroadphaseRect(enemyOnMap->at(i));
		if (AABBCheck(&enemyBroadphase, listposition->at(currentposition)))
		{
			isEnemyCollided = true;
			break;
		}
	}
	if (!isEnemyCollided)
	{
		return currentposition;
	}
	else
	{
		isEnemyCollided = false;
		int size = listposition->size();
		for (int i = 0; i < size; i++)
		{
			if (i != currentposition)
			{
	
				for (int j = 0; j < length; j++)
				{
					MyRectangle enemyBroadphase = BroadphaseRect(enemyOnMap->at(j));
					if (AABBCheck(&enemyBroadphase, listposition->at(i)))
					{
						isEnemyCollided = true;
						break;
					}
				}
				if (!isEnemyCollided)
				{
					return i;
				}
			}
		}
	}
	return -1;
}
//Tim vi tri hoi sinh
int CollisionManager::FindRespawnPosition(vector<MyRectangle*>* listposition, int currentposition, PlayerTank* A, vector<Enemy*>* enemyOnMap)
{
	MyRectangle playerBroadphaseRect = BroadphaseRect(A);
	bool isPlayerCollided = false;
	bool isEnemyCollided = false;
	if (AABBCheck(&playerBroadphaseRect, listposition->at(currentposition)))
	{
		isPlayerCollided = true;
	}
	int length = enemyOnMap->size();
	for (int i = 0; i < length; i++)
	{
		MyRectangle enemyBroadphase = BroadphaseRect(enemyOnMap->at(i));
		if (AABBCheck(&enemyBroadphase, listposition->at(currentposition)))
		{
			isEnemyCollided = true;
			break;
		}
	}
	if (!isPlayerCollided && !isEnemyCollided)
	{
		return currentposition;
	}
	else
	{
		isEnemyCollided = false;
		isPlayerCollided = false;
		int size = listposition->size();
		for (int i = 0; i < size; i++)
		{
			if (i != currentposition)
			{
				if (AABBCheck(&playerBroadphaseRect, listposition->at(i)))
				{
					isPlayerCollided = true;
				}
				for (int j= 0; j < length; j++)
				{
					MyRectangle enemyBroadphase = BroadphaseRect(enemyOnMap->at(j));
					if (AABBCheck(&enemyBroadphase, listposition->at(i)))
					{
						isEnemyCollided = true;
						break;
					}
				}
				if (!isEnemyCollided && !isPlayerCollided)
				{
					return i;
				}
			}
		}
	}
	return -1;
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
