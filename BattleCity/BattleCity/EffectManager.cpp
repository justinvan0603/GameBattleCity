#include "EffectManager.h"
#include "GameTime.h"
EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	//_startTime = GetTickCount();
}
EffectManager* EffectManager::getInstance(LPD3DXSPRITE spriteHandler)
{
	if (_instance == NULL)
		_instance = new EffectManager(spriteHandler);
	return _instance;
}

void EffectManager::AddBulletEffect(D3DXVECTOR2 position)
{
	this->_listEffect.push_back(new Effect(_spriteHandler, EFFECT_SMALL_EXPLODE, SPRITE_WIDTH, SPRITE_HEIGHT, 3, 3,position));
}
void EffectManager::AddDestroyEffect(D3DXVECTOR2 position)
{
	D3DXVECTOR2 effectPosition;
	effectPosition.x = position.x - 17;
	effectPosition.y = position.y - 17;
	this->_listEffect.push_back(new Effect(_spriteHandler, EFFECT_SPECIAL_EXPLODE, SPRITE_WIDTH * 2, SPRITE_HEIGHT * 2, 1, 1,effectPosition));
}
//Ve hieu ung len man hinh
void EffectManager::Draw()
{
	for (vector<Effect*>::iterator i = _listEffect.begin(); i != _listEffect.end();)
	{
		//Neu hieu ung chua ve het frame thi tiep tuc ve sau do goi ham next();
		if ((*i)->_completed == false)
		{
			(*i)->Render();
			(*i)->Next((*i)->_completed);
			i++;
		}
		//Da ve xong thi xoa ra khoi list
		else
		{
			delete *i;
			*i = NULL;
			i = _listEffect.erase(i);
		}
	}
}
void EffectManager::ClearAllEffect()
{
	for (vector<Effect*>::iterator i = _listEffect.begin(); i != _listEffect.end();)
	{
		if ((*i))
		{
			delete *i;
			*i = NULL;
			i = _listEffect.erase(i);
		}
		else
			i++;
	}
	_listEffect.clear();
}