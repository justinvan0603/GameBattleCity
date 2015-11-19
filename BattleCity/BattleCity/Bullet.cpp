#include "Bullet.h"


Bullet::Bullet(LPD3DXSPRITE spriteHandler, int ally)
{
	_allyObject = ally;
	_spriteHandler = spriteHandler;
	_vx = BULLET_SPEED_X;
	_vy = BULLET_SPEED_Y;
	_listSprite = new Sprite*[NUM_OF_DIRECTION];
	_listSprite[UP] = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[LEFT] = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[DOWN] = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[RIGHT] = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_currentDirection = UP;
	_width = 7;
	_height = 11;
	_isTerminated = false;
}
Bullet::Bullet(LPD3DXSPRITE spriteHandler, MoveDirection direction, int posX, int posY, int ally)
{
	_spriteHandler = spriteHandler;
	_allyObject = ally;
	_listSprite = new Sprite*;
	this->_left = posX;
	this->_top = posY;
	_width = 6;
	_height = 10;
	_vx = BULLET_SPEED_X;
	_vy = BULLET_SPEED_Y;
	_isTerminated = false;
	_currentDirection = direction;
	switch (direction)
	{
		case UP:
		{
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			_currentDirection = direction;
			break;
		}
		case LEFT:
		{
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			_currentDirection = direction;
			break;
		}
		case DOWN:
		{
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			_currentDirection = direction;
			break;
		}
		case RIGHT:
		{
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			_currentDirection = direction;
			break;
		}
		default:
			break;
	}
}

void Bullet::Draw()
{
	DynamicObject::Draw();
	if (!_isTerminated)
	{
		if (_currentDirection == MoveDirection::UP)
		{
			
			(*_listSprite)->Render(_left + SPRITE_WIDTH / 2 - BULLET_WIDTH / 2, _top);
			return;
		}
		if (_currentDirection == MoveDirection::LEFT)
		{
			(*_listSprite)->Render(_left, _top + SPRITE_HEIGHT / 2 - BULLET_HEIGHT / 2);
			return;
		}
		if (_currentDirection == MoveDirection::DOWN)
		{
			(*_listSprite)->Render(_left + SPRITE_WIDTH / 2 - BULLET_WIDTH / 2, _top + SPRITE_HEIGHT);
			return;
		}
		if (_currentDirection == MoveDirection::RIGHT)
		{
			(*_listSprite)->Render(_left + SPRITE_WIDTH, _top + SPRITE_HEIGHT / 2 - BULLET_HEIGHT / 2);
			return;
		}
	}
	


}
void Bullet::Move()
{
	
	if (_currentDirection == MoveDirection::UP)
	{
		this->_vx = SPEED_NO;
		this->_vy = -BULLET_SPEED_Y;
		return;
	}
	if (_currentDirection == MoveDirection::DOWN)
	{
		this->_vx = SPEED_NO;
		this->_vy = BULLET_SPEED_Y;
		return;
	}
	if (_currentDirection == MoveDirection::LEFT)
	{
		this->_vy = SPEED_NO;
		this->_vx = -BULLET_SPEED_X;
		return;
	}
	if (_currentDirection == MoveDirection:: RIGHT)
	{
		this->_vy = SPEED_NO;
		this->_vx = BULLET_SPEED_X;
		return;
	}
	
}
void Bullet::Update()
{
	this->Move();
}
int Bullet::getAllyObject()
{
	return _allyObject;
}
void Bullet::setFireDirection(MoveDirection direction)
{
	this->_currentDirection = direction;
}
void Bullet::setAllyObject(int ally)
{
	this->_allyObject = ally;
}
Bullet::~Bullet()
{
}
