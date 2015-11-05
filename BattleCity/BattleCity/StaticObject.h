#pragma once
#include "Sprite.h"
class StaticObject
{
protected:
	Sprite* _image;
	RECT _size;
public:
	StaticObject();
	~StaticObject();
};

