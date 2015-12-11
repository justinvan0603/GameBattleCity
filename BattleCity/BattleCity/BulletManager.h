#pragma once
#include "Bullet.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include "Eagle.h"
#include <vector>
class PowerUp;

//Giai quyet van de khi object bi delete thi lam sao van update duoc dan
//Neu ko lam class nay khi Enemy bi chet ->delete Enemy-> mat list dan -> sai!
class BulletManager
{
private:
	vector<Bullet*> _listPlayerBullet;
	vector<Bullet*> _listEnemyBullet;
	LPD3DXSPRITE _spriteHandler;
private:
	static BulletManager* _instance;
	BulletManager(){ };
	~BulletManager(){};
public:
	static BulletManager* getInstance();
public:
	 void ClearAllBullet();
	 void CleanBulletList();
	 void Draw();
	 void Update();
	 int getPlayerBulletSize();
	 int getEnemyBulletSize();
	 void AddBullet(LPD3DXSPRITE spriteHandler,
							MoveDirection direction, 
							D3DXVECTOR2 position, 
							int ally, 
							int level,
							int **map, 
							vector<vector<StaticObject*>>* listNearbyObject);
	 void UpdateCollisionWithDynamicObject(PlayerTank* player, Enemy* enemy, PowerUp* powerUpItem, Eagle* eagle);
	 
};

