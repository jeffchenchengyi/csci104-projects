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
    var_map.insert(make_pair("RESTART_PROBABILITY", ""));
    var_map.insert(make_pair("STEP_NUMBER", ""));
	ConfigVarExtractor(config, var_map);

    ifstream input((var_map["INDEX_FILE"]).c_str());
    ifstream query((var_map["QUERY_FILE"]).c_str());
    ofstream output((var_map["OUTPUT_FILE"]).c_str());
    float RESTART_PROBABILITY = atof((var_map["RESTART_PROBABILITY"]).c_str());
    int STEP_NUMBER = atoi((var_map["STEP_NUMBER"]).c_str());

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
    Parse(input, query, output, RESTART_PROBABILITY, STEP_NUMBER);

    return 0;
}