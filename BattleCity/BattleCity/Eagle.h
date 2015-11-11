#ifndef __EAGLE_H__
#define __EAGLE_H__
#include "StaticObject.h"
enum EAGLE_STATUS
{
	LIVE =1,
	DEAD 
};
class Eagle: public StaticObject
{
public:
	Eagle();
	Eagle(Sprite* sprite, D3DXVECTOR3 position);
	void Update();
	void Draw();
	void setEagleStatus(EAGLE_STATUS status);
	~Eagle();
private:
	EAGLE_STATUS _status;
};
#endif
