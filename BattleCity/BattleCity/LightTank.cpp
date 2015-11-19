#include "LightTank.h"
#include "CollisionManager.h"

LightTank::LightTank(LPD3DXSPRITE spriteHandler)
{
	this->_id = ID_LIGHT_TANK;
	this->_spriteHandler = spriteHandler;
	//this->_currentDirection = DOWN;
	this->_left = 90; //DEFAULT_TOP_LEFT.x;
	this->_top = 50;// DEFAULT_TOP_LEFT.y;
	this->_vx = LIGHT_TANK_SPEED_X;
	this->_vy = LIGHT_TANK_SPEED_Y;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	_curSprite = _listSprite[DOWN];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;
}
void LightTank:: Draw()
{
	if (!_isTerminated)
	{
		_curSprite->Render(_left, _top);
		ShootableObject::DrawBullet();
		ShootableObject::Draw();
		
	}
	
}
void LightTank::Move()
{

	if (_currentDirection == UP)
	{
		this->_vy = -DEFAULT_PLAYER_SPEED_Y;
		_curSprite = _listSprite[UP];
		return;
	}
	if (_currentDirection == DOWN)
	{
		this->_vy = DEFAULT_PLAYER_SPEED_Y;
		_curSprite = _listSprite[DOWN];	
		return;
	}

	if (_currentDirection == LEFT)
	{
		this->_vx = -DEFAULT_PLAYER_SPEED_X;
		_curSprite = _listSprite[LEFT];
		return;
	}
	if (_currentDirection == RIGHT)
	{
		this->_vx = DEFAULT_PLAYER_SPEED_X;
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
	
	Enemy::MoveWithCollision();
	this->Move();
	//this->Shoot();
	for (vector<Bullet*> ::iterator i = _listBullet.begin(); i != _listBullet.end(); i++)
	{

		(*i)->Update();
	}
	//if (CollisionManager::CollisionWithScreen(this))
	//{
	//	this->_vx = SPEED_NO;
	//	this->_vy = SPEED_NO;
	//	return;
	//}
}

LightTank::~LightTank()
{
}
