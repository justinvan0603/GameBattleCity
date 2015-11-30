#pragma once
#include "Sprite.h"
#include "GameTime.h"
class Effect: public Sprite
{
private:
	D3DXVECTOR2 _position;
	
public:
	bool _completed;
	Effect(LPD3DXSPRITE SpriteHandler, 
		char* Path, 
		int Width, 
		int Height, 
		int Count, 
		int SpritePerRow);
	Effect(LPD3DXSPRITE SpriteHandler,
		char* Path, 
		int Width, 
		int Height, 
		int Count, 
		int SpritePerRow, 
		D3DXVECTOR2 position);
	void Render();
	void Render(int X, int Y);
	void Render(int X, int Y,DWORD starttime, int delaytime);
	void Reset();
	~Effect();
};

