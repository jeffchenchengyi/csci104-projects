# Instructions on how to execute hw2 programs:

## [Problems 2 - 3:](hw3.txt)

> Included in **`hw3.txt`**, questions are also included.



## [Problem 4 (Stacks, 10%)](stackstr.cpp)
### [Header file for Stack class](stackstr.h)
### [Header file for LListStr class](../hw2/lliststr.h)
### [Cpp file for LListStr class](../hw2/lliststr.cpp)

### Compile: 
> **`g++ -g -Wall -std=c++11 stackstr_application.cpp stackstr.cpp ../hw2/lliststr.cpp -o stackstr_application`**, 
which compiles executable in **`stackstr_application`**

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./stackstr_application`**, 
to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks 
suppressed.

### Run: 
> **`./stackstr_application`**



## [Problem 5 (String Expression Parser and Evaluator, 50%)](stringparser.cpp)

### Compile: 
> **`g++ -g -Wall -std=c++11 stringparser.cpp stackstr.cpp ../hw2/lliststr.cpp -o stringparser`**, which compiles 
executable in **`stringparser`**

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all 
./stringparser`**, to check if there are any memory leaks, 
should be only 72,704 bytes in 1 blocks suppressed

### Run: 
> **`./stringparser`**