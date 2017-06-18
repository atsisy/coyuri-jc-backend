#pragma once

#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>

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
		std::string get_value(std::string key)
		{
			if (boost::optional<_return_type> value = p_tree.get_optional<_return_type>(key)) {
				return value.get();
			}

			std::cerr << "Error. FAILD TO PARSE JSON FILE. KEY NOT FOUND -> " << key << "." << std::endl;
			exit(-1);
		}
	};

}