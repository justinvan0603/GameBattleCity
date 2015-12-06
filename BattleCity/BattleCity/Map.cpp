#include "Map.h"
#include <complex>
#include "GameState.h"
#include "MediumTank.h"
#include "HeavyTank.h"
#include "SuperHeavyTank.h"
#include "BulletManager.h"
#include "EffectManager.h"
Map::Map(LPD3DXSPRITE spriteHandler)
{
	delayEndStage = 5000;
	delaytimeReSpanw = 0;
	isPrepareRespawn = false;
	//
	_startTime = GetTickCount();
	_mapMatrix = new int*[NUM_ROW_TILE];
	_steelBoundEagle = false;
	_canUpdateEnemy = true;
	_numEnemy = 0;
	_spriteHandler = spriteHandler;
	_spriteHandler->GetDevice(&d3ddev);
	_spriteItemManager = new SpriteMapItemMagager(_spriteHandler);
	_eagle = new Eagle(_spriteItemManager->getEagleSprite(), getPositionFromMapMatrix(POS_EAGLE_IN_MATRIX_X, POS_EAGLE_IN_MATRIX_Y));
	_powerUpItem = new PowerUp(_spriteItemManager->getPowerUpItem());
	_respawnEffect = _spriteItemManager->getRespawnSprite();
	_player = new PlayerTank(_spriteHandler);
	_listEnemy = new vector<Enemy*>;
	_listEnemyOnMap = new vector<Enemy*>;
	_colisObj = new vector<vector<StaticObject*>>;

	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		_mapMatrix[i] = new int[NUM_COLUMN_TILE];
	}
	changeStage();
}


void Map::changeStage()
{
	string stringLine;
	int i, j;	
	if (!GetFileMap())
		return;
	//read matrix map
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
	InitListEnemy();
	 
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
			//chua lam water
			
			if (type == 0 || type == 1 || type == 10 || type == 11)
				temp[type].push_back(new BrickWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if(type == 2 || type == 3 || type == 12 || type == 13)
			{
				temp[type].push_back(new SteelWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
				/*if(i < 46)
				{
					_lastIndexofSteel = _mapMatrix[i][j] / 100;
				}
				if(i==46)
				{
					if(j < 22)
					{
						_lastIndexofSteel = _mapMatrix[i][j] / 100;
					}
				}*/
					
			}
		}
	}
	for (int i = 0; i < 20;i++)
		_colisObj->push_back(temp[i]);
}

void Map::InitListEnemy()
{
	//a[] & order 
	//0 - medium tank
	//1 - light tank
	//2 - heavy  tank
	//3 - super heavy tank
	int a[4] = { 7,6,4,3 };
	//Thu tu xuat hien cac loai tank 
	string order = "0123"; //Neu thay yeu cau random thi viet them ham random
	float distance = 0.0f;
	int num = 1;
	vector<MediumTank*>* listMedium = new vector<MediumTank*>;
	vector<LightTank*>* listLight = new vector<LightTank*>;
	vector<HeavyTank*>* listHeavy = new vector<HeavyTank*>;
	vector<SuperHeavyTank*>* listSuper = new vector<SuperHeavyTank*>;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (distance > MAX_RESPAWN_POS_X)
			distance = 0.0f;
		if(a[ID_MEDIUM_TANK] > 0)
		{
			MediumTank* temp;
			temp = new MediumTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			a[ID_MEDIUM_TANK] -= 1;
			if(num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listMedium->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if(a[ID_LIGHT_TANK] > 0)
		{
			LightTank* temp;
			temp = new LightTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			a[ID_LIGHT_TANK] -= 1;
			if (num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listLight->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (a[ID_HEAVY_TANK] > 0)
		{
			HeavyTank* temp;
			temp = new HeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			a[ID_HEAVY_TANK] -= 1;
			if (num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listHeavy->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (a[ID_SUPER_HEAVY_TANK] > 0)
		{
			SuperHeavyTank* temp;
			temp = new SuperHeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			a[ID_SUPER_HEAVY_TANK] -= 1;
			if (num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listSuper->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
		}
	}
	int i = 0;
	while(i<NUM_TYPE_ENEMY)
	{
		switch (order[i] - '0')
		{
			case ID_MEDIUM_TANK:
			{
				int n = listMedium->size();
				for (int j = 0; j < n;j++)
				{
					_listEnemy->push_back(listMedium->at(j));
				}				
				break;
			}
			case ID_LIGHT_TANK:
			{
				int n = listLight->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listLight->at(j));
				}
				break;
			}
			case ID_HEAVY_TANK:
			{
				int n = listHeavy->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listHeavy->at(j));
				}
				break;
			}
			case ID_SUPER_HEAVY_TANK:
			{
				int n = listSuper->size();
				for (int j = 0; j < n; j++)
				{
					_listEnemy->push_back(listSuper->at(j));
				}
				break;
			}
		}
		i++;
	}
	

}


void Map::updateMaxtrix()
{
	//muon cho gach nam phia duoi ngang bang dai bang thi hay luu index cua steel truoc dong 46 cot 22
	int type;
	for (int i = 46; i < 52;i++)
	{
		for (int j = 22; j < 52;j++)
		{
			type = _mapMatrix[i][j] % 100;

		}
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
	else
		return true;
}

void Map::Draw()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(99,99,99), 1.0f, 0);
	drawRightMenu();
	drawMap();
	_player->Draw();
	drawPowerUp();
	drawEnemy();
	BulletManager::getInstance()->Draw();
	EffectManager::getInstance(0)->Draw();
}

void Map::drawMap()
{
	//ve map
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		for (short j = 0; j < NUM_COLUMN_TILE; j++)
		{
			if (_mapMatrix[i][j] == -1)
			{
				_spriteItemManager->getBackGround()->Render(0, 0, getPositionFromMapMatrix(i, j));
			}
		}
	}
	int n = _colisObj->size();
	for (int i = 0; i < n; i++)
	{
		int m = _colisObj->at(i).size();
		for (int j = 0; j < m; j++)
		{
			if (_colisObj->at(i).at(j) != NULL)
				_colisObj->at(i).at(j)->Draw();
		}
	}
	_eagle->Draw();
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
		//ve tuong thep, 
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
	float x, y = 0;
	int num_enemy = MAX_ENEMY - _numEnemy;
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
	static Text text = Text(_spriteHandler);
	text.drawText (to_string(StageManager::getInstance()->getStage()),POS_NUM_LEVEL,COLOR_BLACK,20);
	text.drawText(to_string(_player->getLife()), POS_NUM_LIFE, COLOR_BLACK, 17);
}

void Map::Update()
{
	if (Keyboard::getInstance()->IsKeyDown(DIK_1))
	{
		_powerUpItem->enablePowerUp();
	}
	updatePowerItem();
	_player->Update();
	updateEnemy();
	BulletManager::getInstance()->Update();
	
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n-1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			CollisionManager::CollisionEnemy(_listEnemyOnMap->at(i), _listEnemyOnMap->at(j));
		}
	}
	for (int i = 0; i < n; i++)
	{
		CollisionManager::CollisionChangeDirection(_player, _listEnemyOnMap->at(i));
	}

	for (int i = 0; i < n; i++)
	{
		BulletManager::getInstance()->UpdateCollisionWithDynamicObject(_player, _listEnemyOnMap->at(i));
	}

	CollisionManager::CollisionWithItem(_player, _powerUpItem);

	ClearDestroyedEnemy();
	checkEndGame();
}

void Map::updateEnemy()
{
	if(_listEnemyOnMap->size() < MAX_ENEMY_ONE_TIME && _listEnemy->size() >= 1)
	{
		if(_numEnemy == 0)
		{
			respawnAfter(1000);
		}
		else
		{
			respawnAfter(6000);
		}
	}
	int n = _listEnemyOnMap->size();
	for (int i = 0; i < n; i++)
	{
		_listEnemyOnMap->at(i)->Update();
	}
}

void Map::respawnAfter(int delaytime)
{
	delaytimeReSpanw += 50;
	if(delaytime == 1000)
	{
		isPrepareRespawn = true;
	}
	else
	{
		if(delaytimeReSpanw >4000)
		{
			isPrepareRespawn = true;
		}
	}
	if (delaytimeReSpanw > delaytime)
	{
		isPrepareRespawn = false;
		delaytimeReSpanw = 0;
		_listEnemyOnMap->push_back(_listEnemy->front());
		_listEnemy->erase(_listEnemy->begin());
		_numEnemy++;
	}
}


void Map::updatePowerItem()
{
	if (_powerUpItem->IsEnable())
	{
		if (_powerUpItem->IsEaten())
		{
			if (_powerUpItem->getType() == ID_POWER_FREEZE_TIME || _powerUpItem->getType() == ID_POWER_STEELWALL_EAGLE)
			{
				if (_powerUpItem->getType() == ID_POWER_FREEZE_TIME)
				{
					_canUpdateEnemy = false;
				}
				else
				{
					_steelBoundEagle = true;
				}
			}
			else
			{
				if (_powerUpItem->getType() == ID_POWER_BOMB)
				{
					//cho quai no
				}
				if (_powerUpItem->getType() == ID_POWER_SHEILD)
				{
					_player->ActivateShield();
				}
				if (_powerUpItem->getType() == ID_POWER_EXTRA_LIFE)
				{
					_player->addLife();
				}
				if (_powerUpItem->getType() == ID_POWER_STAR)
				{
					_player->PlayerPromoted();
				}
				_powerUpItem->disablePowerUp();
			}
		}
	}
}

void Map::checkEndGame()
{
	if (_player->getLife() == 0)
	{
		ScoreState::get()->setEndAfter(true);
		GameState::switchState(ScoreState::get());
		return;
	}

  	if (_numEnemy == 20 && _listEnemyOnMap->size() == 0)
	{
		if (GameTime::DelayTime(delayEndStage))
		{
			if (_player->getLife() == 0)
			{
				ScoreState::get()->setEndAfter(true);
			}
			else
			{
				//changeStage();
			}
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