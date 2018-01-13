#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

void reverseSentence(ifstream &input, int *numWordsLeft) {
    string nextWord = "";

    //Base case: When the number of words left in the sentence is 1
    if(*numWordsLeft == 1) {
        input >> nextWord;
        cout << nextWord << " ";
    } 
    //Recursive case: Having the cout after the call to itself ensures that the next word is outputted before the current word
    else {
        input >> nextWord;
        (*numWordsLeft)--;
        reverseSentence(input, numWordsLeft);
        cout << nextWord << " ";
    }
}

int main(int argc, char* argv[])
{
    //To check if the input file was also included as a command line parameter
    if (argc < 2) {
	   cerr << "Please provide an input file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    int numWords = 0;

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "Input file could not be open." << endl;
        return 1;
    }

    //Getting integer representing the number of strings in the file
    input >> numWords;
    
    //Primary function
    reverseSentence(input, &numWords);

    return 0;
}