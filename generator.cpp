#include "generator.hpp"

namespace SudokuGenerator {
	std::vector<Number> *result = nullptr;

	void generate(std::vector<Number> *res) {
		result = res;

		result->clear();
		while (!real_generate()) result->clear();
	}

	bool real_generate() {
		return true;
	}
}
