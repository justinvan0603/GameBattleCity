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
	if (!this->direct.initDirect3D(this->win.wndHandle))
		return false;
	// Khởi tạo bàn phím
	/*if (!this->input.CreateInput() || !this->input.InitKeyboard(this->win.wndHandle))
		return false;*/
	return true;
}