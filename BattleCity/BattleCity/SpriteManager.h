#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include "Sprite.h"
#include "GameDefaultConstant.h"
class SpriteManager
{
public:
	Sprite* getBrickSprite();
	Sprite* getSteelSprite();
	Sprite* getEagleSprite();
	Sprite* getBackGround();
	Sprite* getEnemyIcon();
	Sprite* getTankLifeIcon();
	Sprite* getFlagIcon();
	Sprite* getNumber();
	SpriteManager(LPD3DXSPRITE spriteHandler);
	~SpriteManager();
private:
	Sprite* _brick;
	Sprite* _steel;
	Sprite* _eagle;
	Sprite* _backGround;
	Sprite* _enemyIcon;
	Sprite* _tankLifeIcon;
	Sprite* _flagIcon;
	Sprite* _number;
};
#endif
