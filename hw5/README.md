# Instructions on how to execute hw5 programs:

## [Problems 1c (Break QuickSort, 5%), 2 (Break Interpolation Search, 10%):](hw5.txt)

> Answers are in **`hw5.txt`**.


## [Problem 3 (Median Finding in Linear Time, 30%):](hw5q3.pdf)

> Answers are in **`hw5.txt`**.


## [Problem 1a (Write a Functor, 5%)](functor.cpp)
### [Header file for Functor class](functor.h)

### Use [MakeFile](Makefile) to compile functor.cpp functor.h:
> **`make functor.o`** 

### Remove executables:
> **`make clean`**


## [Problem 1b (Implement QuickSort, 25%)](qsort.h)


## [Problem 4 (Create a Custom Exception, 5%)](LengthMismatch.cpp)
### [Header file for LengthMismatch class](LengthMismatch.h)

### Use [MakeFile](Makefile) to compile LengthMismatch.cpp LengthMismatch.h:
> **`make LengthMismatch.o`** 

### Remove executables:
> **`make clean`**


## [Problem 5 (Thanksgiving Dinner, 20%)](Thanksgiving.cpp)
### Use [MakeFile](Makefile) to compile LengthMismatch.o, Thanksgiving.cpp once an int main() is added:
> **`make Thanksgiving`** 

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./Thanksgiving`**, 
to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks 
suppressed.

### Run: 
> **`./Thanksgiving`**

### Remove executables:
> **`make clean`**