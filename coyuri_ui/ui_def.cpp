#include "ui_types.hpp"
#include "ui_values.hpp"
#include <map>

extern std::map<u64_t, Image> image_map;

Image::Image(const TCHAR *file_name)
{
	this->image_handle = LoadGraph(file_name);
}

void Image::draw(i64_t x, i64_t y)
{
	DrawGraph(x, y, this->image_handle, TRUE);
}

GraphicalBanmen::GraphicalBanmen()
{

	u8_t x, y;

	for (x = 0; x < 9; ++x)
	{
		for (y = 0; y < 9; ++y)
		{
			this->banmen[x][y] = EMPTY;
		}
	}

	//           x  y
	this->banmen[0][0] = EN_KYOUSHA;
	this->banmen[1][0] = EN_KEIMA;
	this->banmen[2][0] = EN_GIN;
	this->banmen[3][0] = EN_KIN;
	this->banmen[4][0] = EN_OU;
	this->banmen[5][0] = EN_KIN;
	this->banmen[6][0] = EN_GIN;
	this->banmen[7][0] = EN_KEIMA;
	this->banmen[8][0] = EN_KYOUSHA;
	this->banmen[1][1] = EN_HISHA;
	this->banmen[7][1] = EN_KAKU;

	for (x = 0; x < 9; ++x)
	{
		this->banmen[x][2] = EN_HU;
		this->banmen[x][6] = HU;
	}

	this->banmen[1][7] = KAKU;
	this->banmen[7][7] = HISHA;
	this->banmen[0][8] = KYOUSHA;
	this->banmen[1][8] = KEIMA;
	this->banmen[2][8] = GIN;
	this->banmen[3][8] = KIN;
	this->banmen[4][8] = OU;
	this->banmen[5][8] = KIN;
	this->banmen[6][8] = GIN;
	this->banmen[7][8] = KEIMA;
	this->banmen[8][8] = KYOUSHA;
}

void GraphicalBanmen::redraw()
{
	u8_t x, y;

	for (x = 0; x < 9; ++x) 
	{
		for (y = 0; y < 9; ++y)
		{
			image_map.at(this->banmen[x][y]).draw((x * KOMA_WIDTH) + BANMEN_LEFT_FROM, (y * KOMA_HEIGHT) + BANMEN_TOP_FROM);
		}
	}
}