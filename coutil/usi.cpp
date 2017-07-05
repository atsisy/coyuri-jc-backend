#include <string>
#include <algorithm>
#include "types.hpp"


namespace cut {

	static u8_t ctoi(char ch) {
		return ('0' <= ch && ch <= '9') ? ch - '0' : 0;
	}

	static KOMA_TYPE sfen_koma_to_coyuri(char ch)
	{
		switch (ch)
		{
		case 'K':
			return OU;
		case 'R':
			return HISHA;
		case 'B':
			return KAKU;
		case 'G':
			return KIN;
		case 'S':
			return GIN;
		case 'N':
			return KEIMA;
		case 'L':
			return KYOUSHA;
		case 'P':
			return HU;
		case 'k':
			return EN_OU;
		case 'r':
			return EN_HISHA;
		case 'b':
			return EN_KAKU;
		case 'g':
			return EN_KIN;
		case 's':
			return EN_GIN;
		case 'n':
			return EN_KEIMA;
		case 'l':
			return EN_KYOUSHA;
		case 'p':
			return EN_HU;
		default:
			break;
		}

		return EMPTY;
	}

	BANMEN *load_position(std::stringstream & ss)
	{
		BANMEN *banmen = new BANMEN;
		u8_t x, y, n, limit;

		std::string banmen_sfen, work;
		std::stringstream sfen_ss;
		ss >> banmen_sfen;

		std::replace(banmen_sfen.begin(), banmen_sfen.end(), '/', ' ');

		sfen_ss << banmen_sfen;

		for (y = 0; y < 9; ++y)
		{
			sfen_ss >> work;
			for (x = 0; x < work.length(); ++x)
			{
				if (work.c_str()[x] >= '0' && work.c_str()[x] <= '9')
				{
					for (n = 0, limit = ctoi(work.c_str()[x]); n < limit; ++n, ++x)
					{
						banmen->set_type(x, y, EMPTY);
					}
				}
				else
				{
					banmen->set_type(x, y, sfen_koma_to_coyuri(work.c_str()[x]));
				}
			}
		}

		return banmen;
	}

	BANMEN *create_start_position() {
		BANMEN *banmen = new BANMEN;
		u8_t n;
		
		banmen->set_type(0, 0, EN_KYOUSHA);
		banmen->set_type(1, 0, EN_KEIMA);
		banmen->set_type(2, 0, EN_GIN);
		banmen->set_type(3, 0, EN_KIN);
		banmen->set_type(4, 0, EN_OU);
		banmen->set_type(5, 0, EN_KIN);
		banmen->set_type(6, 0, EN_GIN);
		banmen->set_type(7, 0, EN_KEIMA);
		banmen->set_type(8, 0, EN_KYOUSHA);

		banmen->set_type(1, 1, EN_HISHA);
		banmen->set_type(7, 1, EN_KAKU);

		for (n = 0; n < 9; ++n)
		{
			banmen->set_type(n, 2, EN_HU);
		}

		for (n = 0; n < 9; ++n)
		{
			banmen->set_type(n, 6, EN_HU);
		}

		banmen->set_type(0, 8, EN_KYOUSHA);
		banmen->set_type(1, 8, EN_KEIMA);
		banmen->set_type(2, 8, EN_GIN);
		banmen->set_type(3, 8, EN_KIN);
		banmen->set_type(4, 8, EN_OU);
		banmen->set_type(5, 8, EN_KIN);
		banmen->set_type(6, 8, EN_GIN);
		banmen->set_type(7, 8, EN_KEIMA);
		banmen->set_type(8, 8, EN_KYOUSHA);

		banmen->set_type(1, 7, EN_HISHA);
		banmen->set_type(7, 7, EN_KAKU);

		return banmen;

	}

}