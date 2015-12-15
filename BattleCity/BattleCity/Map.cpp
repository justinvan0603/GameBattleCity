#include "Map.h"
#include <complex>
#include "GameState.h"
#include "MediumTank.h"
#include "HeavyTank.h"
#include "SuperHeavyTank.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "Water.h"
#include "Trees.h"
#include "Ice.h"
#include "StageManager.h"
#include "LightTank.h"
#include "SteelWall.h"
#include "GameSound.h"

Map::Map(LPD3DXSPRITE spriteHandler)
{
	//init rectangleRespawn
	_rectangleRespawn = new vector<MyRectangle*>;
	for (int i = 0; i < NUM_RESPAWN_POS;i++)
	{
		_rectangleRespawn->push_back(new MyRectangle(POS_RESPAWN_Y, POS_RESPAWN_X + i*DISTANCE_RESPAWN_POS_X, SPRITE_WIDTH, SPRITE_WIDTH, 0, 0));
	}	
	_spriteHandler = spriteHandler;
	_spriteHandler->GetDevice(&d3ddev);
	_text = new Text(_spriteHandler);
	_spriteItemManager = new SpriteMapItemMagager(_spriteHandler);
	_powerUpItem = new PowerUp(_spriteItemManager->getPowerUpItem());
	_respawnEffect = _spriteItemManager->getRespawnSprite();
	_eagle = new Eagle(_spriteItemManager->getEagleSprite(), getPositionFromMapMatrix(POS_EAGLE_IN_MATRIX_X, POS_EAGLE_IN_MATRIX_Y));
	_player = new PlayerTank(_spriteHandler);
	_listEnemy = new vector<Enemy*>;
	_listEnemyOnMap = new vector<Enemy*>;
	_mapMatrix = new int*[NUM_ROW_TILE];
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		_mapMatrix[i] = new int[NUM_COLUMN_TILE];
	}
	BulletManager::getInstance();
	EffectManager::getInstance(_spriteHandler);
	changeStage();
}


void Map::changeStage()
{
	//
	_colisObj = new vector<vector<StaticObject*>>;
	posGameOverText = POS_START_GAMEOVER;
	delaytimeReSpanw = DEFINE_ZERO_VALUE;
	delayEndStage = DELAY_TIME_END_PLAYING_STATE;
	isPrepareRespawn = false;
	_maxEnemy = MAX_ENEMY;
	_numEnemy = DEFINE_ZERO_VALUE;
	_startTime = GetTickCount();
	_delayFreeze = DELAY_FREEZE_TIME;
	_delayDrawScorePower = DELAY_TIME_DRAW_SCORE_POWER;
	_isFreeze = false;
	//
	int numOfTypeEnemy[NUM_TYPE_ENEMY];
	string orderAppear;
	string stringLine;
	int tempMaxEnemy;
	if (!GetFileMap())
		return;
	getline(_mapFile, stringLine);
	tempMaxEnemy = std::stoi(stringLine);
	_maxEnemy = tempMaxEnemy;
	for (int i = 0; i < NUM_TYPE_ENEMY;i++)
	{
		getline(_mapFile, stringLine);
		numOfTypeEnemy[i] = std::stoi(stringLine);
	}
	getline(_mapFile, stringLine);
	orderAppear = stringLine;
	//read matrix map
	int i, j;
	i = 0;
	while (!_mapFile.eof())
	{
		j = 0;
		getline(_mapFile, stringLine);
		stringstream ss(stringLine);
		string token;
		while (getline(ss, token, ','))
		{
			_mapMatrix[i][j] = std::stoi(token);
			j++;
		}
		i++;
	}
	InitColisObject();
	_mapFile.close();
	_player->InitMapData(_mapMatrix, _colisObj);
	InitListEnemy(numOfTypeEnemy,orderAppear);
	_powerUpItem->setmap(_mapMatrix);
}

void Map::InitColisObject()
{
	vector<StaticObject*> temp[MAP_NUM_OF_TYPE_OBJ];
	int type;
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		for (short j = 0; j < NUM_COLUMN_TILE; j++)
		{
			type = _mapMatrix[i][j] % 100;

			if (type == ID_BRICKWALL_0 || type == ID_BRICKWALL_1 || type == ID_BRICKWALL_10 || type == ID_BRICKWALL_11)
				temp[type].push_back(new BrickWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if(type == ID_STEELWALL_2 || type == ID_STEELWALL_3 || type == ID_STEELWALL_12 || type == ID_STEELWALL_13)
				temp[type].push_back(new SteelWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == ID_WATER_4 || type == ID_WATER_5 || type == ID_WATER_14 || type == ID_WATER_15)
				temp[type].push_back(new Water(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == ID_TREES_6 || type == ID_TREES_7 || type == ID_TREES_16 || type == ID_TREES_17)
				temp[type].push_back(new Trees(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == ID_ICE_8 || type == ID_ICE_9 || type == ID_ICE_18 || type == ID_ICE_19)
				temp[type].push_back(new Ice(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
		}
	}
	for (int i = 0; i < MAP_NUM_OF_TYPE_OBJ;i++)
		_colisObj->push_back(temp[i]);
}

void Map::InitListEnemy(int numOfEnemy[], string order)
{
	//numOfEnemy[]
	//	0 - medium tank
	//	1 - light tank
	//	2 - heavy  tank
	//	3 - super heavy tank
	//order - Thu tu xuat hien cac loai tank 

	float distance = 0.0f;
	bool isBonusTank = false;
	vector<MediumTank*>* listMedium = new vector<MediumTank*>;
	vector<LightTank*>* listLight = new vector<LightTank*>;
	vector<HeavyTank*>* listHeavy = new vector<HeavyTank*>;
	vector<SuperHeavyTank*>* listSuper = new vector<SuperHeavyTank*>;
	for (int i = 0; i < _maxEnemy; i++)
	{
		isBonusTank = false;
		if (i == 3 || i == 10 || i == 17)
		{
			//set tank has powerup
			isBonusTank = true;
		}
		if (distance > MAX_RESPAWN_POS_X)
			distance = 0.0f;
		if(numOfEnemy[ID_MEDIUM_TANK] > 0)
		{
			MediumTank* temp;
			temp = new MediumTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_MEDIUM_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _colisObj);
			listMedium->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if(numOfEnemy[ID_LIGHT_TANK] > 0)
		{
			LightTank* temp;
			temp = new LightTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_LIGHT_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _colisObj);
			listLight->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (numOfEnemy[ID_HEAVY_TANK] > 0)
		{
			HeavyTank* temp;
			temp = new HeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_HEAVY_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _colisObj);
			listHeavy->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (numOfEnemy[ID_SUPER_HEAVY_TANK] > 0)
		{
			SuperHeavyTank* temp;
			temp = new SuperHeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y), isBonusTank);
			numOfEnemy[ID_SUPER_HEAVY_TANK] -= 1;
			temp->InitMapData(_mapMatrix, _colisObj);
			listSuper->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
		}
	}
	int i = 0;
	int n;
	while(i<NUM_TYPE_ENEMY)
	{
		switch (order[i] - '0')
		{
			case ID_MEDIUM_TANK:
			{
				n = listMedium->size();
				for (int j = 0; j < n;j++)
				{
					_listEnemy->push_back(listMedium->front());
					listMedium->erase(listMedium->begin());
				}		
				delete listMedium;
				break;
			}
			case ID_LIGHT_TANK:
			{
				n = listLight->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listLight->front());
					listLight->erase(listLight->begin());
				}
				delete listLight;
				break;
			}
			case ID_HEAVY_TANK:
			{
				n = listHeavy->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listHeavy->front());
					listHeavy->erase(listHeavy->begin());
				}
				delete listHeavy;
				break;
			}
			case ID_SUPER_HEAVY_TANK:
			{
				n = listSuper->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listSuper->front());
					listSuper->erase(listSuper->begin());
				}
				delete listSuper;
				break;
			}
		}
		i++;
	}
}


bool Map::GetFileMap()
{
	string mapPath = MAP_PATH + std::to_string(StageManager::getInstance()->getStage()) + MAP_FILE_EXTENSION;
	_mapFile.open(mapPath, ios::in);
	if (_mapFile.fail())
	{
		WARNING_BOX(WARNING_MAP_FILE_NOT_FOUND);
		return false;
	}
	return true;
}

void Map::Draw()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, COLOR_GREY, 1.0f, 0);
	drawRightMenu();	
	drawMap();
	drawEagle();
	BulletManager::getInstance()->Draw();
	drawIce();
	drawPlayer();
	drawEnemy();
	drawTrees();
	drawPowerUp();
	EffectManager::getInstance(0)->Draw();
	if (_player->getLife() < 0 || _eagle->getEagleStatus() == EAGLE_STATUS::DEAD)
	{
		_text->drawText("GAME\nOVER", posGameOverText, COLOR_RED, 30, DT_CENTER, 0, 2);
	}
}

void Map::drawTrees()
{
	int n = _colisObj->size();
	for (int i = 0; i < n; i++)
	{
		if (_colisObj->at(i).size() != 0)
		{
			if (i != ID_TREES_6 && i != ID_TREES_7 && i != ID_TREES_16 && i != ID_TREES_17)
				continue;
			int m = _colisObj->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_colisObj->at(i).at(j) != NULL)
					_colisObj->at(i).at(j)->Draw();
			}
		}
	}
}

void Map::drawIce()
{
	int n = _colisObj->size();
	for (int i = 0; i < n; i++)
	{
		if (_colisObj->at(i).size() != 0)
		{
			if (i != ID_ICE_8 && i != ID_ICE_9 && i != ID_ICE_18 && i != ID_ICE_19)
				continue;
			int m = _colisObj->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_colisObj->at(i).at(j) != NULL)
					_colisObj->at(i).at(j)->Draw();
			}
		}
	}
}

void Map::drawMap()
{
	//ve map
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		for (short j = 0; j < NUM_COLUMN_TILE; j++)
		{
			int type = _mapMatrix[i][j] % 100;
			if (type == ID_TREES_6 || type == ID_TREES_7 || type == ID_TREES_16 || type == ID_TREES_17 || _mapMatrix[i][j] == -1)
			{
				_spriteItemManager->getBackGround()->Render(0, 0, getPositionFromMapMatrix(i, j));
			}
		}
	}
	int n = _colisObj->size();
	for (int i = 0; i < n; i++)
	{
		if (_colisObj->at(i).size() != 0)
		{
			if (i == ID_TREES_6 || i == ID_TREES_7 || i == ID_TREES_16 || i == ID_TREES_17 ||
				i == ID_ICE_8 || i == ID_ICE_9 || i == ID_ICE_18 || i == ID_ICE_19)
				continue;
			int m = _colisObj->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_colisObj->at(i).at(j) != NULL)
					_colisObj->at(i).at(j)->Draw();
			}
		}
	}
	
}

void Map::drawEagle()
{
	_eagle->Draw();
}

void Map::drawPlayer()
{
	_player->Draw();
}

void Map::drawPowerUp()
{
	if (_powerUpItem->IsEnable())
	{
		if (_powerUpItem->IsEaten() == false)
		{
			if (GameTime::RenderFrame(_startTime, 500))
			{
				_powerUpItem->Draw();
			}
		}
	}
	if (posPower != DEFAULT_POS_ZERO)
	{
		_text->drawText(to_string(SCORE_POWER_UP),posPower,COLOR_WHITE,14);
		if(GameTime::DelayTime(_delayDrawScorePower))
		{
			_delayDrawScorePower = DELAY_TIME_DRAW_SCORE_POWER;
			posPower = DEFAULT_POS_ZERO;
		}
	}
}

void Map::drawEnemy()
{
	if (isPrepareRespawn)
	{
		if(delaytimeReSpanw % 100 == 0)
		{
			_respawnEffect->Render(_listEnemy->front()->getLeft(), _listEnemy->front()->getTop());
			_respawnEffect->Next();
		}
	}
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->Draw();
	}
}

void Map::drawRightMenu()
{
	///////////Draw khung enemy goc phai
	float x, y;
	int num_enemy = _maxEnemy - _numEnemy;
	for (int i = 0; i < num_enemy; i++)
	{
		if (i % 2 == 0)
		{
			x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
		}
		else
		{
			x = POS_LIST_ENEMY_ICON_TOP_LEFT_X + (TILE_WIDTH * 2);
		}
		y = POS_LIST_ENEMY_ICON_TOP_LEFT_Y + (TILE_HEIGHT * 2)*(i / 2);
		_spriteItemManager->getEnemyIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
	}

	//Draw dem so mang
	_spriteItemManager->getTankLifeIcon()->Render(0, 0, POS_LIFE_IMAGE);
	//Draw so thu tu state hien tai
	_spriteItemManager->getFlagIcon()->Render(0, 0, POS_FLAG_LIFE_IMAGE);
	//Ve so
	_text->drawText (to_string(StageManager::getInstance()->getStage()),POS_NUM_LEVEL,COLOR_BLACK,20);
	int life = _player->getLife();
	if (life < 0)
		life = 0;
	_text->drawText(to_string(life), POS_NUM_LIFE, COLOR_BLACK, 17);
}

void Map::Update()
{
	
	_player->Update();
	updateEnemy();
	BulletManager::getInstance()->Update();
	CollisionManager::CollisionPreventMove(_player, _eagle);
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		bool isCollided = CollisionManager::CollisionPreventMove(_listEnemyOnMap->at(i), _eagle);
		if (isCollided)
			break;
	}
	bool isCollision = false;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = i+1; j < n; j++)
		{
	
				isCollision = CollisionManager::CollisionEnemy(_listEnemyOnMap->at(i), _listEnemyOnMap->at(j));
				if (isCollision)
					break;
			
		}
	}
	for (int i = 0; i < n; i++)
	{
		CollisionManager::CollisionChangeDirection(_player, _listEnemyOnMap->at(i));
	}

	if (_eagle->getEagleStatus() == EAGLE_STATUS::LIVE)
	{
		if (n == 0)
			BulletManager::getInstance()->UpdateCollisionWithDynamicObject(_player, _powerUpItem, _eagle);
		for (int i = 0; i < n; i++)
		{
			BulletManager::getInstance()->UpdateCollisionWithDynamicObject(_player, _powerUpItem, _eagle, _listEnemyOnMap->at(i));
		}

	}

	CollisionManager::CollisionWithItem(_player, _powerUpItem);
	updatePowerItem();
	ClearDestroyedEnemy();
	checkEndGame();
}

void Map::updateEnemy()
{
	if (_listEnemyOnMap->size() < MAX_ENEMY_ONE_TIME && _listEnemy->size() >= 1)
	{
		if (_numEnemy == 0)
		{
			respawnAfter(DELAY_TIME_RESPAWN_1000);
		}
		else
		{
			respawnAfter(DELAY_TIME_RESPAWN_4000);
		}
	}
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->Update();
	}
}

bool Map::checkCollisionRespawnArea()
{
	int index;
	for (index = 0; index < NUM_RESPAWN_POS; index++)
	{
		if(_rectangleRespawn->at(index)->getLeft() == _listEnemy->front()->getLeft())
			break;
	}
	int colli = CollisionManager::FindRespawnPosition(_rectangleRespawn, index, _player, _listEnemyOnMap);
	if ( colli != index)
	{
		if(colli != -1)
		{
			_listEnemy->front()->setPositionX(_rectangleRespawn->at(colli)->getLeft());
			return false;
		}
		return true;
	}
	return false;
}

void Map::respawnAfter(int delaytime)
{
	delaytimeReSpanw += 50;
	if(delaytime == DELAY_TIME_RESPAWN_1000)
	{
		isPrepareRespawn = true;
	}
	else
	{
		if(delaytimeReSpanw >(DELAY_TIME_RESPAWN_4000 - DELAY_TIME_RESPAWN_1000))
		{
			isPrepareRespawn = true;
		}
	}
	if (delaytimeReSpanw > delaytime)
	{

		isPrepareRespawn = false;
		delaytimeReSpanw = 0;
		if(checkCollisionRespawnArea())
		{
			return;
		}
		if(_isFreeze)
		{
			_listEnemy->front()->ActivateFreeze();
		}
		_listEnemyOnMap->push_back(_listEnemy->front());
		_listEnemy->erase(_listEnemy->begin());
		_numEnemy++;
		if (_numEnemy == 11 || _numEnemy == 18)
		{
			if (_powerUpItem->IsEnable())
			{
				_powerUpItem->disablePowerUp();
			}
		}
	}
}


void Map::updatePowerItem()
{
	if (_isFreeze)
	{
		if (GameTime::DelayTime(_delayFreeze))
		{
			_delayFreeze = DELAY_FREEZE_TIME;
			_isFreeze = false;
			UnFreezeEnemyOnMap();
		}
		return;
	}
	if (_powerUpItem->IsEnable())
	{
		if (_powerUpItem->IsEaten())
		{

			if (_powerUpItem->getType() == ID_POWER_FREEZE_TIME)
			{
				_isFreeze = true;
				FreezeEnemyOnMap();
			}
			if (_powerUpItem->getType() == ID_POWER_BOMB)
			{
				ClearEnemyOnMap();
			}
			if (_powerUpItem->getType() == ID_POWER_SHEILD)
			{
				_player->ActivateShield(true);
			}
			if (_powerUpItem->getType() == ID_POWER_EXTRA_LIFE)
			{
				_player->addLife();
			}
			if (_powerUpItem->getType() == ID_POWER_STAR)
			{
				_player->PlayerPromoted();
			}
			posPower = D3DXVECTOR3(_powerUpItem->getLeft(), _powerUpItem->getTop(), 0.0f);
			_powerUpItem->disablePowerUp();
		}
	}
}

void Map::checkEndGame()
{
	if (_player->getLife() < 0 || _eagle->getEagleStatus() == EAGLE_STATUS::DEAD)
	{
		if (posGameOverText.y > POS_END_GAMEOVER_Y)
		{
			posGameOverText.y -= 10;
		}
		if (GameTime::DelayTime(delayEndStage))
		{
			CleanStage();
			ScoreState::get()->setEndAfter(true);
			GameState::switchState(ScoreState::get());
			
		}

		return;
	}

  	if (_numEnemy == _maxEnemy && _listEnemyOnMap->size() == 0)
	{
		if (GameTime::DelayTime(delayEndStage))
		{
			CleanStage();
			//if (_player->getLife() < 0)
			//{
			//	ScoreState::get()->setEndAfter(true);
			//}
			//else
			//{
				StageManager::getInstance()->nextStage();
				if (StageManager::getInstance()->getStage() <= DEFAULT_MAX_STAGE)
				{
					changeStage();
				}				
			//}		
			GameState::switchState(ScoreState::get());
		}
	}

}

vector<vector<StaticObject*>>* Map::getColisObject()
{
	return _colisObj;
}

Eagle * Map::getEagleObject()
{
	return _eagle;
}

Map::~Map()
{
}

int** Map::getMapMatrix()
{
	return this->_mapMatrix;
}

D3DXVECTOR3 Map::getPositionFromMapMatrix(int row, int column)
{
	D3DXVECTOR3 vector;
	vector.x = column*TILE_WIDTH + POS_MAP_TOP_LEFT_X;
	vector.y = row*TILE_HEIGHT + POS_MAP_TOP_LEFT_Y;
	vector.z = 0.0f;
	return vector;
}


D3DXVECTOR2 Map::getPositionObjectInMapMatrix(int x, int y)
{
	D3DXVECTOR2 position;
	position.x = (x - POS_MAP_TOP_LEFT_X) / TILE_WIDTH;
	position.y = (y - POS_MAP_TOP_LEFT_Y) / TILE_HEIGHT;
	return position;
}

void Map::ClearDestroyedEnemy()
{
	for (vector<Enemy*>::iterator i = _listEnemyOnMap->begin(); i != _listEnemyOnMap->end();)
	{
		if ((*i)->_isTerminated)
		{
			delete *i;
			*i = NULL;
			i = _listEnemyOnMap->erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Map::ClearStaticObject()
{
	int n = _colisObj->size();
	for (int i = 0; i < n; i++)
	{
		if (_colisObj->at(i).size() != 0)
		{
			int m = _colisObj->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_colisObj->at(i).at(j) != NULL)
				{
					delete _colisObj->at(i).at(j);
					_colisObj->at(i).at(j) = NULL;
				}
			}
		}
	}
	delete _colisObj;
	_colisObj = NULL;
}

void Map::ClearDynamicObject()
{
	int n = _listEnemy->size();
	for (int i = 0; i < n;i++)
	{
		_listEnemy->erase(_listEnemy->begin());
	}
	n = _listEnemyOnMap->size();
	{
		for (int i = 0; i < n;i++)
		{
			_listEnemyOnMap->erase(_listEnemyOnMap->begin());
		}
	}
}

void Map::SetDefaultPositionPlayer()
{
	_player->setPositionX(DEFAULT_PLAYER_POSITION_X);
	_player->setPositionY(DEFAULT_PLAYER_POSITION_Y);
	_player->SetDirection(MoveDirection::UP);
	_player->ActivateShield();
	
}

void Map::ClearEnemyOnMap()
{
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->_isTerminated = true;
		D3DXVECTOR2 pos(_listEnemyOnMap->at(i)->getLeft(), _listEnemyOnMap->at(i)->getTop());
		EffectManager::getInstance()->AddDestroyEffect(pos);
	}
	GameSound::getInstance()->Play(ID_SOUND_TANK_EXPLODE);
}

void Map::FreezeEnemyOnMap()
{
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->ActivateFreeze();
	}
}

void Map::UnFreezeEnemyOnMap()
{
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->DeactivateFreeze();
	}
}

void Map::CleanStage()
{
	ClearStaticObject();
	ClearDynamicObject();
	SetDefaultPositionPlayer();
	BulletManager::getInstance()->ClearAllBullet();
	_powerUpItem->disablePowerUp();
	_eagle->setEagleStatus(EAGLE_STATUS::LIVE);
	_player->TurnOffSound();
}

void Map::reset()
{
	_player->reset();
	changeStage();
}
