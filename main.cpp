#include <iostream>
#include <fstream>

#include "generator.hpp"

using namespace std;
using namespace SudokuGenerator;

int main() {
	#ifdef linux
		fstream random_seed("/dev/urandom", ios::in);

		unsigned int seed;
		unsigned char in_char;
		for (char i = 0; i < 4; ++i) {
			random_seed >> in_char;
			seed = (seed << 8) + in_char;
		}

		random_seed.close();
		srand(seed);
	#else
		srand(time(0));
	#endif

	vector<Number> arr;
	generate(&arr);
	cout << arr.size() << endl;
	for (int i = 0; i < arr.size(); ++i)
		cout << (int)arr[i].x << ' ' << (int)arr[i].y << ' ' << (int)arr[i].num << endl;

	char res[81];
	for (int i = 0; i < 81; ++i) res[i] = 0;
	for (int i = 0; i < arr.size(); ++i)
		res[arr[i].x + arr[i].y * 9] = arr[i].num;

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j)
			cout << (int)res[j + i * 9];
		cout << endl;
	}

	return 0;
}
