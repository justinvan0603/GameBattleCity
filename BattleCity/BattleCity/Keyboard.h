#pragma once
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE	1024

#define KEY_DOWN(code) ( IsKeyDown(code) )
class Keyboard
{
private:
	LPDIRECTINPUT8       _directInputObject;
	LPDIRECTINPUTDEVICE8 _keyboard;

	BYTE _keyState[256];

	DIDEVICEOBJECTDATA _keyEvent[KEYBOARD_BUFFER_SIZE];

	static Keyboard * _instance;
public:
	Keyboard();
	bool InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	int IsKeyDown(int KeyCode);
	static Keyboard* getInstance();

	void ProcessKeyboard(HWND hWnd);
	~Keyboard();
};

