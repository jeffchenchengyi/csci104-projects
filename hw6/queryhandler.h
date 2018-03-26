#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"
#include "setutility.h"

class QueryHandler {
	public:
	    QueryHandler(
	    	std::ifstream& query,
			const std::set< WebPage* >& webpage_set, 
			std::map< std::string, std::set<WebPage*> >& word_map,
			std::ofstream& output
			);
	    virtual ~QueryHandler();
	    bool isCloseParen(std::string x);
        bool isOpenParen(std::string x);

 	private:
	    //Member functions
	    void analyzeQuery(
			std::string query_command, 
			const std::set< WebPage* >& webpage_set, 
			std::map< std::string, std::set<WebPage*> >& word_map,
			std::ofstream& output
			);
	    void displayWebPage(std::string weblink, std::ofstream& output);
};

#endif