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

	bool json_parser::is_exist(std::string key)
	{
		if (boost::optional<std::string> value = p_tree.get_optional<std::string>(key)) {
			return true;
		}
		else
		{
			return false;
		}
	}
}