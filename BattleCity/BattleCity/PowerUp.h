#ifndef __POWER_UP__
#define __POWER_UP__
#include "Sprite.h"
#include "StaticObject.h"
#include "Text.h"

class PowerUp: public StaticObject
{
public:
	PowerUp();
	PowerUp(Sprite* sprite, Text *text);
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
	Text* _text;
	D3DXVECTOR3 _posPower;		//lưu vị trí của powerup để hỗ trợ việc vẽ điểm của powerup sau khi ăn
	bool _isEnable;
	bool _isEaten;
	int _delayTime;
	int _typePower;
	int** _mapMatrix;
	int _delayDrawScorePower;	//khoảng thời gian điểm đạt được khi ăn powerup được vẽ ra tại vị trí powerup
};
#endif

