#include "Effect.h"


Effect::Effect(LPD3DXSPRITE SpriteHandler, char* Path, int Width, int Height, int Count, int SpritePerRow) 
	:Sprite(SpriteHandler,Path,Width, Height,Count,SpritePerRow)
{

}
Effect::Effect(LPD3DXSPRITE SpriteHandler,
	char* Path,
	int Width,
	int Height,
	int Count,
	int SpritePerRow,
	D3DXVECTOR2 position) : Sprite(SpriteHandler, Path, Width, Height, Count, SpritePerRow)
{
	_completed = false;
	_position = position;
}
void Effect::Render()
{

	this->Render((int)_position.x, (int)_position.y);
	
}
void Effect::Render(int X, int Y)
{
	
	Sprite::Render(X, Y);

}
void Effect::Render(int X, int Y, DWORD starttime, int delaytime)
{
	if (GameTime::RenderFrame(starttime, delaytime))
	{
		Sprite::Render(X, Y);
	}
}
void Effect::Reset()
{

	_Index = 0;
}
Effect::~Effect()
{
}
