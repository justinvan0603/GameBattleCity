#include "Keyboard.h"
#include "DefaultConstant.h"

Keyboard* Keyboard::_instance = NULL;
Keyboard::Keyboard()
{
	_directInput = NULL;
	_directInputDeviceKeyboard = NULL;
}

bool Keyboard::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result = DI_OK;
	result = result | DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_directInput, NULL);
	result = result | _directInput->CreateDevice(GUID_SysKeyboard, &_directInputDeviceKeyboard, NULL);

	result = result | _directInputDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
	result = result | _directInputDeviceKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	result = result | _directInputDeviceKeyboard->Acquire();

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
	if (_directInputDeviceKeyboard)
	{
		_directInputDeviceKeyboard->Unacquire();
		_directInputDeviceKeyboard->Release();
	}
	if (_directInput)
		_directInput->Release();

}

void Keyboard::update(HWND hWnd)
{
	memcpy(_keyStatePrevious, _keyState, sizeof(_keyState));

	HRESULT result;
	int i = sizeof(_keyState);
	result = _directInputDeviceKeyboard->GetDeviceState(sizeof(_keyState), (LPVOID)&_keyState);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			_directInputDeviceKeyboard->Acquire();
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