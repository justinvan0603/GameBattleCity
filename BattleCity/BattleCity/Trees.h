#ifndef __TREES_H__
#define __TREES_H__

#include "StaticObject.h"
class Trees: public StaticObject
{
public:
	Trees(Sprite* sprite, int type, D3DXVECTOR3 pos);
	Trees();
	void Update();
	void Draw();
	void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	~Trees();
};
#endif

