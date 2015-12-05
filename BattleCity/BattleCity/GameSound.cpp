#include "GameSound.h"

GameSound* GameSound::_instance = NULL;
GameSound::GameSound(DSound* dsound)
{
	_startGame = dsound->CreateSound(SOUND_START_GAME);
	//_objectExplode = dsound->CreateSound(SOUND_TANK_EXPLODE);
	//_bulletExplode = dsound->CreateSound(SOUND_BULLET_EXPLODE);
	//_fire = dsound->CreateSound()

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
		_objectExplode.Play();
		break;
	}
	case ID_SOUND_TANK_ENGINE:
	{
		_tankEngine.Play();
		break;
	}
	case ID_SOUND_TANK_MOVE:
	{
		_tankMove.Play();
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
void GameSound::PlayRepeat(int id)
{
	switch (id)
	{
	case ID_SOUND_START_GAME:
	{
		_startGame.PlayRepeat();
		break;
	}
	case ID_SOUND_FIRE:
	{
		_fire.PlayRepeat();
		break;
	}
	case ID_SOUND_BULLET_EXPLODE:
	{
		_bulletExplode.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_EXPLODE:
	{
		_objectExplode.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_ENGINE:
	{
		_tankEngine.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_MOVE:
	{
		_tankMove.PlayRepeat();
	}
	case ID_SOUND_TANK_HIT:
	{
		_tankHit.PlayRepeat();
		break;
	}
	default:
		break;
	}
}
GameSound::~GameSound()
{
}
