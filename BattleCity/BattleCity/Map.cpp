#include "Map.h"

Map::Map(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	_spriteHandler->GetDevice(&d3ddev);
	_spriteManager = new SpriteManager(_spriteHandler);
	_mapMatrix = new int*[NUM_ROW_TILE];
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		_mapMatrix[i] = new int[NUM_COLUMN_TILE];
	}
	_eagle = new Eagle(_spriteManager->getEagleSprite(), getPositionFromMapMatrix(POS_EAGLE_IN_MATRIX_X, POS_EAGLE_IN_MATRIX_Y));
	changeState(MAPSTATE::STATE_1);	//Init state 1
}


void Map::changeState(MAPSTATE state)
{
	fstream mapFile;
	string stringLine;
	string mapFilePath = "Resource\\Map\\lv";
	int i, j;
	switch (state)
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
	mapFile.open(mapFilePath + ".txt", ios::in);
	if (mapFile.fail())
	{
		WARNING_BOX(WARNING_MAP_FILE_NOT_FOUND);
	}
	_mapState = state;
	i = 0;
	while (!mapFile.eof())
	{
		j = 0;
		getline(mapFile, stringLine);
		stringstream ss(stringLine);
		string token;
		while (getline(ss, token, ','))
		{
			_mapMatrix[i][j] = std::stoi(token);
			switch (_mapMatrix[i][j])
			{
			case 0:
			{
				
				break;
			}
			case 1: case 2: case 9: case 10:
			{
				_listBrickWallObject.push_back(new BrickWall(_spriteManager->getBrickSprite(), _mapMatrix[i][j], getPositionFromMapMatrix(i, j)));
			}
			case 17: case 18: case 25: case 26:
			{
				_listSteelWallObject.push_back(new SteelWall(_spriteManager->getSteelSprite(), _mapMatrix[i][j], getPositionFromMapMatrix(i, j)));
			}
			default:
				break;
			}
			j++;
		}		
		i++;
	}

	mapFile.close();	
}

void Map::Draw()
{
	//ham clear nay nam ngoai state
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(99,99,99), 1.0f, 0);
	//end

	//Draw khung enemy goc phai
	int x, y;
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
		_spriteManager->getEnemyIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
	}
	
	//Draw dem so mang
	x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
	y += (TILE_HEIGHT * 2) + 64;
	_spriteManager->getTankLifeIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
		//get so mang va hien thi o day
	//Draw so thu tu state hien tai
	x = POS_LIST_ENEMY_ICON_TOP_LEFT_X;
	y += + (TILE_HEIGHT * 4) + 64;
	_spriteManager->getFlagIcon()->Render(0, 0, D3DXVECTOR3(x, y, 0.0f));
		//get state hien tai roi xuat len mang hinh


	
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		for (short j = 0; j < NUM_COLUMN_TILE; j++)
		{
			if (_mapMatrix[i][j] == 0)
			{
				_spriteManager->getBackGround()->Render(0, 0, getPositionFromMapMatrix(i, j));
			}
		}
	}
	
	for (int i = 0; i < _listBrickWallObject.size(); i++)
	{
		_listBrickWallObject[i]->Draw();
	}
	for (int i = 0; i < _listSteelWallObject.size(); i++)
	{
		_listSteelWallObject[i]->Draw();
	}
	_eagle->Draw();
}

void Map::Update()
{
	//xet va cham va xoa item tren map
}

vector<BrickWall*> Map::getlistBrickWallObject()
{
	return _listBrickWallObject;
}

vector<SteelWall*> Map::getlistSteelWallObject()
{
	return _listSteelWallObject;
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

