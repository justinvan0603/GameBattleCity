#ifndef __GAME_SOUND__
#define __GAME_SOUND__

#include "Sound.h"
#include "DefaultConstant.h"
#include "GameDefaultConstant.h"
#include <map>
using namespace std;

typedef map<string, Sound*> SoundMap;		//Lien ket ten am thanh vs object am thanh tuong ung
typedef pair<string, Sound*> SoundPair;		//Ham khoi tao cua map SoundMap

class GameSound
{
public:
	 static void initialize(HWND windowsHandler);

	 void release();

	 void Play(int id, bool repeat = false);

	 void play(string soundLink, bool repeat = false, bool playFromStart = true);

	 void Stop(int id);

	 void stop(string soundLink);

	 static GameSound* getInstance();

private:
	GameSound();
	~GameSound();

	string switchID(int id);
	//Sound _gameOver;
private:
	static GameSound* _instance;
	SoundMap _loadedSound;
};

#endif // __GAME_SOUND__
