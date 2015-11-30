#include "Map.h"
#include <complex>
#include "GameState.h"

Map::Map(LPD3DXSPRITE spriteHandler)
{
	_startTime = GetTickCount();
	_steelBoundEagle = false;
	_canUpdateEnemy = true;
	_numEnemy = NUM_ENEMY;
	_numTankDie[0] = _numTankDie[1] = _numTankDie[2] = _numTankDie[3] = 0;
	_spriteHandler = spriteHandler;
	_player = new PlayerTank(_spriteHandler);
	_spriteHandler->GetDevice(&d3ddev);
	_spriteItemManager = new SpriteMapItemMagager(_spriteHandler);
	_eagle = new Eagle(_spriteItemManager->getEagleSprite(), getPositionFromMapMatrix(POS_EAGLE_IN_MATRIX_X, POS_EAGLE_IN_MATRIX_Y));
	_powerUpItem = new PowerUp(_spriteItemManager->getPowerUpItem());
	_colisObj = new vector<vector<StaticObject*>>;
	_mapMatrix = new int*[NUM_ROW_TILE];
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

	//Draw khung enemy goc phai
	float x, y = 0;
	int num_enemy = NUM_ENEMY;
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
	x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
	y += (TILE_HEIGHT * 2) + 64;
	_spriteItemManager->getTankLifeIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));

	//Draw so thu tu state hien tai
	x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
	y += + (TILE_HEIGHT * 4) + 64;
	_spriteItemManager->getFlagIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
	//get state hien tai roi xuat len mang hinh
	static Sprite num = Sprite(_spriteHandler, RESOURCE_PATH_NUMBER, IMAGE_NUMBER_WIDTH, IMAGE_NUMBER_HEIGHT, 10, 5);
	num.Render(StageManager::getInstance()->getStage(), POS_NUM_LEVEL);
	num.Render(_player->getLife(), POS_NUM_LIFE);

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

	for (int i = 0; i < _colisObj->size(); i++)
	{
		for (int j = 0; j < _colisObj->at(i).size(); j++)
		{
			if (_colisObj->at(i).at(j) != NULL)
			_colisObj->at(i).at(j)->Draw();
		}
	}

	//D3DXVECTOR2 objectMapIndex;
	//for (int i = 0; i < _colisObj->size();)
	//{
	//	for (int j = 0; j < _colisObj->at(i).size();)
	//	{

	//		if (_colisObj->at(i).at(j)->_isTerminated)
	//		{
	//			objectMapIndex = getPositionObjectInMapMatrix(_colisObj->at(i).at(j)->getLeft(), _colisObj->at(i).at(j)->getTop());
	//			_mapMatrix[(int)objectMapIndex.x][(int)objectMapIndex.y] = -1;
	//			delete _colisObj->at(i).at(j);
	//			_colisObj->at(i).at(j) = NULL;
	//			_colisObj->at(i).at(j) = *_colisObj->at(i).erase(_colisObj->at(i).begin() + j);
	//		}
	//		else
	//		{
	//			_colisObj->at(i).at(j)->Draw();
	//			j++;
	//		}

	//	}
	//	
	//	i++;
	//}
	_eagle->Draw();
	if(_powerUpItem->IsEnable())
	{
		if(_powerUpItem->IsEaten() == false)
		{
			if (GameTime::RenderFrame(_startTime, 300))
			{
				_powerUpItem->Draw();
			}
		}
		//ve tuong thep, 
	}
	
	
}

void Map::Update()
{


	//xet va cham va xoa item tren map

	//xet va cham va xoa item tren map

	if(Keyboard::getInstance()->IsKeyDown(DIK_1))
	{
		_powerUpItem->enablePowerUp();
	}
	if (Keyboard::getInstance()->IsKeyDown(DIK_2))
	{
		_powerUpItem->setEaten();
	}
	if (_powerUpItem->IsEnable())
	{
		if (_powerUpItem->IsEaten())
		{
			if (_powerUpItem->getType() == 2 || _powerUpItem->getType() == 3)
			{
				if(_powerUpItem->getType() == 2)
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
				if (_powerUpItem->getType() == 0)
				{
					//cho quai no
				}
				if (_powerUpItem->getType() == 1)
				{
					//set sheil player
				}
				if (_powerUpItem->getType() == 4)
				{
					_player->addLife();
				}
				if (_powerUpItem->getType() == 5)
				{
					//tac dong len player
				}
				_powerUpItem->disablePowerUp();
			}
		}
	}

	_player->Update();

	if(_canUpdateEnemy)
	{
		//_enemy->Update();
	}


	if (_player->getLife() == 0)
	{
		ScoreState::get()->addResultState(&_numTankDie[4]);
		ScoreState::get()->setEndAfter(true);
		GameState::switchState(ScoreState::get());
		return;
	}

	if (_numEnemy == 0)
	{
		if (_player->getLife() == 0)
		{
			ScoreState::get()->setEndAfter(true);
		}
		else
		{
			changeStage();
		}
		GameState::switchState(ScoreState::get());
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