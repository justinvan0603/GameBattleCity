#include "Enemy.h"
#include "BulletManager.h"
#define ENEMY_BULLET_DELAY 1100
Enemy::Enemy()
{
	_objectType = ENEMY_OBJECT_TYPE;
	_level = LEVEL_ONE;
	_startTime = GetTickCount();
	_currentDirection = DOWN;
	_isCollied = false;
	_isFreeze = false;
}


void Enemy::MoveWithCollision()
{
	if (_isCollied)
	{
		_currentDirection = RandomDirection();
		_isCollied = false;
	}
}
void Enemy::Shoot()
{
	D3DXVECTOR2 bulletPosition = CalculateBulletPosition(_left, _top, _currentDirection);


	//if (BulletManager::getInstance()->getEnemyBulletSize() == 0)
	//{
	//	BulletManager::getInstance()->AddBullet(_spriteHandler, _currentDirection, bulletPosition, ALLY_ENEMY, _level, _map, _listNearByObject);
	//	_startTime = GetTickCount();
	//}
	 if (GameTime::RenderFrame(_startTime, ENEMY_BULLET_DELAY))
	{
		BulletManager::getInstance()->AddBullet(_spriteHandler, _currentDirection, bulletPosition, ALLY_ENEMY, _level, _map, _listNearByObject);
	}
}
bool Enemy::isBonusTank()
{
	return _isBonusTank;
}
void Enemy::ActivateFreeze()
{
	_isFreeze = true;
}
void Enemy::DeactivateFreeze()
{
	_isFreeze = false;
}
Enemy::~Enemy()
{
}
