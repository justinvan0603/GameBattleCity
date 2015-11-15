#include "PlayerTank.h"


PlayerTank::PlayerTank(LPD3DXSPRITE spriteHandler)
{
	this->_id = ID_PLAYER;
	this->_currentDirection = MoveDirection::UP;
	this->_spriteHandler = spriteHandler;
	this->_level = DEFAULT_PLAYER_LEVEL;
	this->_life = DEFAULT_PLAYER_LIFE;
	this->_immortalTime = DEFAULT_IMMORTAL_TIME;
	this->_left = DEFAULT_PLAYER_POSITION_X;
	this->_top = DEFAULT_PLAYER_POSITION_Y;
	this->_vx = DEFAULT_PLAYER_SPEED_X;
	this->_vy = DEFAULT_PLAYER_SPEED_Y;
	this->_hitPoint = DEFAULT_PLAYER_HP;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, PLAYER_SPRITE_UP_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, PLAYER_SPRITE_LEFT_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, PLAYER_SPRITE_DOWN_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, PLAYER_SPRITE_RIGHT_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE, SPRITE_PER_ROW);
	_curSprite = this->_listSprite[UP];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	this->_currentDirection = UP;
	_bullet = new Bullet(_spriteHandler,ALLY_PLAYER);
	isShooting = false;
}

void PlayerTank::Draw()
{
	
	if (isShooting && _isTerminated == false)
	{
		this->_bullet->Draw();
		
	}
	
	_curSprite->Render(_left, _top);


	ShootableObject::Draw();
}
void PlayerTank::Move()
{
	if (!Keyboard::getInstance()->IsKeyDown(DIK_LEFT) && !Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		_vx = 0;
	if (!Keyboard::getInstance()->IsKeyDown(DIK_UP) && !Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
		_vy = 0;
	if (Keyboard::getInstance()->IsKeyDown(DIK_UP))
	{
		this->_vy = -DEFAULT_PLAYER_SPEED_Y;
		//_top += _vy;
		_curSprite = _listSprite[UP];
		_currentDirection = UP;
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		this->_vy = DEFAULT_PLAYER_SPEED_Y;
		//_top += _vy;
		_curSprite = _listSprite[DOWN];
		_currentDirection = DOWN;
		return;
	}
	
	if (Keyboard::getInstance()->IsKeyDown(DIK_LEFT))
	{
		this->_vx = -DEFAULT_PLAYER_SPEED_X;
		//_left += _vx;
		_curSprite = _listSprite[LEFT];
		_currentDirection = LEFT;
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		this->_vx = DEFAULT_PLAYER_SPEED_X;
		//_left += _vx;
		_curSprite = _listSprite[RIGHT];
		_currentDirection = RIGHT;
		return;
	}


}
void PlayerTank::Shoot()
{
	if (Keyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		_bullet->setFireDirection(_currentDirection);
		_bullet->setPositionX(_left);
		_bullet->setPositionY(_top);
		_bullet->Move();
		isShooting = true;
		return;
	}
}
void PlayerTank::Update()
{
	
	this->Move();
	this->Shoot();
	this->_bullet->Update();
}


Bullet* PlayerTank::getBullet()
{
	return this->_bullet;
}

PlayerTank::~PlayerTank()
{

}
