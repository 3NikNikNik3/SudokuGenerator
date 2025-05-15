#include <iostream>

#include "generator.hpp"

using namespace std;
using namespace SudokuGenerator;

int main() {
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
