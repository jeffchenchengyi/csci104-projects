#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

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

    //Couting one newline character at the end of everything
    cout << endl;

    return 0;
}