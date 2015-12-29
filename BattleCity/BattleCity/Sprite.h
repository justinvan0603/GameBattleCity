#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
using namespace std;
class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;		//the container of the images
	LPD3DXSPRITE _SpriteHandler;	//handle to the sprite object

	int _Index;						// Vị trí của sprite hiện tại
	int _Width;						// Chiều rộng của sprite
	int _Height;					// Chiều cao của sprite
	int _Count;						// number of sprite's
	int _SpritePerRow;				// số sprite trên 1 hàng

	D3DXVECTOR3 _CurrentSpriteLocation;//current sprite's location
public:
	Sprite(LPD3DXSPRITE SpriteHandler, char* Path, int Width, int Height, int Count, int SpritePerRow);
	void Next();
	void Next(bool &isCompleted);
	void Next(int startFrame);
	void NextColumn();
	void NextInCurRow();
	void Previous();
	void Render(int X, int Y);
	void Render(D3DXVECTOR3 Location);
	
	void Render(int index, int X, int Y);
	void Render(int index, D3DXVECTOR3 Location);
	void Render(int row, int col, D3DXVECTOR3 Location);
	int getWidth();
	int getHeight();
	int getIndex();
	
	void setWidth(int width);
	void setHeight(int height);
	void setStartFrame(int startFrame);
public:
	~Sprite(void);
};

