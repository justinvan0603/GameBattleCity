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
	// Khởi tạo directX5
	if (!this->win.initDirectX())
		return false;

	_keyboard = Keyboard::getInstance();
	if (!_keyboard->InitKeyboard(this->win.get_hInstance(), this->win.get_windowHandler()))
		return false;
	_player = new PlayerTank(win.getSpriteHandler());
	_map = new Map(win.getSpriteHandler());
	
	return true;
}

bool Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	DWORD timePerFrame = 100 / FRAME_RATE;

			
			win.getDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			
			if (win.getDevice()->BeginScene())
			{
				_player->Draw();
				
				//_bullet->Draw();
				//win.getDevice()->ColorFill(_backBuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
				_map->Draw();
				win.getDevice()->EndScene();
			}
			win.getDevice()->Present(NULL, NULL, NULL, NULL);
			_player->Update();
			_map->Update();
			_keyboard->ProcessKeyboard(win.get_windowHandler());
		
	
	return true;
}