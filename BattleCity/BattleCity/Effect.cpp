#include "Effect.h"


Effect::Effect(LPD3DXSPRITE SpriteHandler, char* Path, int Width, int Height, int Count, int SpritePerRow) 
	:Sprite(SpriteHandler,Path,Width, Height,Count,SpritePerRow)
{

	_animationCount = 0;
	_animationDelay = ANIMATION_DELAY_TIME;
}

void Effect::Render(int X, int Y)
{
	
	if (++_animationCount > _animationDelay)
	{
		_animationCount = 0;
		if (++_Index > _SpritePerRow)
			Reset();
	}
	Sprite::Render(_Index, X, Y);

	//while (_Index < _SpritePerRow)
	//{
	//	if (++_animationCount > _animationDelay)
	//	{
	//		_animationCount = 0;

	//		_Index++;
	//	}
	//	Sprite::Render(_Index, X, Y);
	//}
	//Reset();

}
void Effect::Reset()
{
	_animationDelay = 0;
	_Index = 0;
}
Effect::~Effect()
{
}
