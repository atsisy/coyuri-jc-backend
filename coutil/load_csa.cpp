#include "file_reader.hpp"

namespace cut
{

	static u8_t ctoi(char ch) {
		return ('0' <= ch && ch <= '9') ? ch - '0' : 0;
	}

	static void shougi_point_to_coyuri_point(u8_t *x, u8_t *y) {
		*x = (9 - *x);
		*y -= 1;
	}

	static KOMA_TYPE sente_csa_koma_to_coyuri_koma(char first, char second)
	{
		switch (first)
		{
		case 'F':
			switch (second)
			{
			case 'U':
				return HU;
			default:
				break;
			}
			break;
		case 'K':
			switch (second)
			{
			case 'Y':
				return KYOUSHA;
			case 'E':
				return KEIMA;
			case 'I':
				return KIN;
			case 'A':
				return KAKU;
			default:
				break;
			}
			break;
		case 'G':
			return GIN;
		case 'O':
			return OU;
		case 'H':
			return HISHA;
		case 'T':
			return TOKIN;
		case 'N':
			switch (second)
			{
			case 'Y':
				return NARIKYOU;
			case 'K':
				return NARIKEI;
			case 'G':
				return NARIGIN;
			default:
				break;
			}
			break;
		case 'U':
			return UMA;
		case 'R':
			return RYU;
		default:
			break;
		}
	}

	static KOMA_TYPE gote_csa_koma_to_coyuri_koma(char first, char second)
	{
		switch (first)
		{
		case 'F':
			switch (second)
			{
			case 'U':
				return EN_HU;
			default:
				break;
			}
			break;
		case 'K':
			switch (second)
			{
			case 'Y':
				return EN_KYOUSHA;
			case 'E':
				return EN_KEIMA;
			case 'I':
				return EN_KIN;
			case 'A':
				return EN_KAKU;
			default:
				break;
			}
			break;
		case 'G':
			return EN_GIN;
		case 'O':
			return EN_OU;
		case 'H':
			return EN_HISHA;
		case 'T':
			return EN_TOKIN;
		case 'N':
			switch (second)
			{
			case 'Y':
				return EN_NARIKYOU;
			case 'K':
				return EN_NARIKEI;
			case 'G':
				return EN_NARIGIN;
			default:
				break;
			}
			break;
		case 'U':
			return EN_UMA;
		case 'R':
			return EN_RYU;
		default:
			break;
		}
	}

	CsaLoader::CsaLoader(std::string file_name)
	{
		std::ifstream ifs(file_name);
		std::string str;
		char te_str[te_string_length + 1];
		u8_t from_x, from_y, will_x, will_y;
		KOMA_TYPE type;

		if (ifs.fail())
		{
			std::cerr << "FAILD TO LOAD CSA FILE.   May be file name is wrong." << std::endl;
		}

		getline(ifs, this->csa_version);
		getline(ifs, this->sente_name);
		getline(ifs, this->gote_name);
		getline(ifs, this->event_name);
		getline(ifs, this->site);
		getline(ifs, this->start_time);
		getline(ifs, this->end_time);
		getline(ifs, this->opening);

		for (u8_t y = 0; y < 10; ++y) {
			getline(ifs, str);
		}

		while (ifs.getline(te_str, te_string_length))
		{
			from_x = ctoi(te_str[1]);
			from_y = ctoi(te_str[2]);
			will_x = ctoi(te_str[3]);
			will_y = ctoi(te_str[4]);

			shougi_point_to_coyuri_point(&from_x, &from_y);
			shougi_point_to_coyuri_point(&will_x, &will_y);

			if (te_str[0] == '+')
			{
				this->kif.push_back(Te(from_x, from_y, will_x, will_y, sente_csa_koma_to_coyuri_koma(te_str[5], te_str[6]), SENTE_FLAG));
			}
			else
			{
				this->kif.push_back(Te(from_x, from_y, will_x, will_y, gote_csa_koma_to_coyuri_koma(te_str[5], te_str[6]), SENTE_FLAG));
			}
		}
	}

}