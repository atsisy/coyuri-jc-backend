#pragma once

#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace cut {

	class clock {

	private:
		std::chrono::system_clock::time_point begin;
		std::chrono::system_clock::time_point end;
		double result_val;

	public:
		clock();
		void start();
		double stop();
		double result();

	};

	class json_parser {
	
	private:
		boost::property_tree::ptree p_tree;

	public:
		json_parser(std::string file_name);

		void reset(std::string file_name);

		template <typename _return_type>
		_return_type get_value(std::string key)
		{
			if (boost::optional<_return_type> value = p_tree.get_optional<_return_type>(key)) {
				return value.get();
			}

			std::cerr << "Error. FAILD TO PARSE JSON FILE. KEY NOT FOUND -> " << key << "." << std::endl;
			exit(-1);
		}

		bool is_exist(std::string key);

		std::vector<std::string> json_parser::get_children(std::string key, std::string child_key)
		{
			std::vector<std::string> result;

			BOOST_FOREACH(const boost::property_tree::ptree::value_type & child, p_tree.get_child(key)) {
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

	};

}