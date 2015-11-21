#pragma once
#include "Sound.h"
#include "GameDefaultConstant.h"
class GameSound
{
private:
	
	Sound _startGame;
	Sound _fire;
	Sound _bulletExplode;
	Sound _tankExplode;
	Sound _eagleDestroy;
	Sound _tankHit;
private:
	GameSound(DSound* dsound);
	~GameSound();
	static GameSound* _instance;
public:
	static GameSound* getInstance(DSound* dsound);
	void Play(int id);
};

