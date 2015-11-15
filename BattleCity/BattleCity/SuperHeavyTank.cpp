#include "SuperHeavyTank.h"


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
	//_bullet = new Bullet(_spriteHandler, ALLY_ENEMY);
	isShooting = false;
	this->_isTerminated = false;
}

void SuperHeavyTank::Draw(){}
void SuperHeavyTank::Update(){}
void SuperHeavyTank::Shoot(){}
void SuperHeavyTank::Move(){}
SuperHeavyTank::~SuperHeavyTank()
{
}
