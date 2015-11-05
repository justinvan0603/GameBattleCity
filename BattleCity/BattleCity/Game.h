#pragma once
#include "Window.h"
#include "Input.h"

class Game
{
private:
	Window win;
	//Input input;
public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); // Khởi tạo game
	bool GameRun();
};

