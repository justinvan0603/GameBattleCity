#include "Enemy.h"


Enemy::Enemy()
{
	_objectType = ENEMY_OBJECT_TYPE;
	_level = 1;
	_startTime = GetTickCount();
	_currentDirection = DOWN;
	_isCollied = false;
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

	if (_listBullet.size() == 0)
	{
		_listBullet.push_back(new Bullet(_spriteHandler, _currentDirection,  bulletPosition, ALLY_ENEMY, _level, _map, _listNearByObject));

	}
	else if (GameTime::RenderFrame(_startTime, 1000))
	{
		_listBullet.push_back(new Bullet(_spriteHandler, _currentDirection,  bulletPosition, ALLY_ENEMY, _level, _map, _listNearByObject));


	}
}

Enemy::~Enemy()
{
}
