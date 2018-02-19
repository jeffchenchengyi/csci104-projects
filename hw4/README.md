# Instructions on how to execute hw3 programs:

## [Problems 2 - 3:](CSCI-104hw3q2q3.pdf)

> Answers are in **`CSCI-104hw3q2q3.pdf`**.


## EITHER - 

## [Problem 4 (Stacks, 10%)](stackstr.cpp)
### [Header file for Stack class](stackstr.h)
### [Header file for LListStr class](lliststr.h)
### [Cpp file for LListStr class](lliststr.cpp)

### Use [MakeFile](Makefile) to compile stackstr.cpp stackstr.h lliststr.o:
> **`make stackstr.o`** 

### Remove executables:
> **`make clean`**


## [Problem 5 (String Expression Parser and Evaluator, 50%)](stringparser.cpp)

### Use [MakeFile](Makefile) to compile lliststr.o, stackstr.o, stringparser.cpp:
> **`make stringparser`** 

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./stringparser input.txt output.txt`**, 
to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks 
suppressed.

### Run: 
> **`./stringparser input.txt output.txt`**

### Remove executables:
> **`make clean`**



## OR - 

## [Problem 4 (Stacks, 10%)](stackstr.cpp)
### [Header file for Stack class](stackstr.h)
### [Header file for LListStr class](lliststr.h)
### [Cpp file for LListStr class](lliststr.cpp)

### Compile: 
> **`g++ -g -Wall -std=c++11 stackstr_application.cpp stackstr.cpp lliststr.cpp -o stackstr_application`**, 
which compiles executable in **`stackstr_application`**

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./stackstr_application`**, 
to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks 
suppressed.

### Run: 
> **`./stackstr_application`**


## [Problem 5 (String Expression Parser and Evaluator, 50%)](stringparser.cpp)

### Compile: 
> **`g++ -g -Wall -std=c++11 stringparser.cpp stackstr.cpp lliststr.cpp -o stringparser input.txt output.txt`**, which compiles 
executable in **`stringparser`**

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all 
./stringparser`**, to check if there are any memory leaks, 
should be only 72,704 bytes in 1 blocks suppressed

### Run: 
> **`./stringparser input.txt output.txt`**