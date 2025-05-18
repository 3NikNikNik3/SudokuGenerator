# Sudoku generator

## C++

# About the project

This is a small console-based Sudoku field generator. On average, it generates 27.7 digits.

Example of its work:

```
/-----------\
|   |   |75 |
|39 | 4 |   |
|7  |9  |   |
|-----------|
|  8|  7|2  |
|  7| 92|   |
|   |   |8 6|
|-----------|
|   |43 |   |
|56 | 8 |   |
|   |   | 84|
\-----------/
```

# How to use it

## 1) For personal use

Simply run `./SudokuGenerator` and you will see a Sudoku field. After solving it, enter something to see the solution.

I recommend running it from the console (terminal emulator), but if you are on Windows, you can just open the file.

You can also replace unknown symbols with your own using the flag `-none=<char>`.

## 2) For generating a large number of fields

Run `./SudokuGenerator -field-to-file=fields.txt -answer-to-file=answers.txt -not-wait`, and the fields will appear in the `fields.txt`, while the answers will be in `answers.txt`. You can run it multiple times to get several fields.

For example: `python`
```
import os
for i in range(10):
    os.system('./SudokuGenerator -field-to-file=fields.txt -answer-to-file=answers.txt -not-wait')
```

## 3) For use in other programs

Of course, you can include `generator.h(c)pp`, but my program uses standard output, so you can read the output. In that case, use `./SudokuGenerator -not-beaut -not-wait`.

You will get something like this:

```
2       7
   491   
6     3 8
 3     1 
   9 8 6 
 49    5 
 5    9 3
 17 4    
  432 6  
281563497
773491526
671552398
536264819
121938764
149766852
852117943
317649285
994325671
```

# How to run it locally

## 1) Download the compiled program

You can download it from the [Releases](https://github.com/3NikNikNik3/SudokuGenerator/releases).

## 2) Build it

You will only need `g++`.

Linux: `./build.bash res`

Windows:

`./build.bat res` to use on your PC

`./build.bat static` to use on all PC (with Windows)

And you will only need `SudokuGenerator(.exe)`

# Launch parameters

`-h`, `--h`, `-help` - display all launch parameters

`-not-beaut` - output everything without beauty (all numbers in a row)

`-not-wait` - don't wait before outputting the answer

`-none=<char>` - fill unknown cells with the character `<char>` during output. Default is " "

`-field-to-file=<file>` - put the field in `<file>`. The field is appended to the end of the file

`-answer-to-file=<file>` - put the answer in `<file>`. The answer is appended to the end of the file

# Construction algorithm

We save for each cell which numbers can be in it. We also keep track of whether there is only 1 option left, for speed

We need to repeat until we succeed:

1) Find the cell with the maximum number of options.
2) If only cells with 1 option remain, the field is ready.
3) If not, randomly choose a cell where we will select a specific value.
4) Choose, save of where and what for the field.
5) Remove the selected digit from the necessary places (vertically, horizontally and square). If they cannot be anything, then it is wrong, and we start over :( (on average, 1 retry).
6) Repeat the algorithm until we succeed.

The saved ones are the field, and the answer is the remaining numbers in the cells.

# [ReadMe_ru](https://github.com/3NikNikNik3/SudokuGenerator/blob/main/ReadMe_ru.md)