#include "GameState.h"

#pragma region Game State

MainMenu* MainMenu::_instance = nullptr;
GameState* GameState::_gameState = nullptr;
PlayerTank* GameState::_player = nullptr;
LPD3DXSPRITE GameState::_spriteHandler = nullptr;

void GameState::initialize(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	_player = new PlayerTank(_spriteHandler);
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
	_menuImagePosition = IMAGE_MAIN_MENU_GAME_DEFAULT_POS;
	_selectorPosition = IMAGE_SELECTOR_POS_PLAY;
	_timeDelayChangeSelectorSprite = SELECTOR_SPEED_CHANGE;
	//new sprite image main menu
	_menuImage = new Sprite(_spriteHandler, IMAGE_MAIN_MENU_GAME_PATH, IMAGE_MAIN_MENU_GAME_WIDTH, IMAGE_MAIN_MENU_GAME_HEIGHT, 1, 1);
	_selector = new Sprite(_spriteHandler, IMAGE_SELECTOR_PATH, IMAGE_SELECTOR_WIDTH, IMAGE_SELECTOR_HEIGHT, 2, 2);
	enter();
}

MainMenu::~MainMenu()
{
	//SAFE_RELEASE(image);
}

void MainMenu::update()
{
	//Kiem tra xem chon start hay instruction roi change state
	if(_menuImagePosition.y > 0)
	{
		_menuImagePosition.y -= IMAGE_MAIN_MENU_GAME_DEFAULT_SPEED_UP;
	}
	else
	{
		//tao selector chuyen dong
		_timeDelayChangeSelectorSprite--;
		if (_timeDelayChangeSelectorSprite <= 0)
		{
			_selector->Next();
			_timeDelayChangeSelectorSprite = SELECTOR_SPEED_CHANGE;
		}
		if(Keyboard::getInstance()->IsKeyDown(DIK_DOWN))
		{
			_selectorPosition = IMAGE_SELECTOR_POS_INSTRUCTION;
		}
		if(Keyboard::getInstance()->IsKeyDown(DIK_UP))
		{
			_selectorPosition = IMAGE_SELECTOR_POS_PLAY;
		}
		if(Keyboard::getInstance()->IsKeyDown(DIK_RETURN))
		{
			if (_selectorPosition == IMAGE_SELECTOR_POS_PLAY)
			{
				switchState(StartingState::get());
			}
			else
			{
				//code instruction
			}
		}
	}
	
	
}

void MainMenu::draw()
{
	//ve logo main menu
	_menuImage->Render(0, 0, _menuImagePosition);
	if(_menuImagePosition.y <= 0)
	{
		_selector->Render((int)_selectorPosition.x, (int)_selectorPosition.y);
	}
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
	_currentLevelState = 1;
	_spriteHandler->GetDevice(&_d3ddevice);
	_stateLevelImage = new Sprite(_spriteHandler, IMAGE_STATE_PATH, IMAGE_STATE_WIDTH, IMAGE_STATE_HEIGHT, 1, 1);
	_numLevel = new Sprite(_spriteHandler, RESOURCE_PATH_NUMBER, IMAGE_NUMBER_WIDTH, IMAGE_NUMBER_HEIGHT, 10, 5);
	//_bgTop = new Sprite(_spriteHandler, IMAGE_BG_STARTING_STATE_PATH, IMAGE_BG_STARTING_WIDTH, IMAGE_BG_STARTING_HEIGHT, 0, 1);
	//_bgBottom = new Sprite(_spriteHandler, IMAGE_BG_STARTING_STATE_PATH, IMAGE_BG_STARTING_WIDTH, IMAGE_BG_STARTING_HEIGHT, 0, 1);
	//init sprite state 1, 2, 3 ....
	//code here
}

StartingState::~StartingState()
{

}

int StartingState::getCurrentLevelState()
{
	return _currentLevelState;
}

void StartingState::update()
{
	//dem du thoi gian roi thi chuyen qua playing state
}

void StartingState::draw()
{
	_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(99,99,99), 1.0f, 0);
	_stateLevelImage->Render(IMAGE_STATE_POS);
	//_bgTop->Render(IMAGE_BG_STARTING_TOP_POS);
		//_bgBottom->Render(IMAGE_BG_STARTING_BOTTOM_POS);
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

PlayingState::PlayingState()
{
	_map = new Map(_spriteHandler);
}

void PlayingState::update()
{
	//map, bullet, player update
	_map->Update();
}

void PlayingState::draw()
{
	//draw all item in screen
	_map->Draw();
}

void PlayingState::enter()
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
