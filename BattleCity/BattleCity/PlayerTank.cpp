#include "PlayerTank.h"


PlayerTank::PlayerTank(LPDIRECT3DDEVICE9 device)
{
	this->_currentDirection = MoveDirection::UP;
	this->_device = device;
	D3DXCreateSprite(_device, &this->_spriteHandler);
	this->_level = DEFAULT_PLAYER_LEVEL;
	this->_life = DEFAULT_PLAYER_LIFE;
	this->_immortalTime = DEFAULT_IMMORTAL_TIME;
	this->_positionX = DEFAULT_PLAYER_POSITION_X;
	this->_positionY = DEFAULT_PLAYER_POSITION_Y;
	this->_speedX = DEFAULT_PLAYER_SPEED_X;
	this->_speedY = DEFAULT_PLAYER_SPEED_Y;
	this->_hitPoint = DEFAULT_PLAYER_HP;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, PLAYER_SPRITE_UP_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, PLAYER_SPRITE_LEFT_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, PLAYER_SPRITE_DOWN_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, PLAYER_SPRITE_RIGHT_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
}

void PlayerTank::Draw()
{
	this->_listSprite[UP]->Render(NULL, _positionX, _positionY);
}
void PlayerTank::Move()
{

}
void PlayerTank::Shoot()
{
}
void PlayerTank::Update()
{

}
PlayerTank::~PlayerTank()
{

}
