#include "GameState.h"
#include "ScoreManager.h"

#pragma region Game State

MainMenu* MainMenu::_instance = nullptr;
GameState* GameState::_gameState = nullptr;
LPD3DXSPRITE GameState::_spriteHandler = nullptr;
Text* GameState::_text = nullptr;
DWORD GameState::_startTime = 0;

void GameState::initialize(LPD3DXSPRITE spriteHandler)
{
	_startTime = GetTickCount();
	_spriteHandler = spriteHandler;
	_text = new Text(_spriteHandler);
	switchState(PlayingState::get());
}

void GameState::release()
{

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
		
		if (GameTime::RenderFrame(_startTime, SELECTOR_SPEED_CHANGE))
		{
			_selector->Next();
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
	_startTime = GetTickCount();	
	_spriteHandler->GetDevice(&_d3ddevice);
	//_bgTop = new Sprite(_spriteHandler, IMAGE_BG_STARTING_STATE_PATH, IMAGE_BG_STARTING_WIDTH, IMAGE_BG_STARTING_HEIGHT, 0, 1);
	//_bgBottom = new Sprite(_spriteHandler, IMAGE_BG_STARTING_STATE_PATH, IMAGE_BG_STARTING_WIDTH, IMAGE_BG_STARTING_HEIGHT, 0, 1);
}

StartingState::~StartingState()
{

}

void StartingState::update()
{
	//dem du thoi gian roi thi chuyen qua playing state
	SleepEx(DELAY_TIME_TO_START_PLAYING_STATE , false);
	switchState(PlayingState::get());
}

void StartingState::draw()
{
	_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(99,99,99), 1.0f, 0);
	//_bgTop->Render(IMAGE_BG_STARTING_TOP_POS);
	//_bgBottom->Render(IMAGE_BG_STARTING_BOTTOM_POS);
	_text->drawText("STAGE " + to_string(StageManager::getInstance()->getStage()), IMAGE_STATE_POS , COLOR_BLACK);
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
	//switchState(ScoreState::get());
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

#pragma region Score State
ScoreState* ScoreState::_instance = nullptr;

ScoreState::ScoreState()
{
	_isEnd = true;
	for (int i = 0; i < 4;i++)
	{
		_numTank[i] = 0;
	}
	_iconTankScore = new Sprite(_spriteHandler, ICON_TANK_SCORE_PATH, 48, 176, 1, 1);
}

void ScoreState::update()
{
	SleepEx(20000, false);
	ScoreManager::getInstance()->addScore(_totalScore);
	if(_isEnd)
	{
		GameState::switchState(EndState::get());
	}
	else
	{

		if (StageManager::getInstance()->getStage() == DEFAULT_MAX_STAGE)
		{
			//chuyen toi man hinh congration tu tao sau
		}
		else
		{
			StageManager::getInstance()->nextStage();
			GameState::switchState(StartingState::get());
		}
	}

}

void ScoreState::draw()
{
	_text->drawText("HI-SCORE", POS_HI_SCORE, COLOR_HIGHSCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getHighScore()), POS_HI_SCORE_VALUE, COLOR_SCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText("STAGE", POS_STAGE_TEXT, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(StageManager::getInstance()->getStage()), POS_STAGE_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText("PLAYER", POS_PLAYER_TEXT, COLOR_HIGHSCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getScore()), POS_PLAYER_VALUE, COLOR_SCORE_TEXT, TEXT_SIZE_SCORE_STATE,DT_CENTER,6);
	_iconTankScore->Render(POS_ICON_TANK_SCRORE_STATE);
	float a = BEGIN_X;
	int tempScore;
	_totalScore = 0;
	for (int i = 0; i < 4;i++)
	{
		tempScore = ScoreManager::getInstance()->CalculateScore(i, _numTank[i]);
		_totalScore += tempScore;
		_text->drawText(to_string(tempScore), D3DXVECTOR3(SCORE_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE, DT_RIGHT, 4);
		_text->drawText("PTS", D3DXVECTOR3(PTS_POS_X,a , 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
		_text->drawText(to_string(_numTank[i]), D3DXVECTOR3(NUM_TANK_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE,DT_RIGHT,2);
		a += DISTANCE_LINE;
	}
	_text->drawText("______", POS_LINE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText("TOTAL", POS_TOTAL_TEXT, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(_totalScore), POS_TOTAL_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE,DT_RIGHT,2);
}

void ScoreState::enter()
{

}

ScoreState* ScoreState::get()
{
	if (_instance == nullptr)
	{
		_instance = new ScoreState();
	}

	return _instance;
}

void ScoreState::setEndAfter(bool isEnd)
{
	_isEnd = isEnd;
}

void ScoreState::addResultState(int numtank[4])
{
	for (int i = 0; i < 4;i++)
	{
		_numTank[i] = numtank[i];
	}
}

ScoreState::~ScoreState()
{

}

#pragma endregion


#pragma region End State 
EndState* EndState::_instance = nullptr;

EndState::EndState()
{
	_endImage = new Sprite(_spriteHandler, ICON_END_GAME_PATH, 324, 211, 1, 1);
}

void EndState::update()
{
	//countdown time and return to main menu
	SleepEx(2000, false);
	switchState(MainMenu::get());
}

void EndState::draw()
{
	//Draw game over picture
	_endImage->Render(POS_ICON_END);
}

void EndState::enter()
{
	
}

EndState* EndState::get()
{
	if (_instance == nullptr)
	{
		_instance = new EndState();
	}

	return _instance;
}

EndState::~EndState()
{

}



#pragma endregion
