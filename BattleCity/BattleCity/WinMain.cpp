#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	///this is a comment
	Game *game = new Game();
	if (!game->GameInit(hInstance))
		return false;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	DWORD frame_start = GetTickCount();;
	DWORD tick_per_frame = 100 / 60;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		DWORD now = GetTickCount();
		DWORD DeltaTime = now - frame_start;
		if (DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			game->GameUpdate();
			game->GameDraw();
		}

		
	
	}
	//Game.Release();
	return 0;
}