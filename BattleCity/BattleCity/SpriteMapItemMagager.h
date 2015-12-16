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
	Sprite* getPowerUpItem();
	Sprite* getRespawnSprite();
	SpriteMapItemMagager(LPD3DXSPRITE spriteHandler);
	~SpriteMapItemMagager();
private:
	Sprite* _environment;		//gach, thep, rung ...
	Sprite* _eagle;				//Dai bang
	Sprite* _backGround;		//Nen den
	Sprite* _enemyIcon;			//icon dich ben goc phai
	Sprite* _tankLifeIcon;		//hinh di kem so mang
	Sprite* _flagIcon;			// la co di kem so stage
	Sprite* _powerUpItem;		//item powerup
	Sprite* _respawnEffect;		//HU hoi sinh
};
#endif
