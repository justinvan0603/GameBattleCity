#include "Window.h"


Window::Window()
{
}


Window::~Window()
{
	if (d3ddev != NULL)
		d3ddev->Release();
	if (d3d != NULL)
		d3d->Release();
}

bool Window::initWindow(HINSTANCE hInstance)
{
	this->hInst = hInstance;
	WNDCLASSEX wcex;
	// Xác lập thuộc tính đối tượng kiểu WNDCLASSEX structure. Các thuộc tính này sẽ tác
	// động tới cách thể hiện của cửa sổ chương trình
	wcex.cbSize = sizeof(WNDCLASSEX); // hàm sizeof() trả về kích thước của một đối
	//tượng kiểu dữ liệu đầu vào – đơn vị tính là byte
	wcex.style = CS_HREDRAW | CS_VREDRAW; // xác lập kiểu lớp
	wcex.lpfnWndProc = (WNDPROC)WndProc; // xác lập tên hàm gọi lại callback procedure
	wcex.cbClsExtra = 0; // xác lập số byte cấp phát thêm cho Class
	wcex.cbWndExtra = 0; // xác lập số byte cấp phát thêm cho mỗi instance của Class
	wcex.hInstance = hInst; // con trỏ (handle) trỏ tới instance của ứng dụng
	wcex.hIcon = 0; //loại biểu tượng chương trình
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// xác lập kiểu con trỏ chuột mặc định
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // màu nền của cửa sổ
	wcex.lpszMenuName = NULL; // con trỏ trỏ tới object dữ liệu thực đơn ứng dụng
	wcex.lpszClassName = WINDOWS_NAME; // tên lớp đăng ký với hệ thống
	wcex.hIconSm = 0; // con trỏ tới dữ liệu biểu tượng cửa sổ ứng dụng
	RegisterClassEx(&wcex); //gọi hàm đăng ký lớp với hệ thống
	// Tạo cửa sổ mới
	wndHandle = CreateWindow(
		WINDOWS_NAME, //tên lớp sử dụng đã khai báo và đăng ký ở trên
		WINDOWS_NAME, //tiêu đề của cửa sổ chương trình
		WS_OVERLAPPEDWINDOW, //loại của sổ chương trình
		CW_USEDEFAULT, // toạ độ X của của sổ khi xuất hiện
		CW_USEDEFAULT, // toạ độ Y của của sổ khi xuất hiện
		Win_WIDTH, // kích thước bề ngang của cửa sổ - đơn vị là pixel
		Win_HEIGHT, // kích thước chiều cao của cửa sổ
		NULL, // con trỏ trỏ tới đối tượng cha ;
		//NULL = đối tượng quản lý là desktop của Windows
		NULL, // con trỏ đối tượng menu của chương trình; NULL = không sử dụng
		hInstance, // con trỏ instance của ứng dụng
		NULL); // không có giá trị gì được truyền cho cửa sổ
	// Kiểm tra lại xem quá trinh khởi tạo cửa sổ có thành công hay không
	if (!wndHandle)
		return false;
	// Thể hiện cửa sổ lên màn hình Window
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

bool Window::initDirectX()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) 
		return false;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		wndHandle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL) {
		MessageBox(NULL, "Failed to create device", "Error", MB_OK);
		return false;
	}
	D3DXCreateSprite(d3ddev, &spriteHandler);
	_directXSound = new DSound(wndHandle);
	GameSound::getInstance(_directXSound);
	return true;
}
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	// Kiểm tra xem có thông điệp nào được gửi tới hàng đợi cửa ứng dụng không
	switch (message) //lọc các thông điệp
	{
	case WM_DESTROY: //bắt thông điệp yêu cầu kết thúc ứng dụng
		PostQuitMessage(0); //gọi hàm xử lý
		break;
	}
	// Chú ý, hàm này yêu cầu bạn phải cung cấp thông điệp trả về cho quá trình
	// xứ lý tiếp theo
	return DefWindowProc(hWnd, message, wParam, lParam);
}
HINSTANCE& Window::get_hInstance()
{
	return hInst;
}
HWND& Window::get_windowHandler()
{
	return wndHandle;
}

bool Window::startDraw()
{
	if(d3ddev == NULL )
	{
		MessageBox(NULL, "Device can't use", "Error", MB_OK);
		return false;
	}
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->BeginScene();
	return true;
}

void Window::stopDraw()
{
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9& Window::getDevice()
{
	return d3ddev;
}
LPD3DXSPRITE& Window::getSpriteHandler()
{
	return spriteHandler;
}