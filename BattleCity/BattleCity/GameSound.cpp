#include "GameSound.h"


GameSound* GameSound::instance_ = nullptr;


GameSound::GameSound()
{
}


GameSound::~GameSound()
{
	FOR_A(loadedSound_.begin(), loadedSound_.end())
		SAFE_RELEASE(i->second);
	loadedSound_.clear();
}

string GameSound::switchID(int id)
{
	string soundLink;
	switch (id)
	{
	case ID_SOUND_START_GAME:
	{
		soundLink = SOUND_START_GAME;
		break;
	}
	case ID_SOUND_FIRE:
	{
		soundLink = SOUND_FIRE;
		break;
	}
	case ID_SOUND_BRICK_EXPLODE:
	{
		soundLink = SOUND_BRICK_EXPLODE;
		break;
	}
	case ID_SOUND_TANK_EXPLODE:
	{
		soundLink = SOUND_TANK_EXPLODE;
		break;
	}
	case ID_SOUND_TANK_ENGINE:
	{
		soundLink = SOUND_TANK_ENGINE;
		break;
	}
	case ID_SOUND_TANK_HIT:
	{
		soundLink = SOUND_TANK_HIT;
		break;
	}
	case ID_SOUND_TANK_MOVE:
	{
		soundLink = SOUND_TANK_MOVE;
		break;
	}

	case ID_SOUND_ALLY_EXPLODE:
	{
		soundLink = SOUND_ALLY_EXPLODE;
		break;
	}
	case ID_SOUND_ITEM_APPEAR:
	{
		soundLink = SOUND_ITEM_APPEAR;
		break;
	}
	case ID_SOUND_ITEM_EAT:
	{
		soundLink = SOUND_ITEM_EAT;
		break;
	}
	case ID_SOUND_LIFE_UP:
	{
		soundLink = SOUND_LIFE_UP;
		break;
	}
	case ID_SOUND_STEEL_WALL_EXPLODE:
	{
		soundLink = SOUND_STEEL_WALL_EXPLODE;
		break;
	}
	case ID_SOUND_COUNT_SCORE:
	{
		soundLink = SOUND_COUNT_SCORE;
		break;
	}
	case ID_SOUND_GAME_OVER:
	{
		soundLink = SOUND_GAME_OVER;
		break;
	}
	default:
		break;
	}
	return soundLink;
}

void GameSound::initialize(HWND windowsHandler)
{
	Sound::initializeSoundClass(windowsHandler);
}


void GameSound::play(string soundLink, bool repeat /*= false*/, bool playFromStart /*= true*/)
{
	try
	{
		if (playFromStart)
			loadedSound_.at(soundLink)->stop();

		loadedSound_.at(soundLink)->play(repeat);
	}
	catch (exception)
	{
		loadedSound_.insert(SoundPair(soundLink, new Sound(soundLink.c_str())));
		loadedSound_.at(soundLink)->play(repeat);
	}
}
void GameSound::Play(int id, bool repeat)
{
	play(switchID(id),repeat);
}


GameSound* GameSound::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GameSound();
	}

	return instance_;
}

void GameSound::release()
{
	SAFE_RELEASE(instance_);
	Sound::releaseSoundClass();
}


void GameSound::stop(string soundLink)
{
	try
	{
		loadedSound_.at(soundLink)->stop();
	}
	catch (exception)
	{

	}
}

void GameSound::Stop(int id)
{
	stop(switchID(id));
}
