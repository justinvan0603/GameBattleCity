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

Map::Map(LPD3DXSPRITE spriteHandler)
{
	delayEndStage = 5000;
	delaytimeReSpanw = 0;
	isPrepareRespawn = false;
	_maxEnemy = MAX_ENEMY;
	//init rectangleRespawn
	_rectangleRespawn = new vector<MyRectangle*>;
	for (int i = 0; i < 3;i++)
	{
		_rectangleRespawn->push_back(new MyRectangle(POS_RESPAWN_Y, POS_RESPAWN_X + i*DISTANCE_RESPAWN_POS_X, SPRITE_WIDTH, SPRITE_WIDTH, 0, 0));
	}
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
	int numOfTypeEnemy[4];
	string orderAppear;
	string stringLine;
	int tempMaxEnemy;
	if (!GetFileMap())
		return;
	getline(_mapFile, stringLine);
	tempMaxEnemy = std::stoi(stringLine);
	if (tempMaxEnemy > _maxEnemy)
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

			if (type == 0 || type == 1 || type == 10 || type == 11)
				temp[type].push_back(new BrickWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if(type == 2 || type == 3 || type == 12 || type == 13)
				temp[type].push_back(new SteelWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == 4 || type == 5 || type == 14 || type == 15)
				temp[type].push_back(new Water(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == 6 || type == 7 || type == 16 || type == 17)
				temp[type].push_back(new Trees(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
			if (type == 8 || type == 9 || type == 18 || type == 19)
				temp[type].push_back(new Ice(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
		}
	}
	for (int i = 0; i < 20;i++)
		_colisObj->push_back(temp[i]);
}

void Map::InitListEnemy(int numOfEnemy[], string order)
{
	//a[]
	//	0 - medium tank
	//	1 - light tank
	//	2 - heavy  tank
	//	3 - super heavy tank
	//order - Thu tu xuat hien cac loai tank 

	float distance = 0.0f;
	int num = 1;
	vector<MediumTank*>* listMedium = new vector<MediumTank*>;
	vector<LightTank*>* listLight = new vector<LightTank*>;
	vector<HeavyTank*>* listHeavy = new vector<HeavyTank*>;
	vector<SuperHeavyTank*>* listSuper = new vector<SuperHeavyTank*>;
	for (int i = 0; i < _maxEnemy; i++)
	{
		if (distance > MAX_RESPAWN_POS_X)
			distance = 0.0f;
		if(numOfEnemy[ID_MEDIUM_TANK] > 0)
		{
			MediumTank* temp;
			temp = new MediumTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			numOfEnemy[ID_MEDIUM_TANK] -= 1;
			if(num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listMedium->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if(numOfEnemy[ID_LIGHT_TANK] > 0)
		{
			LightTank* temp;
			temp = new LightTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			numOfEnemy[ID_LIGHT_TANK] -= 1;
			if (num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listLight->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (numOfEnemy[ID_HEAVY_TANK] > 0)
		{
			HeavyTank* temp;
			temp = new HeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			numOfEnemy[ID_HEAVY_TANK] -= 1;
			if (num == 4 || num == 11 || num == 18)
			{
				//set tank has powerup
			}
			temp->InitMapData(_mapMatrix, _colisObj);
			listHeavy->push_back(temp);
			distance += DISTANCE_RESPAWN_POS_X;
			continue;
		}
		if (numOfEnemy[ID_SUPER_HEAVY_TANK] > 0)
		{
			SuperHeavyTank* temp;
			temp = new SuperHeavyTank(_spriteHandler, D3DXVECTOR2(POS_RESPAWN_X + distance, POS_RESPAWN_Y));
			numOfEnemy[ID_SUPER_HEAVY_TANK] -= 1;
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
	drawEnemy();
	drawTrees();
	drawPowerUp();
	BulletManager::getInstance()->Draw();
	EffectManager::getInstance(0)->Draw();
}

void Map::drawTrees()
{
	int n = _colisObj->size();
	for (int i = 0; i < n; i++)
	{
		if (_colisObj->at(i).size() != 0)
		{
			if (_colisObj->at(i).at(0)->getId() != ID_TREES)
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
			if (_mapMatrix[i][j] == -1)
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
			if (_colisObj->at(i).at(0)->getId() == ID_TREES)
				continue;
			int m = _colisObj->at(i).size();
			for (int j = 0; j < m; j++)
			{
				if (_colisObj->at(i).at(j) != NULL)
					_colisObj->at(i).at(j)->Draw();
			}
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
			bool isCollided =CollisionManager::CollisionEnemy(_listEnemyOnMap->at(i), _listEnemyOnMap->at(j));
			if (isCollided)
				break;
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

bool Map::checkCollisionRespawnArea()
{
	int index;
	for (index = 0; index < 3; index++)
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
		if(checkCollisionRespawnArea())
		{
			return;
		}
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

  	if (_numEnemy == _maxEnemy && _listEnemyOnMap->size() == 0)
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
