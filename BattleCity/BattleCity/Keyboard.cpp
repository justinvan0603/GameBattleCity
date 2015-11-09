#include "Keyboard.h"

Keyboard* Keyboard::_instance = NULL;
Keyboard::Keyboard()
{
	_directInputObject = NULL;
	_keyboard = NULL;
}

bool Keyboard::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_directInputObject, NULL);
	if (result != DI_OK)
		return false;
	result = _directInputObject->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL);
	if (result != DI_OK)
		return false;
	_keyboard->SetDataFormat(&c_dfDIKeyboard);
	_keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	result = _keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK)
		return false;
	result = _keyboard->Acquire();
	if (result != DI_OK)
		return false;
	return true;
}
int Keyboard::IsKeyDown(int KeyCode)
{
	return (_keyState[KeyCode] & 0x80);
}
Keyboard* Keyboard::getInstance()
{
	if (_instance == NULL)
		_instance = new Keyboard();
	return _instance;
}
Keyboard::~Keyboard()
{
	if (_keyboard)
	{
		_keyboard->Unacquire();
		_keyboard->Release();
	}
	if (_directInputObject)
		_directInputObject->Release();

}

void Keyboard::ProcessKeyboard(HWND hWnd)
{
	if (_keyboard->Poll() != DI_OK)
		_keyboard->Acquire();
	_keyboard->GetDeviceState(sizeof(_keyState), _keyState);
	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(hWnd, WM_QUIT, 0, 0);
	}
	DWORD dwElement = KEYBOARD_BUFFER_SIZE;
	HRESULT result = _keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvent, &dwElement, 0);
}
