#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include "Object.h"
class StaticObject : public Object
{
protected:
	Sprite* _image;
public: 
	StaticObject();	
	~StaticObject();
};
#endif
