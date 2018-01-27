#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "lliststr.h"

using namespace std;

void printList(LListStr *list) {
    cout << "Assassination List: ";
    for(int i = 0; i < list->size(); i++) {
        cout << i << ". " << list->get(i) << "<->";
    }
    cout << endl;
}

void printRemainingPlayers(LListStr *list) {
    for(int i = 0; i < list->size(); i++) {
        cout << list->get(i) << endl;
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

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "Input file could not be open." << endl;
        return 1;
    }

    //Getting the command in the input file
    string command = "";
    int pos = 0;
    string str = "";

    //Create new LLIstStr 
    LListStr* assassinList = new LListStr();

    //Take in the first word as the command, according
    //to what they are, execute individual functions
    while(input >> command) {
        if(command == "ADD") {
            input >> pos >> str;
            assassinList->insert(pos, str);
        } else if(command == "REPLACE") {
            input >> pos >> str;
            assassinList->set(pos, str);
        } else {
            input >> pos;
            //Only continue with removal if there is at least two players
            if(assassinList->size() != 0 || assassinList->size() != 1) {
                string assassinated = "";
                if(pos == (assassinList->size() - 1)) {
                    assassinated = assassinList->get(0);
                    assassinList->remove(0);
                } else {
                    assassinated = assassinList->get(pos + 1);
                    assassinList->remove(pos + 1);
                }
                if(assassinated != "") {
                    cout << "Assassinated: " << assassinated << endl;
                }
            }
        }
    }

    //The end, check if the list has only one player left
    //or if there are other remaining players
    if(assassinList->size() == 1) {
        cout << "Winner: " << assassinList->get(0) << endl;
    } else if(assassinList->size() > 1) {
        cout << "Remaining Players: " << assassinList->size() << endl;
        printRemainingPlayers(assassinList);
    }

    delete assassinList;

    return 0;
}