#ifndef __MAP_H__
#define __MAP_H__
#include <vector>
#include <fstream>
#include "BrickWall.h"
#include "Eagle.h"
#include "SpriteMapItemMagager.h"
#include "PlayerTank.h"
#include "CollisionManager.h"
#include "PowerUp.h"
using std::vector;

class Map
{
public:
	Map(LPD3DXSPRITE spriteHandler);
	void changeStage();
	void Draw();
	void Update();
	void reset();
	vector<vector<StaticObject*>>* getColisObject();
	Eagle* getEagleObject();
	int** getMapMatrix();
	static D3DXVECTOR3 getPositionFromMapMatrix(int row, int column);
	~Map();
private:
	PlayerTank*	_player;
	int** _mapMatrix;
	int _numEnemy;
	int _maxEnemy;
	bool isPrepareRespawn;
	int delaytimeReSpanw;
	int delayEndStage;
	int _delayFreeze;
	bool _isFreeze;
	DWORD _startTime;
	vector<vector<StaticObject*>>* _colisObj;
	vector<Enemy*>* _listEnemy;
	vector<Enemy*>* _listEnemyOnMap;
	vector<MyRectangle*>* _rectangleRespawn;
	fstream _mapFile;
	SpriteMapItemMagager* _spriteItemManager;
	Eagle* _eagle;
	PowerUp* _powerUpItem;
	Sprite* _respawnEffect;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DDEVICE9 d3ddev;
	D3DXVECTOR2 getPositionObjectInMapMatrix(int x, int y);
	bool GetFileMap();
	void InitColisObject();
	void InitListEnemy(int numOfEnemy[], string order);
	void checkEndGame();
	void updateEnemy();
	bool checkCollisionRespawnArea();
	void respawnAfter(int delaytime);
	void updatePowerItem();
	void drawMap();
	void drawTrees();
	void drawIce();
	void drawPowerUp();
	void drawEnemy();
	void drawRightMenu();
	//Xoa enemy da bi ban ra khoi list (JT)
	void ClearDestroyedEnemy();
	void ClearStaticObject();
	void SetDefaultPositionPlayer();
	void ClearEnemyOnMap();
	void FreezeEnemyOnMap();
	void UnFreezeEnemyOnMap();
};
#endif
