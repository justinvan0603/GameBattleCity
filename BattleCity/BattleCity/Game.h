﻿#pragma once
#include "Window.h"

#include "PlayerTank.h"
#include "Keyboard.h"
class Game
{
private:
	Window win;
	PlayerTank* _player;
	Keyboard* _keyboard;
	//Bullet* _bullet;
public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); // Khởi tạo game
	bool GameRun();
};

