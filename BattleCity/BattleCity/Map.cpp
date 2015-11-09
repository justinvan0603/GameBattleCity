#include "Map.h"

Map::Map(LPD3DXSPRITE spriteHandler)
{
	_spriteHandler = spriteHandler;
	_spriteManager = new SpriteManager(_spriteHandler);
	_mapMatrix = new int*[NUM_ROW_TILE];
	for (short i = 0; i < NUM_ROW_TILE; i++)
	{
		_mapMatrix[i] = new int[NUM_COLUMN_TILE];
	}

	changeState(MAPSTATE::STATE_1);	//Init state 1
}


void Map::changeState(MAPSTATE state)
{
	_mapState = state;
	int _map1[NUM_ROW_TILE][NUM_COLUMN_TILE] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,17,18,17,18,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,25,26,25,26,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,17,18,17,18,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,25,26,25,26,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 1,2,1,2,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,1,2,1,2, },
	{ 9,10,9,10,0,0,0,0,9,10,9,10,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,9,10,9,10,0,0,0,0,9,10,9,10, },
	{ 17,18,17,18,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,17,18,17,18, },
	{ 25,26,25,26,0,0,0,0,9,10,9,10,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,9,10,9,10,0,0,0,0,25,26,25,26, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,9,10,9,10,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,1,2,1,2,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,9,10,9,10,9,10,9,10,0,0,0,0,9,10,1,2,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,9,10,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,1,2,1,2,0,0,0,0,1,2,1,2,0,0,0,0, },
	{ 0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0,0,0,9,10,9,10,9,10,9,10,0,0,0,0,0,0,9,10,9,10,0,0,0,0,9,10,9,10,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,0,0,0,0,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,0,0,0,0,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	
	if (_mapState == MAPSTATE::STATE_1)
	{
		for (short i = 0; i < NUM_ROW_TILE; i++)
		{
			for (short j = 0; j < NUM_COLUMN_TILE; j++)
			{
				_mapMatrix[i][j] = _map1[i][j];
				switch (_mapMatrix[i][j])
				{
				case 0:
				{
					break;
				}
				case 1: case 2: case 9: case 10:
				{
					_listBrickWallObject.push_back(new BrickWall(_spriteManager->getBrickSprite(), _mapMatrix[i][j] ,getPositionFromMapMatrix(i, j)));
				}
				case 17: case 18: case 25: case 26:
				{
					_listSteelWallObject.push_back(new SteelWall(_spriteManager->getSteelSprite(), _mapMatrix[i][j], getPositionFromMapMatrix(i, j)));
				}
				default:
					break;
				}
			}
		}
	}
	
	
}

void Map::Draw()
{
	for (int i = 0; i < _listBrickWallObject.size(); i++)
	{
		_listBrickWallObject[i]->Draw();
	}
	for (int i = 0; i < _listSteelWallObject.size(); i++)
	{
		_listSteelWallObject[i]->Draw();
	}
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

Map::~Map()
{
}

D3DXVECTOR3 Map::getPositionFromMapMatrix(int row, int column)
{
	D3DXVECTOR3 vector;
	vector.x = column*TILE_WIDTH;
	vector.y = row*TILE_HEIGHT;
	vector.z = 0.0f;
	return vector;
}