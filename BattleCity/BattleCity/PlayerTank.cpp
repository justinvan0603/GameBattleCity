#include "PlayerTank.h"
#include "CollisionManager.h"

PlayerTank::PlayerTank(LPD3DXSPRITE spriteHandler)
{
	//this->_bulletDelay = new GameTime(BULLET_DELAY_FPS);
	_startTime = GetTickCount();
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
	isShooting = false;
}

void PlayerTank::Draw()
{
	
	if (_isTerminated == false)
	{
		int size = _listBullet.size();
		
		_curSprite->Render(_left, _top);
		
		ShootableObject::Draw();
		ShootableObject::DrawBullet();
	}

	
	

	
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
		_curSprite = _listSprite[UP];
		_currentDirection = UP;
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		this->_vy = DEFAULT_PLAYER_SPEED_Y;
		_curSprite = _listSprite[DOWN];
		_currentDirection = DOWN;
		return;
	}
	
	if (Keyboard::getInstance()->IsKeyDown(DIK_LEFT))
	{
		this->_vx = -DEFAULT_PLAYER_SPEED_X;

		_curSprite = _listSprite[LEFT];
		_currentDirection = LEFT;
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		this->_vx = DEFAULT_PLAYER_SPEED_X;

		_curSprite = _listSprite[RIGHT];
		_currentDirection = RIGHT;
		return;
	}
	

	
}
void PlayerTank::Shoot()
{
	
	if (Keyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		D3DXVECTOR2 bulletPosition = CalculateBulletPosition(_left, _top,_currentDirection);
		if (_listBullet.size() == 0)
		{

			_listBullet.push_back(new Bullet(_spriteHandler, _currentDirection, bulletPosition.x, bulletPosition.y, ALLY_PLAYER));
			_startTime = GetTickCount();
		}
		else if (GameTime::RenderFrame(_startTime,2000))
		{
			_listBullet.push_back(new Bullet(_spriteHandler, _currentDirection, bulletPosition.x, bulletPosition.y, ALLY_PLAYER));

			isShooting = true;
			return;
		}
		
		isShooting = true;
	}
}
void PlayerTank::Update()
{

	//FindNearbyObject();
	this->Move();
	this->Shoot();
	//this->_bullet->Update();
	
	for (vector<Bullet*> ::iterator i = _listBullet.begin(); i != _listBullet.end(); i++)
	{


		(*i)->Update();
	}
	if (CollisionManager::CollisionWithScreen(this))
	{
		this->_vx = SPEED_NO;
		this->_vy = SPEED_NO;
		return;
	}
	DynamicObject::Update();
}




PlayerTank::~PlayerTank()
{

}
