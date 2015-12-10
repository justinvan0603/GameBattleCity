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
	bool _isEnable;
	bool _isEaten;
	int _typePower;
	int** _mapMatrix;
};
#endif

