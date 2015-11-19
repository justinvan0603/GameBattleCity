#pragma once
#include "Window.h"
#include "GameState.h"
#include "PlayerTank.h"
#include "LightTank.h"
#include "Keyboard.h"
#include "Map.h"
#include "CollisionManager.h"
class Game
{
private:
	Window win;
	PlayerTank* _player;
	Keyboard* _keyboard;
	BrickWall* _wall;
	SpriteManager* _spriteManager;
	Map* _map;
	LightTank* _enemy;
public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); // Khởi tạo game
	bool GameRun();
};

