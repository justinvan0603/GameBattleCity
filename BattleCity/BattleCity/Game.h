#pragma once
#include "Window.h"
#include "GameState.h"
#include "PlayerTank.h"
#include "LightTank.h"
#include "Keyboard.h"
#include "Map.h"
#include "CollisionManager.h"
#include "EffectManager.h"

class Game
{
private:
	Window* win;
	Keyboard* _keyboard;

public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); // Khởi tạo game
	void GameUpdate();
	void GameRun();
	void GameRelease();
};

