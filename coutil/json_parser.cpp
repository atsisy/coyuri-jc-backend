#include "coutil.hpp"
#include <iostream>
#include <boost/foreach.hpp>

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

	std::vector<std::string> json_parser::get_children(std::string key, std::string child_key)
	{
		std::vector<std::string> result;

		BOOST_FOREACH(const boost::property_tree::ptree::value_type& child, p_tree.get_child(key)) {
			const boost::property_tree::ptree & info = child.second;

			if (boost::optional<std::string> object = info.get_optional<std::string>(child_key))
			{
				result.push_back(object.get());
			}
			else {
				std::cerr << "FAILD TO PARSE. IN FUNCTION json_parser::get_children" << std::endl;
				exit(-1);
			}
		}

		return result;
	}
}