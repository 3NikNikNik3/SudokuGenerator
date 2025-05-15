#!/bin/bash

if [ "$1" == "res" ]; then
	g++ -c generator.hpp generator.cpp -O3 -s
	g++ main.cpp generator.o -o SudokuGenerator -O3 -s
else
	g++ -c generator.hpp generator.cpp
	g++ main.cpp generator.o -o SudokuGenerator
fi

rm generator.o generator.hpp.gch
