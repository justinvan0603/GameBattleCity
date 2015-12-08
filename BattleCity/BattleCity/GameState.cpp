#include "GameState.h"

#include "CollisionManager.h"
#include "EffectManager.h"
#include "BulletManager.h"


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
	BulletManager::getInstance();
	EffectManager::getInstance(_spriteHandler);
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
		if (Keyboard::getInstance()->getKeyState(DIK_RETURN) == KeyState::KEY_PRESS)
		{
			_menuImagePosition.y = 0;
		}
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

#pragma region Instruction
Instruction* Instruction::_instance = nullptr;

Instruction::Instruction()
{
	
}

Instruction::~Instruction()
{
	
}

void Instruction::update()
{
	

}

void Instruction::draw()
{
	
}

Instruction* Instruction::get()
{
	if (_instance == nullptr)
		_instance = new Instruction();

	return _instance;
}

void Instruction::enter()
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
	if (GameTime::RenderFrame(_startTime, 3000))
	{
		switchState(PlayingState::get());
	}
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
	//GameSound::getInstance(0)->PlayRepeat(1);
	
}

void PlayingState::update()
{
	//map, bullet, player update
	
	_map->Update();
	
	//_player->Update();
	//switchState(ScoreState::get());
	//_enemy->Update();
	//CollisionManager::CollisionChangeDirection(_player, _enemy);
	
	//vector<Bullet*> listBullet = _player->getListBullet();
	//for (vector<Bullet*>::iterator i = listBullet.begin(); i != listBullet.end(); i++)
	//{
	//	bool flag = CollisionManager::CollisionBulletWithObject(*i, _enemy);
	//}
	
	
}

void PlayingState::draw()
{
	//draw all item in screen
	
	_map->Draw();
	//_enemy->Draw();
	//_player->Draw();
	

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
	_isEnd = false;
	_delayTime = 10000;
	_iconTankScore = new Sprite(_spriteHandler, ICON_TANK_SCORE_PATH, 48, 176, 1, 1);
}

void ScoreState::update()
{
	if (GameTime::DelayTime(_delayTime))
	{
		ScoreManager::getInstance()->renewValue();
		if (_isEnd)
		{
			GameState::switchState(EndState::get());
		}
		else
		{

			if (StageManager::getInstance()->getStage() == DEFAULT_MAX_STAGE)
			{
				//chuyen toi man hinh congration tu tao sau
				//chuc mung diem cao, end game quay lai tu dau
			}
			else
			{
				StageManager::getInstance()->nextStage();
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
	_text->drawText(to_string(StageManager::getInstance()->getStage()), POS_STAGE_VALUE, COLOR_WHITE, TEXT_SIZE_SCORE_STATE);
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
