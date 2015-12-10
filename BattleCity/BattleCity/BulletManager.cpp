#include "BulletManager.h"
#include "CollisionManager.h"

BulletManager* BulletManager::_instance = nullptr;

BulletManager* BulletManager::getInstance()
{
	if (_instance == NULL)
		_instance = new BulletManager();
	return _instance;
}
void BulletManager::AddBullet(LPD3DXSPRITE spriteHandler,
	MoveDirection direction, 
	D3DXVECTOR2 position, 
	int ally,
	int level,
	int **map, 
	vector<vector<StaticObject*>>* listNearbyObject)
{
	switch (ally)
	{
	case ALLY_PLAYER:
	{
		_listPlayerBullet.push_back(new Bullet(spriteHandler, direction, position, ally, level, map, listNearbyObject));
		break;
	}
	case ALLY_ENEMY:
	{
		_listEnemyBullet.push_back(new Bullet(spriteHandler, direction, position, ally, level, map, listNearbyObject));
		break;
	}
	default:
		break;
	}
}
void BulletManager::Draw()
{
	for (vector<Bullet*> ::iterator i = _listPlayerBullet.begin(); i != _listPlayerBullet.end(); i++)
	{

		(*i)->Draw();
	}

	for (vector<Bullet*> ::iterator i = _listEnemyBullet.begin(); i != _listEnemyBullet.end(); i++)
	{

		(*i)->Draw();
	}
}
void BulletManager::Update()
{
	for (vector<Bullet*> ::iterator i = _listPlayerBullet.begin(); i != _listPlayerBullet.end(); i++)
	{

		(*i)->Update();
	}

	for (vector<Bullet*> ::iterator i = _listEnemyBullet.begin(); i != _listEnemyBullet.end(); i++)
	{

		(*i)->Update();
	}

	for (vector<Bullet*> ::iterator i = _listPlayerBullet.begin(); i != _listPlayerBullet.end(); i++)
	{
		for (vector<Bullet*> ::iterator j = _listEnemyBullet.begin(); j != _listEnemyBullet.end(); j++)
		{

			bool isCollided = CollisionManager::CollisionBulletWithObject(*i, *j);
			if (isCollided)
				break;
		}

	}


	CleanBulletList();
}

void BulletManager::UpdateCollisionWithDynamicObject(PlayerTank* player, Enemy* enemy, PowerUp* powerUpItem)
{
	for (vector<Bullet*> ::iterator i = _listEnemyBullet.begin(); i != _listEnemyBullet.end(); i++)
	{
		bool isCollided = CollisionManager::CollisionBulletWithObject(*i, player);
		if (isCollided)
			break;
	}
	
	for (vector<Bullet*> ::iterator i = _listPlayerBullet.begin(); i != _listPlayerBullet.end(); i++)
	{

		bool isCollided = CollisionManager::CollisionBulletWithObject(*i, enemy);
		if (isCollided)
		{
			if(enemy->isBonusTank())
			{
				powerUpItem->enablePowerUp();
			}
			break;
		}
	}

}
void BulletManager::CleanBulletList()
{
	for (vector<Bullet*> ::iterator i = _listPlayerBullet.begin(); i != _listPlayerBullet.end();)
	{
		if ((*i)->_isTerminated)
		{
			delete *i;
			*i = NULL;
			i = _listPlayerBullet.erase(i);

		}
		else
			i++;
	}
	for (vector<Bullet*> ::iterator i = _listEnemyBullet.begin(); i != _listEnemyBullet.end();)
	{
		if ((*i)->_isTerminated)
		{
			delete *i;
			*i = NULL;
			i = _listEnemyBullet.erase(i);

		}
		else
			i++;
	}
}
int BulletManager::getPlayerBulletSize()
{
	return _listPlayerBullet.size();
}
int BulletManager::getEnemyBulletSize()
{
	return _listEnemyBullet.size();
}
