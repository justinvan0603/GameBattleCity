#pragma once
#include "Window.h"
#include "DirectX.h"
#include "Input.h"

class Game
{
private:
	Window win;
	DirectX direct;
	//Input input;
public:
	Game();
	~Game();

	bool GameInit(HINSTANCE); // Khởi tạo game
	
};

