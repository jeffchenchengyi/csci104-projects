# Instructions on how to execute hw3 programs:

## [Problems 1 (Class Structure and Inheritance, 15%)](hw4.jpg)

> Answers are in **`hw4.jpg`**.


## [Problem 2 (Web Search, 85%)](search.cpp)

### Use [MakeFile](Makefile) to compile webpage.h and webpage.cpp into webpage.o and webpage.o and search.cpp to search:
> **`make search`** 

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./search input.txt query.txt output.txt`**, 
to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks 
suppressed.

### Run: 
> **`./search input.txt query.txt output.txt`**

### Remove executables:
> **`make clean`**