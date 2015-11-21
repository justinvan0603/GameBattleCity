#include "GameSound.h"

GameSound* GameSound::_instance = NULL;
GameSound::GameSound(DSound* dsound)
{
	_bulletExplode = dsound->CreateSound(SOUND_BULLET_EXPLODE);
	_eagleDestroy = dsound->CreateSound(SOUND_EAGLE_DESTROY);
	_fire = dsound->CreateSound(SOUND_FIRE);
	_startGame = dsound->CreateSound(SOUND_START_GAME);
	_tankExplode = dsound->CreateSound(SOUND_TANK_EXPLODE);
	_tankExplode = dsound->CreateSound(SOUND_TANK_HIT);
}
GameSound* GameSound::getInstance(DSound* dsound)
{
	if (_instance == NULL)
		_instance = new GameSound(dsound);
	return _instance;
}
void GameSound::Play(int id)
{
	switch (id)
	{
	case ID_SOUND_START_GAME:
	{
		_startGame.Play();
		break;
	}
	case ID_SOUND_FIRE:
	{
		_fire.Play();
		break;
	}
	case ID_SOUND_BULLET_EXPLODE:
	{
		_bulletExplode.Play();
		break;
	}
	case ID_SOUND_TANK_EXPLODE:
	{
		_tankExplode.Play();
		break;
	}
	case ID_SOUND_EAGLE_DESTROY:
	{
		_eagleDestroy.Play();
		break;
	}
	case ID_SOUND_TANK_HIT:
	{
		_tankHit.Play();
		break;
	}
	default:
		break;
	}
}

GameSound::~GameSound()
{
}
