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
vector<Bullet*> ShootableObject::getListBullet()
{
	return _listBullet;
}
ShootableObject::~ShootableObject()
{
}
