#include "PlayerTank.h"
#include "CollisionManager.h"
#include "BulletManager.h"
#include "GameSound.h"

PlayerTank::PlayerTank(LPD3DXSPRITE spriteHandler)
{
	//this->_bulletDelay = new GameTime(BULLET_DELAY_FPS);
	_startTime = GetTickCount();
	_delayShield = PLAYER_SHIELD_TIME;
	this->_objectType = DYNAMIC_OBJECT;
	this->_id = ID_PLAYER;
	this->_currentDirection = MoveDirection::UP;
	this->_spriteHandler = spriteHandler;
	this->_level = LEVEL_FOUR;
	this->_life = DEFAULT_PLAYER_LIFE;
	//this->_immortalTime = DEFAULT_IMMORTAL_TIME;
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
	_isMoving = false;
	_playTankSoundMove = 1;
	_playTankSoundEngine = 1;

}

void PlayerTank::Draw()
{
	if (!_isTerminated)
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
}
void PlayerTank::Move()
{
	if (_isTerminated)
		return;
	if (!Keyboard::getInstance()->IsKeyDown(DIK_LEFT) && !Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
		_vx = 0;
	if (!Keyboard::getInstance()->IsKeyDown(DIK_UP) && !Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
		_vy = 0;
	if (Keyboard::getInstance()->IsKeyDown(DIK_UP))
	{
		_isMoving = true;
		this->_vy = -DEFAULT_PLAYER_SPEED_Y;
		_curSprite = _listSprite[UP];
		_currentDirection = UP;
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
	{
		_isMoving = true;
		this->_vy = PLAYER_SPEED_PROMOTED_Y;
		_curSprite = _listSprite[DOWN];
		_currentDirection = DOWN;
		return;
	}
	
	if (Keyboard::getInstance()->IsKeyDown(DIK_LEFT))
	{
		_isMoving = true;
		this->_vx = -PLAYER_SPEED_PROMOTED_X;
		_curSprite = _listSprite[LEFT];
		_currentDirection = LEFT;
		return;
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_RIGHT))
	{
		_isMoving = true;
		this->_vx = PLAYER_SPEED_PROMOTED_X;
		_curSprite = _listSprite[RIGHT];
		_currentDirection = RIGHT;
		return;
	}
	_isMoving = false;
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
			if (GameTime::RenderFrame(_startTime, 100))
			{
				BulletManager::getInstance()->AddBullet(_spriteHandler, _currentDirection, bulletPosition, ALLY_PLAYER, _level, _map, _listNearByObject);
				_startTime = GetTickCount();
				GameSound::getInstance()->Play(ID_SOUND_FIRE);
			}
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
	if (!_isTerminated)
	{
		if (_life < 0)
		{
			return;
		}

		FindNearbyObject();
		this->Move();

		if (_isMoving)
		{
			if (_playTankSoundMove == 1)
			{
				GameSound::getInstance()->Stop(ID_SOUND_TANK_ENGINE);
				GameSound::getInstance()->Play(ID_SOUND_TANK_MOVE, true);
				_playTankSoundMove++;
				_playTankSoundEngine = 1;
			}

		}
		else
		{
			if (_playTankSoundEngine == 1)
			{
				GameSound::getInstance()->Stop(ID_SOUND_TANK_MOVE);
				GameSound::getInstance()->Play(ID_SOUND_TANK_ENGINE, true);
				_playTankSoundEngine++;
				_playTankSoundMove = 1;
			}
		}
		this->Shoot();

		for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end(); i++)
		{
			if (CollisionManager::CollisionPreventMove(this, *i))
			{
				break;
			}
		}

		CollisionManager::CollisionWithScreen(this);
		DynamicObject::Update();
		this->_listSprite[_currentDirection]->NextColumn();
		this->_curSprite = this->_listSprite[_currentDirection];
	}
	//if (_isTerminated)
	//{
	//	if (_life > 0)
	//	{
	//		Respawn();
	//	}
	//	else
	//	{
	//		_life--;
	//		setPositionX(0);
	//		setPositionY(0);
	//	}
	//}

	
}

void PlayerTank::reset()
{
	this->_currentDirection = MoveDirection::UP;
	this->_level = LEVEL_ONE;
	this->_life = DEFAULT_PLAYER_LIFE;
	//this->_immortalTime = DEFAULT_IMMORTAL_TIME;
	this->_hitPoint = DEFAULT_PLAYER_HP;
	_curSprite = this->_listSprite[_currentDirection];
	this->_isImmortal = true;
	setPositionX(DEFAULT_PLAYER_POSITION_X);
	setPositionY(DEFAULT_PLAYER_POSITION_Y);
	_isMoving = false;
	_playTankSoundMove = 1;
	_playTankSoundEngine = 1;
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
void PlayerTank::Respawn(int posX, int posY)
{
	if (_isTerminated == true)
	{
		if (_life > 0)
		{
			_life--;
			setCurrentMoveDirection(MoveDirection::UP);
			setPositionX(posX);
			setPositionY(posY);
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
void PlayerTank::setLife(int life)
{
	_life = life;
}

int PlayerTank::getLife()
{
	return _life;
}

void PlayerTank::ActivateShield(bool isFromPowerUp)
{
	if(isFromPowerUp)
		this->_delayShield = PLAYER_SHIELD_TIME*3;
	else
		this->_delayShield = PLAYER_SHIELD_TIME;
	this->_isActiveShield = true;
	this->_isImmortal = true;
}

void PlayerTank::TurnOffSound()
{
	GameSound::getInstance()->Stop(ID_SOUND_TANK_ENGINE);
	GameSound::getInstance()->Stop(ID_SOUND_TANK_MOVE);
	_playTankSoundEngine = 1;
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
