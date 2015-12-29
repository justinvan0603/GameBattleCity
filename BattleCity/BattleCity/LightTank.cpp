#include "LightTank.h"
#include "CollisionManager.h"

LightTank::LightTank(LPD3DXSPRITE spriteHandler)
{
	this->_id = ID_LIGHT_TANK;
	this->_spriteHandler = spriteHandler;
	this->_currentDirection = RIGHT;
	this->_left = 100; //DEFAULT_TOP_LEFT.x;
	this->_top = 51;// DEFAULT_TOP_LEFT.y;
	this->_vx = (int)DYNAMIC_OBJECT_HIGH_SPEED.x; 
	this->_vy = (int)DYNAMIC_OBJECT_HIGH_SPEED.y; 
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	_curSprite = _listSprite[_currentDirection];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;

}

LightTank::LightTank(LPD3DXSPRITE spriteHandler, D3DXVECTOR2 position, bool isBonus)
{
	this->_id = ID_LIGHT_TANK;
	this->_level = LEVEL_ONE;
	this->_spriteHandler = spriteHandler;
	this->_currentDirection = DOWN;
	this->_left = (int)position.x; //DEFAULT_TOP_LEFT.x;
	this->_top = (int)position.y;// DEFAULT_TOP_LEFT.y;
	this->_vx = (int)DYNAMIC_OBJECT_HIGH_SPEED.x;
	this->_vy = (int)DYNAMIC_OBJECT_HIGH_SPEED.y; 
	this->_listSprite = new Sprite*[MoveDirection::NUM_OF_DIRECTION];
	this->_listSprite[UP] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_UP, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	this->_listSprite[LEFT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_LEFT, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	this->_listSprite[DOWN] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_DOWN, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	this->_listSprite[RIGHT] = new Sprite(_spriteHandler, LIGHT_TANK_RESOURCE_RIGHT, SPRITE_WIDTH, SPRITE_HEIGHT, ENEMY_NORMAL_NUMB_OF_SPRITE, ENEMY_NORMAL_SPRITE_PER_ROW);
	_curSprite = _listSprite[_currentDirection];
	_width = SPRITE_WIDTH;
	_height = SPRITE_HEIGHT;
	isShooting = false;
	this->_isTerminated = false;
	_isBonusTank = isBonus;

	
}
void LightTank:: Draw()
{
	if (!_isTerminated)
	{
		if (!_isFreeze)
			ShootableObject::Draw();
		_curSprite->Render(_left, _top);	
	}
	//ShootableObject::DrawBullet();
}
void LightTank::Move()
{
	//Note: Sau khi biet nguoi dung bam phim nao thi xu ly van toc va return ra ngay de tranh viec
			//Di chuyen theo duong cheo
	if (_currentDirection != LEFT && _currentDirection != RIGHT)
		_vx = 0;
	if (_currentDirection != UP && _currentDirection != DOWN)
		_vy = 0;
	if (_currentDirection == UP)
	{
		this->_vy = -DYNAMIC_OBJECT_HIGH_SPEED.y;
		_curSprite = _listSprite[UP];
		return;
	}
	if (_currentDirection == DOWN)
	{
		this->_vy = (int)DYNAMIC_OBJECT_HIGH_SPEED.y;
		_curSprite = _listSprite[DOWN];	
		return;
	}

	if (_currentDirection == LEFT)
	{
		this->_vx = -(int)DYNAMIC_OBJECT_HIGH_SPEED.x;
		_curSprite = _listSprite[LEFT];
		return;
	}
	if (_currentDirection == RIGHT)
	{
		this->_vx = (int)DYNAMIC_OBJECT_HIGH_SPEED.x;
		_curSprite = _listSprite[RIGHT];
		return;
	}
}
void LightTank::Shoot()
{
	Enemy::Shoot();
}
void LightTank::Update()
{
	//Kiem tra neu enemy dang o trang thai dong bang thi khong update 
	if (_isFreeze)
	{
		if (_isBonusTank)
		{
			this->_listSprite[_currentDirection]->NextInCurRow();
			this->_curSprite = this->_listSprite[_currentDirection];
		}
		return;
	}
	//Tim cac doi tuong tinh xung quanh tank add vao list de xet va cham
	FindNearbyObject();
	this->Move();
	this->Shoot();
	//Xet va cham giua tank voi cac object tinh de ngan khong chi di chuyen
	for (vector<Object*>::iterator i = _listCollisionObject.begin(); i != _listCollisionObject.end(); i++)
	{
		_isCollied = CollisionManager::CollisionPreventMove(this, *i);
		//Chi can va cham voi 1 object trong list la co the chan di chuyen
		if (_isCollied)
		{
			Enemy::MoveWithCollision();
			break;
		}
	}
	//Kiem tra va cham voi man hinh
	if (CollisionManager::CollisionWithScreen(this))
	{
		this->_isCollied = true;
	}
	//Neu co va cham thi chuyen huong
	Enemy::MoveWithCollision();
	//Xoa list object xung quanh lighttank
	DynamicObject::Update();
	//Neu tank o trang thai la bonus thi goi ham sprite->Next de thay doi mau sac cua tank
	if (_isBonusTank)
	{
		this->_listSprite[_currentDirection]->Next();
		this->_curSprite = this->_listSprite[_currentDirection];
	}
	//Neu khong o trang thai bonus thi chuyen giua cot de tao hieu ung cuon banh xe
	else
	{
		this->_listSprite[_currentDirection]->NextColumn();
		this->_curSprite = this->_listSprite[_currentDirection];
	}
}

LightTank::~LightTank()
{
}
