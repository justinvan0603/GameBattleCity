#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__
#include "Sprite.h"
#include "GameDefaultConstant.h"
class SpriteMapItemMagager
{
public:
	Sprite* getEnvironment();
	Sprite* getEagleSprite();
	Sprite* getBackGround();
	Sprite* getEnemyIcon();
	Sprite* getTankLifeIcon();
	Sprite* getFlagIcon();
	Sprite* getNumber();
	Sprite* getPowerUpItem();
	SpriteMapItemMagager(LPD3DXSPRITE spriteHandler);
	~SpriteMapItemMagager();
private:
	Sprite* _environment;
	Sprite* _eagle;
	Sprite* _backGround;
	Sprite* _enemyIcon;
	Sprite* _tankLifeIcon;
	Sprite* _flagIcon;
	Sprite* _number;
	Sprite* _powerUpItem;
};
#endif
