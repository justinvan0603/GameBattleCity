#pragma once
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE	1024

#define CHECK_IF_STATE_IS_DOWN(state) (state & 0x80)
enum KeyState
{
	KEY_DOWN = 0,
	KEY_PRESS,
	KEY_RELEASE,
	KEY_UP,
	NUM_OF_KEY_STATE
};

class Keyboard
{
private:
	LPDIRECTINPUT8       _directInputObject;
	LPDIRECTINPUTDEVICE8 _keyboard;

	BYTE _keyState[256];
	BYTE _keyStatePrevious[256];

	DIDEVICEOBJECTDATA _keyEvent[KEYBOARD_BUFFER_SIZE];

	static Keyboard * _instance;
public:
	Keyboard();
	bool InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	int IsKeyDown(int KeyCode);
	static Keyboard* getInstance();
	KeyState Keyboard::getKeyState(int key);
	void update(HWND hWnd);
	~Keyboard();
};

