#include "Bullet.h"


Bullet::Bullet(LPDIRECT3DDEVICE9 device)
{
	_device = device;
	D3DXCreateSprite(_device, &_spriteHandler);
	_speedX = BULLET_SPEED_X;
	_speedY = BULLET_SPEED_Y;
	_positionX = _positionY = 200;
	_listSprite = new Sprite*[NUM_OF_DIRECTION];
	_listSprite[UP] = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[LEFT] = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[DOWN] = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[RIGHT] = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_currentDirection = UP;
	
}

void Bullet::Draw()
{
	if (_currentDirection == MoveDirection::UP)
	{
		_listSprite[UP]->Render(_positionX +5, _positionY);
		return;
	}
	if (_currentDirection == MoveDirection::LEFT)
	{
		_listSprite[LEFT]->Render(_positionX, _positionY + 6);
		return;
	}
	if (_currentDirection == MoveDirection::DOWN)
	{
		_listSprite[DOWN]->Render(_positionX +5, _positionY +6);
		return;
	}
	if (_currentDirection == MoveDirection::RIGHT)
	{
		_listSprite[RIGHT]->Render(_positionX +5, _positionY+6);
		return;
	}
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
	this->Draw();
	this->Move();
}

void Bullet::setFireDirection(MoveDirection direction)
{
	this->_currentDirection = direction;
}
Bullet::~Bullet()
{
}
