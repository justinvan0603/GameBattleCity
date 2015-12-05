#include "EffectManager.h"
#include "GameTime.h"
EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	_startTime = GetTickCount();
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

}
void EffectManager::Draw()
{
	for (vector<Effect*>::iterator i = _listEffect.begin(); i != _listEffect.end();)
	{
		if ((*i)->_completed == false)
		{
			(*i)->Render();
			if (GameTime::RenderFrame(_startTime,5))
				(*i)->Next((*i)->_completed);
			i++;
		}
		else
		{
			delete *i;
			*i = NULL;
			i = _listEffect.erase(i);
		}
	}
}
