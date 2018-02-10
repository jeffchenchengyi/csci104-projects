#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "stackstr.h"

using namespace std;

/*-------------START OF LEGAL CHAR CHECK FUNCTIONS--------------*/
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
/*-------------END OF LEGAL CHAR CHECK FUNCTIONS--------------*/

/*-------------START OF CHECKING FUNCTIONS--------------*/
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

//Check if close paren comes after open and if number of
//parens are equal
bool isParensOk(const string& line) {
    int extra_paren_count = 0;
    int len = line.length();
    for(int i = 0; i < len; i++) {
        string s(1, line[i]);
        if(isOpenParen(s)) {
            extra_paren_count++;
        } else if(isCloseParen(s)) {
            extra_paren_count--;
            if(extra_paren_count < 0) {
                return false;
            }
        }
    }
    return (extra_paren_count == 0) ? true : false;
}

//To ensure substring is not <Y> or any other wrong format
bool isLegalStringExp(const string& original_Y) {
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

//To check that there is only either one '-' or multiple
//'+' in between a set of parentheses
bool isCorrectFormatInsideParen(const string& exp) {
    int exp_len = exp.length();
    StackStr exp_stack;
    for(int i = 0; i < exp_len; i++) {
        if(isCloseParen(string(1, exp[i]))) {
            int subtract_count = 0;
            int add_count = 0;
            string before_close = exp_stack.top();
            string after_open;
            while(!isOpenParen(exp_stack.top())) {
                after_open = exp_stack.top();
                if(isSubtract(exp_stack.top())) {
                    subtract_count++;
                    exp_stack.pop();
                } else if(isAdd(exp_stack.top())) {
                    add_count++;
                    exp_stack.pop();
                } else {
                    exp_stack.pop();
                }
            }
            if(!(((subtract_count == 1) && (add_count == 0)) || 
                    ((subtract_count == 0) && (add_count > 0)))
                    ) {
                return false;
            }
            if(before_close != "Y" || after_open != "Y") {
                return false;
            }
            exp_stack.pop();
            exp_stack.push("Y");
        } else {
            exp_stack.push(string(1, exp[i]));
        }
    }
    return true;
}

//To ensure that all operators are in the correct pos
bool isOperatorsOk(const string& line) {
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
    if(!isCorrectFormatInsideParen(simple_string)) {
        return false;
    }
    return true;
}

//To check if my operators, parentheses, and strings 
//are legal
bool isIllegalExp(const string& line) {
    if(isParensOk(line)) {
        return isOperatorsOk(line) ? false : true;
    } else {
        return true;
    }
}

//To remove unecessary whitespaces and check if input
//malformed
bool isMalformed(string& line) {
    bool malformed = false;
    int len = line.length();
    //Traverse through string to eliminate whitespace
    //and signal if there exists illegal chars
    for(int i = 0; i < len; i++) {
        if(!isLegalChar(line[i])) {
            if(isblank(line[i])) {
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
/*-------------END OF CHECKING FUNCTIONS--------------*/

/*-------------START OF EVALUATION FUNCTIONS--------------*/
//Reads the removeFront and removeBack operators to edit 
//string accordingly
string editString(string x) {
    int index = x.length() - 1;
    string new_string;

    //Insert all the alphabets in the new string first
    while((index >= 0) && (isalpha(x[index]))) {
        new_string.insert(0, string(1, x[index]));
        index--;
    }

    //Apply the removeFront or removeBack operators if 
    //the string length is > 1
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

//Evaluates the expression and pushes it back onto
//the stack, contains a *SPECIAL CHECK* to ensure
//no (cat -cat) situation
bool evalExpression(StackStr& current_stack) {
    string filtered_string;
    StackStr exp_stack;
    bool addition = true;

    //Where we form the strings to be evaluated from the
    //stack with string type characters
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

    //Where the actual string operations happen, concatenation
    //and removal of substring
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

        //*SPECIAL CHECK* to ensure that no empty string
        //is returned, else malformed
        if(filtered_string == sub_string) {
            return false;
        }

        if(pos >= 0 && pos < len) {
            filtered_string.erase(pos, sub_string.length());
        }
    }

    //Remove the opening parentheses
    current_stack.pop();
    current_stack.push(filtered_string);
    return true;
}
/*-------------END OF EVALUATION FUNCTIONS--------------*/

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
        StackStr original_stack;

        //If input string is length == 0, it is malformed
        if(len != 0) {
            bool malformed = isMalformed(line);
            if(malformed) {
                output << "Malformed" << endl;
            } else {
                for(int i = 0; i < len; i++) {
                    if(isCloseParen(string(1, line[i]))) {
                        malformed = !(evalExpression(original_stack));
                        if(malformed) {
                            break;
                        }
                    } else {
                        string s(1, line[i]);
                        original_stack.push(s);
                    }
                }

                //Check again if it was a malformed expression because 
                //(cat - cat) is not legal
                if(!malformed) {
                    //Transfer remaining items from stack to a string
                    string final_string;
                    while(!original_stack.empty()) {
                        final_string.insert(0, original_stack.top());
                        original_stack.pop();
                    }

                    //Remove all uneccessary whitespaces 
                    string updated_string;
                    for (int i = 0; i < (int)final_string.length(); i++) {
                        if(final_string[i]) {
                            updated_string.append(string(1, final_string[i]));
                        }
                    }
                    output << editString(updated_string) << endl;
                } else {
                    output << "Malformed" << endl;
                }
            }
        } else {
            output << "Malformed" << endl;
        }
    }

    return 0;
}