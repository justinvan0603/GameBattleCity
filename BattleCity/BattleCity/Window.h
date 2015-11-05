#pragma once

#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "DefaultConstant.h"

class Window
{
public:
	HINSTANCE hInst;
	HWND wndHandle;
public:
	Window();
	~Window();
	bool initWindow(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

