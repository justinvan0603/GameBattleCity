#include "BonusTank.h"
#include "CollisionManager.h"

BonusTank::BonusTank(LPD3DXSPRITE spriteHandler, D3DXVECTOR2 position)
{
	this->_id = ID_BONUS_TANK;
	this->_level = 1;
	_spriteHandler = spriteHandler;
	_lastTime = 0;
	_left = (int)position.x;
	_top = (int)position.y;
	_vx = BONUS_TANK_BULLET_SPEED_X;
	_vy = BONUS_TANK_BULLET_SPEED_Y; 
	this->_listSprite = new Sprite*[NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, BONUS_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, BONUS_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, 2, 2);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, BONUS_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, 2, 2);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, BONUS_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT,2, 2);
	this->_currentDirection = DOWN;
	this->_curSprite = this->_listSprite[_currentDirection];
}

void BonusTank::Draw()
{
	if (!_isTerminated)
	{
		_curSprite->Render(_left, _top);
		ShootableObject::DrawBullet();
		ShootableObject::Draw();

	}
}

void BonusTank::Move()
{
	if (_currentDirection == UP)
	{
		this->_vy = -BONUS_TANK_BULLET_SPEED_Y;
		_curSprite = _listSprite[UP];
		return;
	}
	if (_currentDirection == DOWN)
	{
		this->_vy = BONUS_TANK_BULLET_SPEED_Y;
		_curSprite = _listSprite[DOWN];
		return;
	}

	if (_currentDirection == LEFT)
	{
		this->_vx = -BONUS_TANK_BULLET_SPEED_X;
		_curSprite = _listSprite[LEFT];
		return;
	}
	if (_currentDirection == RIGHT)
	{
		this->_vx = BONUS_TANK_BULLET_SPEED_X;
		_curSprite = _listSprite[RIGHT];
		return;
	}
}
void BonusTank::Shoot()
{
	Enemy::Shoot();
}
void BonusTank::Update()
{
	FindNearbyObject();
	this->Move();
	//this->Shoot();
	for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end(); i++)
	{
		CollisionManager::CollisionPreventMove(this, *i);
	}
	for (vector<Bullet*> ::iterator i = _listBullet.begin(); i != _listBullet.end(); i++)
	{

		(*i)->Update();
	}
	if (CollisionManager::CollisionWithScreen(this))
	{
		_isCollied = true;
	}
	Enemy::MoveWithCollision();
	DynamicObject::Update();
	DWORD now = GetTickCount();
	if (now - _lastTime > 1000 / 2)
	{
		_lastTime = now;
		if (_currentDirection == MoveDirection::UP)
		{
			_listSprite[UP]->Next();
			return;
		}
		if (_currentDirection == MoveDirection::LEFT)
		{
			_listSprite[LEFT]->Next();
			return;
		}
		if (_currentDirection == MoveDirection::DOWN)
		{
			_listSprite[DOWN]->Next();
			return;
		}
		if (_currentDirection == MoveDirection::RIGHT)
		{
			_listSprite[RIGHT]->Next();
			return;
		}
	}
}
BonusTank::~BonusTank()
{
}
