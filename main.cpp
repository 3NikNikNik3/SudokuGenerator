#include <iostream>
#include <fstream>
#include <chrono>

#include "generator.hpp"

using namespace std;
using namespace SudokuGenerator;

void print(ostream *out, char arr[81], bool beau) {
	if (beau)
		*out << "/-----------\\" << endl;
	for (char i = 0; i < 3; ++i) {
		for (char j = 0; j < 9; ++j) {
			if (beau)
				*out << '|';
			for (char k = 0; k < 3; ++k) {
				*out << arr[i * 27 + j * 3 + k];
			}
			if (j % 3 == 2) {
				if (beau)
					*out << '|';
				*out << endl;
			}
		}
		if (beau && i != 2)
			*out << "|-----------|" << endl;
	}
	if (beau)
		*out << "\\-----------/" << endl;
}

const string arg_to_file[2] = { "-field-to-file=", "-answer-to-file=" };
const string arg_none = { "-none=" };

bool is_to_file_arg(const string &arg) {
	if (arg.size() < 15)
		return false;

	char what = 0;
	if (arg[1] == 'a') what = 1;

	for (char i = 0; i < arg_to_file[what].size(); ++i)
		if (arg[i] != arg_to_file[what][i])
			return false;
	return true;
}

bool is_none_arg(const string &arg) {
	if (arg.size() < 7)
		return false;

	for (char i = 0; i < 6; ++i)
		if (arg[i] != arg_none[i])
			return false;
	return true;
}

int main(int argc, char **argv) {
	// init random seed
	auto seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

	srand(seed);

	// parse arg
	bool beautiful = true, wait = true;
	ostream *out_ans = &cout, *out_field = &cout;
	// 0 - res, 1 - ans
	char use_file = 0;
	char def_none = ' ';

	for (int i = 1; i < argc; ++i) {
		string arg(argv[i]);
		if (arg == "-h" || arg == "--h" || arg == "-help") {
			cout << "This programm is generator of sudoku game\n\t-h (--h, -help) - print help...\n\t-not-beaut - without beautiful print\n\t-not-wait - dont wait to print answer\n\t-none=<char> - set none-char on field, use only first char. On default is ' '\n\t-field-to-file=<file> - put field to <file>\n\t-answer-to-file=<file> - put answer to <file>" << std::endl;
			return 0;
		} else if (arg == "-not-beaut")
			beautiful = false;
		else if (arg == "-not-wait")
			wait = false;
		else if (is_none_arg(arg))
			def_none = arg[6];
		else if (is_to_file_arg(arg)) {
			int from_i;
			if (arg[1] == 'a') {
				use_file |= 2;
				from_i = 16;
			} else {
				use_file |= 1;
				from_i = 15;
			}

			ofstream *file = new ofstream;
			arg.erase(arg.begin(), arg.begin() + from_i);
			file->open(arg, ios::app);

			if (from_i == 16)
				out_ans = file;
			else
				out_field = file;
		} else {
			#ifdef linux
				cerr << "\033[31m";
			#endif
			cerr << "Error: I dont know, what happend " << arg << endl;
			return 1;
		}
	}

	// generate
	vector<Number> arr;
	char *ans = new char[81];
	generate(&arr, ans);

	// make field sudoku
	char res[81];
	for (int i = 0; i < 81; ++i) res[i] = def_none;
	for (int i = 0; i < arr.size(); ++i)
		res[arr[i].x + arr[i].y * 9] = arr[i].num + '0';

	// print
	if (beautiful && !(use_file & 1))
		*out_field << "sudoku:" << endl;
	print(out_field, res, beautiful);

	if (wait) {
		cout << "enter something to see answer ";
		char q;
		cin >> q;
	}

	if (beautiful && !(use_file & 2))
		*out_ans << "answer:" << endl;
	for (char i = 0; i < 81; ++i)
		ans[i] += '0';
	print(out_ans, ans, beautiful);

	// close

	if (use_file & 1) {
		((ofstream*)out_field)->close();
		delete out_field;
	}
	if (use_file & 2) {
		((ofstream*)out_ans)->close();
		delete out_ans;
	}

	delete[] ans;

	#ifdef _WIN32
		if (argc == 1)
			system("pause");
	#endif

	return 0;
}
