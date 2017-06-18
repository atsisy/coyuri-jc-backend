#include "coutil.hpp"
#include <iostream>

namespace cut {

	json_parser::json_parser(std::string file_name)
	{
		boost::property_tree::read_json(file_name, p_tree);
	}

	void json_parser::reset(std::string file_name)
	{
		boost::property_tree::read_json(file_name, p_tree);
	}

}