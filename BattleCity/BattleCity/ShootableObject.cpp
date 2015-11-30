#include "ShootableObject.h"


ShootableObject::ShootableObject()
{
}
void ShootableObject::DrawBullet()
{
	int size = _listBullet.size();
	for (vector<Bullet*> ::iterator i = _listBullet.begin(); i != _listBullet.end(); i++)
	{
			
			(*i)->Draw();
	}
}
void ShootableObject::CleanBulletList()
{
	for (vector<Bullet*> ::iterator i = _listBullet.begin(); i != _listBullet.end();)
	{
		if ((*i)->_isTerminated)
		{
			delete *i;
			*i = NULL;
			i = _listBullet.erase(i);
			
		}
		else
			i++;
	}
}
vector<Bullet*> ShootableObject::getListBullet()
{
	return _listBullet;
}
D3DXVECTOR2 ShootableObject::CalculateBulletPosition(int left, int top, MoveDirection currentDirection)
{
	int X;
	int Y;
	D3DXVECTOR2 position;
	switch (currentDirection)
	{
		case UP:
		{
			X = left + SPRITE_WIDTH / 2 - BULLET_WIDTH / 2;
			Y = top + BULLET_HEIGHT;
			break;
		}
		case LEFT:
		{
			X = left + BULLET_WIDTH;
			Y = top + SPRITE_HEIGHT / 2 - BULLET_HEIGHT / 2;
			break;
		}
		case DOWN:
		{
			X = left + SPRITE_WIDTH / 2 - BULLET_WIDTH / 2;
			Y = top + SPRITE_HEIGHT - BULLET_HEIGHT;
			break;
		}
		case RIGHT:
		{
			X = left + SPRITE_WIDTH - BULLET_WIDTH;
			Y = top + SPRITE_HEIGHT / 2 - BULLET_HEIGHT / 2;
			break; 
		}
		default:
			break;
	}
	position.x = X;
	position.y = Y;
	return position;
}

ShootableObject::~ShootableObject()
{
}
