#pragma once
#include "Object.h"
class StaticObject : public Object
{
protected:
	Sprite* _image;

public:
	StaticObject();

	~StaticObject();
};

