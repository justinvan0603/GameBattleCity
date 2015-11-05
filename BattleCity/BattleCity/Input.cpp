//#include "Input.h"
//
//Input::Input(HINSTANCE hInstance, HWND hWnd)
//{
//	this->hInstance = hInstance;
//	this->hWnd = hWnd;
//
//	dinput = NULL;
//	dev_keyboard = NULL;
//	dev_mouse = NULL;
//}
//
////--------------------------------------
////Initalize all  controller devices
////--------------------------------------
//int Input::Init()
//{
//	InitKeyboard();
//	InitMouse();
//	//try
//	//{
//	//	if (!InitKeyboard())
//	//		throw Exception(ERR_CREATE_KEYBOARD, IDERR_CREATE_KEYBOARD);
//
//	//	if (!InitMouse())
//	//		throw Exception(ERR_CREATE_MOUSE, IDERR_CREATE_MOUSE);
//
//	//	return 1;
//	//}
//	//catch (Exception exc)
//	//{
//	//	throw exc;
//	//}
//}
//
////--------------------------------------
////Initalize keyboard
////--------------------------------------
//int Input::InitKeyboard()
//{
//	HRESULT result;
//	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
//	if (result != DI_OK)
//		return 0;
//
//	result = dinput->CreateDevice(GUID_SysKeyboard, &dev_keyboard, NULL);
//	if (result != DI_OK)
//		return 0;
//
//	result = dev_keyboard->SetDataFormat(&c_dfDIKeyboard);
//	if (result != DI_OK)
//		return 0;
//
//	result = dev_keyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
//	if (result != DI_OK)
//		return 0;
//
//	result = dev_keyboard->Acquire();
//	if (result != DI_OK)
//		return 0;
//
//	SetTimer(hWnd, 0, 1000 / 12, NULL);
//
//	return 1;
//}
//
//
////--------------------------------------
////Initalize mouse
////--------------------------------------
//int Input::InitMouse()
//{
//	HRESULT result;
//	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
//	if (result != DI_OK)
//		return 0;
//
//	result = dinput->CreateDevice(GUID_SysMouse, &dev_mouse, NULL);
//	if (result != DI_OK)
//		return 0;
//
//	result = dev_mouse->SetDataFormat(&c_dfDIMouse);
//	if (result != DI_OK)
//		return 0;
//
//	result = dev_mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
//	if (result != DI_OK)
//		return 0;
//
//	result = dev_mouse->Acquire();
//	if (result != DI_OK)
//		return 0;
//
//	return 1;
//}
//
////--------------------------------------
////Get the state of keyboard
///*/--------------------------------------
//HRESULT Controls::ReadDataFromKeyboard()
//{
//HRESULT hr;
//BYTE    diks[256];   // DirectInput keyboard state buffer
//int     i;
//
//if( dev_keyboard == NULL)
//return S_OK;
//
//return S_OK;
//}*/
//
//void Input::Release()
//{
//	dev_keyboard->Unacquire();
//	dev_keyboard->Release();
//	dinput->Release();
//
//}
//
//Input::~Input(void)
//{
//}
