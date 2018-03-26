#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
/*------------- START INITIALIZE REQUIRED FILES -------------
    //To check if the config file was also included as a command line parameter
    ifstream config;
    if(argc < 2) {
    	cout << "*Default config.txt will be used*" << endl;
    	config.open("config.txt");
    } else {
    	config.open(argv[1]);
    }

    //If the config file given could not be found or could not be open
    if(config.fail()) {
        cerr << "Configuration file could not be open." << endl;
        return -1;
    }
------------- END INITIALIZE REQUIRED FILES -------------*/

/*------------- START CONFIGURATION VARIABLES -------------
    string INDEX_FILE, QUERY_FILE, OUTPUT_FILE;
    string config_line;
    while(getline(config, config_line)) {
    	string data, variable;
    	if(!config_line.empty()) {
    		stringstream ss(config_line);
    		char curr_char;
    		while(ss >> curr_char) {
    			if(curr_char == '=') {
	    			while(ss >> curr_char) {
	    				if(curr_char == '#') {
	    					break;
	    				} else {
	    					data.append(string(1, curr_char));
	    				}
	    			}
	  				break;
	   			} else if(curr_char == '#') {
	   				break;
	   			} else {
	  				variable.append(string(1, curr_char));
	   			}
			}
    	}
    	if(!data.empty()) {
    		if(variable == "INDEX_FILE") {
    			INDEX_FILE = data;
    		} else if(variable == "QUERY_FILE") {
    			QUERY_FILE = data;
    		} else if(variable == "OUTPUT_FILE") {
    			OUTPUT_FILE = data;
    		}
    	}
    }

    ifstream input(INDEX_FILE);
    ifstream query(QUERY_FILE);
    ofstream output(OUTPUT_FILE);*/
    if (argc < 4) {
       cerr << "Please provide input, query, and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ifstream query(argv[2]);
    ofstream output(argv[3]);

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "Input file could not be open." << endl;
        return 1;
    }

    //If the query file given could not be found or could not be open
    if(query.fail()) {
        cout << "Query file could not be open." << endl;
        return 1;
    }

    //If the output file given could not be found or could not be open
    if(output.fail()) {
        cout << "Output file could not be open." << endl;
        return 1;
    }
/*------------- END CONFIGURATION VARIABLES -------------*/
    Parser(input, query, output);
    return 0;
}