## Instructions on how to execute hw1 programs:

# Problems 1 - 4:

> Included in hw1.txt, questions are also included.



# Problem 5:

> Compile: **`g++ -g -Wall -std=c++11 barry.cpp barry`**, which compiles executable in **`barry`**

> Memory leak check: **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./barry`**, to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks suppressed.

> Run: **`./barry XXXXXXXXXX`**, where **`XXXXXXXXXX`** is the max. 10 digit number used to check if **_increasing order_** or **_Not increasing order_**. 



# Problem 6:

> Compile: **`g++ -g -Wall -std=c++11 hw1q6.cpp hw1q6`**, which compiles executable in **`hw1q6`**

> Memory leak check: **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./hw1q6 hw1q6_input.txt`**, to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks suppressed

> Run: **`./hw1q6 hw1q6_input.txt`**, where **`hw1q6input.txt`** is the input file used. Program will reverse the sentence included in **`hw1q6input.txt`** and separate each word by a single whitespace. First sentence must be an integer that indicates how many words there are inside the sentence to be reversed.



# Problem 7:

> Compile: **`g++ -g -Wall -std=c++11 game_of_pointers.cpp game_of_pointers`**, which compiles executable in **`game_of_pointers`**.

> Memory leak check: **`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./game_of_pointers game_of_pointers_input.txt game_of_pointers_output.txt`**, to check if there are any memory leaks, should be only 72,704 bytes in 1 blocks suppressed.

> Run: **`./game_of_pointers game_of_pointers_input.txt game_of_pointers_output.txt`**, where **`game_of_pointers_input.txt`** is the input file that has at least 4 lines, where each line has exactly one non-negative integer. The first integer indicates n, the number of rows of protectors and also the number of columns of invaders. The second integer indicates m, the number of columns of protectors and also the number of rows of invaders. The third integer indicates how many protectors there are in reserve. The fourth integer indicates x, the number of skirmishes. There will be exactly x more lines (after the first 4) in the input file, indicating who fights in each duel (more details below). **`game_of_pointers_output.txt`** will contain the results of the battle and the winner at the last line after the program is run.