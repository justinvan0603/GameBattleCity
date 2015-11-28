#pragma once
#include "DynamicObject.h"



class Bullet : public DynamicObject
{
private:
	int _allyObject;
	
public:
	Bullet(LPD3DXSPRITE,int);
	Bullet(LPD3DXSPRITE, MoveDirection, int, int, int,int, int ** , vector<vector<StaticObject*>>* );
	Bullet(LPD3DXSPRITE, MoveDirection, D3DXVECTOR2, int, int, int **, vector<vector<StaticObject*>>*);
	void setAllyObject(int ally);
	int getAllyObject();
	void Draw();
	void Move();
	void Update();
	void setFireDirection(MoveDirection direction);
	~Bullet();
};

