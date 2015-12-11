#include "PlayerTank.h"
#include "CollisionManager.h"
#include "BulletManager.h"
#include "GameSound.h"
#define PLAYER_SHIELD_TIME 4000
PlayerTank::PlayerTank(LPD3DXSPRITE spriteHandler)
{
	//this->_bulletDelay = new GameTime(BULLET_DELAY_FPS);
	_startTime = GetTickCount();
	_delayShield = 5000;
	this->_objectType = DYNAMIC_OBJECT;
	this->_id = ID_PLAYER;
	this->_currentDirection = MoveDirection::UP;
	this->_spriteHandler = spriteHandler;
	this->_level = LEVEL_ONE;
	this->_life = DEFAULT_PLAYER_LIFE;
	this->_immortalTime = DEFAULT_IMMORTAL_TIME;
	this->_left = DEFAULT_PLAYER_POSITION_X;
	this->_top = DEFAULT_PLAYER_POSITION_Y;
	this->_vx = DEFAULT_PLAYER_SPEED_X;
	this->_vy = DEFAULT_PLAYER_SPEED_Y;
	this->_hitPoint = DEFAULT_PLAYER_HP;
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, PLAYER_SPRITE_UP_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, PLAYER_NUMB_OF_SPRITE, PLAYER_SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, PLAYER_SPRITE_LEFT_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, PLAYER_NUMB_OF_SPRITE, PLAYER_SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, PLAYER_SPRITE_DOWN_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, PLAYER_NUMB_OF_SPRITE, PLAYER_SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, PLAYER_SPRITE_RIGHT_PATH, SPRITE_WIDTH, SPRITE_HEIGHT, PLAYER_NUMB_OF_SPRITE, PLAYER_SPRITE_PER_ROW);
	this->_shieldEffect = new Effect(_spriteHandler, EFFECT_SHIELD, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE_SHIELD, NUMB_OF_SPRITE_SHIELD);
	_curSprite = this->_listSprite[_currentDirection];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	this->_isImmortal = true;

}

void PlayerTank::Draw()
{

	if (GameTime::DelayTime(_delayShield))
	{
		this->_isImmortal = false;
		this->_isActiveShield = false;
	}
	else
	{
		this->_shieldEffect->Next();
	}
	if (_isImmortal == true)
	{
		this->_shieldEffect->Render(_left, _top);
	}
	if (_isTerminated == false)
	{
		//_curSprite->Render(_left, _top);

		////Sau khi cat sprite theo level su dung ham nay de ve player theo level an duoc//
				_curSprite->Render(_level - 1, _left, _top);//
		ShootableObject::Draw();
	}
	
}
void PlayerTank::Move()
{
	GameSound::getInstance()->Stop(ID_SOUND_TANK_MOVE);
	GameSound::getInstance()->Play(ID_SOUND_TANK_ENGINE);
	if (!Keyboard::getInstance()->IsKeyDown(DIK_LEFT) && !Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		_vx = 0;
	if (!Keyboard::getInstance()->IsKeyDown(DIK_UP) && !Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
		_vy = 0;
	if (Keyboard::getInstance()->IsKeyDown(DIK_UP))
	{
		
		this->_vy = -DEFAULT_PLAYER_SPEED_Y;
		_curSprite = _listSprite[UP];
		_currentDirection = UP;
		GameSound::getInstance()->Stop(ID_SOUND_TANK_ENGINE);
		GameSound::getInstance()->Play(ID_SOUND_TANK_MOVE);
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{

		this->_vy = PLAYER_SPEED_PROMOTED_Y;
		_curSprite = _listSprite[DOWN];
		_currentDirection = DOWN;
		GameSound::getInstance()->Stop(ID_SOUND_TANK_ENGINE);
		GameSound::getInstance()->Play(ID_SOUND_TANK_MOVE);
		return;
	}
	
	if (Keyboard::getInstance()->IsKeyDown(DIK_LEFT))
	{

		this->_vx = -PLAYER_SPEED_PROMOTED_X;
		_curSprite = _listSprite[LEFT];
		_currentDirection = LEFT;
		GameSound::getInstance()->Stop(ID_SOUND_TANK_ENGINE);
		GameSound::getInstance()->Play(ID_SOUND_TANK_MOVE);
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
	{

		this->_vx = PLAYER_SPEED_PROMOTED_X;
		_curSprite = _listSprite[RIGHT];
		_currentDirection = RIGHT;
		GameSound::getInstance()->Stop(ID_SOUND_TANK_ENGINE);
		GameSound::getInstance()->Play(ID_SOUND_TANK_MOVE);
		return;
	}
}
void PlayerTank::Shoot()
{
	
	if (Keyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		
		int _delayTime;
		if (_level < LEVEL_THREE)
			_delayTime = PLAYER_DEFAULT_BULLET_RELOAD_TIME;
		else
			_delayTime = PLAYER_PROMOTED_BULLET_RELOAD_TIME;
		D3DXVECTOR2 bulletPosition = CalculateBulletPosition(_left, _top,_currentDirection);
		if (BulletManager::getInstance()->getPlayerBulletSize() == 0)
		{
			BulletManager::getInstance()->AddBullet(_spriteHandler, _currentDirection, bulletPosition, ALLY_PLAYER, _level, _map, _listNearByObject);
			_startTime = GetTickCount();
			GameSound::getInstance()->Play(ID_SOUND_FIRE);
		}
		if (_level >= 3)
		{
			if (GameTime::RenderFrame(_startTime, _delayTime) && BulletManager::getInstance()->getPlayerBulletSize() < 2)
			{
				BulletManager::getInstance()->AddBullet(_spriteHandler, _currentDirection, bulletPosition, ALLY_PLAYER, _level, _map, _listNearByObject);
				isShooting = true;
				GameSound::getInstance()->Play(ID_SOUND_FIRE);
				return;
			}
		}
		else if (GameTime::RenderFrame(_startTime, _delayTime))
		{
			BulletManager::getInstance()->AddBullet(_spriteHandler, _currentDirection, bulletPosition, ALLY_PLAYER, _level, _map, _listNearByObject);
			isShooting = true;
			GameSound::getInstance()->Play(ID_SOUND_FIRE);
			return;
		}
		

	}
}
void PlayerTank::Update()
{
	if(_life < 0)
	{
		return;
	}
	
	FindNearbyObject();
	this->Move();
	this->Shoot();
	
	for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end(); i++)
	{
		if (CollisionManager::CollisionPreventMove(this, *i))
		{
			break;
		}	
	}

	CollisionManager::CollisionWithScreen(this);
	if (_isTerminated)
	{
		if (_life > 0)
		{
			Respawn();
		}
		else
		{
			_life--;
			setPositionX(0);
			setPositionY(0);
		}
	}
	DynamicObject::Update();
	this->_listSprite[_currentDirection]->NextColumn();
	this->_curSprite = this->_listSprite[_currentDirection];
	
}

void PlayerTank::reset()
{
	this->_currentDirection = MoveDirection::UP;
	this->_level = LEVEL_ONE;
	this->_life = DEFAULT_PLAYER_LIFE;
	this->_immortalTime = DEFAULT_IMMORTAL_TIME;
	this->_hitPoint = DEFAULT_PLAYER_HP;
	_curSprite = this->_listSprite[_currentDirection];
	this->_isImmortal = true;
	setPositionX(DEFAULT_PLAYER_POSITION_X);
	setPositionY(DEFAULT_PLAYER_POSITION_Y);
}

void PlayerTank::Respawn()
{
	if (_isTerminated == true)
	{
		if (_life > 0)
		{
			_life--;
			setCurrentMoveDirection(MoveDirection::UP);
			setPositionX(DEFAULT_PLAYER_POSITION_X);
			setPositionY(DEFAULT_PLAYER_POSITION_Y);
			_level = LEVEL_ONE;
			_isTerminated = false;
			ActivateShield();
		}
	}
}
void PlayerTank::PlayerPromoted()
{
	if (_level < LEVEL_FOUR)
	{
		_level++;
	}
}

int PlayerTank::getLife()
{
	return _life;
}

void PlayerTank::ActivateShield()
{
	this->_delayShield = 5000;
	this->_isActiveShield = true;
	this->_isImmortal = true;
}

void PlayerTank::addLife()
{
	_life++;
}
void PlayerTank::SetDirection(MoveDirection direction)
{
	_currentDirection = direction;
	_curSprite = _listSprite[_currentDirection];
}
PlayerTank::~PlayerTank()
{

}
