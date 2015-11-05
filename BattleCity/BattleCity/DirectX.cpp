#include "DirectX.h"


DirectX::DirectX()
{

}


DirectX::~DirectX()
{
	this->d3d->Release();
	this->d3d = NULL;
	this->d3ddev->Release();
	this->d3ddev = NULL;
}

bool DirectX::initDirect3D(HWND wndHandle)
{
	d3d = NULL;
	d3ddev = NULL;
	// Create the DirectX object
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}
	// Fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = Win_HEIGHT;
	d3dpp.BackBufferWidth = Win_WIDTH;
	d3dpp.hDeviceWindow = wndHandle;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.EnableAutoDepthStencil = TRUE;
	// Create a default DirectX device
	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		wndHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev)))
	{
		return false;
	}

	// Khởi tạo spriteHandler
	if (FAILED(D3DXCreateSprite(d3ddev, &spriteHandler)))
		return false;
	return true;
}