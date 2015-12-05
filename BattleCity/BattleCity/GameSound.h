#pragma once
#include "Sound.h"
#include "GameDefaultConstant.h"
class GameSound
{
private:
	
	Sound _startGame;
	Sound _fire;
	Sound _bulletExplode;
	Sound _objectExplode;
	Sound _tankEngine;
	Sound _tankMove;
	Sound _tankHit;
	Sound _powerAppear;
	Sound _eatPower;
	Sound _lifeUp;
private:
	GameSound(DSound* dsound);
	~GameSound();
	static GameSound* _instance;
public:
	static GameSound* getInstance(DSound* dsound);
	void Play(int id);
	void PlayRepeat(int id);
};

