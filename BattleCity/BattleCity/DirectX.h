#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "DefaultConstant.h"

class DirectX
{
private: 
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPD3DXSPRITE spriteHandler;
	IDirect3DSurface9 *backbuffer;
public:
	DirectX();
	~DirectX();
	bool initDirect3D(HWND);
};

