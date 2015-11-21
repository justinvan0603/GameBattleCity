#ifndef __STEEL_WALL_H__
#define __STEEL_WALL_H__
#include "StaticObject.h"
class SteelWall: public StaticObject
{
public:
	SteelWall();
	SteelWall(Sprite* sprite, int typeSteel, D3DXVECTOR3 pos);
	void Draw();
	void Update();
	void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	~SteelWall();
private:
	int _typeSteel;
};
#endif
