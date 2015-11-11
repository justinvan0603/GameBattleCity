#include "Bullet.h"


Bullet::Bullet(LPD3DXSPRITE spriteHandler)
{
	
	_spriteHandler = spriteHandler;
	_vx = BULLET_SPEED_X;
	_vy = BULLET_SPEED_Y;
	_listSprite = new Sprite*[NUM_OF_DIRECTION];
	_listSprite[UP] = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[LEFT] = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[DOWN] = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[RIGHT] = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_currentDirection = UP;
	_width = 6;
	_height = 10;
}
Bullet::Bullet(LPD3DXSPRITE spriteHandler, MoveDirection direction, int posX, int posY)
{
	_spriteHandler = spriteHandler;
	_listSprite = new Sprite*;
	this->_left = posX;
	this->_top = posY;
	_currentDirection = direction;
	switch (direction)
	{
		case UP:
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			break;
		case LEFT:
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			break;
		case DOWN:
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			break;
		case RIGHT:
			*_listSprite = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
			break;
		default:
			break;
	}
}

void Bullet::Draw()
{
	DynamicObject::Draw();

	if (_currentDirection == MoveDirection::UP)
	{
		_listSprite[UP]->Render(_left +12, _top);
		return;
	}
	if (_currentDirection == MoveDirection::LEFT)
	{
		_listSprite[LEFT]->Render(_left, _top + 8);
		return;
	}
	if (_currentDirection == MoveDirection::DOWN)
	{
		_listSprite[DOWN]->Render(_left +10, _top +6);
		return;
	}
	if (_currentDirection == MoveDirection::RIGHT)
	{
		_listSprite[RIGHT]->Render(_left +12, _top+11);
		return;
	}

	//switch (_currentDirection)
	//{
	//case UP:
	//	
	//	break;
	//case LEFT:
	//	break;
	//case DOWN:
	//	break;
	//case RIGHT:
	//	break;
	//default:
	//	break;
	//}
	
	//_spriteHandler->End();
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

void Bullet::setFireDirection(MoveDirection direction)
{
	this->_currentDirection = direction;
}
Bullet::~Bullet()
{
}
