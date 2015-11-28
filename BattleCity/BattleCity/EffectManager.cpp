#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
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
