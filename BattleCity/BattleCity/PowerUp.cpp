#include "PowerUp.h"
#include "GameTime.h"
#include "Map.h"
#include <random>


PowerUp::PowerUp()
{
}

PowerUp::PowerUp(Sprite* sprite)
{
	_image = sprite;
	this->_width = SPRITE_WIDTH;
	this->_height = SPRITE_WIDTH;
	_currentPos = 0;
}

void PowerUp::Draw()
{
	_image->Render(_typePower, D3DXVECTOR3((float)this->_left,(float)this->_top,0.0f));
}

void PowerUp::Update()
{

}
//----------------------------------
// Kiem tra item da dc an hay chua
//----------------------------------
bool PowerUp::IsEaten()
{
	return _isEaten;
}

//----------------------------------
//Kiem tra powerup co dang kich hoat hay khong
//----------------------------------
bool PowerUp::IsEnable()
{
	return _isEnable;
}

//----------------------------------
// Goi khi item bi an
//----------------------------------
void PowerUp::setEaten()
{
	_isEaten = true;
}

//----------------------------------
// Tra ve loai item
//----------------------------------
int PowerUp::getType()
{
	return _typePower;
}

//----------------------------------
// Tat power sau khi an
//----------------------------------
void PowerUp::disablePowerUp()
{
	_isEnable = false;
	_isEaten = false;
	this->_top = 0;
	this->_left = 0;
}

//----------------------------------
// Kich hoat khi quai do nhap nhay bi ban chet
//----------------------------------
void PowerUp::enablePowerUp()
{
	_isEnable = true;
	srand(time(NULL));
	_typePower = ID_POWER_BOMB + rand() % (ID_POWER_STAR - ID_POWER_BOMB + 1);	//random item
	
	this->_top = y[_currentPos];
	this->_left = x[_currentPos];
	//if (_currentPos < NUM_POWER_PER_MAP -1)
	_currentPos++;
}

void PowerUp::setmap(int** map)
{
	_mapMatrix = map;
	int col, row, type;
	bool flag = false;

	for (int i = 0; i < NUM_POWER_PER_MAP; i++)
	{
		do
		{
			std::random_device rd;		//c++ 11
			std::mt19937 gen(rd());
			uniform_int_distribution<> dist(0, 49);		//random ra so int, min 0, max 48  <-> [0,49)
			col = dist(gen);
			row = dist(gen);
			type = _mapMatrix[row][col] % 100;
			if (type == ID_STEELWALL_2 || type == ID_STEELWALL_3 || type == ID_STEELWALL_12 || type == ID_STEELWALL_13 ||
				type == ID_WATER_4 || type == ID_WATER_5 || type == ID_WATER_14 || type == ID_WATER_15)
			{
				flag = true;
			}
		} while (((col < 30) && (col > 21) && (row < 49) && (row > 45)) || flag);  //ko cho lot vao toa do phao dai
		D3DXVECTOR3 pos = Map::getPositionFromMapMatrix(row, col);	//lay vi tri tu ma tran map
		x[i] = pos.x;
		y[i] = pos.y;
	}
	_currentPos = 0;
}

PowerUp::~PowerUp()
{
}
