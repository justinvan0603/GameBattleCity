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
	_curSprite = this->_listSprite[UP];
	
}

void PlayerTank::Draw()
{
	this->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	_curSprite->Render(_positionX, _positionY);

	this->_spriteHandler->End();

}
void PlayerTank::Move()
{
	if (Keyboard::getInstance()->IsKeyDown(DIK_UP))
	{
		this->_speedY = -DEFAULT_PLAYER_SPEED_Y;
		this->_positionY += this->_speedY;
		_curSprite = _listSprite[UP];
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		this->_speedY = DEFAULT_PLAYER_SPEED_Y;
		this->_positionY += this->_speedY;
		_curSprite = _listSprite[DOWN];
		return;
	}
	if (!Keyboard::getInstance()->IsKeyDown(DIK_UP) && !Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
		_speedY = 0;
	if (Keyboard::getInstance()->IsKeyDown(DIK_LEFT))
	{
		this->_speedX = -DEFAULT_PLAYER_SPEED_X;
		this->_positionX += this->_speedX;
		_curSprite = _listSprite[LEFT];
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		this->_speedX = DEFAULT_PLAYER_SPEED_X;
		this->_positionX += this->_speedX;
		_curSprite = _listSprite[RIGHT];
		return;
	}

	if (!Keyboard::getInstance()->IsKeyDown(DIK_LEFT) && !Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		_speedX = 0;
}
void PlayerTank::Shoot()
{
}
void PlayerTank::Update()
{
	this->Move();
}
PlayerTank::~PlayerTank()
{

}
