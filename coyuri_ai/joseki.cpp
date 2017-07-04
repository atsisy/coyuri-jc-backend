#include "types.hpp"
#include "coutil.hpp"

cut::Jouseki::Jouseki(std::string file_name)
{
	u8_t i, size;
	std::vector<i64_t> x_vector;
	std::vector<i64_t> y_vector;
	std::vector<i64_t> from_x_vector;
	std::vector<i64_t> from_y_vector;
	std::vector<KOMA_TYPE> type_vector;

	cut::json_parser parser(file_name);

	load_json_elem<i64_t>(parser, "Jouseki", "go_x", &x_vector);
	load_json_elem<i64_t>(parser, "Jouseki", "go_y", &y_vector);
	load_json_elem<i64_t>(parser, "Jouseki", "from_x", &from_x_vector);
	load_json_elem<i64_t>(parser, "Jouseki", "from_y", &from_y_vector);
	load_json_elem<KOMA_TYPE>(parser, "Jouseki", "type", &type_vector);

	for (i = 0, size = x_vector.size(); i < size; ++i) {
		this->jouseki_list.push_back(Te(from_x_vector.at(i), from_y_vector.at(i), x_vector.at(i), y_vector.at(i), type_vector.at(i), _AI_TURN));
	}

}