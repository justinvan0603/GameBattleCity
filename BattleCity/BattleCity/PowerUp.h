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
	bool IsEnable();
	bool IsEaten();
	void setEaten();
	int getType();
	void disablePowerUp();
	void enablePowerUp();
	~PowerUp();
private:
	int _typePower;
	bool _isEnable;
	bool _isEaten;
};
#endif

