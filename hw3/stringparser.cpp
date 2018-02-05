#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <stack>
//#include "stackstr.h"

using namespace std;

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
            isRemoveBack(x)
            ) ? true : false;
}

bool isParensOk(const string &line) {
    int open_paren_count = 0;
    int close_paren_count = 0;
    int len = line.length();
    for(int i = 0; i < len; i++) {
        string s(1, line[i]);
        if(isOpenParen(s)) {
            open_paren_count++;
        } else if(isCloseParen(s)) {
            close_paren_count++;
        }
    }
    return (open_paren_count == close_paren_count) ? true : false;
}

//To ensure substring is not <Y> or any other wrong format
bool isLegalStringExp(const string &original_Y) {
    string Y = original_Y;
    bool isLegalString = true;
    int len = Y.length();
    //Ensure last character is an alphabet
    if(isalpha(Y[len - 1])) {
        while(isalpha(Y[len - 1]) && (len > 0)) {
            Y.pop_back();
            len--;
        }
    } else if(isOpenParen(string(1, Y[len - 1]))) {
        Y.pop_back();
    } else {
        isLegalString = false;
        return isLegalString;
    }
    //Ensures no more alphabets remain in string
    //after removing alphabets from the back
    for(int i = 0; i < len; i++) {
        if(isalpha(Y[i])) {
            isLegalString = false;
            return isLegalString;
        }
    }
    return isLegalString;
}

//To ensure that all operators are in the correct pos
bool isOperatorsOk(const string &line) {
    string simple_string;
    int len = line.length();
    for(int i = 0; i < len; i++) {
        if(isalpha(line[i]) || 
                isRemoveFront(string(1, line[i])) || 
                isRemoveBack(string(1, line[i]))) {
            string Y;
            while(!(isAdd(string(1, line[i])) ||
                    isSubtract(string(1, line[i])) ||
                    isOpenParen(string(1, line[i])) ||
                    isCloseParen(string(1, line[i]))) &&
                    (i < len)
                ) {
                Y.append(string(1, line[i]));
                i++;
            }
            if(isOpenParen(string(1, line[i]))) {
                Y.append(string(1, line[i]));
            }
            //To nullify last i++;
            i--;
            if(!isLegalStringExp(Y)) {
                return false;
            }
            simple_string.append("Y");
        } else {
            simple_string.append(string(1, line[i]));
        }
    }
    //Check if there exists at most one "-" is between parentheses
    //Check if every "+" is between parentheses
    int simple_str_len = simple_string.length();

    for(int i = 0; i < simple_str_len; i++) {
        if(isSubtract(string(1, simple_string[i]))) {
            //Check left side of subtract sign
            if((i - 1) >= 0) {
                if(string(1, simple_string[i - 1]) == "Y") {
                    if((i - 2) >= 0) {
                        if(!isOpenParen(string(1, simple_string[i - 2]))) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if(isCloseParen(string(1, simple_string[i - 1]))) {
                    if((i - 2) >= 0) {
                        if(string(1, simple_string[i - 2]) != "Y") {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
            //Check right side of subtract sign
            if((i + 1) < simple_str_len) {
                if(string(1, simple_string[i + 1]) == "Y") {
                    if((i + 2) < simple_str_len) {
                        if(!isCloseParen(string(1, simple_string[i + 2]))) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if(isOpenParen(string(1, simple_string[i + 1]))) {
                    if((i + 2) < simple_str_len) {
                        if(string(1, simple_string[i + 2]) != "Y") {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if(isAdd(string(1, simple_string[i]))) {
            //Check that my sides of addition sign are both Y
            if((i - 1) >= 0) {
                if(string(1, simple_string[i - 1]) != "Y") {
                    return false;
                }
            } else {
                return false;
            }
            if((i + 1) < simple_str_len) {
                if(string(1, simple_string[i + 1]) != "Y") {
                    return false;
                }
            } else {
                return false;
            }
        } else if(isOpenParen(string(1, simple_string[i]))) {
            if((i + 1) < simple_str_len) {
                if(string(1, simple_string[i + 1]) != "Y" && 
                        !isOpenParen(string(1, simple_string[i + 1]))
                        ) {
                    return false;
                }
            } else {
                return false;
            }
        } else if(isCloseParen(string(1, simple_string[i]))) {
            if((i - 1) >= 0) {
                if(string(1, simple_string[i - 1]) != "Y" && 
                        !isCloseParen(string(1, simple_string[i - 1]))
                        ) {
                    return false;
                }
            } else {
                return false;
            }
        } 
    }
    return true;
}

bool isIllegalExp(const string &line) {
    return (!(isParensOk(line)) || 
            !(isOperatorsOk(line))
            ) ? true : false;
}

bool isMalformed(string &line) {
    bool malformed = false;
    int len = line.length();
    //Traverse through string to eliminate whitespace
    //and signal if there exists illegal chars
    for(int i = 0; i < len; i++) {
        if(!isLegalChar(line[i])) {
            if(isWhiteSpace(line[i])) {
                line.erase(i, 1);
                i--;
                len--;
            } else {
                malformed = true;
                return malformed;
            }
        }
    }

    malformed = isIllegalExp(line);
    return malformed;
}

string editString(string x) {
    int index = x.length() - 1;
    string new_string;
    while(isalpha(x[index]) && index >= 0) {
        new_string.insert(0, string(1, x[index]));
        index--;
    }
    for(int i = index; i >= 0; i--) {
        string s(1, x[i]);
        if(isRemoveFront(s)) {
            if(new_string.length() > 1) {
                new_string.erase(0, 1);
            }
        } else if(isRemoveBack(s)) {
            if(new_string.length() > 1) {
                new_string.pop_back();
            }
        }
    }
    return new_string;
}

void evalExpression(stack<string> &current_stack) {
    string filtered_string;
    stack<string> exp_stack;
    bool addition = true;
    while(!isOpenParen(current_stack.top())) {
        string current_string;
        while(!(isAdd(current_stack.top()) || 
                isSubtract(current_stack.top()) || 
                isOpenParen(current_stack.top()))
                ) {
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

        //Stack to store original string
        stack<string> original_stack;

        //If input string is length == 0, it is malformed
        if(len != 0) {
            bool malformed = isMalformed(line);
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
                cout << final_string << endl;
                cout << editString(final_string) << endl;
            }
        } else {
            output << "Malformed" << endl;
        }
    }

    return 0;
}