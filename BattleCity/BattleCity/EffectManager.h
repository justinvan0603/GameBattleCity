#pragma once
#include "Effect.h"
#include "Object.h"
#include "GameDefaultConstant.h"
class EffectManager
{
private:
	Effect* _shieldEffect;
	Effect* _respawnEffect;
	Effect* _smallExplodeEffect;
	Effect* _specialExplodeEffect;
private: //Singletton Pattern
	static EffectManager* _instance;
	EffectManager(LPD3DXSPRITE);
	~EffectManager();
public:
	static EffectManager* getInstance(LPD3DXSPRITE);
public:
	
	void RenderEffect(int id, int X, int Y);
	void RenderShield(Object*);
	
};

