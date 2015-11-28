#include "LightTank.h"
#include "CollisionManager.h"

LightTank::LightTank(LPD3DXSPRITE spriteHandler)
{
	this->_id = ID_LIGHT_TANK;
	this->_spriteHandler = spriteHandler;
	this->_currentDirection = RIGHT;
	this->_left = 100; //DEFAULT_TOP_LEFT.x;
	this->_top = 51;// DEFAULT_TOP_LEFT.y;
	this->_vx = 4;//(int)DYNAMIC_OBJECT_LOW_SPEED.x; //LIGHT_TANK_SPEED_X;
	this->_vy = 4;//(int)DYNAMIC_OBJECT_LOW_SPEED.y; //LIGHT_TANK_SPEED_Y;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	_curSprite = _listSprite[_currentDirection];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;

}

LightTank::LightTank(LPD3DXSPRITE spriteHandler, D3DXVECTOR2 position)
{
	this->_id = ID_LIGHT_TANK;
	this->_level = 1;
	this->_spriteHandler = spriteHandler;
	this->_currentDirection = RIGHT;
	this->_left = (int)position.x; //DEFAULT_TOP_LEFT.x;
	this->_top = (int)position.y;// DEFAULT_TOP_LEFT.y;
	this->_vx = 4;//(int)DYNAMIC_OBJECT_LOW_SPEED.x; //LIGHT_TANK_SPEED_X;
	this->_vy = 4;//(int)DYNAMIC_OBJECT_LOW_SPEED.y; //LIGHT_TANK_SPEED_Y;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	_curSprite = _listSprite[_currentDirection];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;
}
void LightTank:: Draw()
{
	if (!_isTerminated)
	{
		ShootableObject::Draw();
		_curSprite->Render(_left, _top);	
		
	}
	ShootableObject::DrawBullet();
}
void LightTank::Move()
{
	if (_currentDirection != LEFT && _currentDirection != RIGHT)
		_vx = 0;
	if (_currentDirection != UP && _currentDirection != DOWN)
		_vy = 0;
	if (_currentDirection == UP)
	{
		this->_vy = -4;// (int)DYNAMIC_OBJECT_HIGH_SPEED.y;
		_curSprite = _listSprite[UP];
		return;
	}
	if (_currentDirection == DOWN)
	{
		this->_vy = 4;// (int)DYNAMIC_OBJECT_HIGH_SPEED.y;
		_curSprite = _listSprite[DOWN];	
		return;
	}

	if (_currentDirection == LEFT)
	{
		this->_vx = -4;// (int)DYNAMIC_OBJECT_HIGH_SPEED.x;
		_curSprite = _listSprite[LEFT];
		return;
	}
	if (_currentDirection == RIGHT)
	{
		this->_vx = 4;// (int)DYNAMIC_OBJECT_HIGH_SPEED.x;
		_curSprite = _listSprite[RIGHT];
		return;
	}
}
void LightTank::Shoot()
{
	Enemy::Shoot();
}
void LightTank::Update()
{
	
	FindNearbyObject();
	this->Move();
	//this->Shoot();
	for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end(); i++)
	{
		_isCollied = CollisionManager::CollisionPreventMove(this, *i);
		if (_isCollied)
			break;
	}
	//for (vector<Bullet*> ::iterator i = _listBullet.begin(); i != _listBullet.end(); i++)
	//{

	//	(*i)->Update();
	//}
	if (CollisionManager::CollisionWithScreen(this))
	{
		this->_isCollied = true;
	}
	Enemy::MoveWithCollision();
	DynamicObject::Update();
}

LightTank::~LightTank()
{
}
