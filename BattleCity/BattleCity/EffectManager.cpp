#include "EffectManager.h"

EffectManager* EffectManager::_instance = NULL;
EffectManager::EffectManager(LPD3DXSPRITE spriteHandler)
{
	_shieldEffect = new Effect(spriteHandler, EFFECT_SHIELD,106,56 , 6, 6);
	//_respawnEffect = new Effect(spriteHandler, EFFECT_RESPAWN, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE_RESPAWN, NUMB_OF_SPRITE_RESPAWN);
	//_smallExplodeEffect = new Effect(spriteHandler, EFFECT_SMALL_EXPLODE, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE_SMALL_EXPLODE, NUMB_OF_SPRITE_SMALL_EXPLODE);
	//_specialExplodeEffect = new Effect(spriteHandler, EFFECT_SPECIAL_EXPLODE, SPRITE_WIDTH, SPRITE_HEIGHT, NUMB_OF_SPRITE_SPECIAL_EXPLODE, NUMB_OF_SPRITE_SPECIAL_EXPLODE);
}
EffectManager* EffectManager::getInstance(LPD3DXSPRITE spriteHandler)
{
	if (_instance == NULL)
		_instance = new EffectManager(spriteHandler);
	return _instance;
}
void EffectManager::RenderEffect(int id,int X ,int Y)
{
	switch (id)
	{
		case ID_EFFECT_SHIELD:
		{
			_shieldEffect->Render(X, Y);
			break;
		}
		case ID_EFFECT_RESPAWN:
		{
			_respawnEffect->Render(X, Y);
			break;
		}
		case ID_EFFECT_SMALL_EXPLODE:
		{
			_smallExplodeEffect->Render(X, Y);
			break;
		}
		case ID_EFFECT_SPECIAL_EXPLODE:
		{
			_specialExplodeEffect->Render(X, Y);
			break;
		}

		default:
			break;
	}
}
void EffectManager::RenderShield(Object* targetObject)
{

}
EffectManager::~EffectManager()
{
	if (_shieldEffect != NULL)
	{
		delete _shieldEffect;
		_shieldEffect = NULL;
	}
	if (_respawnEffect != NULL)
	{
		delete _respawnEffect;
		_respawnEffect = NULL;
	}
	if (_smallExplodeEffect != NULL)
	{
		delete _smallExplodeEffect;
		_smallExplodeEffect = NULL;
	}
	if (_specialExplodeEffect != NULL)
	{
		delete _specialExplodeEffect;
		_specialExplodeEffect = NULL;
	}
	if (_instance != NULL)
	{
		delete _instance;
		_instance = NULL;
	}
}
