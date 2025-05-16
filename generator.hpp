#include <vector>

namespace SudokuGenerator {
	struct Number {
		char x, y, num;

		Number(char x, char y, char num);
	};

	void generate(std::vector<Number> *res, char *ans);

	bool real_generate(char *ans);
}
