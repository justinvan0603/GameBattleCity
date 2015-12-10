#include "GameState.h"
#include "ScoreManager.h"
#include "StageManager.h"


#pragma region Game State

GameState* GameState::_gameState = nullptr;
LPD3DXSPRITE GameState::_spriteHandler = nullptr;
Text* GameState::_text = nullptr;

void GameState::initialize(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	_text = new Text(_spriteHandler);
	switchState(MainMenu::get());
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
MainMenu* MainMenu::_instance = nullptr;
MainMenu::MainMenu()
{
	//new sprite image main menu
	_menuImage = new Sprite(_spriteHandler, IMAGE_MAIN_MENU_GAME_PATH, IMAGE_MAIN_MENU_GAME_WIDTH, IMAGE_MAIN_MENU_GAME_HEIGHT, 1, 1);
	_selector = new Sprite(_spriteHandler, IMAGE_SELECTOR_PATH, IMAGE_SELECTOR_WIDTH, IMAGE_SELECTOR_HEIGHT, 2, 2);
	_delayTime = 200;
	MainMenu::reset();
}

MainMenu::~MainMenu()
{
	SAFE_RELEASE(_menuImage);
	SAFE_RELEASE(_selector);
}

void MainMenu::update()
{
	//Kiem tra xem chon start hay instruction roi change state
	if(_menuImagePosition.y > 0)
	{
		_menuImagePosition.y -= IMAGE_MAIN_MENU_GAME_DEFAULT_SPEED_UP;
		if (Keyboard::getInstance()->getKeyState(DIK_RETURN) == KeyState::KEY_PRESS)
		{
			_menuImagePosition.y = 0;
		}
	}
	else
	{
		//tao selector chuyen dong
		
		
		if (GameTime::DelayTime(_delayTime))
		{
			_delayTime = 200;
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
		if(Keyboard::getInstance()->getKeyState(DIK_RETURN) == KeyState::KEY_PRESS)
		{
			if (_selectorPosition == IMAGE_SELECTOR_POS_PLAY)
			{
				switchState(StartingState::get());
			}
			else
			{
				switchState(Instruction::get());
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

void MainMenu::reset()
{
	_menuImagePosition = IMAGE_MAIN_MENU_GAME_DEFAULT_POS;
	_selectorPosition = IMAGE_SELECTOR_POS_PLAY;
}

MainMenu* MainMenu::get()
{
	if (_instance == nullptr)
		_instance = new MainMenu();

	return _instance;
}

#pragma endregion

#pragma region Instruction
Instruction* Instruction::_instance = nullptr;

Instruction::Instruction()
{
	_imageTabStory = new Sprite(_spriteHandler, IMAGE_TAB_STORY_PATH, 212, 212, 1, 1);
	_imageTabControl = new Sprite(_spriteHandler, IMAGE_TAB_CONTROL_PATH, SPRITE_WIDTH, SPRITE_HEIGHT*7, 1, 1);
	_imageBulletRight = new Sprite(_spriteHandler, BULLET_SPRITE_RIGHT_PATH, BULLET_WIDTH, BULLET_HEIGHT, 1, 1);
	_imageTabEmies = new Sprite(_spriteHandler, IMAGE_TAB_ENEMIES_PATH, SPRITE_WIDTH, 176, 1, 1);
	_imageTabPowerUp = new Sprite(_spriteHandler, IMAGE_TAB_POWERUP_PATH, SPRITE_WIDTH, 224, 1, 1);
	_imageTabEnvironment = new Sprite(_spriteHandler, IMAGE_TAB_ENVIRONMENT_PATH, SPRITE_WIDTH, 224, 1, 1);
	Instruction::reset();
}

Instruction::~Instruction()
{
	SAFE_RELEASE(_imageTabStory);
	SAFE_RELEASE(_imageTabControl);
	SAFE_RELEASE(_imageBulletRight);
	SAFE_RELEASE(_imageTabEmies);
	SAFE_RELEASE(_imageTabPowerUp);
	SAFE_RELEASE(_imageTabEnvironment);
}

void Instruction::update()
{
	if(Keyboard::getInstance()->getKeyState(DIK_RIGHT) == KeyState::KEY_PRESS)
	{
		if(_currentTab < 5)
		{
			_currentTab++;
		}
	}
	if(Keyboard::getInstance()->getKeyState(DIK_LEFT) == KeyState::KEY_PRESS)
	{
		if (_currentTab > 1)
		{
			_currentTab--;
		}
	}
	if (Keyboard::getInstance()->getKeyState(DIK_ESCAPE) == KeyState::KEY_PRESS)
	{
		switchState(MainMenu::get());
	}
}

void Instruction::draw()
{
	_text->drawText(TEXT_TUT, POS_TUTORIAL,COLOR_WHITE,10);
	_text->drawText(TEXT_TAB_STORY, POS_TEXT_STORY, COLOR_WHITE);
	_text->drawText(TEXT_TAB_CONTROL, POS_TEXT_CONTROL, COLOR_WHITE);
	_text->drawText(TEXT_TAB_ENEMIES, POS_TEXT_ENEMIES, COLOR_WHITE);
	_text->drawText(TEXT_TAB_POWER_UP, POS_TEXT_POWER_UP, COLOR_WHITE);
	_text->drawText(TEXT_TAB_ENVIRONMENT, POS_TEXT_ENVIRONMENT, COLOR_WHITE);

	switch (_currentTab)
	{
		case 1:
		{
			_text->drawText(TEXT_TAB_STORY, POS_TEXT_STORY, COLOR_RED);
			_text->drawText(TEXT_INFO_STORY
				, POS_TEXT_INFO_STORY, COLOR_WHITE, 10,0,0,9);
			_imageTabStory->Render(POS_IMAGE_STORY);
			break;
		}
		case 2:
		{		
			_text->drawText(TEXT_TAB_CONTROL, POS_TEXT_CONTROL, COLOR_RED);

			float translateX = 100.0f, translateY = 100.0f;
			_text->drawText(TEXT_TAB_CONTROL_ACTION, D3DXVECTOR3(translateX + 105.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12,DT_CENTER,9);
			_text->drawText(TEXT_TAB_CONTROL_KEY, D3DXVECTOR3(translateX + 260.0f, translateY + 60.0f , 0.0f), COLOR_WHITE, 12);
		
			_imageTabControl->Render(0, D3DXVECTOR3(translateX + 140.0f,translateY + 80.0f,0.0f));
			_imageBulletRight->Render(0, D3DXVECTOR3(translateX + 175.0f, translateY + 285.0f, 0.0f));

			_text->drawText(TEXT_TAB_CONTROL_UP, D3DXVECTOR3(translateX + 260.0f, translateY + 93.0f, 0.0f), COLOR_WHITE, 12);
			_text->drawText(TEXT_TAB_CONTROL_RIGHT, D3DXVECTOR3(translateX + 260.0f, translateY + 140.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_CONTROL_DOWN, D3DXVECTOR3(translateX + 260.0f, translateY + 185.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_CONTROL_LEFT, D3DXVECTOR3(translateX + 260.0f, translateY + 235.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_CONTROL_SPACE, D3DXVECTOR3(translateX + 260.0f, translateY + 285.0f, 0.0f), COLOR_WHITE, 10);
			break;
		}
		case 3: 
		{
			_text->drawText(TEXT_TAB_ENEMIES, POS_TEXT_ENEMIES, COLOR_RED);

			float translateX = 0.0f, translateY = 100.0f;
			_text->drawText(TEXT_TAB_ENEMIES_TYPETANK, D3DXVECTOR3(translateX + 105.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12, DT_CENTER, 9);
			_text->drawText(TEXT_TAB_ENEMIES_TANKINFO, D3DXVECTOR3(translateX + 260.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12);

			_imageTabEmies->Render(0, D3DXVECTOR3(translateX + 140.0f, translateY + 80.0f, 0.0f));

			_text->drawText(TEXT_TAB_ENEMIES_INFO_BASIC, D3DXVECTOR3(translateX + 260.0f, translateY + 93.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_ENEMIES_INFO_FAST, D3DXVECTOR3(translateX + 260.0f, translateY + 140.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_ENEMIES_INFO_POWER, D3DXVECTOR3(translateX + 260.0f, translateY + 185.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_ENEMIES_INFO_SHEILD, D3DXVECTOR3(translateX + 260.0f, translateY + 235.0f, 0.0f), COLOR_WHITE, 10);

			break;
		}
		case 4:
		{
			_text->drawText(TEXT_TAB_POWER_UP, POS_TEXT_POWER_UP, COLOR_RED);

			float translateX = -100.0f, translateY = 100.0f;
			_text->drawText(TEXT_TAB_ENEMIES_TYPETANK, D3DXVECTOR3(translateX + 105.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12, DT_CENTER, 9);
			_text->drawText(TEXT_TAB_ENEMIES_TANKINFO, D3DXVECTOR3(translateX + 260.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12);

			_imageTabPowerUp->Render(0, D3DXVECTOR3(translateX + 140.0f, translateY + 80.0f, 0.0f));

			_text->drawText(TEXT_TAB_POWER_UP_GRENADE, D3DXVECTOR3(translateX + 258.0f, translateY + 88.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_POWER_UP_HELMET, D3DXVECTOR3(translateX + 258.0f, translateY + 136.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_POWER_UP_TIMER, D3DXVECTOR3(translateX + 258.0f, translateY + 179.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_POWER_UP_TANK, D3DXVECTOR3(translateX + 260.0f, translateY + 235.0f, 0.0f), COLOR_WHITE, 10);
			_text->drawText(TEXT_TAB_POWER_UP_STAR, D3DXVECTOR3(translateX + 258.0f, translateY + 278.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 3);

			break;
		}
		case 5:
		{
			_text->drawText(TEXT_TAB_ENVIRONMENT, POS_TEXT_ENVIRONMENT, COLOR_RED);

			float translateX = -100.0f, translateY = 100.0f;
			_text->drawText(TEXT_TAB_ENEMIES_TYPETANK, D3DXVECTOR3(translateX + 105.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12, DT_CENTER, 9);
			_text->drawText(TEXT_TAB_ENEMIES_TANKINFO, D3DXVECTOR3(translateX + 260.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12);

			_imageTabEnvironment->Render(0, D3DXVECTOR3(translateX + 140.0f, translateY + 80.0f, 0.0f));

			_text->drawText(TEXT_TAB_ENVIRONMENT_BRICK, D3DXVECTOR3(translateX + 258.0f, translateY + 88.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_ENVIRONMENT_STEEL, D3DXVECTOR3(translateX + 258.0f, translateY + 136.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_ENVIRONMENT_TREES, D3DXVECTOR3(translateX + 258.0f, translateY + 179.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_ENVIRONMENT_WATER, D3DXVECTOR3(translateX + 260.0f, translateY + 235.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);
			_text->drawText(TEXT_TAB_ENVIRONMENT_ICE, D3DXVECTOR3(translateX + 258.0f, translateY + 278.0f, 0.0f), COLOR_WHITE, 10, 0, 0, 2);

			break;
		}
	}
		

}

void Instruction::reset()
{
	_currentTab = 1;
}

Instruction* Instruction::get()
{
	if (_instance == nullptr)
		_instance = new Instruction();

	return _instance;
}

#pragma endregion


#pragma region Starting

StartingState* StartingState::_instance = nullptr;

StartingState::StartingState()
{	
	_spriteHandler->GetDevice(&_d3ddevice);
	_delayTime = 5000;
}

StartingState::~StartingState()
{
	SAFE_RELEASE(_d3ddevice);
}

void StartingState::update()
{
	//dem du thoi gian roi thi chuyen qua playing state
	if (GameTime::DelayTime(_delayTime))
	{
		_delayTime = 5000;
		switchState(PlayingState::get());
	}
}

void StartingState::draw()
{
	_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(99,99,99), 1.0f, 0);
	_text->drawText("STAGE " + to_string(StageManager::getInstance()->getStage()), IMAGE_STATE_POS , COLOR_BLACK);
}

void StartingState::reset()
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

void PlayingState::reset()
{
	_map->reset();
}

PlayingState::~PlayingState()
{
	SAFE_RELEASE(_map);
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
	_delayTime = 10000;
	_iconTankScore = new Sprite(_spriteHandler, ICON_TANK_SCORE_PATH, 48, 176, 1, 1);
	ScoreState::reset();
}

void ScoreState::update()
{
	if (GameTime::DelayTime(_delayTime))
	{
		_delayTime = 10000;
		ScoreManager::getInstance()->renewValue();
		if (_isEnd)
		{
			GameState::switchState(GameOverState::get());
		}
		else
		{

			if (StageManager::getInstance()->getStage() > DEFAULT_MAX_STAGE)
			{
				GameState::switchState(EndGame::get());
			}
			else
			{
				
				GameState::switchState(StartingState::get());
			}
		}
	}
}

void ScoreState::draw()
{
	_text->drawText("HI-SCORE", POS_HI_SCORE, COLOR_HIGHSCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getHighScore()), POS_HI_SCORE_VALUE, COLOR_SCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText("STAGE", POS_STAGE_TEXT, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(StageManager::getInstance()->getStage() - 1), POS_STAGE_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText("PLAYER", POS_PLAYER_TEXT, COLOR_HIGHSCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getPlayerScore()), POS_PLAYER_VALUE, COLOR_SCORE_TEXT, TEXT_SIZE_SCORE_STATE,DT_CENTER,6);
	_iconTankScore->Render(POS_ICON_TANK_SCRORE_STATE);
	float a = BEGIN_X;
	
	for (int i = 0; i < NUM_TYPE_ENEMY;i++)
	{
		_text->drawText(to_string(ScoreManager::getInstance()->getScoreTank(i)), D3DXVECTOR3(SCORE_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE, DT_RIGHT, 4);
		_text->drawText("PTS", D3DXVECTOR3(PTS_POS_X,a , 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
		_text->drawText(to_string(ScoreManager::getInstance()->getNumTank(i)), D3DXVECTOR3(NUM_TANK_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE,DT_RIGHT,2);
		a += DISTANCE_LINE;
	}
	_text->drawText("______", POS_LINE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText("TOTAL", POS_TOTAL_TEXT, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getNumTank()), POS_TOTAL_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE,DT_RIGHT,2);
}

void ScoreState::reset()
{
	_isEnd = false;
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

ScoreState::~ScoreState()
{
	SAFE_RELEASE(_iconTankScore);
}

#pragma endregion


#pragma region GameOverState 
GameOverState* GameOverState::_instance = nullptr;

GameOverState::GameOverState()
{
	_gameOverImage = new Sprite(_spriteHandler, ICON_END_GAME_PATH, 324, 211, 1, 1);
	_delayTime = 10000;
}

void GameOverState::update()
{
	if(GameTime::DelayTime(_delayTime))
	{
		_delayTime = 10000;
		switchState(MainMenu::get());
	}	
}

void GameOverState::draw()
{
	//Draw game over picture
	_gameOverImage->Render(POS_ICON_END);
}

void GameOverState::reset()
{
}

GameOverState* GameOverState::get()
{
	if (_instance == nullptr)
	{
		_instance = new GameOverState();
	}

	return _instance;
}

GameOverState::~GameOverState()
{
	SAFE_RELEASE(_gameOverImage);
}
#pragma endregion

#pragma region End State 
EndGame* EndGame::_instance = nullptr;

EndGame::EndGame()
{
	_delayTime = 10000;
	_arrayColor[0] = COLOR_RED;
	_arrayColor[1] = COLOR_YELLOW;
	_arrayColor[2] = COLOR_GREEN;
	_arrayColor[3] = COLOR_BLUE;
	_arrayColor[4] = COLOR_WHITE;
	EndGame::reset();
}

void EndGame::update()
{
	_score = ScoreManager::getInstance()->getPlayerScore();
	if (GameTime::DelayTime(_delayTime))
	{
		_delayTime = 10000;
		_isFlash = true;
	}
	if(_colorIndex > 4)
	{
		_colorIndex = 0;
	}
	_congraColor = _arrayColor[_colorIndex];
	_colorIndex++;
	if (Keyboard::getInstance()->getKeyState(DIK_ESCAPE) == KEY_PRESS)
	{
		//reset player, score, stage, main menu, noi chung la het cac stage
		StageManager::getInstance()->reset();
		ScoreManager::getInstance()->reset();
		MainMenu::get()->reset();
		Instruction::get()->reset();
		PlayingState::get()->reset();
		ScoreState::get()->reset();
		/*EndGame::get()->*/reset();
		switchState(MainMenu::get());	
	}
}

void EndGame::draw()
{
	_text->drawText("CONGRATULATION", D3DXVECTOR3(40.0f, 130.0f, 0.0f), _congraColor, 40);
	_text->drawText("You have successfully defended the fortress \nfrom the attack of enemy tanks. You are a tank \ncommander of the best. We are very proud of you.", D3DXVECTOR3(50.0f, 230.0f, 0.0f), COLOR_SCORE_TEXT, 12,0,0,4);
	_text->drawText("Your score: ", D3DXVECTOR3(50.0f, 300.0f, 0.0f), COLOR_SCORE_TEXT, 12);
	_text->drawText(to_string(_score), D3DXVECTOR3(200.0f, 300.0f, 0.0f), COLOR_RED, 14);
	if(_isFlash)
	{
		_text->drawText("Press ESC to return Main menu", D3DXVECTOR3(330.0f, 545.0f, 0.0f), COLOR_WHITE, 10);
	}	
}

void EndGame::reset()
{
	_isFlash = false;
	_congraColor = COLOR_WHITE;
	_colorIndex = 0;
}

EndGame* EndGame::get()
{
	if (_instance == nullptr)
	{
		_instance = new EndGame();
	}

	return _instance;
}

EndGame::~EndGame()
{

}

#pragma endregion
