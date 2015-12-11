#include "PowerUp.h"
#include "GameTime.h"
#include "Map.h"


PowerUp::PowerUp()
{
}

PowerUp::PowerUp(Sprite* sprite)
{
	_image = sprite;
	this->_width = SPRITE_WIDTH;
	this->_height = SPRITE_WIDTH;
}

void PowerUp::Draw()
{
	_image->Render(_typePower, D3DXVECTOR3((float)this->_left,(float)this->_top,0.0f));
}

void PowerUp::Update()
{

}

bool PowerUp::IsEaten()
{
	return _isEaten;
}

bool PowerUp::IsEnable()
{
	return _isEnable;
}

void PowerUp::setEaten()
{
	_isEaten = true;
}

int PowerUp::getType()
{
	return _typePower;
}

void PowerUp::disablePowerUp()
{
	_isEnable = false;
	_isEaten = false;
	this->_top = 0;
	this->_left = 0;
}

void PowerUp::enablePowerUp()
{
	_isEnable = true;
	srand(time(NULL));
	_typePower = ID_POWER_BOMB + rand() % (ID_POWER_STAR - ID_POWER_BOMB + 1);
	int col, row, type;
	bool flag;
	do
	{
		flag = false;
		srand(time(NULL));
		col = rand() % 49; //52-1-3-0+1
		row = rand() % 49;
		type = _mapMatrix[row][col] % 100;
		if (type == ID_STEELWALL_2 || type == ID_STEELWALL_3 || type == ID_STEELWALL_12 || type == ID_STEELWALL_13 ||
			type == ID_WATER_4 || type == ID_WATER_5 || type == ID_WATER_14 || type == ID_WATER_15)
		{
			flag = true;
		}
	} while (((col < 30) && (col > 21) && (row < 49) && (row > 45)) || flag);  //ko cho lot vao toa do phao dai
	D3DXVECTOR3 pos = Map::getPositionFromMapMatrix(row, col);
	this->_top = pos.y;
	this->_left = pos.x;
}

void PowerUp::setmap(int** map)
{
	_mapMatrix = map;
}

PowerUp::~PowerUp()
{
}
