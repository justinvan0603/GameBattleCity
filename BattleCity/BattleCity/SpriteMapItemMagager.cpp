#include "SpriteMapItemMagager.h"


Sprite* SpriteMapItemMagager::getEnvironment()
{
	return _environment;
}


Sprite * SpriteMapItemMagager::getEagleSprite()
{
	return _eagle;
}

Sprite * SpriteMapItemMagager::getBackGround()
{
	return _backGround;
}

Sprite * SpriteMapItemMagager::getEnemyIcon()
{
	return _enemyIcon;
}

Sprite * SpriteMapItemMagager::getTankLifeIcon()
{
	return _tankLifeIcon;
}

Sprite * SpriteMapItemMagager::getFlagIcon()
{
	return _flagIcon;
}

Sprite* SpriteMapItemMagager::getPowerUpItem()
{
	return _powerUpItem;
}

Sprite* SpriteMapItemMagager::getRespawnSprite()
{
	return _respawnEffect;
}

SpriteMapItemMagager::SpriteMapItemMagager(LPD3DXSPRITE spriteHandler)
{
	_environment = new Sprite(spriteHandler, MAP_RESOURCE_PATH_ENVIRONMENT, TILE_WIDTH , TILE_HEIGHT , 20, 10);
	_eagle = new Sprite(spriteHandler, MAP_RESOURCE_PATH_EAGLE, TILE_WIDTH * 4, TILE_HEIGHT * 4, 2, 2);
	_backGround = new Sprite(spriteHandler, MAP_RESOURCE_PATH_BG, TILE_WIDTH, TILE_HEIGHT, 1, 1);
	_enemyIcon = new Sprite(spriteHandler, RESOURCE_PATH_ENEMY_ICON, TILE_WIDTH * 2, TILE_HEIGHT * 2, 1, 1);
	_tankLifeIcon = new Sprite(spriteHandler, RESOURCE_PATH_TANKLIFE_ICON, TILE_WIDTH * 4, TILE_HEIGHT * 4, 1, 1);
	_flagIcon = new Sprite(spriteHandler, RESOURCE_PATH_FLAG_LEVEL_ICON, TILE_WIDTH * 4, TILE_HEIGHT * 4, 1, 1);
	_powerUpItem = new Sprite(spriteHandler, MAP_RESOURCE_PATH_POWERUP, TILE_WIDTH * 4, TILE_HEIGHT * 4, 6, 6);
	_respawnEffect = new Sprite(spriteHandler, RESPAWN_SPRITE_PATH, TILE_WIDTH * 4, TILE_HEIGHT * 4, 10, 10);
}


SpriteMapItemMagager::~SpriteMapItemMagager()
{
}
