#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DefaultConstant.h"
class Window
{
private:
	HINSTANCE hInst;
	HWND wndHandle;
	LPDIRECT3D9 d3d; // Biến tổng cho của toàn bộ thư viện directx
    LPDIRECT3DDEVICE9 d3ddev; // Đối tượng đại diện cho card đồ họa của máy tính
	LPD3DXSPRITE spriteHandler;
public:
	Window();
	~Window();
	bool initWindow(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	bool initDirectX();
	LPD3DXSPRITE& getSpriteHandler();
	LPDIRECT3DDEVICE9& getDevice();
	HINSTANCE& get_hInstance();
	HWND& get_windowHandler();
	bool startDraw();
	void stopDraw();
};

