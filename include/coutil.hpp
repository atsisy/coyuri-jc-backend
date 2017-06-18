#pragma once

#include <chrono>

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

}