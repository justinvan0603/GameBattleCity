#include "GameSound.h"

GameSound* GameSound::_instance = NULL;
GameSound::GameSound(DSound* dsound)
{
	_startGame = dsound->CreateSound(SOUND_START_GAME);
	_fire = dsound->CreateSound(SOUND_FIRE);
	_brickExplode = dsound->CreateSound(SOUND_BRICK_EXPLODE);
	_eatPower = dsound->CreateSound(SOUND_ITEM_EAT);
	_enemyExplode = dsound->CreateSound(SOUND_TANK_EXPLODE);
	_allyExplode = dsound->CreateSound(SOUND_ALLY_EXPLODE);
	_powerAppear = dsound->CreateSound(SOUND_ITEM_APPEAR);
	_tankEngine = dsound->CreateSound(SOUND_TANK_ENGINE);
	_tankHit = dsound->CreateSound(SOUND_TANK_HIT);
	_tankMove = dsound->CreateSound(SOUND_TANK_MOVE);
	_lifeUp = dsound->CreateSound(SOUND_LIFE_UP);
	_steelwallExplode = dsound->CreateSound(SOUND_STEEL_WALL_EXPLODE);
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
		if(!_startGame._isPlaying)
		_startGame.Play();
		break;
	}
	case ID_SOUND_FIRE:
	{
		if (!_fire._isPlaying)
		_fire.Play();
		
		break;
	}
	case ID_SOUND_BRICK_EXPLODE:
	{
		if (!_brickExplode._isPlaying)
		_brickExplode.Play();
		break;
	}
	case ID_SOUND_TANK_EXPLODE:
	{
		if (!_enemyExplode._isPlaying)
		_enemyExplode.Play();
		break;
	}
	case ID_SOUND_TANK_ENGINE:
	{
		if (!_tankEngine._isPlaying)
		_tankEngine.Play();
		break;
	}
	case ID_SOUND_TANK_HIT:
	{
		if (!_tankHit._isPlaying)
		_tankHit.Play();
		break;
	}
	case ID_SOUND_TANK_MOVE:
	{
		if (!_tankMove._isPlaying)
		_tankMove.Play();
		break;
	}

	case ID_SOUND_ALLY_EXPLODE:
	{
		if (!_allyExplode._isPlaying)
		_allyExplode.Play();
		break;
	}
	case ID_SOUND_ITEM_APPEAR:
	{
		if (!_powerAppear._isPlaying)
		_powerAppear.Play();
		break;
	}
	case ID_SOUND_ITEM_EAT:
	{
		if (!_eatPower._isPlaying)
		_eatPower.Play();
		break;
	}
	case ID_SOUND_LIFE_UP:
	{
		if (!_lifeUp._isPlaying)
		_lifeUp.Play();
		break;
	}
	case ID_SOUND_STEEL_WALL_EXPLODE:
	{
		if (!_steelwallExplode._isPlaying)
		_steelwallExplode.Play();
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
	case ID_SOUND_BRICK_EXPLODE:
	{
		_brickExplode.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_EXPLODE:
	{
		_enemyExplode.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_ENGINE:
	{
		_tankEngine.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_HIT:
	{
		_tankHit.PlayRepeat();
		break;
	}
	case ID_SOUND_TANK_MOVE:
	{
		_tankMove.PlayRepeat();
	}
	case ID_SOUND_ALLY_EXPLODE:
	{
		_allyExplode.PlayRepeat();
		break;
	}
	case ID_SOUND_ITEM_APPEAR:
	{
		_powerAppear.PlayRepeat();
		break;
	}
	case ID_SOUND_ITEM_EAT:
	{
		_eatPower.PlayRepeat();
		break;
	}
	case ID_SOUND_LIFE_UP:
	{
		_lifeUp.PlayRepeat();
		break;
	}
	case ID_SOUND_STEEL_WALL_EXPLODE:
	{
		_steelwallExplode.PlayRepeat();
	}
	default:
		break;
	}
}
void GameSound::Stop(int id)
{
	switch (id)
	{
	case ID_SOUND_START_GAME:
	{
		_startGame.Stop();
		break;
	}
	case ID_SOUND_FIRE:
	{
		_fire.Stop();

		break;
	}
	case ID_SOUND_BRICK_EXPLODE:
	{
		_brickExplode.Stop();
		break;
	}
	case ID_SOUND_TANK_EXPLODE:
	{
		_enemyExplode.Stop();
		break;
	}
	case ID_SOUND_TANK_ENGINE:
	{
		_tankEngine.Stop();
		break;
	}
	case ID_SOUND_TANK_HIT:
	{
		_tankHit.Stop();
		break;
	}
	case ID_SOUND_TANK_MOVE:
	{
		_tankMove.Stop();
		break;
	}

	case ID_SOUND_ALLY_EXPLODE:
	{
		_allyExplode.Stop();
		break;
	}
	case ID_SOUND_ITEM_APPEAR:
	{
		_powerAppear.Stop();
		break;
	}
	case ID_SOUND_ITEM_EAT:
	{
		_eatPower.Stop();
		break;
	}
	case ID_SOUND_LIFE_UP:
	{
		_lifeUp.Stop();
		break;
	}
	case ID_SOUND_STEEL_WALL_EXPLODE:
	{
		_steelwallExplode.Stop();
	}
	default:
		break;
	}
}
GameSound::~GameSound()
{
}
