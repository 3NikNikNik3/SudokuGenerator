#include <iostream>
#include <fstream>

#include "generator.hpp"

using namespace std;
using namespace SudokuGenerator;

int main() {
	// init random seed
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

	// generate
	vector<Number> arr;
	char *ans = new char[81];
	generate(&arr, ans);

	// make field sudoku
	char res[81];
	for (int i = 0; i < 81; ++i) res[i] = ' ';
	for (int i = 0; i < arr.size(); ++i)
		res[arr[i].x + arr[i].y * 9] = arr[i].num + '0';

	// print
	cout << "sudoku:" << endl;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j)
			cout << res[j + i * 9];
		cout << endl;
	}

	cout << "enter something to see answer ";
	char q;
	cin >> q;

	cout << endl << "answer:";
	for (char i = 0; i < 81; ++i) {
		if (i % 9 == 0) cout << endl;
		cout << (int)ans[i];
	}
	cout << endl;

	delete[] ans;

	return 0;
}
