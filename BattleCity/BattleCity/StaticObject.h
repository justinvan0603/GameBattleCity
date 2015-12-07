#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include "Object.h"
class StaticObject : public Object
{
protected:
	Sprite* _image;
	int _type;
public: 
	virtual void Init(Sprite* sprite, int type, D3DXVECTOR3 pos);
	virtual void Draw();
	virtual void Update();
	StaticObject();	
	StaticObject(Sprite* sprite, int type, D3DXVECTOR3 pos);
	~StaticObject();
};
#endif
