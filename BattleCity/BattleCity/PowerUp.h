#ifndef __POWER_UP__
#define __POWER_UP__
#include "Sprite.h"
#include "StaticObject.h"

class PowerUp: public StaticObject
{
public:
	PowerUp();
	PowerUp(Sprite* sprite);
	void Draw();
	void Update();
	bool IsEaten();
	bool IsEnable();
	void setEaten();
	int getType();
	void disablePowerUp();
	void enablePowerUp();
	void setmap(int** map);
	~PowerUp();
private:
	bool _isEnable;		//Co dang kich hoat hay khong
	bool _isEaten;		//Bi an hay chua
	int _typePower;		//Loai PowerUp: Life, bomb,.. loai tuong ung vs index tren sprite PowerUp
	int** _mapMatrix;	//Ho tro viec random vi tri powerUp
	int x[NUM_POWER_PER_MAP];			//danh sach toa doa x cua PU
	int y[NUM_POWER_PER_MAP];			//danh sach toa do y cua PU
	int _currentPos;	//Toa do PU hien tai
};
#endif

