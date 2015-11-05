#include "Game.h"



Game::Game()
{
	
}


Game::~Game()
{
}

bool Game::GameInit(HINSTANCE hInstance)
{
	// Khởi tạo cửa sổ game
	if (!this->win.initWindow(hInstance))
		return false; 
	// Khởi tạo directX
	if (!this->win.initDirectX())
		return false;
	// Khởi tạo bàn phím
	/*if (!this->input.CreateInput() || !this->input.InitKeyboard(this->win.wndHandle))
		return false;*/
	return true;
}

bool Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	DWORD timePerFrame = 100 / FRAME_RATE;
	//float playerX = 0;
	//float playerY = 0;
	//float vx = 5.0;
	//float vy = 0.0;
	DWORD startTime = GetTickCount();
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DWORD currentTime = GetTickCount();
		DWORD passedTime = currentTime - startTime;

		if (passedTime >= timePerFrame)
		{
			win.getDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			if (win.getDevice()->BeginScene())
			{

				//win.getDevice()->ColorFill(_backBuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));

				win.getDevice()->EndScene();
			}
			win.getDevice()->Present(NULL, NULL, NULL, NULL);

		}
	}
	return true;
}