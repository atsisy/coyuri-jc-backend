#include "ui_types.hpp"
#include "ui_values.hpp"
#include <map>

std::map<u64_t, Image> image_map;

static void init();
void set_image_map();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init();

	GraphicalBanmen gr_banmen;
	gr_banmen.redraw();

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

	set_image_map();
	DrawFillBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(205, 220, 220));
}

void set_image_map() 
{	
	image_map.insert(std::make_pair(EMPTY, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\ban.png"))));
	image_map.insert(std::make_pair(HU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\hu.png"))));
	image_map.insert(std::make_pair(KYOUSHA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\kyousha.png"))));
	image_map.insert(std::make_pair(KEIMA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\keima.png"))));
	image_map.insert(std::make_pair(GIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\gin.png"))));
	image_map.insert(std::make_pair(KIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\kin.png"))));
	image_map.insert(std::make_pair(HISHA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\hisha.png"))));
	image_map.insert(std::make_pair(KAKU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\kaku.png"))));
	image_map.insert(std::make_pair(TOKIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\tokin.png"))));
	image_map.insert(std::make_pair(NARIKYOU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\narikyou.png"))));
	image_map.insert(std::make_pair(NARIKEI, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\narikei.png"))));
	image_map.insert(std::make_pair(NARIGIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\narigin.png"))));
	image_map.insert(std::make_pair(RYU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\ryu.png"))));
	image_map.insert(std::make_pair(UMA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\uma.png"))));
	image_map.insert(std::make_pair(OU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\ou.png"))));

	image_map.insert(std::make_pair(EN_HU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\hu.png"))));
	image_map.insert(std::make_pair(EN_KYOUSHA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\kyousha.png"))));
	image_map.insert(std::make_pair(EN_KEIMA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\keima.png"))));
	image_map.insert(std::make_pair(EN_GIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_gin.png"))));
	image_map.insert(std::make_pair(EN_KIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_kin.png"))));
	image_map.insert(std::make_pair(EN_HISHA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_hisha.png"))));
	image_map.insert(std::make_pair(EN_KAKU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_kaku.png"))));
	image_map.insert(std::make_pair(EN_TOKIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_tokin.png"))));
	image_map.insert(std::make_pair(EN_NARIKYOU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_narikyou.png"))));
	image_map.insert(std::make_pair(EN_NARIKEI, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_narikei.png"))));
	image_map.insert(std::make_pair(EN_NARIGIN, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_narigin.png"))));
	image_map.insert(std::make_pair(EN_RYU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_ryu.png"))));
	image_map.insert(std::make_pair(EN_UMA, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_uma.png"))));
	image_map.insert(std::make_pair(EN_OU, Image(TEXT("C:\\Users\\Akihiro\\Pictures\\image\\en_ou.png"))));

}