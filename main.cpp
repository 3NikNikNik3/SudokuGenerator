#include <iostream>
#include <fstream>

#include "generator.hpp"

using namespace std;
using namespace SudokuGenerator;

void print(ostream *out, char arr[81], bool buiti) {
	if (buiti)
		*out << "/-----------\\" << endl;
	for (char i = 0; i < 3; ++i) {
		for (char j = 0; j < 9; ++j) {
			if (buiti)
				*out << '|';
			for (char k = 0; k < 3; ++k) {
				*out << arr[i * 27 + j * 3 + k];
			}
			if (j % 3 == 2) {
				if (buiti)
					*out << '|';
				*out << endl;
			}
		}
		if (buiti && i != 2)
			*out << "|-----------|" << endl;
	}
	if (buiti)
		*out << "\\-----------/" << endl;
}

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
	print(&cout, res, true);

	cout << "enter something to see answer ";
	char q;
	cin >> q;

	cout << endl << "answer:" << endl;
	for (char i = 0; i < 81; ++i)
		ans[i] += '0';
	print(&cout, ans, true);

	delete[] ans;

	return 0;
}
