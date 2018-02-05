#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <stack>
//#include "stackstr.h"

using namespace std;
/*
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
    return (x == '-' || x == ')') ? true : false;
}
*/

bool isRemoveBack(string x) {
    return (x == "<") ? true : false;
}

bool isRemoveFront(string x) {
    return (x == ">") ? true : false;
}

bool isSubtract(string x) {
    return (x == "-") ? true : false;
}

bool isAdd(string x) {
    return (x == "+") ? true : false;
}

bool isCloseParen(string x) {
    return (x == ")") ? true : false;
}

bool isOpenParen(string x) {
    return (x == "(") ? true : false;
}

//Check to see if char is whitespace
bool isWhiteSpace(char c) {
    return (c == ' ') ? true : false;
}

//Check if char is one of the valid characters allowed
bool isLegalChar(char c) {
    string x(1, c);
    return ((isalpha(c) && islower(c)) || 
            isOpenParen(x) || 
            isCloseParen(x) || 
            isAdd(x) || 
            isSubtract(x) || 
            isRemoveFront(x) || 
            isRemoveBack(x)) ? true : false;
}

string editString(string x) {
    int len = x.length();
    string new_string;
    for (int i = len - 1; i >= 0; i--) {
        string s(1, x[i]);
        if(isRemoveFront(s) && (new_string.length() > 1)) {
            new_string.erase(0, 1);
        } else if(isRemoveBack(s) && (new_string.length() > 1)) {
            new_string.pop_back();
        } else {
            new_string.insert(0, s);
        }
    }
    return new_string;
}

void evalExpression(stack<string>& current_stack) {
    string filtered_string;
    stack<string> exp_stack;
    bool addition = true;
    while(!isOpenParen(current_stack.top())) {
        string current_string;
        while(!(isAdd(current_stack.top()) || 
                isSubtract(current_stack.top()) || 
                isOpenParen(current_stack.top()))) {
            current_string.insert(0, current_stack.top());
            current_stack.pop();
        }
        
        exp_stack.push(current_string);
        if(isAdd(current_stack.top())) {
            current_stack.pop();
        } else if(isSubtract(current_stack.top())) {
            addition = false;
            current_stack.pop();
        } else {
            break;
        }
    }

    if(addition) {
        while(!exp_stack.empty()) {
            string new_string = editString(exp_stack.top());
            exp_stack.pop();
            filtered_string.append(new_string);
        }
    } else {
        filtered_string = editString(exp_stack.top());
        int len = filtered_string.length();
        exp_stack.pop();
        string sub_string = editString(exp_stack.top());
        exp_stack.pop();
        int pos = filtered_string.find(sub_string);
        if(pos >= 0 && pos < len) {
            filtered_string.erase(pos, sub_string.length());
        }
    }

    //Remove the opening parentheses
    current_stack.pop();
    current_stack.push(filtered_string);
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
        bool malformed = false;

        //Stack to store original string
        stack<string> original_stack;

        //Stack to track final string
        stack<string> final_stack;

        //If input string is length == 0, it is malformed
        //Traverse through string to eliminate whitespace
        //and signal if there exists illegal chars
        if(len != 0) {
            for(int i = 0; i < len; i++) {
                if(!isLegalChar(line[i])) {
                    if(isWhiteSpace(line[i])) {
                        line.erase(i, 1);
                        i--;
                        len--;
                    } else {
                        malformed = true;
                        break;
                    }
                }
            }
            if(malformed) {
                output << "Malformed" << endl;
            } else {
                for(int i = 0; i < len; i++) {
                    if(line[i] == ')') {
                        evalExpression(original_stack);
                    } else {
                        string s(1, line[i]);
                        original_stack.push(s);
                    }
                }
                string final_string;
                while(!original_stack.empty()) {
                    final_string.insert(0, original_stack.top());
                    original_stack.pop();
                }
                output << editString(final_string) << endl;
            }
        } else {
            output << "Malformed" << endl;
        }
    }

    return 0;
}