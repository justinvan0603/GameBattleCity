#ifndef __WATER_H__
#define __WATER_H__ 
#include "StaticObject.h"

class Water: public StaticObject
{
public:
	Water(Sprite* sprite, int type, D3DXVECTOR3 pos);
	Water();
	void Update();
	void Draw();
	void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	~Water();
private:
	int _delayTime;
	int _indexDistance;
};
#endif

