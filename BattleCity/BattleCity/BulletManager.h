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
	vector<Bullet*> _listPlayerBullet;	//List dan do player ban ra
	vector<Bullet*> _listEnemyBullet;	//List dan do tat ca cac enemy dang co tren man hinh ban ra
	LPD3DXSPRITE _spriteHandler;
private:
	static BulletManager* _instance;	//Singleton pattern!
	BulletManager(){ };
	~BulletManager(){};
public:
	static BulletManager* getInstance();
public:
	 void ClearAllBullet();	//Xoa het tat ca dan trong cac list, dung khi ket thuc 1 man choi
	 void CleanBulletList();	//Xoa cac vien dan _isterminated = true
	 void Draw();
	 void Update();
	 int getPlayerBulletSize();	//Lay kich thuoc list dan cua player
	 int getEnemyBulletSize();	//Lay kich thuoc list dan cua enemy
	 void AddBullet(LPD3DXSPRITE spriteHandler,
							MoveDirection direction, 
							D3DXVECTOR2 position, 
							int ally, 
							int level,
							int **map, 
							vector<vector<StaticObject*>>* listNearbyObject);	//Them 1 vien dan vao list dua tren ally nao
	 void UpdateCollisionWithDynamicObject(PlayerTank* player, Eagle* eagle, PowerUp* powerUpItem=0, Enemy* enemy = 0);
	 //Xet va cham dan: player-enemyBullet playerBullet-Enemy, playerbullet, enemybullet -eagle, playerbullet-enemybullet
	 
};

