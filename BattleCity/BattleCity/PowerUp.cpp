#include "PowerUp.h"
#include "GameTime.h"


PowerUp::PowerUp()
{
}

PowerUp::PowerUp(Sprite* sprite)
{
	_image = sprite;
	_isEnable = false;
	_isEaten = false;
}

void PowerUp::Draw()
{
	//_image->Render(_typePower,D3DXVECTOR3((float)_left, (float)_top,0.0f));
	_image->Render(_typePower, D3DXVECTOR3((float)this->_left,(float)this->_top,0.0f));
}

void PowerUp::Update()
{

}

bool PowerUp::IsEnable()
{
	return _isEnable;
}

bool PowerUp::IsEaten()
{
	return _isEaten;
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
}

void PowerUp::enablePowerUp()
{
	_isEnable = true;
	srand(time(NULL));
	_typePower = 0 + rand() % (5 - 0 + 1);
	
	this->_top = 0 + rand() % (100 - 0 + 1);
	this->_left = 0 + rand() % (100 - 0 + 1);
}

PowerUp::~PowerUp()
{
}
