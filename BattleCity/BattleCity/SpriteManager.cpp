#include "SpriteManager.h"



Sprite * SpriteManager::getBrickSprite()
{
	return _Brick;
}

Sprite * SpriteManager::getSteelSprite()
{
	return _Steel;
}

SpriteManager::SpriteManager(LPD3DXSPRITE spriteHandler)
{
	_Brick = new Sprite(spriteHandler, MAP_RESOURCE_PATH_BRICKWALL, TILE_WIDTH, TILE_HEIGHT, 4, 2);
	_Steel = new Sprite(spriteHandler, MAP_RESOURCE_PATH_STEELWALL, TILE_WIDTH, TILE_HEIGHT, 4, 2);
}


SpriteManager::~SpriteManager()
{
}
