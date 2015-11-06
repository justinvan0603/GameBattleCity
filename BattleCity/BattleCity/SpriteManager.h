#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include "Sprite.h"
#include "GameDefaultConstant.h"
class SpriteManager
{
public:
	Sprite* getBrickSprite();
	Sprite* getSteelSprite();
	SpriteManager(LPD3DXSPRITE spriteHandler);
	~SpriteManager();
private:
	Sprite* _Brick;
	Sprite* _Steel;
};
#endif
