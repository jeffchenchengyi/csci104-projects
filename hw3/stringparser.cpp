#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
//#include "stackstr.h"

using namespace std;

//Only '<', '>', & alphabets can succeed '-'
bool isLegalAftAddChar(char x) {
    return (x == '<' || x == '>' || isalpha(x)) ? true : false;
}

//Only '(', '<', '>', & alphabets can succeed '-'
bool isLegalAftSubtrChar(char x) {
    return (x == '(' || x == '<' || x == '>' || isalpha(x)) ? true : false;
}

//Only '-', '+', ')', & alphabets can succeed alphabets
bool isLegalAftAlphaChar(char x) {
    return (x == '-' || x == '+' || x == ')' || isalpha(x)) ? true : false;
}

//Only '(', '<', '>', & alphabets can succeed '<' or '>'
bool isLegalAftRemoveChar(char x) {
    return (x == '(' || x == '<' || x == '>' || isalpha(x)) ? true : false;
}

//Only '<', '>', '(', & alphabet can succeed ')'
bool isLegalAftOpenParenChar(char x) {
    return (x == '<' || x == '>' || x == '(' || isalpha(x)) ? true : false;
}

//Only '-', ')', & nothing can succeed ')'
bool isLegalAftCloseParenChar(char x) {
    return (x == '-' || x == ')' || x == '') ? true : false;
}

//Check to see if char is whitespace
bool isWhiteSpace(char x) {
    return (x == ' ') ? true : false;
}

//Check if char is one of the valid characters allowed
bool isLegalChar(char x) {
    return (isalpha(x) || x == '(' || x == ')' || x == '-' 
        || x == '+' || x == '<' || x == '>') ? true : false;
}

int main(int argc, char* argv[])
{
    //To check if the input and output file was also included as a command line parameter
    if (argc < 3) {
       cerr << "Please provide an input and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "Input file could not be open." << endl;
        return 1;
    }

    //If the output file given could not be found or could not be open
    if(output.fail()) {
        cout << "Output file could not be open." << endl;
        return 1;
    }

    //string to store each line in input file
    string line;

    //Getting the command in the input file
    while(getline(input, line)) {
        int len = line.length();
        /*
        //Stack to track parentheses
        stack <char> paren_stack;

        //Stack to track other expressions
        stack <char> exp_stack;

        //Stack to track final evaluation
        stack <char> eval_stack;
    */      
        if(len != 0) {
            for(int i = 0; i < (int)line.length(); i++) {
                if(!isLegalChar(line[i])) {
                    if(isWhiteSpace(line[i])) {
                        line.erase(i, 1);
                        i--;
                    } else {
                        output << "Malformed" << endl;
                        break;
                    }
                } else {
                    cout << line[i];
                }
            }
            cout << endl;
        } else {
            output << "Malformed" << endl;
        }
    }

    return 0;
}