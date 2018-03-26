#ifndef CONFIGVAREXTRACTOR_H
#define CONFIGVAREXTRACTOR_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>

class ConfigVarExtractor {
	public:
	    ConfigVarExtractor(
	    	std::ifstream& config, 
	    	std::map<std::string, std::string>& var_map
	    	);
	    virtual ~ConfigVarExtractor();

 	private:
	    //Member functions
	    void extractVar(
	    	std::ifstream& config, 
	    	std::map<std::string, std::string>& var_map
	    	);
};

#endif