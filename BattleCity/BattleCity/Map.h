#ifndef __MAP_H__
#define __MAP_H__
#include "GameDefaultConstant.h"
#include <vector>
#include "BrickWall.h"
#include "SteelWall.h"
#include "SpriteManager.h"
using std::vector;

enum MAPSTATE
{
	STATE_1 = 1,
	STATE_2,
	STATE_3
};
class Map
{
public:
	Map(LPD3DXSPRITE spriteHandler);
	void changeState(MAPSTATE state);
	void Draw();
	void Update();
	vector<BrickWall*> getlistBrickWallObject();
	vector<SteelWall*> getlistSteelWallObject();
	~Map();
private:
	int** _mapMatrix;
	MAPSTATE _mapState;
	LPD3DXSPRITE _spriteHandler;
	SpriteManager* _spriteManager;
	vector<BrickWall*> _listBrickWallObject;
	vector<SteelWall*> _listSteelWallObject;

	D3DXVECTOR3 getPositionFromMapMatrix(int row, int column);
};
#endif
