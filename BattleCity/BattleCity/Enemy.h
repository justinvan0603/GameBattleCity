#pragma once
#include "ShootableObject.h"


class Enemy : public ShootableObject
{

protected:
	bool _isBonusTank;	// Doi tuong co phai la tank mang item khong
	bool _isFreeze;	//Doi tuong co dang o trang thai dong bang khong
public:
	void DeActivateBonus();
	bool _isCollied; //doi tuong co va cham voi object khac khong
	Enemy();
	virtual void Draw()=0; 
	void Move()=0;
	void MoveWithCollision();	//Ham xu ly khi co va cham thi chuyen huong enemy
	void Shoot();
	void Update() = 0;
	//void RandomShoot();
	bool isBonusTank();		//kiem tra phai la bonus tank khong
	void ActivateFreeze();	//Ham kich hoat trang thai dong bang
	void DeactivateFreeze();	//Huy trang thai dong bang
	bool isFreeze();
	~Enemy();
};

