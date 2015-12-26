#include "Game.h"

Game::Game()
{
	_window = new Window();
}


Game::~Game()
{
}

//----------------------------------
// Khởi tạo game
//----------------------------------
bool Game::GameInit(HINSTANCE hInstance)
{
	// Khởi tạo cửa sổ game
	if (!_window->initWindow(hInstance))
	{
		WARNING_BOX(WARNING_GAME_CAN_NOT_INIT_WINDOW);
		return false;
	}
	// Khởi tạo directX
	if (!_window->initDirectX())
	{
		WARNING_BOX(WARNING_GAME_CAN_NOT_INIT_D3D);
		return false;
	}	
	//Khoi tao keyboard
	_keyboard = Keyboard::getInstance();
	if (!_keyboard->InitKeyboard(_window->get_hInstance(), _window->get_windowHandler()))
	{
		WARNING_BOX(WARNING_GAME_CAN_NOT_INIT_KEYBOARD);
		return false;
	}
	//Khoi tao am thanh
	if(!GameSound::initialize(_window->get_windowHandler()))
	{
		WARNING_BOX(WARNING_CAN_NOT_INIT_SOUND);
		return false;
	}

	//Khoi tao GameState quan li cac trang thai cua game
	GameState::initialize(_window->getSpriteHandler());
	
	return true;
}

//----------------------------------
//Cập nhật game
//----------------------------------
void Game::GameUpdate()
{
	//Cap nhat trang thai cua ban phim
	_keyboard->update(_window->get_windowHandler());
	//Update gamestate
	GameState::stateUpdate();
}

//----------------------------------
//Vẽ Game
//----------------------------------
void Game::GameDraw()
{
	if(_window->startDraw())
	{
		GameState::stateDraw();
		_window->stopDraw();
	}	
}

//----------------------------------
//Giải phóng tài nguyên game
//----------------------------------
void Game::GameRelease()
{
	SAFE_RELEASE(_window);
	SAFE_RELEASE(_keyboard);
	GameSound::getInstance()->release();
	GameState::release();
}
