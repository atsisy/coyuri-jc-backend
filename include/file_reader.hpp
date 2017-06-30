#pragma once

#include "coutil.hpp"

namespace cut
{
	class CsaLoader {

	private:
		std::vector<Te> kif;
		std::string csa_version;
		std::string sente_name;
		std::string gote_name;
		std::string event_name;
		std::string site;
		std::string start_time;
		std::string end_time;
		std::string opening;
		BANMEN first_banmen;

	public:
		CsaLoader(std::string file_name);

	};

	constexpr u8_t te_string_length = 7;
}