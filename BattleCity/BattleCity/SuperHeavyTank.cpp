#include "SuperHeavyTank.h"
#include "CollisionManager.h"

SuperHeavyTank::SuperHeavyTank(LPD3DXSPRITE spriteHandler)
{
	this->_id = ID_SUPER_HEAVY_TANK;
	this->_spriteHandler = spriteHandler;
	this->_currentDirection = RIGHT;
	this->_left = DEFAULT_TOP_LEFT.x;
	this->_top = DEFAULT_TOP_LEFT.y;
	this->_vx = 1;
	this->_vy = 1;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	_curSprite = _listSprite[RIGHT];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;
}
SuperHeavyTank::SuperHeavyTank(LPD3DXSPRITE spriteHandler, D3DXVECTOR2 position, bool isBonus)
{
	this->_id = ID_SUPER_HEAVY_TANK;
	this->_level = LEVEL_ONE;
	this->_hitPoint = 3;
	this->_spriteHandler = spriteHandler;
	this->_currentDirection = DOWN;
	this->_left = (int)position.x;
	this->_top = (int)position.y;
	this->_vx = (int)DYNAMIC_OBJECT_LOW_SPEED.x;
	this->_vy = (int)DYNAMIC_OBJECT_LOW_SPEED.y;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, 3, 3);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, 3, 3);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, 3,3);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, SUPER_HEAVY_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, 3, 3);
	_curSprite = _listSprite[_currentDirection];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;
	_isBonusTank = true;
	if (_isBonusTank)
	{
		for (int i = 0; i < NUM_OF_DIRECTION; i++)
		{
			this->_listSprite[i]->setStartFrame(_hitPoint - 2);
		}
	}
}
void SuperHeavyTank::Draw()
{
	if (!_isTerminated)
	{
		if (!_isFreeze)
			ShootableObject::Draw();
		if (!_isBonusTank || _hitPoint < 3)
			_curSprite->Render(_hitPoint - 1, _left, _top);
		else
			_curSprite->Render(_left, _top);

	}

}
void SuperHeavyTank::Update()
{
	if (_isFreeze)
		return;
	FindNearbyObject();
	this->Move();
	this->Shoot();
	for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end(); i++)
	{
		_isCollied = CollisionManager::CollisionPreventMove(this, *i);
		if (_isCollied)
			break;
	}
	if (CollisionManager::CollisionWithScreen(this))
	{
		this->_isCollied = true;
	}
	Enemy::MoveWithCollision();
	DynamicObject::Update();
	if (_isBonusTank &&  _hitPoint == 3)
	{
		_listSprite[_currentDirection]->Next(_hitPoint - 1);
	}

}
void SuperHeavyTank::Shoot()
{
	Enemy::Shoot();
}
void SuperHeavyTank::Move()
{
	if (_currentDirection != LEFT && _currentDirection != RIGHT)
		_vx = 0;
	if (_currentDirection != UP && _currentDirection != DOWN)
		_vy = 0;
	if (_currentDirection == UP)
	{
		this->_vy = -(int)DYNAMIC_OBJECT_LOW_SPEED.y;
		_curSprite = _listSprite[UP];
		return;
	}
	if (_currentDirection == DOWN)
	{
		this->_vy = (int)DYNAMIC_OBJECT_LOW_SPEED.y;
		_curSprite = _listSprite[DOWN];
		return;
	}

	if (_currentDirection == LEFT)
	{
		this->_vx = -(int)DYNAMIC_OBJECT_LOW_SPEED.x;
		_curSprite = _listSprite[LEFT];
		return;
	}
	if (_currentDirection == RIGHT)
	{
		this->_vx = (int)DYNAMIC_OBJECT_LOW_SPEED.x;
		_curSprite = _listSprite[RIGHT];
		return;
	}
}
int SuperHeavyTank::getHitPoint()
{
	return _hitPoint;
}
void SuperHeavyTank::lostHitPoint()
{
	_hitPoint--;
}
SuperHeavyTank::~SuperHeavyTank()
{
}
