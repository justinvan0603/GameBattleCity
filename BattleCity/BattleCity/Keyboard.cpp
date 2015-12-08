#include "Keyboard.h"
#include "DefaultConstant.h"

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
	_keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

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

void Keyboard::update(HWND hWnd)
{
	memcpy(_keyStatePrevious, _keyState, sizeof(_keyState));

	HRESULT result;
	int i = sizeof(_keyState);
	result = _keyboard->GetDeviceState(sizeof(_keyState), (LPVOID)&_keyState);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			_keyboard->Acquire();
		else
			WARNING_BOX(WARNING_CAN_NOT_READ_KEYBOARD);
	}
}
// -----------------------------------------------
// Desc: Check if the key is DOWN, UP, just PRESS or just RELEASE.
// -----------------------------------------------
KeyState Keyboard::getKeyState(int key)
{
	if (CHECK_IF_STATE_IS_DOWN(_keyState[key]))
	{
		if (CHECK_IF_STATE_IS_DOWN(_keyStatePrevious[key]))
			return KeyState::KEY_DOWN;
		else
			return KeyState::KEY_PRESS;
	}
	else 
	{
		if (CHECK_IF_STATE_IS_DOWN(_keyStatePrevious[key]))
			return KeyState::KEY_RELEASE;
		else
			return KeyState::KEY_UP;
	}
}