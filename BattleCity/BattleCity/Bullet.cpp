#include "Bullet.h"
#include "EffectManager.h"
#include "CollisionManager.h"
#include "GameSound.h"
Bullet::Bullet(LPD3DXSPRITE spriteHandler, int ally)
{
	_allyObject = ally;
	_spriteHandler = spriteHandler;
	_listSprite = new Sprite*[NUM_OF_DIRECTION];
	_listSprite[UP] = new Sprite(_spriteHandler, BULLET_SPRITE_UP_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[LEFT] = new Sprite(_spriteHandler, BULLET_SPRITE_LEFT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[DOWN] = new Sprite(_spriteHandler, BULLET_SPRITE_DOWN_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_listSprite[RIGHT] = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_currentDirection = UP;
	_width = 8;
	_height = 8;
	_isTerminated = false;
}
Bullet::Bullet(LPD3DXSPRITE spriteHandler, MoveDirection direction, int posX, int posY, int ally,int level, int** map, vector<vector<StaticObject*>>* listNearByObject)
{
	_spriteHandler = spriteHandler;
	_allyObject = ally;
	_listSprite = new Sprite*;
	this->_left = posX;
	this->_top = posY;
	_width = BULLET_WIDTH;
	_height = BULLET_HEIGHT;
	_level = level;
	_isTerminated = false;
	_currentDirection = direction;
	_map = map;
	_listNearByObject = listNearByObject;
	this->_id = ID_BULLET;
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
Bullet::Bullet(LPD3DXSPRITE spriteHandler, MoveDirection direction,D3DXVECTOR2 position, int ally, int level , int ** map, vector<vector<StaticObject*>>* listNearbyObject)
{
	_spriteHandler = spriteHandler;
	_allyObject = ally;
	_listSprite = new Sprite*;
	this->_left = (int)position.x;
	this->_top = (int)position.y;
	_width = BULLET_WIDTH;
	_height = BULLET_HEIGHT;
	_level = level;
	_isTerminated = false;
	_currentDirection = direction;
	_map = map;
	_listNearByObject = listNearbyObject;
	this->_id = ID_BULLET;
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
	
	if (_isTerminated == false)
	{
		DynamicObject::Draw();
		if (_currentDirection == MoveDirection::UP)
		{

			(*_listSprite)->Render(_left, _top);
			return;
		}
		if (_currentDirection == MoveDirection::LEFT)
		{
			(*_listSprite)->Render(_left, _top);
			return;
		}
		if (_currentDirection == MoveDirection::DOWN)
		{
			(*_listSprite)->Render(_left, _top);
			return;
		}
		if (_currentDirection == MoveDirection::RIGHT)
		{
			(*_listSprite)->Render(_left, _top);
			return;
		}
	}
	
}
void Bullet::Move()
{
	
	if (_currentDirection == MoveDirection::UP)
	{
		this->_vx = SPEED_NO;
		
		if (_level == 1)
		{
			this->_vy = -DEFAULT_BULLET_SPEED_Y;
		}
		else
			this->_vy = -BULLET_PROMOTED_SPEED_Y;
		return;
	}
	if (_currentDirection == MoveDirection::DOWN)
	{
		this->_vx = SPEED_NO;
		if (_level == 1)
			this->_vy = DEFAULT_BULLET_SPEED_Y;
		else
			this->_vy = BULLET_PROMOTED_SPEED_Y;
		return;
	}
	if (_currentDirection == MoveDirection::LEFT)
	{
		this->_vy = SPEED_NO;
		if (_level == 1)
			this->_vx = -DEFAULT_BULLET_SPEED_X;
		else
			this->_vx = -BULLET_PROMOTED_SPEED_X;
		return;
	}
	if (_currentDirection == MoveDirection:: RIGHT)
	{
		this->_vy = SPEED_NO;
		if (_level == 1)
			this->_vx = DEFAULT_BULLET_SPEED_X;
		else
			this->_vx = BULLET_PROMOTED_SPEED_X;
		return;
	}
	
}
void Bullet::Update()
{
	FindNearbyObject();
	this->Move();
	
	D3DXVECTOR2 posInMap;
	bool flag = false;
	for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end();i++)
	{
		if (!(*i)->_isTerminated)
			flag = CollisionManager::CollisionBulletWithObject(this, *i);
		if (flag && (*i)->_isTerminated)
		{
			posInMap = Object::getPositionObjectInMap((*i)->getLeft(), (*i)->getTop());
			int value = _map[(int)posInMap.y][(int)posInMap.x];
			_map[(int)posInMap.y][(int)posInMap.x] = -1;
			if (value != -1)
			{
				delete _listNearByObject->at(value % 100).at(value / 100);
				_listNearByObject->at(value % 100).at(value / 100) = NULL;
			}
		}

	}

	bool isCollided=  CollisionManager::CollisionWithScreen(this);
	if (isCollided)
	{
		if (_allyObject == ALLY_PLAYER)
			GameSound::getInstance()->Play(ID_SOUND_STEEL_WALL_EXPLODE);
		D3DXVECTOR2 pos;
		pos.x = _left - BULLET_WIDTH;
		pos.y = _top - BULLET_HEIGHT;
		EffectManager::getInstance()->AddBulletEffect(pos);
	}
	DynamicObject::Update();
	
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
