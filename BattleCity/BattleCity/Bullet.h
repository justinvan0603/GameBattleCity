#pragma once
#include "DynamicObject.h"


//Lop dinh nghia ra dan trong game
class Bullet : public DynamicObject
{
private:
	int _allyObject;	//Bien chi dinh vien dan nay do player hay enemy ban ra
	
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

