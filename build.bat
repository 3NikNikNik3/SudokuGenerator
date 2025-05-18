if "%1" == "res" (
	g++ generator.cpp generator.hpp -c -O3 -s
	g++ generator.o main.cpp -o SudokuGenerator.exe -O3 -s
) else if "%1" == "static" (
	g++ generator.cpp generator.hpp -c -O3 -static -s
	g++ generator.o main.cpp -o SudokuGenerator.exe -O3 -static -s
) else (
	g++ generator.cpp generator.hpp -c
	g++ generator.o main.cpp -o SudokuGenerator.exe
)
del generator.o
del generator.hpp.gch