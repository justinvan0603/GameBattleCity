#pragma once
#include "Sprite.h"
#define ANIMATION_DELAY_TIME 2
class Effect: public Sprite
{
private:
	int _animationCount;
	int _animationDelay;

public:
	Effect(LPD3DXSPRITE SpriteHandler, char* Path, int Width, int Height, int Count, int SpritePerRow);
	void Render(int X, int Y);
	void Reset();
	~Effect();
};

