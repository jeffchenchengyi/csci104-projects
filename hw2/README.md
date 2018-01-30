# Instructions on how to execute hw2 programs:

## [Problems 1 - 4:](hw2.txt)

> Included in **`hw2.txt`**, questions are also included.



## [Problem 5:](fullsort.cpp)

### Compile: 
> Add in some **`main`** code that passes in a pointer to the head 
of a mostly sorted list(or any list to be sorted) into the
fullsort function and it will return a pointer to the
head of a sorted list
**`g++ -g -Wall -std=c++11 fullsort.cpp -o fullsort`**, 
which compiles executable in **`fullsort`**

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./fullsort`**, 
to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks 
suppressed.

### Run: 
> **`./fullsort`**



## [Problem 6:](lliststr.cpp)
### [Header file for  class](lliststr.h)
### [Test Cases Program](lliststr_test.cpp)

### Compile: 
> **`g++ -g -Wall -std=c++11 lliststr_test.cpp lliststr.cpp -o lliststr_test`**, which compiles 
executable in **`lliststr_test`**

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all 
./lliststr_test`**, to check if there are any memory leaks, 
should be only 72,704 bytes in 1 blocks suppressed

### Run: 
> **`./lliststr_test`**



## [Problem 7:](assassin.cpp)

### Compile: 
> **`g++ -g -Wall -std=c++11 assassin.cpp lliststr.cpp -o assassin`**, 
which compiles executable in **`assassin`**.

### Memory leak check: 
> **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all 
./assassin assassin_input.txt`**, 
to check if there are any memory leaks, should be only 
72,704 bytes in 1 blocks suppressed.

### Run: 
> **`./assassin assassin_input.txt`**, where **`assassin_input.txt`**, 
contains the list of commands for the game, such as:

>**`ADD 0 Sandra
ADD 0 Aaron
ACT 1`**

> Output on Terminal:

>**`Assassinated: Aaron
Winner: Sandra`**