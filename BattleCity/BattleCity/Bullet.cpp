#include "Bullet.h"


Bullet::Bullet(LPD3DXSPRITE spriteHandler)
{
	
	_spriteHandler = spriteHandler;
	_speedX = BULLET_SPEED_X;
	_speedY = BULLET_SPEED_Y;
	//_positionX = _positionY = 200;
	_listSprite = new Sprite*[NUM_OF_DIRECTION];
	_listSprite[UP] = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[LEFT] = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[DOWN] = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[RIGHT] = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_currentDirection = DOWN;

}
Bullet::Bullet(LPD3DXSPRITE spriteHandler, MoveDirection direction, int posX, int posY)
{
	_spriteHandler = spriteHandler;
	_listSprite = new Sprite*;
	this->_positionX = posX;
	this->_positionY = posY;
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
	//_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	if (_currentDirection == MoveDirection::UP)
	{
		_listSprite[UP]->Render(_positionX +12, _positionY-59);
		return;
	}
	if (_currentDirection == MoveDirection::LEFT)
	{
		_listSprite[LEFT]->Render(_positionX, _positionY + 10);
		return;
	}
	if (_currentDirection == MoveDirection::DOWN)
	{
		_listSprite[DOWN]->Render(_positionX +10, _positionY +6);
		return;
	}
	if (_currentDirection == MoveDirection::RIGHT)
	{
		_listSprite[RIGHT]->Render(_positionX +12, _positionY+11);
		return;
	}

	switch (_currentDirection)
	{
	case UP:
		
		break;
	case LEFT:
		break;
	case DOWN:
		break;
	case RIGHT:
		break;
	default:
		break;
	}
	
	//_spriteHandler->End();
}
void Bullet::Move()
{
	
	if (_currentDirection == MoveDirection::UP)
	{
		this->_speedX = SPEED_NO;
		this->_speedY = -BULLET_SPEED_Y;
		this->_positionY += this->_speedY;
		return;
	}
	if (_currentDirection == MoveDirection::DOWN)
	{
		this->_speedX = SPEED_NO;
		this->_speedY = BULLET_SPEED_Y;
		this->_positionY += this->_speedY;
		return;
	}
	if (_currentDirection == MoveDirection::LEFT)
	{
		this->_speedY = SPEED_NO;
		this->_speedX = -BULLET_SPEED_X;
		this->_positionX += this->_speedX;
		return;
	}
	if (_currentDirection == MoveDirection:: RIGHT)
	{
		this->_speedY = SPEED_NO;
		this->_speedX = BULLET_SPEED_X;
		this->_positionX += this->_speedX;
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
