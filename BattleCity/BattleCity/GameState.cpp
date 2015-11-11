#include "GameState.h"

#pragma region Game State

Keyboard* GameState::_controler = nullptr;
MainMenu* MainMenu::_instance = nullptr;
GameState* GameState::_gameState = nullptr;
PlayerTank* GameState::_player = nullptr;

void GameState::initialize(Keyboard* controler)
{
	_controler = controler;
	switchState(PlayingState::get());
}

void GameState::release()
{
	SAFE_RELEASE(_player);
}


void GameState::stateUpdate()
{
	_gameState->update();
}


void GameState::switchState(GameState* newState)
{
	_gameState = newState;
	_gameState->enter();
}


void GameState::stateDraw()
{
	_gameState->draw();
}

void GameState::update()
{

}

void GameState::draw()
{

}
#pragma endregion

#pragma region Main Menu
MainMenu::MainMenu()
{
	//new sprite image main menu

	enter();
}

MainMenu::~MainMenu()
{
	//SAFE_RELEASE(image);
}

void MainMenu::update()
{
	//Kiem tra xem chon start hay instruction roi change state
}

void MainMenu::draw()
{
	//ve logo main menu
}

MainMenu* MainMenu::get()
{
	if (_instance == nullptr)
		_instance = new MainMenu();

	return _instance;
}

void MainMenu::enter()
{
	
}

#pragma endregion

#pragma region Starting

StartingState* StartingState::_instance = nullptr;

StartingState::StartingState()
{
	_timeCounter = 0;
	_numOfState = NUMBER_OF_STATE;
	//init sprite state 1, 2, 3 ....
}

StartingState::~StartingState()
{

}

int StartingState::getCurrentState()
{
	return _currentState;
}

void StartingState::update()
{
	//dem du thoi gian roi thi chuyen qua playing state
}

void StartingState::draw()
{
	//Draw 
}

void StartingState::enter()
{
	
}

StartingState* StartingState::get()
{
	if (_instance == nullptr)
	{
		_instance = new StartingState();
	}

	return _instance;
}

#pragma endregion

#pragma region Playing

PlayingState* PlayingState::_instance = nullptr;

void PlayingState::update()
{
	//map, bullet, player update
}

void PlayingState::draw()
{
	//draw all item in screen
}

void PlayingState::enter()
{
	
}

PlayingState::PlayingState()
{

}

PlayingState::~PlayingState()
{

}

PlayingState* PlayingState::get()
{
	if (_instance == nullptr)
	{
		_instance = new PlayingState();
	}

	return _instance;
}


#pragma endregion

#pragma region Dead State
DeadScene* DeadScene::_instance = nullptr;
void DeadScene::update()
{
	//countdown time and return to main menu
}

void DeadScene::draw()
{
	//Draw game over picture
}

void DeadScene::enter()
{
	
}


DeadScene* DeadScene::get()
{
	if (_instance == nullptr)
	{
		_instance = new DeadScene();
	}

	return _instance;
}

DeadScene::DeadScene()
{
	//init sprite to draw
}

DeadScene::~DeadScene()
{

}



#pragma endregion
