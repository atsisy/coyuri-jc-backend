#include "ui_types.hpp"
#include "ui_values.hpp"

static void init();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	init();

	WaitKey();

	DxLib_End();
	return 0;
}

static void init() 
{
	ChangeWindowMode(TRUE);

	SetMainWindowText(TEXT("将棋少女"));

	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (DxLib_Init() == -1)
	{
		return exit(-1);
	}

	DrawFillBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(205, 220, 220));
}