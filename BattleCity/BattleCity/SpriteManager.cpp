#include "SpriteManager.h"



Sprite * SpriteManager::getBrickSprite()
{
	return _brick;
}

Sprite * SpriteManager::getSteelSprite()
{
	return _steel;
}

Sprite * SpriteManager::getEagleSprite()
{
	return _eagle;
}

Sprite * SpriteManager::getBackGround()
{
	return _backGround;
}

Sprite * SpriteManager::getEnemyIcon()
{
	return _enemyIcon;
}

Sprite * SpriteManager::getTankLifeIcon()
{
	return _tankLifeIcon;
}

Sprite * SpriteManager::getFlagIcon()
{
	return _flagIcon;
}

Sprite * SpriteManager::getNumber()
{
	return _number;
}

SpriteManager::SpriteManager(LPD3DXSPRITE spriteHandler)
{
	_brick = new Sprite(spriteHandler, MAP_RESOURCE_PATH_BRICKWALL, TILE_WIDTH, TILE_HEIGHT, 4, 2);
	_steel = new Sprite(spriteHandler, MAP_RESOURCE_PATH_STEELWALL, TILE_WIDTH, TILE_HEIGHT, 4, 2);
	_eagle = new Sprite(spriteHandler, MAP_RESOURCE_PATH_EAGLE, TILE_WIDTH * 4, TILE_HEIGHT * 4, 2, 2);
	_backGround = new Sprite(spriteHandler, MAP_RESOURCE_PATH_BG, TILE_WIDTH, TILE_HEIGHT, 1, 1);
	_enemyIcon = new Sprite(spriteHandler, RESOURCE_PATH_ENEMY_ICON, TILE_WIDTH * 2, TILE_HEIGHT * 2, 1, 1);
	_tankLifeIcon = new Sprite(spriteHandler, RESOURCE_PATH_TANKLIFE_ICON, TILE_WIDTH * 4, TILE_HEIGHT * 4, 1, 1);
	_flagIcon = new Sprite(spriteHandler, RESOURCE_PATH_FLAG_LEVEL_ICON, TILE_WIDTH * 4, TILE_HEIGHT * 4, 1, 1);
	_number = new Sprite(spriteHandler, RESOURCE_PATH_NUMBER, TILE_WIDTH * 2, TILE_HEIGHT * 2, 10, 5);
}


SpriteManager::~SpriteManager()
{
}
