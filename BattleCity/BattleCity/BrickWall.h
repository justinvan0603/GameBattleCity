#ifndef __BRICK_WALL_H__
#define __BRICK_WALL_H__

#include "StaticObject.h"
class BrickWall: public StaticObject
{
public:
	BrickWall(Sprite* sprite, int typeBrick, D3DXVECTOR3 pos);
	BrickWall();
	void Update();
	void Draw();
	void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	~BrickWall();
private:
	int _typeBrick;

};
#endif 

