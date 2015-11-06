#ifndef __BRICK_WALL_H__
#define __BRICK_WALL_H__

#include "StaticObject.h"
class BrickWall: public StaticObject
{
public:
	BrickWall(Sprite* sprite, int typeBrick, D3DXVECTOR3 pos);
	void Update();
	void Draw();
	~BrickWall();
private:
	int _typeBrick;

};
#endif 

