#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include "Object.h"
class StaticObject : public Object
{
protected:
	Sprite* _image;
public: 
	StaticObject();	
	virtual void Draw() = 0;
	~StaticObject();
};
#endif
