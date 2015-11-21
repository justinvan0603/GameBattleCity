#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include "Object.h"
class StaticObject : public Object
{
protected:
	Sprite* _image;
public: 
	virtual void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	virtual void Draw();
	StaticObject();	
	~StaticObject();
};
#endif
