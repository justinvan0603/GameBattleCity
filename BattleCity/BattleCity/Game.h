#ifndef __GAME_H__
#define __GAME_H__

#include "Window.h"
#include "Keyboard.h"
#include "GameState.h"

class Game
{
private:
	Window* _window;
	Keyboard* _keyboard;

public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); 
	void GameUpdate();		
	void GameDraw();		
	void GameRelease();		
};
#endif

