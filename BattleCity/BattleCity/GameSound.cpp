#include "GameSound.h"


GameSound* GameSound::_instance = nullptr;


GameSound::GameSound()
{
}


GameSound::~GameSound()
{
	FOR_A(_loadedSound.begin(), _loadedSound.end())
		SAFE_RELEASE(i->second);	//->second: release Sound*, string(first) ko can release
	_loadedSound.clear();
}

//----------------------------------
// Duyet ID de tim duong dan file am thanh tuong ung
//----------------------------------
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

bool GameSound::initialize(HWND windowsHandler)
{
	HRESULT result = Sound::initializeSoundClass(windowsHandler);
	if (result == S_OK)
		return true;
	return false;
}

//----------------------------------
// Chay am thanh. Duyen tren map de tim ra doi tuong Sound tuong ung vs duong dan. Neu chua co
// thi tao 1 anh xa moi, add vao Map roi play
//----------------------------------
void GameSound::play(string soundLink, bool repeat /*= false*/, bool playFromStart /*= true*/)
{
	try
	{
		if (playFromStart)
			_loadedSound.at(soundLink)->stop();

		_loadedSound.at(soundLink)->play(repeat);
	}
	catch (exception)
	{
		_loadedSound.insert(SoundPair(soundLink, new Sound(soundLink.c_str())));
		_loadedSound.at(soundLink)->play(repeat);
	}
}
void GameSound::Play(int id, bool repeat)
{
	play(switchID(id),repeat);
}


GameSound* GameSound::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameSound();
	}

	return _instance;
}

void GameSound::release()
{
	SAFE_RELEASE(_instance);
	Sound::releaseSoundClass();
}


void GameSound::stop(string soundLink)
{
	try
	{
		_loadedSound.at(soundLink)->stop();
	}
	catch (exception)
	{

	}
}

void GameSound::Stop(int id)
{
	stop(switchID(id));
}
