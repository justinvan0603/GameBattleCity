#pragma once
#define MOUSEL	0
#define MOUSER	1
#define MOUSEM	2
#include <dinput.h>

class Input
{
private:
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dimouse;
	LPDIRECTINPUTDEVICE8 dikeyboard;
	DIMOUSESTATE mouse_state;
public:
	Input();
	int Init_DirectInput(HWND);
	int Init_Keyboard(HWND);
	void Poll_Keyboard();
	int Key_Down(int);
	void Kill_Keyboard();
	void Poll_Mouse();
	int Init_Mouse(HWND);
	int Mouse_Button(int);
	int Mouse_X();
	int Mouse_Y();
	void Kill_Mouse();
	~Input();
};

