#ifndef __MAP_H__
#define __MAP_H__
#include <vector>
#include <fstream>
#include "GameDefaultConstant.h"
#include "DefaultConstant.h"
#include "BrickWall.h"
#include "SteelWall.h"
#include "Eagle.h"
#include "SpriteMapItemMagager.h"
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
	vector<vector<StaticObject*>>* getColisObject();
	Eagle* getEagleObject();
	~Map();
private:
	int** _mapMatrix;
	MAPSTATE _mapState;
	fstream _mapFile;
	SpriteMapItemMagager* _spriteItemManager;
	Eagle* _eagle;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DDEVICE9 d3ddev;
	D3DXVECTOR3 getPositionFromMapMatrix(int row, int column);
	bool GetFileMap();
	void InitColisObject();
	vector<vector<StaticObject*>>* _colisObj;
};
#endif
