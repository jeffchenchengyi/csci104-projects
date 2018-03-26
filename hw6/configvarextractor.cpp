#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

ConfigVarExtractor::ConfigVarExtractor(
	ifstream& config, 
	map<string, string>& var_map
	) {
	extractVar(config, var_map);
}

ConfigVarExtractor::~ConfigVarExtractor() {
}

void ConfigVarExtractor::extractVar(
	ifstream& config, 
	map<string, string>& var_map
	) {
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
    		map<string, string>::iterator map_itr = var_map.find(variable);
    		if(map_itr != var_map.end()) {
    			map_itr->second = data;
    		}
    	}
    }
}