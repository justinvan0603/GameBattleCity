#pragma once
#include "Sprite.h"
class CollisionManager
{
public:
	CollisionManager();
	static bool isCollision(RECT* A, RECT* B);
	~CollisionManager();
};

