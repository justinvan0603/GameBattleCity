#pragma once
#include "Effect.h"
#include "Object.h"
#include "GameDefaultConstant.h"
//Ta khong the ve cac hieu ung rieng le nam ton tai trong tung loai doi tuong
//Nhu vay se gay kho khan khi quan ly, xu ly va tieu ton bo nho
//Lop singletton EffectManager nhan tat ca cac hieu ung xay ra trong 1 thoi diem va ve ra
//sau khi ve xong (tuc la _isComplete = true) thi xoa vung nho ra khoi list
class EffectManager
{
private:
	LPD3DXSPRITE _spriteHandler;
	vector<Effect*> _listEffect;	//List chua tat ca cac effect
	//DWORD _startTime;
private: 
	static EffectManager* _instance;
	EffectManager(LPD3DXSPRITE);
	~EffectManager();
public:
	static EffectManager* getInstance(LPD3DXSPRITE = 0);
public:
	void AddBulletEffect(D3DXVECTOR2 position);	//Them effect dan no vao list
	void AddDestroyEffect(D3DXVECTOR2 position);	//Khi co xe tank hay eagle bi tieu diet thi add hieu ung no tank vao
	void Draw();
	
};

