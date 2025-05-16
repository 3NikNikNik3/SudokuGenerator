#include "generator.hpp"

#include <cstdlib>
#include <set>

namespace SudokuGenerator {
	Number::Number(char x, char y, char num): x(x), y(y), num(num) {}

	std::vector<Number> *result = nullptr;

	void generate(std::vector<Number> *res, char *ans) {
		result = res;

		result->clear();
		while (!real_generate(ans)) result->clear();
	}

	char get_count(unsigned short &what, char &cache) {
		if (cache != -1)
			return cache;
		if (!(what >> 9)) {
			char count = 0;
			for (unsigned short now = what & ((1 << 9) - 1); now != 0; now >>= 1)
				count += now & 1;

			if (count == 1)
				what |= 1 << 9;
			cache = count;
			return count;
		}
		cache = 1;
		return 1;
	}

	char get_first_1(unsigned short num) {
		char i = 0;
		for (num &= (1 << 9) - 1; num != 0; num >>= 1, ++i)
			if (num & 1)
				return i;
		return 10;
	}

	bool real_generate(char *ans) {
		// 0-8 - number is, 9 - one
		unsigned short field[81];
		char cache[81];
		for (int i = 0; i < 81; ++i) {
			field[i] = (1 << 9) - 1;
			cache[i] = -1;
		}

		char variants[81];
		int len_variants = 0;

		while (true) {
			// create variants
			len_variants = 0;
			char count_max = 0;
			for (char i = 0; i < 81; ++i) {
				if (!(field[i] >> 9)) {
					char count = get_count(field[i], cache[i]);
					if (count_max < count) {
						len_variants = 1;
						variants[0] = i;
						count_max = count;
					} else if (count_max == count)
						variants[len_variants++] = i;
				}
			}

			// check end
			if (len_variants == 0) {
				for (int i = 0; i < 81; ++i)
					ans[i] = get_first_1(field[i]) + 1;
				return true;
			}

			// what chose
			char open_now = variants[rand() % len_variants];
			unsigned short open_number = rand() % count_max + 1;
			for (char now = field[open_now] & ((1 << 9) - 1), i = 0; now != 0; now >>= 1, ++i) {
				open_number -= now & 1;
				if (open_number == 0) {
					open_number = ((1 << 9) - 1) - (1 << i);
					field[open_now] = (1 << 9) | (1 << i);
					cache[open_now] = 1;
					result->push_back({open_now % 9, open_now / 9, i + 1});
					break;
				}

			}

			// choseing
			std::pair<char, unsigned short> will_open[81];
			char len_will_open = 0;
			will_open[len_will_open++] = {open_now, open_number};
			for (char k = 0; k < len_will_open; ++k) {
				std::pair<char, unsigned short> now = will_open[k];

				// |
				for (char j = 0; j < 9; ++j)
					if (j != now.first / 9) {
						if (!(field[j * 9 + now.first % 9] >> 9)) {
							field[j * 9 + now.first % 9] &= now.second;
							cache[j * 9 + now.first % 9] = -1;

							char count = get_count(field[j * 9 + now.first % 9], cache[j * 9 + now.first % 9]);
							if (count == 1) {
								will_open[len_will_open++] = {j * 9 + now.first % 9, ((1 << 9) - 1) - ((unsigned short)1 << get_first_1(field[j * 9 + now.first % 9]))};
							} else if (count == 0)
								return false;
						}
					}

				// -
				for (char j = 0; j < 9; ++j)
					if (j != now.first % 9) {
						if (!(field[j + now.first / 9 * 9] >> 9)) {
							field[j + now.first / 9 * 9] &= now.second;
							cache[j + now.first / 9 * 9] = -1;

							char count = get_count(field[j + now.first / 9 * 9], cache[j + now.first / 9 * 9]);
							if (count == 1)
								will_open[len_will_open++] = {j + now.first / 9 * 9, ((1 << 9) - 1) - (1 << get_first_1(field[j + now.first / 9 * 9]))};
							else if (count == 0)
								return false;
						}
					}

				// rect
				const char rect_x = (now.first % 9 / 3), rect_y = (now.first / 9) / 3;
				for (char x = 0; x < 3; ++x)
					for (char y = 0; y < 3; ++y) {
						int now_j = rect_x * 3 + x + (rect_y * 3 + y) * 9;
						if (now_j != now.first)
							if (!(field[now_j] >> 9)) {
								field[now_j] &= now.second;
								cache[now_j] = -1;

								char count = get_count(field[now_j], cache[now_j]);
								if (count == 1)
									will_open[len_will_open++] = {now_j, ((1 << 9) - 1) - (1 << get_first_1(field[now_j]))};
								else if (count == 0)
									return false;
							}
					}
			}
		}
	}
}
