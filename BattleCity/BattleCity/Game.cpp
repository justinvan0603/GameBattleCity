#include "Game.h"


Game::Game()
{
	win = new Window();
}


Game::~Game()
{
}

bool Game::GameInit(HINSTANCE hInstance)
{
	// Khởi tạo cửa sổ game
	if (!win->initWindow(hInstance))
	{
		WARNING_BOX(WARNING_GAME_CAN_NOT_INIT_WINDOW);
		return false;
	}
	// Khởi tạo directX
	if (!win->initDirectX())
	{
		WARNING_BOX(WARNING_GAME_CAN_NOT_INIT_D3D);
		return false;
	}	
	//Khoi tao keyboard
	_keyboard = Keyboard::getInstance();
	if (!_keyboard->InitKeyboard(win->get_hInstance(), win->get_windowHandler()))
	{
		WARNING_BOX(WARNING_GAME_CAN_NOT_INIT_KEYBOARD);
		return false;
	}
	GameState::initialize(win->getSpriteHandler());
	
	return true;
}

void Game::GameUpdate()
{
	_keyboard->ProcessKeyboard(win->get_windowHandler());
	GameState::stateUpdate();
}

void Game::GameRun()
{
	if(win->startDraw())
	{
		GameState::stateDraw();
		win->stopDraw();
	}	
}

void Game::GameRelease()
{
	//write code here
}
