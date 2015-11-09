#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}

bool CollisionManager::isCollision(RECT* A, RECT* B)
{
	if (A->left <= B->right && A->right >= B->left && A->bottom >= B->top && A->top <= B->bottom)
	{
		if (B->bottom >= A->top && B->top <= A->bottom)
		{
			return true;
		}
	}
	return false;
}
CollisionManager::~CollisionManager()
{
}
