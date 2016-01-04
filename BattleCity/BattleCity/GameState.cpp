#include "GameState.h"

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
	//Xoa bien ve chu va release doi tuong ve SpriteHandler, cac bien singletton con lai he dieu hanh tu don
	SAFE_RELEASE(_text);
	if (_spriteHandler)
		_spriteHandler->Release();
}


void GameState::stateUpdate()
{
	_gameState->update();
}

//----------------------------------
// Chuyen qua lai giua cac state
//----------------------------------
void GameState::switchState(GameState* newState)
{
	_gameState = newState;
}


void GameState::stateDraw()
{
	_gameState->draw();
}

//----------------------------------
// Cap nhat trang thai game
//----------------------------------
void GameState::update()
{

}

//----------------------------------
// Ve game len man hinh
//----------------------------------
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
	_delayTime = SELECTOR_SPEED_CHANGE;
	MainMenu::reset();

}

MainMenu::~MainMenu()
{
	SAFE_RELEASE(_menuImage);
	SAFE_RELEASE(_selector);
	
}

void MainMenu::update()
{
	if (_posYMenu > 0)	//kiem tra xem menu da chay len xong chua, neu cua thi tiep tuc chay
	{
		_posYMenu -= IMAGE_MAIN_MENU_GAME_DEFAULT_SPEED_UP;
		if (Keyboard::getInstance()->getKeyState(DIK_RETURN) == KeyState::KEY_PRESS)	//neu nhan Enter thi skip ko cho nua, hien ra luon
		{
			_posYMenu = 0;
		}
	}
	else
	{
		//tao selector chuyen dong
		if (GameTime::DelayTime(_delayTime))
		{
			_delayTime = SELECTOR_SPEED_CHANGE;
			_selector->Next();
		}
		if (Keyboard::getInstance()->IsKeyDown(DIK_DOWN))	//Chuyen xuong instruction
		{
			_selectorPosition = IMAGE_SELECTOR_POS_INSTRUCTION;
		}
		if (Keyboard::getInstance()->IsKeyDown(DIK_UP))		//Chuyen len Play
		{
			_selectorPosition = IMAGE_SELECTOR_POS_PLAY;
		}
		if (Keyboard::getInstance()->getKeyState(DIK_RETURN) == KeyState::KEY_PRESS) //Nh?n Enter -> enter State
		{
			if (_selectorPosition == IMAGE_SELECTOR_POS_PLAY)
			{
				ScoreManager::getInstance()->reset();	//Reset diem truoc khi bat dau choi moi
				switchState(StartingState::get());		//Play
			}
			else
			{
				switchState(Instruction::get());		//Instruction
			}
		}
	}
}

void MainMenu::draw()
{

	if (_posYMenu <= 0) //Neu menu da chay len xong, ve selector 
	{
		_selector->Render((int)_selectorPosition.x, (int)_selectorPosition.y);
	}
	//Ve cac text len man hinh
	float translateX = 0.0f, translateY = 0.0f;	//bien dung de dich chuyen menu neu can
	_menuImage->Render(0, D3DXVECTOR3(translateX + 70.0f, _posYMenu + translateY + 110.0f, 0.0f)); //70, 110
	_text->drawText(TEXT_PlAYER_SCORE, D3DXVECTOR3(translateX + 45.0f, _posYMenu + translateY + 58.0f, 0.0f), COLOR_WHITE, 20);
	_text->drawText(TEXT_HI_SCORE, D3DXVECTOR3(translateX + 237.0f, _posYMenu + translateY + 58.0f, 0.0f), COLOR_WHITE, 20);
	//Ve diem cua nguoi choi truoc
	_text->drawText(to_string(ScoreManager::getInstance()->getPlayerScore()), D3DXVECTOR3(translateX + 87.0f, _posYMenu + translateY + 58.0f, 0.0f), COLOR_WHITE, 20, DT_RIGHT, 6); //I-
																																													//ve diem cao nhat
	_text->drawText(to_string(ScoreManager::getInstance()->getHighScore()), D3DXVECTOR3(translateX + 304.0f, _posYMenu + translateY + 58.0f, 0.0f), COLOR_WHITE, 20, DT_RIGHT, 6);  //HI-
	_text->drawText(TEXT_PLAY, D3DXVECTOR3(translateX + 240.0f, _posYMenu + translateY + 310.0f, 0.0f), COLOR_WHITE, 20);
	_text->drawText(TEXT_INSTRUCTION, D3DXVECTOR3(translateX + 240.0f, _posYMenu + translateY + 344.0f, 0.0f), COLOR_WHITE, 20);
	_text->drawText(TEXT_SE_UIT, D3DXVECTOR3(translateX + 270.0f, _posYMenu + translateY + 417.0f, 0.0f), COLOR_RED, 20);
	_text->drawText(TEXT_ABOUT, D3DXVECTOR3(translateX + -70.0f, _posYMenu + translateY + 454.0f, 0.0f), COLOR_WHITE, 20, DT_CENTER, 0, 2);
}

//----------------------------------
// Reset lai trang thai mac dinh cua menu
//----------------------------------
void MainMenu::reset()
{
	_posYMenu = MAIN_MENU_GAME_DEFAULT_POS_Y;
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
	_imageTabControl = new Sprite(_spriteHandler, IMAGE_TAB_CONTROL_PATH, SPRITE_WIDTH, SPRITE_HEIGHT * 7, 1, 1);
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
	//Chuyen qua lai giua cac tab
	if (Keyboard::getInstance()->getKeyState(DIK_RIGHT) == KeyState::KEY_PRESS)
	{
		if (_currentTab < 5)
		{
			_currentTab++;
		}
	}
	if (Keyboard::getInstance()->getKeyState(DIK_LEFT) == KeyState::KEY_PRESS)
	{
		if (_currentTab > 1)
		{
			_currentTab--;
		}
	}
	//Nhan ESC dde thoat
	if (Keyboard::getInstance()->getKeyState(DIK_ESCAPE) == KeyState::KEY_PRESS)
	{
		_currentTab = 1;
		switchState(MainMenu::get());
	}
}

void Instruction::draw()
{
	//ve menu phia tren
	_text->drawText(TEXT_TUT, POS_TUTORIAL, COLOR_WHITE, 10);
	_text->drawText(TEXT_TAB_STORY, POS_TEXT_STORY, COLOR_WHITE);
	_text->drawText(TEXT_TAB_CONTROL, POS_TEXT_CONTROL, COLOR_WHITE);
	_text->drawText(TEXT_TAB_ENEMIES, POS_TEXT_ENEMIES, COLOR_WHITE);
	_text->drawText(TEXT_TAB_POWER_UP, POS_TEXT_POWER_UP, COLOR_WHITE);
	_text->drawText(TEXT_TAB_ENVIRONMENT, POS_TEXT_ENVIRONMENT, COLOR_WHITE);

	switch (_currentTab)
	{
	case 1:	//Tab Story
	{
		_text->drawText(TEXT_TAB_STORY, POS_TEXT_STORY, COLOR_RED);
		_text->drawText(TEXT_INFO_STORY
			, POS_TEXT_INFO_STORY, COLOR_WHITE, 10, 0, 0, 9);
		_imageTabStory->Render(POS_IMAGE_STORY);
		break;
	}
	case 2:	//Tab control
	{
		_text->drawText(TEXT_TAB_CONTROL, POS_TEXT_CONTROL, COLOR_RED);

		float translateX = 100.0f, translateY = 100.0f;
		_text->drawText(TEXT_TAB_CONTROL_ACTION, D3DXVECTOR3(translateX + 105.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12, DT_CENTER, 9);
		_text->drawText(TEXT_TAB_CONTROL_KEY, D3DXVECTOR3(translateX + 260.0f, translateY + 60.0f, 0.0f), COLOR_WHITE, 12);

		_imageTabControl->Render(0, D3DXVECTOR3(translateX + 140.0f, translateY + 80.0f, 0.0f));
		_imageBulletRight->Render(0, D3DXVECTOR3(translateX + 175.0f, translateY + 285.0f, 0.0f));

		_text->drawText(TEXT_TAB_CONTROL_UP, D3DXVECTOR3(translateX + 260.0f, translateY + 93.0f, 0.0f), COLOR_WHITE, 12);
		_text->drawText(TEXT_TAB_CONTROL_RIGHT, D3DXVECTOR3(translateX + 260.0f, translateY + 140.0f, 0.0f), COLOR_WHITE, 10);
		_text->drawText(TEXT_TAB_CONTROL_DOWN, D3DXVECTOR3(translateX + 260.0f, translateY + 185.0f, 0.0f), COLOR_WHITE, 10);
		_text->drawText(TEXT_TAB_CONTROL_LEFT, D3DXVECTOR3(translateX + 260.0f, translateY + 235.0f, 0.0f), COLOR_WHITE, 10);
		_text->drawText(TEXT_TAB_CONTROL_SPACE, D3DXVECTOR3(translateX + 260.0f, translateY + 285.0f, 0.0f), COLOR_WHITE, 10);
		break;
	}
	case 3:		//tab enemies
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
	case 4:		//tab power up
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
	case 5:		//tab environment
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
	_delayTime = DELAY_TIME_TO_START_PLAYING_STATE;

}

StartingState::~StartingState()
{
	SAFE_RELEASE(_d3ddevice);
}

void StartingState::update()
{
	//dem du thoi gian roi thi chuyen qua playing state
	if (_delayTime == DELAY_TIME_TO_START_PLAYING_STATE)
		GameSound::getInstance()->Play(ID_SOUND_START_GAME);
	if (GameTime::DelayTime(_delayTime))
	{
		_delayTime = DELAY_TIME_TO_START_PLAYING_STATE;
		//GameSound::getInstance()->Stop(ID_SOUND_START_GAME);
		switchState(PlayingState::get());
	}

}

void StartingState::draw()
{
	_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, COLOR_GRAY, 1.0f, 0); //Clear man hinh sang mau xam trang
	_text->drawText(TEXT_STAGE + to_string(StageManager::getInstance()->getStage()), IMAGE_STATE_POS, COLOR_BLACK);
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
	//map, bullet, player update...
	_map->Update();
}

void PlayingState::draw()
{
	//draw all item in screen	
	_map->Draw();
}

//----------------------------------
// Reset khi choi thua hoac pha dao, chuyen map ve stage 1, player ve standar
//----------------------------------
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
	_delayTime = DELAY_TIME_SCORE;
	_iconTankScore = new Sprite(_spriteHandler, ICON_TANK_SCORE_PATH, 48, 176, 1, 1);
	_numTypeEnemy = 0;
	ScoreState::reset();
}

void ScoreState::update()
{
	if (GameTime::DelayTime(_delayTime))
	{
		_delayTime = DELAY_TIME_SCORE;
		_numTypeEnemy = 0;
		ScoreManager::getInstance()->renewValue();	//Reset gia tri so luong tank moi loai bi ban
		if (_isEnd)
		{
			writeFile(); //Ghi diem cao vao file
			GameState::switchState(GameOverState::get()); //Chuyen den man gameover
		}
		else
		{
			if (StageManager::getInstance()->getStage() > DEFAULT_MAX_STAGE) //Neu choi xong het man
			{
				writeFile();
				GameState::switchState(EndGame::get());	//EndGame
			}
			else
			{
				GameState::switchState(StartingState::get()); //Choi stage tiep theo
			}
		}
	}
}

//-------------
// Vi li do chuyen map ngay khi ket thuc playing state nen so stage phai dc - 1
//----------
void ScoreState::draw()
{
	_text->drawText(TEXT_HISCORE, POS_HI_SCORE, COLOR_HIGHSCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getHighScore()), POS_HI_SCORE_VALUE, COLOR_SCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(TEXT_STAGE, POS_STAGE_TEXT, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(StageManager::getInstance()->getStage() - !_isEnd), POS_STAGE_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(TEXT_PLAYER, POS_PLAYER_TEXT, COLOR_HIGHSCORE_TEXT, TEXT_SIZE_SCORE_STATE);
	_text->drawText(to_string(ScoreManager::getInstance()->getPlayerScore()), POS_PLAYER_VALUE, COLOR_SCORE_TEXT, TEXT_SIZE_SCORE_STATE, DT_CENTER, 6);
	_iconTankScore->Render(POS_ICON_TANK_SCRORE_STATE);
	_text->drawText(TEXT_LINE, POS_LINE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
	_text->drawText(TEXT_TOTAL, POS_TOTAL_TEXT, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);

	float a = BEGIN_X;
	if (_delayTime % DELAY_TIME_DRAW_SCORE == 0)
	{
		if (_numTypeEnemy < NUM_TYPE_ENEMY)
		{
			_numTypeEnemy++;	
			GameSound::getInstance()->Play(ID_SOUND_COUNT_SCORE);
		}
	}
	for (int i = 0; i < _numTypeEnemy; i++)
	{
		_text->drawText(to_string(ScoreManager::getInstance()->getScoreTank(i)), D3DXVECTOR3(SCORE_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE, DT_RIGHT, 4);
		_text->drawText(TEXT_PTS, D3DXVECTOR3(PTS_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
		_text->drawText(to_string(ScoreManager::getInstance()->getNumTank(i)), D3DXVECTOR3(NUM_TANK_POS_X, a, 0.0f), COLOR_WHITE, TEXT_SIZE_SCORE_STATE, DT_RIGHT, 2);
		a += DISTANCE_LINE;
	}
	if(_delayTime <= DELAY_TIME_DRAW_SCORE)
	{
		_text->drawText(to_string(ScoreManager::getInstance()->getNumTank()), POS_TOTAL_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE, DT_RIGHT, 2);
	}
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

//----------------------------------
// Set Next State la GameOver
//----------------------------------
void ScoreState::setEndAfter(bool isEnd)
{
	_isEnd = isEnd;
}

//----------------------------------
// Ghi diem cao nhat vao file txt
//----------------------------------
void ScoreState::writeFile()
{
	ofstream myfile(FILE_HI_SCORE_PATH);
	if (myfile.is_open())
	{
		myfile << ScoreManager::getInstance()->getHighScore();
		myfile.close();
	}
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
	_gameOverImage = new Sprite(_spriteHandler, ICON_GAME_OVER_PATH, ICON_GAME_OVER_WIDTH, ICON_GAME_OVER_HEIGHT, 1, 1);
	_delayTime = DELAY_TIME_GAMEOVER;
}

void GameOverState::update()
{
	if (_delayTime == DELAY_TIME_GAMEOVER)
		GameSound::getInstance()->Play(ID_SOUND_GAME_OVER);
	if (GameTime::DelayTime(_delayTime))
	{
		_delayTime = DELAY_TIME_GAMEOVER;
		//reset player, score, stage, main menu, noi chung la het cac state
		StageManager::getInstance()->reset();
		MainMenu::get()->reset();
		PlayingState::get()->reset();
		ScoreState::get()->reset();
		/*EndGame::get()->*/reset();
		switchState(MainMenu::get());
	}
}

void GameOverState::draw()
{
	//Draw game over picture
	_gameOverImage->Render(POS_ICON_GAME_OVER);
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
		_isFlash = true;
	}
	if (_colorIndex > 4)
	{
		_colorIndex = 0;
	}
	_congraColor = _arrayColor[_colorIndex];
	_colorIndex++;
	if (Keyboard::getInstance()->getKeyState(DIK_ESCAPE) == KEY_PRESS)
	{
		//reset player, score, stage, main menu, noi chung la het cac state
		StageManager::getInstance()->reset();
		MainMenu::get()->reset();
		PlayingState::get()->reset();
		ScoreState::get()->reset();
		/*EndGame::get()->*/reset();
		switchState(MainMenu::get());
	}
}

void EndGame::draw()
{
	_text->drawText(TEXT_CONGRA, D3DXVECTOR3(40.0f, 130.0f, 0.0f), _congraColor, 40);
	_text->drawText(TEXT_DESC, D3DXVECTOR3(50.0f, 230.0f, 0.0f), COLOR_SCORE_TEXT, 12, 0, 0, 4);
	_text->drawText(TEXT_YOUR_SCORE, D3DXVECTOR3(50.0f, 300.0f, 0.0f), COLOR_SCORE_TEXT, 12);
	_text->drawText(to_string(_score), D3DXVECTOR3(200.0f, 300.0f, 0.0f), COLOR_RED, 14);
	if (_isFlash)
	{
		_text->drawText(TEXT_ESC, D3DXVECTOR3(330.0f, 545.0f, 0.0f), COLOR_WHITE, 10);
	}
}

void EndGame::reset()
{
	_isFlash = false;
	_congraColor = COLOR_WHITE;
	_colorIndex = 0;
	_delayTime = DELAY_TIME_GAME_END;
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