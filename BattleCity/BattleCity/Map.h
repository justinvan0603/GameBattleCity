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
#include "PlayerTank.h"
#include "CollisionManager.h"
#include "LightTank.h"
#include "PowerUp.h"
using std::vector;

class Map
{
public:
	Map(LPD3DXSPRITE spriteHandler);
	void changeStage();
	void Draw();


	void Update();
	vector<vector<StaticObject*>>* getColisObject();
	Eagle* getEagleObject();
	int** getMapMatrix();
	~Map();
private:
	PlayerTank*	_player;
	int** _mapMatrix;
	int _numEnemy;
	bool _steelBoundEagle;
	bool _canUpdateEnemy;
	int _lastIndexofSteel;
	bool isPrepareRespawn;
	DWORD _startTime;
	fstream _mapFile;
	SpriteMapItemMagager* _spriteItemManager;
	Eagle* _eagle;
	PowerUp* _powerUpItem;
	Sprite* _respawnEffect;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DDEVICE9 d3ddev;
	D3DXVECTOR3 getPositionFromMapMatrix(int row, int column);
	D3DXVECTOR2 getPositionObjectInMapMatrix(int x, int y);
	bool GetFileMap();
	void InitColisObject();
	void InitListEnemy();
	void updateMaxtrix();
	void checkEndGame();
	void updateEnemy();
	void respawnAfter(int delaytime);
	void updatePowerItem();
	void drawMap();
	void drawPowerUp();
	void drawEnemy();
	void drawRightMenu();

	//Xoa enemy da bi ban ra khoi list (JT)
	void ClearDestroyedEnemy();

	vector<vector<StaticObject*>>* _colisObj;
	vector<Enemy*>* _listEnemy;
	vector<Enemy*>* _listEnemyOnMap;
	int delaytimeReSpanw;
	int delayEndStage;
};
#endif
