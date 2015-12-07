#ifndef __ICE_H__
#define __ICE_H__
#include "StaticObject.h"
class Ice : public StaticObject
{
public:
	Ice();
	Ice(Sprite* sprite, int type, D3DXVECTOR3 pos);
	void Update();
	void Draw();
	void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	~Ice();
};
#endif

