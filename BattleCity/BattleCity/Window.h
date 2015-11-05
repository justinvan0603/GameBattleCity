#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

class Window
{
public:
	HINSTANCE hInst;
	HWND wndHandle;
	LPDIRECT3D9 d3d; // Biến tổng cho của toàn bộ thư viện directx
	LPDIRECT3DDEVICE9 d3ddev; // Đối tượng đại diện cho card đồ họa của máy tính
public:
	Window();
	~Window();
	bool initWindow(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	bool initDirectX();
};

