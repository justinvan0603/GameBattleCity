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
#include "Text.h"
using std::vector;

class Map
{
public:
	Map(LPD3DXSPRITE spriteHandler);
	void changeStage();
	void Draw();
	void Update();
	void reset();
	vector<vector<StaticObject*>>* getStaticObject();
	Eagle* getEagleObject();
	int** getMapMatrix();
	static D3DXVECTOR3 getPositionFromMapMatrix(int row, int column);
	~Map();
private:
	PlayerTank*	_player;		//Đối tượng tank được người chơi điều khiển (tank màu vàng).
	int** _mapMatrix;		//Ma trận hai chiều kiểu int lưu giữ vị trí các đối tượng tĩnh (gạch, thép, sông, băng, rừng)
	int _numEnemy;		//số lượng tank địch còn lại chưa xuất hiện
	int _maxEnemy;		//số lượng tank địch tối đa trong một stage.
	bool _isPrepareRespawn;		//biến cờ hiệu dùng để báo có một chiếc tank địch chuẩn bị xuất hiện
	int _delaytimeReSpawn;		//thời gian giãn cách xuất hiện tank địch
	int _delayEndStage;			//thời gian chờ chuẩn bị chuyển qua ScoreState
	int _delayFreeze;			//thời gian poweup Shield hoạt động
	bool _isFreeze;		//biến cờ hiệu báo rằng vật phẩm Shield đang được phát huy tác dụng
	Text* _text;	//ỗ trợ vẽ điểm powerup, dòng chữ “GAMEOVER” khi người chơi thua cuộc, số stage hiện tại, số mạng còn lại của người chơi. 
	D3DXVECTOR3 _posGameOverText;	//vị trí vẽ lên dòng chữ “GAMEOVER”
	vector<vector<StaticObject*>>* _listStaticObject;	//danh sách các đối tượng tĩnh trên màn hình bao gồm: tường gạch, tường thép, rừng, sông, băng. 
	vector<Enemy*>* _listEnemy;		//danh sách tank sẽ sẽ xuất hiện trong 1 stage.
	vector<Enemy*>* _listEnemyOnMap;	//danh sách tank địch đang xuất hiện trên màn hình.
	vector<MyRectangle*>* _rectangleEnemyRespawn;	//danh sách các vị trí mà tank địch sẽ xuất hiện 
	vector<MyRectangle*>* _playerRespawnPos;		//danh sách vị trí mà người chơi sẽ xuất hiện.
	fstream _mapFile;			//hỗ trợ việc đọc file map có định dạng txt
	SpriteMapItemMagager* _spriteItemManager;	//quản lí các sprite của StaticObject trên màn chơi. 
	Eagle* _eagle;		//đối tượng căn cứ (hình con đại bàng) mà người chơi phải bảo vệ
	PowerUp* _powerUpItem;	//Quản lí powerup
	Sprite* _respawnEffect;		// hỗ trợ việc tạo hiệu ứng tại vị trí tank chuẩn bị xuất hiện
	LPD3DXSPRITE _spriteHandler;	//hỗ trợ việc vẽ các đối tượng lên màn hình
	LPDIRECT3DDEVICE9 _d3ddev;		//
	D3DXVECTOR2 getPositionObjectInMapMatrix(int x, int y);
	bool GetFileMap();
	void InitStaticObject();
	void InitListEnemy(int numOfEnemy[], string order);
	void checkEndGame();
	void updateEnemy();
	bool checkCollisionRespawnArea();
	void respawnAfter(int delaytime);
	void updatePowerItem();
	void drawMap();
	void drawEagle();
	void drawPlayer();
	void drawTrees();
	void drawIce();
	void drawPowerUp();
	void drawEnemy();
	void drawRightMenu();
	//Xoa enemy da bi ban ra khoi list (JT)
	void ClearDestroyedEnemy();
	void ClearStaticObject();
	void ClearDynamicObject();
	void SetDefaultValuePlayer();
	void ClearEnemyOnMap();
	void FreezeEnemyOnMap();
	void UnFreezeEnemyOnMap();
	void CleanStage();
};
#endif
