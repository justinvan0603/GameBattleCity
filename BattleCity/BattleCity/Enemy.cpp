#include "Enemy.h"


Enemy::Enemy()
{
	_startTime = GetTickCount();
	_currentDirection = DOWN;
	_isCollied = false;
}

MoveDirection Enemy::RandomDirection()
{
	srand(time(0));
	return static_cast<MoveDirection>(rand() % NUM_OF_DIRECTION);
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
	D3DXVECTOR2 bulletPosition = CalculateBulletPosition(_left, _top,_currentDirection);

	if (_listBullet.size() == 0)
		_listBullet.push_back(new Bullet(_spriteHandler, _currentDirection, bulletPosition.x, bulletPosition.y, ALLY_ENEMY));
	else if (GameTime::RenderFrame(_startTime,1000))
		_listBullet.push_back(new Bullet(_spriteHandler, _currentDirection, bulletPosition.x, bulletPosition.y,ALLY_ENEMY));
}

Enemy::~Enemy()
{
}
