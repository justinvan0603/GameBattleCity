#pragma once
#include "Effect.h"
#include "Object.h"
#include "GameDefaultConstant.h"
class EffectManager
{
private:
	LPD3DXSPRITE _spriteHandler;
	vector<Effect*> _listEffect;
	DWORD _startTime;
private: //Singletton Pattern
	static EffectManager* _instance;
	EffectManager(LPD3DXSPRITE);
	~EffectManager();
public:
	static EffectManager* getInstance(LPD3DXSPRITE = 0);
public:
	void AddBulletEffect(D3DXVECTOR2 position);
	void AddDestroyEffect(D3DXVECTOR2 position);
	void Draw();
	
};

