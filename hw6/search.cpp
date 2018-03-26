#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "configvarextractor.h"
#include "parse.h"

using namespace std;

int main(int argc, char* argv[]) {
/*
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

	map<string, string> var_map;
	var_map.insert(make_pair("INDEX_FILE", ""));
	var_map.insert(make_pair("QUERY_FILE", ""));
	var_map.insert(make_pair("OUTPUT_FILE", ""));
	ConfigVarExtractor(config, var_map);

    ifstream input(var_map[INDEX_FILE]);
    ifstream query(var_map[QUERY_FILE]);
    ofstream output(var_map[OUTPUT_FILE]);*/

    if (argc < 4) {
       cerr << "Please provide input, query, and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ifstream query(argv[2]);
    ofstream output(argv[3]);

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "INDEX_FILE could not be open." << endl;
        return 1;
    }

    //If the query file given could not be found or could not be open
    if(query.fail()) {
        cout << "QUERY_FILE could not be open." << endl;
        return 1;
    }

    //If the output file given could not be found or could not be open
    if(output.fail()) {
        cout << "OUTPUT_FILE could not be open." << endl;
        return 1;
    }

    //Handles parsing and querying in Parser class
    Parse(input, query, output);

    return 0;
}