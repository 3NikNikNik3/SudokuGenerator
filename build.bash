#!/bin/bash

g++ -c generator.hpp generator.cpp
g++ main.cpp generator.o -o SudokuGenerator
rm generator.o generator.hpp.gch
