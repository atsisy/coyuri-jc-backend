#include "coutil.hpp"

namespace cut {

	clock::clock() {}

	void clock::start() {
		begin = std::chrono::system_clock::now();
	}

	double clock::stop() {
		end = std::chrono::system_clock::now();
		result_val = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		return result_val;
	}

	double clock::result() {
		return result_val;
	}
}