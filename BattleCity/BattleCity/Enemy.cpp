#include "Enemy.h"
#include "BulletManager.h"
#define ENEMY_BULLET_DELAY 1200
Enemy::Enemy()
{
	_objectType = ENEMY_OBJECT_TYPE;
	_level = LEVEL_ONE;
	_startTime = GetTickCount();
	_currentDirection = DOWN;
	_isCollied = false;
	_isFreeze = false;
}
void Enemy::DeActivateBonus()
{
	_isBonusTank = false;
}

void Enemy::MoveWithCollision()
{
	if (_isCollied)
	{
		RandomChangeDirection();
	
		_isCollied = false;
	}
}
void Enemy::Shoot()
{
	D3DXVECTOR2 bulletPosition = CalculateBulletPosition(_left, _top, _currentDirection); // Tinh vi tri xuat hien cua vien dan theo huong di chuyen

	 if (GameTime::RenderFrame(_startTime, ENEMY_BULLET_DELAY))	//Kiem tra khoang thoi gian giua 2 lan ban
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
