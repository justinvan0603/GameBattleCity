#pragma once
#include "Window.h"

#include "PlayerTank.h"
#include "Keyboard.h"
#include "Map.h"
class Game
{
private:
	Window win;
	PlayerTank* _player;
	Keyboard* _keyboard;
	Map* _map;
public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); // Khởi tạo game
	bool GameRun();
};

