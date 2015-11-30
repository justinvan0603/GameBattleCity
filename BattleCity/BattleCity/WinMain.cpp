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
	GameTime *gt = new GameTime(120);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (gt->CanCreateFrame())
		{
			game->GameUpdate();
			game->GameRun();
			
		}
		else
			Sleep(gt->GetTimePerFrame());
	}
	//Game.Release();
	return 0;
}