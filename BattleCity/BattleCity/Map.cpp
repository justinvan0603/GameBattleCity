#include "Map.h"
#include <complex>

Map::Map(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	_spriteHandler->GetDevice(&d3ddev);
	_spriteItemManager = new SpriteMapItemMagager(_spriteHandler);
	_eagle = new Eagle(_spriteItemManager->getEagleSprite(), getPositionFromMapMatrix(POS_EAGLE_IN_MATRIX_X, POS_EAGLE_IN_MATRIX_Y));
	_colisObj = new vector<vector<StaticObject*>>;
	_mapMatrix = new int*[NUM_ROW_TILE];
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		_mapMatrix[i] = new int[NUM_COLUMN_TILE];
	}
	changeState(MAPSTATE::STATE_1);	//Init state 1
}


void Map::changeState(MAPSTATE state)
{
	string stringLine;
	int i, j;	
	_mapState = state;
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
				temp[type].push_back(new SteelWall(_spriteItemManager->getEnvironment(), type, getPositionFromMapMatrix(i, j)));
		}
	}
	for (int i = 0; i < 20;i++)
		_colisObj->push_back(temp[i]);
}

bool Map::GetFileMap()
{
	string mapFilePath = "Resource\\Map\\lv";
	switch (_mapState)
	{
	case STATE_1:
	{
		mapFilePath = mapFilePath + "1";
		break;
	}

	case STATE_2:
	{
		mapFilePath = mapFilePath + "2";
		break;
	}
	case STATE_3:
	{
		mapFilePath = mapFilePath + "3";
		break;
	}
	default:
		break;
	}
	_mapFile.open(mapFilePath + ".txt", ios::in);
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
	//get so mang va hien thi o day
	int playerLife = 

	//Draw so thu tu state hien tai
	x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
	y += + (TILE_HEIGHT * 4) + 64;
	_spriteItemManager->getFlagIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
	//get state hien tai roi xuat len mang hinh


	
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

	for (int i = 0; i < _colisObj->size();i++)
	{
		for (int j = 0; j < _colisObj->at(i).size();j++)
		{
			_colisObj->at(i).at(j)->Draw();
		}
	}

	_eagle->Draw();
}

void Map::Update()
{
	//xet va cham va xoa item tren map
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

D3DXVECTOR3 Map::getPositionFromMapMatrix(int row, int column)
{
	D3DXVECTOR3 vector;
	vector.x = column*TILE_WIDTH + POS_MAP_TOP_LEFT_X;
	vector.y = row*TILE_HEIGHT + POS_MAP_TOP_LEFT_Y;
	vector.z = 0.0f;
	return vector;
}

